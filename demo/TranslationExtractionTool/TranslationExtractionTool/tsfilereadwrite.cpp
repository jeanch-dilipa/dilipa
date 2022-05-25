#include "tsfilereadwrite.h"
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDebug> ///zf_debug #include <QDebug>

TsFileReadWrite::TsFileReadWrite()
{
}

bool TsFileReadWrite::loadTransFromTsFile(QList<TranslationSt> &transList, const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QDomDocument doc;
    bool setContentRes = doc.setContent(&file);
    file.close();
    if(!setContentRes)
    {
        return false;
    }

    transList.clear();

    QDomNodeList contextList = doc.elementsByTagName("context");
    for(int i = 0; i < contextList.size(); i++)
    {   //遍历所有context
        QDomNodeList messageNodeList = contextList.at(i).childNodes();
        QDomNode nameNode = messageNodeList.at(0);
        QString currentContext;
        if(nameNode.nodeName() == "name")
        {   //获取context名（context的第一个子节点"name"）
            currentContext = nameNode.toElement().text();
        }

        for(int j = 1; j < messageNodeList.size(); j++)
        {   //遍历一个context中的所有message
            if(messageNodeList.at(j).nodeName() == "message")
            {
                QDomNodeList transNodeList = messageNodeList.at(j).childNodes();
                TranslationSt trans;
                for(int k = 0; k < transNodeList.size(); k++)
                {
                    QDomNode node = transNodeList.at(k);
                    if(node.nodeName() == "source")
                    {   //原文
                        trans.source = node.toElement().text();
                    }
                    else if(node.nodeName() == "translation")
                    {   //译文
                        trans.translation = node.toElement().text();
                        trans.type = node.toElement().attribute("type");
                    }
                }

                if(!trans.source.isNull())
                {   //插入一条翻译
                    trans.context = currentContext;
                    transList.append(trans);
                }
            }
        }
    }

    return true;
}

bool TsFileReadWrite::exportTransToTsFile(const QString &fileName, const QList<TranslationSt> &transList, bool skipObsolete, bool markUnfinished)
{
    QFile file(fileName);
    QDomDocument doc;

    if(file.exists())
    {   //文件存在，更新
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }
        bool setContentRes = doc.setContent(&file);
        file.close();
        if(!setContentRes)
        {
            return false;
        }

        QDomNodeList contextList = doc.elementsByTagName("context");
        for(int i = 0; i < contextList.size(); i++)
        {   //遍历所有context
            QDomNodeList messageNodeList = contextList.at(i).childNodes();
            QDomNode nameNode = messageNodeList.at(0);
            QString currentContext;
            if(nameNode.nodeName() == "name")
            {   //获取context名（context的第一个子节点"name"）
                currentContext = nameNode.toElement().text();
            }

            for(int j = 1; j < messageNodeList.size(); j++)
            {   //遍历一个context中的所有message
                if(messageNodeList.at(j).nodeName() == "message")
                {
                    QDomNodeList transNodeList = messageNodeList.at(j).childNodes();
                    QDomNode oldTransNode;
                    QDomAttr typeAttr;
                    QString source;

                    for(int k = 0; k < transNodeList.size(); k++)
                    {
                        QDomNode node = transNodeList.at(k);
                        if(node.nodeName() == "source")
                        {   //原文
                            source = node.toElement().text();
                        }
                        else if(node.nodeName() == "translation")
                        {   //译文
                            oldTransNode = node;
                            typeAttr = node.toElement().attributeNode("type");
                        }
                    }

                    TranslationSt transNew;
                    bool found = false;
                    foreach(TranslationSt trans, transList)
                    {   //找到当前的翻译（source和context都相等的）
                        if((trans.context.isEmpty() || trans.context == currentContext) && trans.source == source)
                        {
                            transNew = trans;
                            found = true;
                            break;
                        }
                    }

                    if(found && (transNew.translation != oldTransNode.toElement().text()))
                    {   //翻译有区别，更新
                        if(!(skipObsolete && (transNew.type == OBSOLETE || transNew.type == VANISHED)))
                        {
                            QDomElement newElement = doc.createElement("translation");
                            if(typeAttr.value() == OBSOLETE || typeAttr.value() == VANISHED)
                            {   //过期的翻译，保持过期属性
                                newElement.setAttributeNode(typeAttr);
                            }
                            else if(markUnfinished)
                            {   //其他翻译，只要被更新过，设置为“未完成”
                                newElement.setAttribute("type", UNFINISHED);
                            }
                            newElement.appendChild(doc.createTextNode(transNew.translation));
                            messageNodeList.at(j).replaceChild(newElement, oldTransNode);
                        }
                    }
                }
            }
        }
    }
    else
    {   //文件不存在，创建
        QDomImplementation imp;
        //创建一个Document，根节点为"TS"，DOCTYPE为"TS"
        doc = imp.createDocument(QString(), "TS", imp.createDocumentType("TS", QString(), QString()));
        QDomElement rootElement = doc.documentElement(); //获取根节点
        rootElement.setAttribute("version", "2.0"); //设置版本
        //在根节点前插入处理指令
        doc.insertBefore(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""), rootElement);
        //插入defaultcodec节点（2.1版本的貌似没有这个节点，但是是兼容的）
        QDomElement codecElement = doc.createElement("defaultcodec");
        codecElement.appendChild(doc.createTextNode("UTF-8"));
        rootElement.appendChild(codecElement);

        //插入翻译内容
        QString currentContext = "_INVALID_CONTEXT_"; //当前上下文
        QDomNode currentContextNode; //当前上下文节点
        QDomElement newElement; //用于保存新创建的节点
        for(int i = 0; i < transList.size(); i++)
        {
            if(skipObsolete && (transList[i].type == OBSOLETE || transList[i].type == VANISHED))
            {   //跳过失效的或消失的
                continue;
            }

            if(transList[i].context != currentContext)
            {   //上下文改变，创建一个新的上下文
                currentContext = transList[i].context;
                currentContextNode = rootElement.appendChild(doc.createElement("context"));
                newElement = doc.createElement("name");
                newElement.appendChild(doc.createTextNode(currentContext));
                currentContextNode.appendChild(newElement);
            }

            //插入message（每一个翻译有一个message）
            QDomNode msgNode = currentContextNode.appendChild(doc.createElement("message"));
            //插入原文
            newElement = doc.createElement("source");
            newElement.appendChild(doc.createTextNode(transList[i].source));
            msgNode.appendChild(newElement);
            //插入译文
            newElement = doc.createElement("translation");
            newElement.appendChild(doc.createTextNode(transList[i].translation));
            if(!transList[i].type.isEmpty())
            {
                newElement.setAttribute("type", transList[i].type);
            }
            else if(markUnfinished)
            {   //标记“未完成”
                newElement.setAttribute("type", UNFINISHED);
            }
            msgNode.appendChild(newElement);
        }
    }

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }

    QTextStream outStream(&file);
    doc.save(outStream, 4);
    file.close();

    return true;
}
