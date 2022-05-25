#include "newspaper.h"
#include "reader.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    newspaper newspaper("one");
    reader reader;
    QObject::connect(&newspaper,&newspaper::newspape,&reader,&reader::read);
    newspaper.send();

    return a.exec();
}
