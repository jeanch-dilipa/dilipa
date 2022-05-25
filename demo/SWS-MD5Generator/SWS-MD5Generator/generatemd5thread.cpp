#include "generatemd5thread.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QCryptographicHash>

GenerateMd5Thread::GenerateMd5Thread() : QThread(NULL)
{
    this->moveToThread(this);
}

void GenerateMd5Thread::run()
{
    this->exec();
}

void GenerateMd5Thread::slotGenerateMd5(QStringList srcFileList, QString dstFile)
{
    QFile md5file(dstFile);
    QTextStream stream(&md5file);
    stream.setCodec(QTextCodec::codecForName("UTF-8")); //统一UTF-8编码，防止中文文件名乱码。

    QStringList md5InfoList;
    //如果本身就存在该文件，先获取其内容
    if(QFile::exists(md5file.fileName()))
    {
        if(md5file.open(QIODevice::ReadOnly | QIODevice::Text) == true)
        {
            //读取文件原有的md5信息
            while(!stream.atEnd())
            {
                QString lineStr = stream.readLine().trimmed();
                if(!lineStr.isEmpty())
                {
                    md5InfoList << lineStr;
                }
            }

            md5file.close();
        }
    }

    //重新打开md5文件并清除内容
    if(md5file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text) == false)
    {
        emit signalGenerateProcess(0, srcFileList.size(), true, tr("打开或创建md5.txt出错"));
        return ;
    }

    int successCnt = 0; //成功数量统计
    QFile file;
    foreach (QString fileName, srcFileList)
    {
        file.setFileName(fileName);
        if(file.open(QIODevice::ReadOnly) == true)
        {
            QByteArray md5Ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
            QString fileNameNoPath = fileName.split('/').last(); //不包括路径的文件名

            //查找原来有没有这个文件的md5信息
            bool isAlreadyHave = false;
            for(int i = 0; i < md5InfoList.size(); i++)
            {
                if(md5InfoList[i].split(':').value(0) == fileNameNoPath)
                {
                    isAlreadyHave = true;
                    md5InfoList[i] = fileNameNoPath + ":" + md5Ba.toHex(); //如果原来有这一行，就直接更新
                    break;
                }
            }
            if(!isAlreadyHave)
            {
                md5InfoList.append(fileNameNoPath + ":" + md5Ba.toHex()); //原来没有，就在后面添加
            }

            successCnt++;
            emit signalGenerateProcess(successCnt, srcFileList.size()); //更新进度
        }
        file.close();
    }

    //写入已经更新的所有信息
    foreach (QString line, md5InfoList) {
        stream << (line + "\n");
    }
    md5file.close();

    if(successCnt == 0)
    {
        QFile::remove(md5file.fileName());
    }

    emit signalGenerateProcess(successCnt, srcFileList.size(), true); //发送写入完成
}
