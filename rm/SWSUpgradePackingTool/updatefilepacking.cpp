#include "updatefilepacking.h"
#include "crc.h"
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QDebug>

#ifdef Q_OS_WIN
#define TEMPDIR "C:/Windows/Temp/swspacking/"
#else
#define TEMPDIR ""
#endif

#define Z7AFILE       (TEMPDIR"7za.exe")
#define Z7ADLLFILE    (TEMPDIR"7za.dll")
#define Z7XADLLFILE   (TEMPDIR"7zxa.dll")

#define TEMPPACKETTAR (TEMPDIR"temppacking.tar")
#define TEMPPACKET    (TEMPDIR"temppacking.tar.gz")
#define TEMPSETTING   (TEMPDIR"setting")
#define TEMPMD5       (TEMPDIR"md5")

UpdateFilePacking::UpdateFilePacking(QObject *parent) : QObject(parent)
{
    check7zaProgram();

    m_generateMd5Thread = new GenerateMd5Thread();
    connect(m_generateMd5Thread, &GenerateMd5Thread::signalGenerateFinished, this, &UpdateFilePacking::slotGenerateMd5Finished);

    m_process = new QProcess(this);
    connect(m_process, &QProcess::errorOccurred, this, &UpdateFilePacking::slotProcessErrorOccurred);
}

UpdateFilePacking::~UpdateFilePacking()
{
    delete m_generateMd5Thread;

    if(!QDir(TEMPDIR).removeRecursively())
    {
        qDebug() << "remove temp directory falied!";
    }
}

QList<QUrl> UpdateFilePacking::resolveDirectory(QList<QUrl> urls)
{
    QList<QUrl> files; //除去文件夹剩余的文件
    QList<QUrl> entryFiles; //文件夹下的文件
    QDir dir;
    for(int i = 0; i < urls.size(); i++)
    {
        dir.setPath(urls[i].toString().remove("file:///"));
        if(dir.exists())
        {   //是文件夹，获取文件夹下所有文件+文件夹
            QFileInfoList infoList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
            QList<QUrl> fileList;
            for(int j = 0; j < infoList.size(); j++)
            {   //必须加"file:///"，不然盘符会被QUrl转成小写，看着不爽
                fileList.append(QUrl("file:///" + infoList[j].absoluteFilePath()));
            }
            entryFiles += resolveDirectory(fileList);
        }
        else
        {   //是文件，直接添加到结果中
            files.append(urls[i]);
        }
    }

    return (files + entryFiles);
}

void UpdateFilePacking::check7zaProgram()
{
    //释放7za打包工具
    if(!QDir().mkpath(TEMPDIR))
    {
        qDebug() << "create temp directory failed!";
        return;
    }

    if(!QFile::exists(Z7AFILE))
    {
        QFile::copy(":/7za.exe", Z7AFILE);
    }
    if(!QFile::exists(Z7ADLLFILE))
    {
        QFile::copy(":/7za.dll", Z7ADLLFILE);
    }
    if(!QFile::exists(Z7XADLLFILE))
    {
        QFile::copy(":/7zxa.dll", Z7XADLLFILE);
    }
}

void UpdateFilePacking::clearOldTempFile()
{
    QFile::remove(TEMPSETTING);
    QFile::remove(TEMPPACKETTAR);
    QFile::remove(TEMPPACKET);
}

void UpdateFilePacking::slotPacking(QString packetName, QString packetVer, QStringList fileList, QStringList assignVerList, QString minNoRebootVer)
{
    //清除上次打包生成的临时文件
    clearOldTempFile();

    //检查文件空
    if(fileList.isEmpty())
    {
        emit signalPackFinished(false);
        emit signalShowMessage(tr("还没有添加要打包的文件！"));
        return;
    }

    //检查升级包版本合法性
    if(!packetVer.contains(QRegExp("^V\\d\\.\\d\\.\\d{2} [A-Z]$")))
    {
        emit signalPackFinished(false);
        emit signalShowMessage(tr("【升级包版本】 填写错误！"));
        return;
    }

    //检查无需重启主控的最低版本合法性
    if(!minNoRebootVer.contains(QRegExp("^V\\d\\.\\d\\.\\d{2} [A-Z]$")))
    {
        emit signalPackFinished(false);
        emit signalShowMessage(tr("【无需重启主控最低版本】 填写错误！"));
        return;
    }

    //生成配置文件
    QSettings setting(TEMPSETTING, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    setting.setValue("minNoRebootVersion", minNoRebootVer); //不需要先升主控，重启再升数据库的最低版本
    foreach(QString assignVer, assignVerList)
    {
        QStringList splitList = assignVer.split(',', QString::SkipEmptyParts);
        if(splitList.size() == 2)
        {
            QString type =  splitList.at(0);
            QString version =  splitList.at(1);
            if(type == "MainPro")
            {   //指定主控程序版本
                if(!version.contains(QRegExp("^V\\d\\.\\d\\.\\d{2} [A-Z]$")))
                {   //检查版本合法性
                    emit signalPackFinished(false);
                    emit signalShowMessage(tr("【主控程序指定版本】 填写错误！"));
                    return;
                }
                setting.setValue("mainProVerion", version);
            }
            else if(type == "Database")
            {   //指定数据库版本
                if(!version.contains(QRegExp("^V\\d\\.\\d{2}$")))
                {
                    emit signalPackFinished(false);
                    emit signalShowMessage(tr("【数据库指定版本】 填写错误！"));
                    return;
                }
                setting.setValue("dbVersion", version);
            }
            else if(type == "Language")
            {   //指定语言版本
                if(!version.contains(QRegExp("^V\\d\\.\\d{2}$")))
                {
                    emit signalPackFinished(false);
                    emit signalShowMessage(tr("【语言指定版本】 填写错误！"));
                    return;
                }
                setting.setValue("languageVersion", version);
            }
        }
    }

    m_packetFileName = packetName;
    m_packetVersion = packetVer;
    m_srcFileList = fileList;

    //开始生成md5文件
    m_generateMd5Thread->start();
    m_generateMd5Thread->signalGenerateMd5(fileList, TEMPMD5);
}

void UpdateFilePacking::slotGenerateMd5Finished(bool success, QString errorString)
{
    m_generateMd5Thread->quit();

    if(success)
    {   //md5生成完成，开始打包
        //打包第一步，生成tar文件
        QStringList arguments;
        arguments << "a" << "-ttar" << TEMPPACKETTAR << m_srcFileList << TEMPSETTING << TEMPMD5;
        connect(m_process, (void (QProcess:: *)(int, QProcess::ExitStatus))&QProcess::finished, this, &UpdateFilePacking::slotTempPacketTarFinished);
        m_process->start(Z7AFILE, arguments);
    }
    else
    {
        emit signalPackFinished(false);
        emit signalShowMessage(errorString);
    }
}

void UpdateFilePacking::slotTempPacketTarFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if((exitStatus == QProcess::NormalExit) && (exitCode == 0))
    {   //打包第二步，生成tar.gz文件
        disconnect(m_process, (void (QProcess:: *)(int, QProcess::ExitStatus))&QProcess::finished, this, &UpdateFilePacking::slotTempPacketTarFinished);
        connect(m_process, (void (QProcess:: *)(int, QProcess::ExitStatus))&QProcess::finished, this, &UpdateFilePacking::slotTempPacketFinished);
        m_process->start(Z7AFILE, {"a", TEMPPACKET, TEMPPACKETTAR});
    }
    else
    {
        emit signalPackFinished(false);
        emit signalShowMessage(tr("【错误】") + m_process->errorString());
    }
}

