#ifndef XLSXREADWRITE_H
#define XLSXREADWRITE_H
#include "common.h"

class XlsxReadWrite
{
public:
    XlsxReadWrite();

    //从Excel文件导入翻译
    bool loadTransFromXlsxFile(QList<TranslationSt> &transList, const QString &fileName);
    //导出翻译到Excel文件
    bool exportTransToXlsxFile(const QString &fileName, const QList<QList<TranslationSt>> &transLists, const QStringList &headers, bool skipObsolete = false);
};

#endif // XLSXREADWRITE_H
