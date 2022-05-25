#ifndef COMMON_H
#define COMMON_H

#include <QMetaType>
#include <QString>

#define OBSOLETE   "obsolete"   //失效的
#define VANISHED   "vanished"   //消失的
#define UNFINISHED "unfinished" //未完的

//翻译提取内容结构体
struct TranslationSt
{
    TranslationSt(){}
    TranslationSt(const QString &source, const QString &translation, const QString &context)
    {
        this->source = source;
        this->translation = translation;
        this->context = context;
    }

    QString source;       //原文
    QString translation;  //译文
    QString context;      //上下文
    QString type;         //翻译属性（""、"obsolete"、"unfinished"、"vanished"）
};

Q_DECLARE_METATYPE(TranslationSt)

#endif // COMMON_H
