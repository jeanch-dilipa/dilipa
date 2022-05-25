#include "reader.h"
#include <QDebug>

reader::reader()
{

}

void reader::read(const QString &name)
{
    qDebug()<<"I HOLD IT"<<name;
}
