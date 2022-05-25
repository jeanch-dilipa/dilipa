#include "timeroption.h"

#include <QApplication>
#include <QList>
#include <QStack>
#include <QQueue>
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QMultiMap>


Q_PROPERTY(QString name
           READ read()
           WRITE write()
           MEMBER str
           RESET set()
           NOTIFY singal()
           DESIGNABLE true
           CONSTANT "1"
           FINAL false)
typedef enum{
 str1=1,
}__attribute__((packed)) kk;

//__attribute__设置函数、变量、类型属性

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    QList<QString> qlist;
    QStack<QString> qstack;
    QQueue<QString> queue;
    for (int i=0;i<30;i++)
    {
        if(i<10) qlist.append((QString)i);
        else if(i<20) qstack.push((QString)i);
        else queue.enqueue((QString)i);
    }
    foreach(QString str,qlist)
        qDebug()<<str;
    foreach(QString str,qstack)
        qDebug()<<qstack.pop();
    foreach(QString str,queue)
        qDebug()<<queue.dequeue();

    QSet<QString> set;
    QMap<QString,int> map;
    QMultiMap<QString,int> multimap1,multimap2,multimap3;
    set<< "1" << "2" << "3";
    qDebug()<<set;
    map["1"]=1;
    map["2"]=2;
    map["3"]=3;
    qDebug()<<map["1"]<<map.value("2")<<map.value("kk",10);
    multimap1.insert("kk",1);
    multimap2.insert("kk",2);
    multimap3 =multimap1+multimap2;
    qlist.clear();
    QList<int> values = multimap3.values("kk");
    for(int i=0;i<values.size();i++)
        qDebug()<<values.at(i);

    timeroption ti;
    ti.show();


    return a.exec();
}
