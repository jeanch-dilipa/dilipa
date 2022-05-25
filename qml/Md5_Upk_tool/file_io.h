#ifndef FILE_IO_H
#define FILE_IO_H

#include <QObject>

#include "file_upk.h"

class File_io : public QObject
{
    Q_OBJECT
public:
    explicit File_io(QObject *parent = nullptr);
    ~ File_io();

    QString rootfilepath="";

signals:
    void isfilefilter(QStringList);
    void isneedfile(QString filepath,QString rootpath);
    void createmd5(QStringList);
    void createok(bool issucceed);
    void clearrootfilepath();
    void createupk(QStringList,QString);
    void showinfo(QString info);

private:
    void fileprintf(QStringList filepath);
    void filecreatemd5(QStringList filepath);

    File_upk upk;
};

#endif // FILE_IO_H
