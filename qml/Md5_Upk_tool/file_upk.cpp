#include "file_upk.h"
#include "crc.h"
#include "file_io.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSettings>


#ifdef Q_OS_WIN
#define TEMPDIR "F:/Temp/md5_upk_tool/"
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

#define qdebug qDebug()<<__FILE__<<__LINE__

File_upk::File_upk(QObject *parent) : QObject(parent)
{
    ini7za();
    connect(this,(void(File_upk:: *)(QStringList,QString))&File_upk::createupk,this,&File_upk::createtar);
    m_process=new QProcess(this);
    connect(m_process,&QProcess::errorOccurred,[=]{qdebug<<"m_process";});
}

File_upk::~File_upk()
{
    delete m_process;
//    if(!QDir(TEMPDIR).removeRecursively())
//    {
//        qdebug<<"remove error!";
//    }
}

void File_upk::ini7za()
{
    QDir().mkpath(TEMPDIR);
    if(!QFile::exists(Z7AFILE))
        QFile::copy(":/7za.exe",Z7AFILE);
    if(!QFile::exists(Z7ADLLFILE))
        QFile::copy(":/7za.dll",Z7ADLLFILE);
    if(!QFile::exists(Z7XADLLFILE))
        QFile::copy(":/7zxa.dll",Z7XADLLFILE);
}

void File_upk::clearupktemp()
{
    QFile::remove(TEMPSETTING);
    QFile::remove(TEMPPACKETTAR);
    QFile::remove(TEMPPACKET);
}

void File_upk::createtar(QStringList upkfilelist,QString rootfilepath)
{
    this->rootfilepath=rootfilepath;
    for(int i=0;i<upkfilelist.length();i++)
        upkfilelist[i]=upkfilelist[i].remove("file:///");

    clearupktemp();
    createconfig();

    File_io fileio;
    fileio.rootfilepath=TEMPDIR;
    fileio.createmd5(upkfilelist);
    QFile filemd5(TEMPDIR"md5.txt");
    filemd5.rename(TEMPDIR"md5");

    QStringList z7alist;
    z7alist<<"a"<<"-ttar"<<TEMPPACKETTAR<<TEMPSETTING<<TEMPMD5<<upkfilelist;
    connect(m_process,(void (QProcess :: *)(int,QProcess::ExitStatus))&QProcess::finished,this,&File_upk::creategz);//函数指针
    m_process->start(Z7AFILE,z7alist);
}

void File_upk::creategz(int exitcode, QProcess::ExitStatus exitstatus)
{
    if((exitstatus==QProcess::NormalExit)&&(exitcode==0))
    {
        disconnect(m_process,(void (QProcess::*)(int,QProcess::ExitStatus))&QProcess::finished,this,&File_upk::creategz);
        connect(m_process,(void (QProcess::*)(int,QProcess::ExitStatus))&QProcess::finished,this,(void (File_upk::*)(int,QProcess::ExitStatus))&File_upk::createupk);
//        connect(m_process,static_cast<void (QProcess:: * )(int,QProcess::ExitStatus)>(&QProcess::finished),this,(void (File_upk::*)(int,QProcess::ExitStatus))&File_upk::createupk);
        m_process->start(Z7AFILE,{"a",TEMPPACKET,TEMPPACKETTAR});
    }
}

void File_upk::createupk(int exitcode, QProcess::ExitStatus exitstatus)
{
    disconnect(m_process,(void (QProcess::*)(int,QProcess::ExitStatus))&QProcess::finished,this,(void (File_upk::*)(int,QProcess::ExitStatus))&File_upk::createupk);

    if((exitstatus==QProcess::NormalExit)&&(exitcode==0))
    {
        QFile filetemp(TEMPPACKET);
        if(filetemp.open(QIODevice::ReadOnly))
        {
            QFile upknamefile(rootfilepath+"sws.upk");
            if(upknamefile.open(QIODevice::WriteOnly))
            {
                quint32 vernum=verstrtonum("V6.2.01 G");
                QByteArray fileheadbyte=QByteArray("SWS-6000")+QByteArray((char *)&vernum,sizeof (vernum));
                ushort crcsum=CRC((uchar *)fileheadbyte.data(),fileheadbyte.size()).Sum();
                int size=fileheadbyte.size();
                fileheadbyte[size]=(crcsum&0x00ff);
                fileheadbyte[size+1]=(crcsum>>8);

                upknamefile.write(fileheadbyte+filetemp.readAll());
                upknamefile.flush();        //刷新缓存

                upknamefile.close();
            }
            filetemp.close();
        }
#ifdef  Q_OS_LINUX
        system("sync");         //linux立即写入
#endif
        emit showinfo("Upgrade package created successfully");
    }
}

quint32 File_upk::verstrtonum(QString str)
{
    quint32 vernum=0;
    str=str.mid(str.indexOf(QRegExp("[0-9]")));
    QStringList verlist=str.split(".");
    if(verlist.size()>=3)
    {
        QStringList vertaillist=verlist[2].split(' ');
        if(vertaillist.size()>=2)
        {
            quint8 verd3=verlist[0].toInt();
            quint8 verd2=verlist[1].toInt();
            quint8 verd1=vertaillist[0].toInt();
            quint8 verd0=vertaillist[1].toInt();
            vernum=(verd3<<24)|(verd2<<16)|(verd1<<8)|verd0;
        }
    }
    else if(verlist.size()==2)
    {
        quint8 verd1=verlist[0].toInt();
        quint8 verd0=verlist[1].toInt();
        vernum=(verd1<<8)|verd0;
    }
    return vernum;
}

void File_upk::createconfig()
{
    QSettings setting(TEMPSETTING, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
//    setting.beginGroup("General");
    setting.setValue("minNoRebootVersion", "V6.2.01 A"); //不需要先升主控，重启再升数据库的最低版本
    //    setting.endGroup();
}

