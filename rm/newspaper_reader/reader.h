#ifndef READER_H
#define READER_H
#include <QObject>

class reader:public QObject
{
    Q_OBJECT
public:
    reader();
    void read(const QString &name);
};

#endif // READER_H
