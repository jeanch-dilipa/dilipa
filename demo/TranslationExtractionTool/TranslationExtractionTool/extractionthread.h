#ifndef EXTRACTIONTHREAD_H
#define EXTRACTIONTHREAD_H

#include <QThread>
#include <QUrl>
#include "tsfilereadwrite.h"
#include "xlsxreadwrite.h"

//用于C++和QML互发信号的处理类（qml和C++线程的信号直接连接的话，不能跨线程处理--或许是我没搞懂？）
class ExtractionSignalHandler : public QObject
{
    Q_OBJECT
public:
    explicit ExtractionSignalHandler(QObject *parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE QList<QUrl> resolveDirectory(QList<QUrl> urls); //将包含的文件夹全部递归获取文件
signals:
    //开始导出信号（dstPath--目标文件或文件夹；srcfiles--源文件；dstType--导出类型[0:xlsx,1:ts]；singleXlsx--是否导出单个xlsx；skipObsolete--跳过失效的；markUnfinished--标记未完成）
    void signalExport(QString dstPath, QStringList srcfiles, int dstType, bool singleXlsx, bool skipObsolete, bool markUnfinished);

    void signalExportFinished(); //导出结束信号
    void signalShowMessage(QString msg); //在界面显示通知
};

//真正的处理线程
class ExtractionThread : public QThread
{
    Q_OBJECT
public:
    explicit ExtractionThread(ExtractionSignalHandler *signalHandler, QObject *parent = nullptr);
    ~ExtractionThread();

protected:
    void run();

private slots:
    void slotExport(QString dstPath, QStringList srcfiles, int dstType, bool singleXlsx, bool skipObsolete, bool markUnfinished);

private:
    void exportXlsxFromTs(const QString &dstPath,const QStringList &srcfiles, const bool singleXlsx, const bool skipObsolete);
    void exportTsFromXlsx(const QString &dstPath,const QStringList &srcfiles, const bool skipObsolete, const bool markUnfinished);
    inline void setExportFinished(const QString &msg); //设置导出结束并发送界面信息

private:
    TsFileReadWrite tsrw;
    XlsxReadWrite xlsxrw;
    ExtractionSignalHandler *m_signalHandler;
};

#endif // EXTRACTIONTHREAD_H
