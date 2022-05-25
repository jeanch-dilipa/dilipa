#ifndef GENERATEMD5THREAD_H
#define GENERATEMD5THREAD_H

#include <QThread>
#include <QStringList>

class GenerateMd5Thread : public QThread
{
    Q_OBJECT
public:
    explicit GenerateMd5Thread();
    ~GenerateMd5Thread();

    void run();

signals:
    //外部触发信号
    void signalGenerateMd5(QStringList srcFileList, QString dstFile, QString originFile = ""); //开始生成md5

    //内部触发信号
    void signalGenerateFinished(bool success, QString errorString = ""); //md5文件生成结束

private slots:
    void slotGenerateMd5(QStringList srcFileList, QString dstFile, QString originFile);
};

#endif // GENERATEMD5THREAD_H