void UpdateFilePacking::slotTempPacketFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    disconnect(m_process, (void (QProcess:: *)(int, QProcess::ExitStatus))&QProcess::finished, this, &UpdateFilePacking::slotTempPacketFinished);
    if((exitStatus == QProcess::NormalExit) && (exitCode == 0))
    {
        QFile fileTemp(TEMPPACKET);
        if(!fileTemp.open(QIODevice::ReadOnly))
        {
            emit signalPackFinished(false);
            emit signalShowMessage(tr("【错误】临时文件打开失败！"));
            return;
        }

        QFile packetFile(m_packetFileName);
        if(!packetFile.open(QIODevice::WriteOnly))
        {
            fileTemp.close();
            emit signalPackFinished(false);
            emit signalShowMessage(tr("【错误】目标文件创建失败！"));
            return;
        }

        //添加包头及校验
        quint32 verNum = verStrToNum(m_packetVersion);
        QByteArray fileHeadByt = QByteArray("SWS-6000") + QByteArray((char *)&verNum, sizeof(verNum));
        ushort crcSum = CRC((uchar *)fileHeadByt.data(), fileHeadByt.size()).Sum();
        int size = fileHeadByt.size();
        fileHeadByt[size] = (crcSum & 0x00FF);
        fileHeadByt[size+1] = (crcSum >> 8);

        //写入目标文件
        packetFile.write(fileHeadByt + fileTemp.readAll());
        packetFile.flush();

        fileTemp.close();
        packetFile.close();

#ifdef Q_OS_LINUX
        system("sync");
#endif

        emit signalPackFinished(true);
        emit signalShowMessage(tr("升级包创建完成！"));
    }
    else
    {
        emit signalPackFinished(false);
        emit signalShowMessage(tr("【错误】") + m_process->errorString());
    }
}

void UpdateFilePacking::slotProcessErrorOccurred(QProcess::ProcessError error)
{
    emit signalPackFinished(false);
    emit signalShowMessage(tr("【错误】") + m_process->errorString());
}

QString UpdateFilePacking::verNumToStr(quint32 verNum)
{
    QString verStr;

    if((verNum & 0xFFFF0000) != 0)
    {   //高两个字节不为0判定为主控，取4个字节
        verStr = QString("%1.%2.%3 %4")
                .arg(verNum >> 24)
                .arg((verNum >> 16) & 0xFF)
                .arg((verNum >> 8) & 0xFF, 2, 10, QChar('0'))
                .arg(char(verNum & 0xFF));
    }
    else
    {   //其他取低2个字节
        verStr = QString("%1.%2").arg((verNum >> 8) & 0xFF).arg(verNum & 0xFF, 2, 10, QChar('0'));
    }

    return verStr;
}

quint32 UpdateFilePacking::verStrToNum(QString verStr)
{
    quint32 verNum = 0;

    verStr = verStr.mid(verStr.indexOf(QRegExp("[0-9]"))); //去除前面的一些特殊字符（若有），从数字开始
    QStringList verList = verStr.split('.');

    if(verList.size() >= 3)
    {   //有两个点判定为主控程序，取四个字节
        QStringList verTailList = verList[2].split(' ');
        if(verTailList.size() >= 2)
        {
            quint8 verD3 = verList[0].toInt();
            quint8 verD2 = verList[1].toInt();
            quint8 verD1 = verTailList[0].toInt();
            quint8 verD0 = verTailList[1][0].toLatin1();
            verNum = (verD3 << 24) | (verD2 << 16) | (verD1 << 8) | verD0;
        }
    }
    else if(verList.size() == 2)
    {   //其他，使用低2个字节
        quint8 verD1 = verList[0].toInt();
        quint8 verD0 = verList[1].toInt();
        verNum = (verD1 << 8) | verD0;
    }
    else
    {
        ; //此为编程规范要求
    }

    return verNum;
}
