#include "generatemd5thread.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QCryptographicHash>

GenerateMd5Thread::GenerateMd5Thread() : QThread(NULL)
{
    this->moveToThread(this);

    connect(this, &GenerateMd5Thread::signalGenerateMd5, this, &GenerateMd5Thread::slotGenerateMd5);
}

GenerateMd5Thread::~GenerateMd5Thread()
{
    if(this->isRunning())
    {
        this->quit();
        this->wait();
    }
}

void GenerateMd5Thread::run()
{
    this->exec();
}

void GenerateMd5Thread::slotGenerateMd5(QStringList srcFileList, QString dstFile, QString originFile)
{
    QStringList md5InfoList;

    //若有原来的md5文件，先获取其内容
    if(!originFile.isEmpty() && QFile::exists(originFile))
    {
        QFile originMd5File(originFile);
        if(originMd5File.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //读取文件原有的md5信息
            while(!originMd5File.atEnd())
            {
                QString lineStr = QString(originMd5File.readLine().trimmed());
                if(!lineStr.isEmpty() && lineStr.contains(':'))
                {
                    md5InfoList << lineStr;
                }
            }

            originMd5File.close();
        }
    }

    QFile dstMd5file(dstFile);
    QTextStream stream(&dstMd5file);
    stream.setCodec(QTextCodec::codecForName("UTF-8")); //统一UTF-8编码，防止中文文件名乱码。

    if(!dstMd5file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        emit signalGenerateFinished(false, tr("打开或创建md5文件出错"));
        return;
    }

    QFile file;
    foreach (QString fileName, srcFileList)
    {
        QString fileNameNoPath = fileName.split('/').last(); //不包括路径的文件名

        bool isAlreadyHave = false;
        for(int i = 0; i < md5InfoList.size(); i++)
        {   //查找原来有没有这个文件的md5信息
            if(md5InfoList[i].split(':').value(0) == fileNameNoPath)
            {   //如果原来有这一行，保持
                isAlreadyHave = true;
                break;
            }
        }

        if(!isAlreadyHave)
        {   //原来没有，就在后面添加
            file.setFileName(fileName);
            if(file.open(QIODevice::ReadOnly))
            {
                QByteArray md5Ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
                md5InfoList.append(fileNameNoPath + ":" + md5Ba.toHex());
                file.close();
            }
            else
            {
                emit signalGenerateFinished(false, tr("【md5生成】文件读取错误：") + fileNameNoPath);
                return;
            }
        }
    }

    //写入已经更新的所有信息
    foreach(QString line, md5InfoList)
    {
        stream << (line + "\n");
    }
    dstMd5file.close();

    emit signalGenerateFinished(true); //发送写入完成
}
