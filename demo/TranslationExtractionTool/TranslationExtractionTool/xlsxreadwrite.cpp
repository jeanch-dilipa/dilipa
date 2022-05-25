#include "xlsxreadwrite.h"
#include <LibXlsxRW/xlsxdocument.h>
#include <QDebug> ///zf_debug #include <QDebug>

#define OBSOLETE_COLOR QColor(216, 216, 216) //失效的行颜色
#define VANISHED_COLOR QColor(218, 218, 218) //消失的行颜色

XlsxReadWrite::XlsxReadWrite()
{

}

bool XlsxReadWrite::loadTransFromXlsxFile(QList<TranslationSt> &transList, const QString &fileName)
{
    if(!QFile::exists(fileName))
    {
        return false;
    }

    QXlsx::Document xlsx(fileName);
    QStringList sheets = xlsx.sheetNames();
    if(sheets.isEmpty())
    {
        return false;
    }
    xlsx.selectSheet(sheets.first());
    QXlsx::CellRange range = xlsx.currentWorksheet()->dimension(); //获取整个表的范围
    if(range.rowCount() < 2 || range.columnCount() < 2)
    {   //至少有2行（表头+1行数据），2列（source、translation）
        return false;
    }

    transList.clear();
    bool hasContext = (range.columnCount() > 2 && xlsx.read(1, 1).toString() == "context"); //是否有上下文列
    //开始读取翻译内容
    TranslationSt trans;
    for(int i = 2; i <= range.rowCount(); i++)
    {
        trans.context = hasContext ? xlsx.read(i, 1).toString() : QString();
        trans.source = xlsx.read(i, hasContext ? 2 : 1).toString();
        trans.translation = xlsx.read(i, hasContext ? 3 : 2).toString();
        QColor backColor = xlsx.cellAt(i, hasContext ? 2 : 1)->format().patternBackgroundColor();
        if(backColor == OBSOLETE_COLOR)
        {
            trans.type = OBSOLETE;
        }
        else if(backColor == VANISHED_COLOR)
        {
            trans.type = VANISHED;
        }
        else
        {
            trans.type.clear();
        }
        transList.append(trans);
    }

    return true;
}

bool XlsxReadWrite::exportTransToXlsxFile(const QString &fileName, const QList<QList<TranslationSt>> &transLists, const QStringList &headers, bool skipObsolete)
{
    if(fileName.isEmpty() || transLists.isEmpty() || transLists.size() != headers.size())
    {
        return false;
    }

    QXlsx::Document xlsx;
    xlsx.addSheet("Sheet1");
    QXlsx::Format defaultFormat;
    //设置表头格式
    defaultFormat.setFontName("Times New Roman");
    defaultFormat.setFontBold(true);
    defaultFormat.setFontSize(15);
    defaultFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    //导出表头
    xlsx.write(1, 1, "context", defaultFormat);
    xlsx.write(1, 2, "source", defaultFormat);
    for(int i = 0; i < headers.size(); i++)
    {
        xlsx.write(1, i+3, headers[i], defaultFormat);
    }

    //设置翻译内容单元格格式
    defaultFormat.setFontBold(false);
    defaultFormat.setFontSize(13);
    defaultFormat.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    //开始导出翻译内容（以第一个翻译为主导，并找到其他符合该原文的翻译内容）
    QXlsx::Format format = defaultFormat;
    for(int i = 0, curRow = 2; i < transLists[0].size(); i++)
    {
        if(transLists[0][i].type == OBSOLETE || transLists[0][i].type == VANISHED)
        {   //废弃的或者消失的
            if(skipObsolete)
            {   //跳过
                continue;
            }
            else
            {   //不跳过，将该行标记为灰色
                format.setPatternBackgroundColor(transLists[0][i].type == OBSOLETE ? OBSOLETE_COLOR : VANISHED_COLOR);
                format.setBorderStyle(QXlsx::Format::BorderThin);
                format.setBorderColor(QColor(182, 182, 182)); //设置了背景色之后，需要设置边框颜色，否则多个行会看起来合在一起
            }
        }
        else
        {   //不是废弃的或消失的，恢复默认格式
            format = defaultFormat;
        }

        xlsx.write(curRow, 1, transLists[0][i].context, format); //写入上下文
        xlsx.write(curRow, 2, transLists[0][i].source, format);  //写入原文
        xlsx.write(curRow, 3, transLists[0][i].translation, format); //写入第一个译文
        //查找其他翻译的译文并写入
        for(int j = 1; j < transLists.size(); j++)
        {
            int size = transLists[j].size();
            bool found = false; //是否找到
            for(int k = 0; k < size; k++)
            {   //遍历每一个翻译的所有内容
                int idx = (i+k)%size; //为了增加遍历效率，每次从主翻译的那一行开始找

                if(transLists[j][idx].context == transLists[0][i].context && transLists[j][idx].source == transLists[0][i].source)
                {   //上下文和原文均相同才认为是同一行翻译
                    xlsx.write(curRow, 3+j, transLists[j][idx].translation, format); //写入译文
                    found = true;
                    break;
                }
            }
            if(!found)
            {   //没有找到，但还是要把改行的format修改
                xlsx.write(curRow, 3+j, QString(), format);
            }
        }
        curRow++;
    }

    xlsx.setColumnHidden(1, true);  //隐藏context列

    //设置原文和译文列宽
    int columnWidth = 300/(headers.size()+1);
    if(columnWidth < 30)
    {
        columnWidth = 30;
    }
    else if(columnWidth > 100)
    {
        columnWidth = 100;
    }
    xlsx.setColumnWidth(2, 2 + headers.size(), columnWidth);

    return xlsx.saveAs(fileName);
}
