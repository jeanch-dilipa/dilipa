#ifndef TSFILEREADWRITE_H
#define TSFILEREADWRITE_H
#include "common.h"

class TsFileReadWrite
{
public:
    TsFileReadWrite();

    //从ts文件导入翻译
    bool loadTransFromTsFile(QList<TranslationSt> &transList, const QString &fileName);
    //导出翻译到ts文件
    bool exportTransToTsFile(const QString &fileName, const QList<TranslationSt> &transList, bool skipObsolete = false, bool markUnfinished = true);
};

#endif // TSFILEREADWRITE_H
