#ifndef GENERATEMD5THREAD_H
#define GENERATEMD5THREAD_H

#include <QThread>
#include <QStringList>

class GenerateMd5Thread : public QThread
{
    Q_OBJECT
public:
    explicit GenerateMd5Thread();

    void run();

signals:
    void signalGenerateProcess(int sucessNum, int totalNum, bool finish = false, QString errorString = "");

private slots:
    void slotGenerateMd5(QStringList srcFileList, QString dstFile);

private:

};

#endif // GENERATEMD5THREAD_H
