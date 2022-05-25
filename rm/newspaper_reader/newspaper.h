#ifndef NEWSPAPER_H
#define NEWSPAPER_H
#include <QObject>

class newspaper:public QObject
{
    Q_OBJECT
private:
    QString m_name;
public:
    newspaper(const QString name);
    void send();
signals:
    void newspape(const QString name) const;

};

#endif // NEWSPAPER_H
