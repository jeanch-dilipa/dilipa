#ifndef UPDATEFILEPACKING_H
#define UPDATEFILEPACKING_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QUrl>
#include "generatemd5thread.h"

class UpdateFilePacking : public QObject
{
    Q_OBJECT
public:
    explicit UpdateFilePacking(QObject *parent = nullptr);
    ~UpdateFilePacking();

    Q_INVOKABLE QList<QUrl> resolveDirectory(QList<QUrl> urls); //将包含的文件夹全部递归获取文件

Q_SIGNALS:
    void signalShowMessage(QString msg);   //需要显示提示信息信号
    void signalPackFinished(bool success); //打包结束信号

public Q_SLOTS:
    void slotPacking(QString packetName, QString packetVer, QStringList fileList, QStringList assignVerList, QString minNoRebootVer); //开始打包
    void slotShowTxtFile(QString filePath); //显示文本文件内容

private slots:
    void slotGenerateMd5Finished(bool success, QString errorString);
    void slotTempPacketTarFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void slotTempPacketFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void slotProcessErrorOccurred(QProcess::ProcessError error);

private:
    void check7zaProgram();  //检查打包工具
    void clearOldTempFile(); //清除上一次生成的临时文件

    QString verNumToStr(quint32 verNum); //版本数字转字符
    quint32 verStrToNum(QString verStr); //版本字符转数字

private:
    QProcess *m_process; //用于打包的进程
    QStringList m_showTxtFileList; //已经正在显示的文本文件
    GenerateMd5Thread *m_generateMd5Thread;  //md5生成线程
    QString m_packetFileName;  //升级包文件名
    QString m_packetVersion;   //升级包版本
    QStringList m_srcFileList; //要打包的文件列表
};

#endif // UPDATEFILEPACKING_H
