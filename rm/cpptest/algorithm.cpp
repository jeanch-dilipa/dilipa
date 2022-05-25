#include "algorithm.h"
#include <QDebug>

algorithm::algorithm()
{
}

algorithm::~algorithm()
{
}
void algorithm::add()
{
    int i=1;
    for (;;) {
        i++;
        if(i==5)break;
    }
    qDebug()<<i;
}
