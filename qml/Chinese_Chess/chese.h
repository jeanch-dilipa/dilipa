#ifndef CHESE_H
#define CHESE_H

#include <QObject>
#include <QThread>

class Chese : public QThread
{
    Q_OBJECT
public:
    Chese();
};

#endif // CHESE_H
