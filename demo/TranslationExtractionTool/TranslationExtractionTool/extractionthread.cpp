#include "extractionthread.h"
#include <QDir>
#include <QDebug> ///zf_debug #include <QDebug>

QList<QUrl> ExtractionSignalHandler::resolveDirectory(QList<QUrl> urls)
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

ExtractionThread::ExtractionThread(ExtractionSignalHandler *signalHandler, QObject *parent) : QThread(parent), m_signalHandler(signalHandler)
{
    connect(m_signalHandler, &ExtractionSignalHandler::signalExport, this, &ExtractionThread::slotExport);

    this->moveToThread(this);
}

ExtractionThread::~ExtractionThread()
{
    this->quit();
    this->wait();
}

void ExtractionThread::run()
{
    this->exec();
}

void ExtractionThread::slotExport(QString dstPath, QStringList srcfiles, int dstType, bool singleXlsx, bool skipObsolete, bool markUnfinished)
{
    if(srcfiles.isEmpty())
    {
        setExportFinished(tr("还没有添加文件!"));
        return;
    }

    if(dstType == 0)
    {   //导出xlsx
        exportXlsxFromTs(dstPath, srcfiles, singleXlsx, skipObsolete);
    }
    else
    {   //导出ts
        exportTsFromXlsx(dstPath, srcfiles, skipObsolete, markUnfinished);
    }
}

void ExtractionThread::exportXlsxFromTs(const QString &dstPath, const QStringList &srcfiles, const bool singleXlsx, const bool skipObsolete)
{
    QList<QList<TranslationSt>> tansLists; //所有文件的所有翻译
    bool success = false;

    //先从所有ts文件中获取翻译内容
    QList<TranslationSt> tansList;
    for(int i = 0; i < srcfiles.size(); i++)
    {
        success = tsrw.loadTransFromTsFile(tansList, srcfiles[i]);
        if(success)
        {
            tansLists.append(tansList);
        }
        else
        {   //某文件加载失败，结束
            QString path = srcfiles[i];
            setExportFinished("【" + path.mid(path.lastIndexOf('/')+1) + "】" + tr("加载翻译失败!"));
            return;
        }
    }

    //开始导出到xlsx
    if(singleXlsx == 1 || tansLists.size() == 1)
    {   //将多个翻译导出到一个xlsx文件或仅有一个翻译
        QStringList headers;
        for(int i = 0; i < srcfiles.size(); i++)
        {
            QString headerName = srcfiles[i];
            headerName = headerName.mid(headerName.lastIndexOf('/')+1); //去除前缀，只剩文件名
            headerName.remove(QRegExp("\\..*")); //去除后缀
            headers.append(headerName);
        }
        success = xlsxrw.exportTransToXlsxFile(dstPath, tansLists, headers, skipObsolete);
    }
    else
    {   //批量导出
        for(int i = 0; i < tansLists.size(); i++)
        {
            QDir dstDir(dstPath);
            if(!dstDir.exists())
            {   //自动创建生成目录
                if(!dstDir.mkpath(dstPath))
                {
                    setExportFinished(tr("【错误】创建导出目录失败！"));
                    return;
                }
            }

            //自动生成目标文件名
            QString dstPathName = dstPath; //目标文件名（带目录）
            if(dstPathName.at(dstPathName.size()-1) != QChar('/'))
            {
                dstPathName += "/";
            }

            QString tansHeader = srcfiles[i]; //翻译列的表头名称
            tansHeader = tansHeader.mid(tansHeader.lastIndexOf('/')+1); //去除前缀，只剩文件名
            tansHeader = tansHeader.remove(QRegExp("\\..*")); //去除后缀
            dstPathName += tansHeader + ".xlsx"; //目标文件名（全路径）

            success = xlsxrw.exportTransToXlsxFile(dstPathName, {tansLists[i]}, {tansHeader}, skipObsolete);
            if(!success)
            {
                setExportFinished("【" + tansHeader + ".xlsx" + "】" + tr("导出失败！"));
                return;
            }
        }
    }

    if(success)
    {
        setExportFinished(tr("导出完成！"));
    }
    else
    {
        setExportFinished(tr("【错误】导出失败！"));
    }
}

void ExtractionThread::exportTsFromXlsx(const QString &dstPath, const QStringList &srcfiles, const bool skipObsolete, const bool markUnfinished)
{
    QList<QList<TranslationSt>> tansLists; //所有文件的所有翻译
    bool success = false;

    //先从所有ts文件中获取翻译内容
    QList<TranslationSt> tansList;
    for(int i = 0; i < srcfiles.size(); i++)
    {
        success = xlsxrw.loadTransFromXlsxFile(tansList, srcfiles[i]);
        if(success)
        {
            tansLists.append(tansList);
        }
        else
        {   //某文件加载失败，结束
            QString path = srcfiles[i];
            setExportFinished("【" + path.mid(path.lastIndexOf('/')+1) + "】" + tr("加载翻译失败!"));
            return;
        }
    }

    if(tansLists.size() == 1)
    {   //只有一个源文件需要导出
        success = tsrw.exportTransToTsFile(dstPath, tansLists[0], skipObsolete, markUnfinished);
    }
    else
    {   //有多个源文件需要导出
        for(int i = 0; i < tansLists.size(); i++)
        {
            QDir dstDir(dstPath);
            if(!dstDir.exists())
            {   //自动创建生成目录
                if(!dstDir.mkpath(dstPath))
                {
                    setExportFinished(tr("【错误】创建导出目录失败！"));
                    return;
                }
            }

            //自动生成目标文件名
            QString dstPathName = dstPath; //目标文件名（带目录）
            if(dstPathName.at(dstPathName.size()-1) != QChar('/'))
            {
                dstPathName += "/";
            }

            QString dstFileName = srcfiles[i]; //目标文件名（不带目录）
            dstFileName = dstFileName.mid(dstFileName.lastIndexOf('/')+1); //去除前缀，只剩文件名
            dstFileName = dstFileName.remove(QRegExp("\\..*")) + ".ts"; //替换后缀
            dstPathName += dstFileName;

            success = tsrw.exportTransToTsFile(dstPathName, tansLists[i], skipObsolete, markUnfinished);
            if(!success)
            {
                setExportFinished("【" + dstFileName + "】" + tr("导出失败！"));
                return;
            }
        }
    }

    if(success)
    {
        setExportFinished(tr("导出完成！"));
    }
    else
    {
        setExportFinished(tr("【错误】导出失败！"));
    }
}

void ExtractionThread::setExportFinished(const QString &msg)
{
    m_signalHandler->signalExportFinished();
    m_signalHandler->signalShowMessage(msg);
}
