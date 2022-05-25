#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <QObject>
#include <QDebug>

class hello_world : public QObject
{
    Q_OBJECT

    Q_ENUMS(color)
//                          读       写                   信号
    Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)     //属性定义
public:
    enum color      //枚举使用Q_ENUMS()
    {
        Red=1,
        Blue,
        Green
    };

    explicit hello_world(QObject *parent = nullptr);

    Q_INVOKABLE void show(color c)      //成员函数使用Q_INVOKABLE定义，且只支持public，protected
    {
        qDebug()<<c;
    }
    QString str()
    {
        return m_str;
    }

    void setStr(QString s)
    {
        m_str=s;
        emit strChanged();
    }

public slots:       //信号与槽直接可用
    void dosomething(color c)
    {
        qDebug()<<"hello world"<<c;
        emit change();
    }

    void cslot(QString chr)
    {
        qDebug()<<chr<<12;
    }

signals:
    void change();
    void strChanged();


private:

    QString m_str;

};



#endif // HELLO_WORLD_H
