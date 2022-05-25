#include "file_io.h"
#include "file_upk.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDir>
#include <QFileInfoList>

#ifdef Q_OS_WIN
#define TEMPDIR "F:/Temp/md5_upk_tool/"
#else
#define TEMPDIR ""
#endif

#define qdebug qDebug()<<__FILE__<<__LINE__


File_io::File_io(QObject *parent) : QObject(parent)
{
    connect(this,&File_io::isfilefilter,this,&File_io::fileprintf);
    connect(this,&File_io::createmd5,this,&File_io::filecreatemd5);
    connect(this,&File_io::clearrootfilepath,[=]{rootfilepath="";});
    connect(this,&File_io::createupk,&upk,(void (File_upk::*)(QStringList,QString))&File_upk::createupk);
    connect(&upk,&File_upk::showinfo,this,&File_io::showinfo);
}

File_io::~File_io()
{
//    if(!QDir(TEMPDIR).removeRecursively())
//    {
//        qdebug<<"remove error!";
//    }
}

void File_io::fileprintf(QStringList filepath)
{
    QString filename;
    QDir dir;
    for(int i=0;i<filepath.length();i++)
    {
        QString dirpath=filepath[i].mid(8);
        dir.setPath(dirpath);
        if(dir.exists())
        {
            QFileInfoList infolist=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
            QString infofilepath;
            for(int j=0;j<infolist.length();j++)
            {
                infofilepath="file:///"+infolist[j].absoluteFilePath();
                filename=infofilepath.right(infofilepath.length()-infofilepath.lastIndexOf("/")-1);
                if(filename=="SWS-6000-Revolution"||filename=="NSWSHD"||filename=="NSWSHDF"||filename=="compatibility")
                {
                    if(rootfilepath.isEmpty())
                    {
                        rootfilepath=infofilepath.left(infofilepath.lastIndexOf("/")+1);
                        rootfilepath=rootfilepath.mid(8);
                    }
                    emit isneedfile(infofilepath,rootfilepath);
                }
                if(filename.contains(".qm")||filename.contains(".db")||filename.contains("bin")||filename.contains(".ini"))
                {
                    if(rootfilepath.isEmpty())
                    {
                        rootfilepath=infofilepath.left(infofilepath.lastIndexOf("/")+1);
                        rootfilepath=rootfilepath.mid(8);
                    }
                    emit isneedfile(infofilepath,rootfilepath);
                }
            }
        }
        else
        {
            filename=filepath[i].right(filepath[i].length()-filepath[i].lastIndexOf("/")-1);
            if(filename=="SWS-6000-Revolution"||filename=="NSWSHD"||filename=="NSWSHDF"||filename=="compatibility")
            {
                if(rootfilepath.isEmpty())
                {
                    rootfilepath=filepath[0].left(filepath[0].lastIndexOf("/")+1);
                    rootfilepath=rootfilepath.mid(8);
                }
                emit isneedfile(filepath[i],rootfilepath);
            }
            if(filename.contains(".qm")||filename.contains(".db")||filename.contains("bin")||filename.contains(".ini"))
            {
                if(rootfilepath.isEmpty())
                {
                    rootfilepath=filepath[0].left(filepath[0].lastIndexOf("/")+1);
                    rootfilepath=rootfilepath.mid(8);
                }
                emit isneedfile(filepath[i],rootfilepath);
            }
        }
    }
}

void File_io::filecreatemd5(QStringList filepath)
{
    QFile md5file(rootfilepath+"md5.txt");
    QTextStream stream(&md5file);
    stream.setCodec(QTextCodec::codecForName("UTF-8"));

    QStringList md5list;

    if(QFile::exists(md5file.fileName()))
    {
        if(md5file.open(QIODevice::ReadWrite))
        {
            while(!stream.atEnd())
            {
                QString info=stream.readLine().trimmed();
                if(!info.isEmpty())
                    md5list<<info;
            }
        md5file.close();
        }
    }

    QFile file;
    for(int i=0;i<filepath.length();i++)
    {
        file.setFileName(filepath[i].mid(8));
        if(!filepath[i].isEmpty())
        {
            if(file.open(QIODevice::ReadWrite))
            {
                QByteArray md5data=QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
                QString filename=filepath[i].split('/').last();

                bool isexist=false;
                for(int j=0;j<md5list.length();j++)
                    if(filename==md5list[j].split(':').value(0))
                    {
                        isexist=true;
                        md5list[j]=filename+":"+md5data.toHex();
                        break;
                    }
                if(!isexist)
                    md5list.append(filename+":"+md5data.toHex());
                file.close();
            }
        }
    }

    if(md5file.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        foreach(QString lineinfo,md5list)
        {
            stream<<(lineinfo+"\n");
        }
    }
    emit createok(true);

}
