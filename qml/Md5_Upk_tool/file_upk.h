#ifndef FILE_UPK_H
#define FILE_UPK_H

#include <QObject>
#include <QProcess>

class File_upk : public QObject
{
    Q_OBJECT
public:
    explicit File_upk(QObject *parent = nullptr);
    ~File_upk();

signals:
    void createupk(QStringList,QString);
    void showinfo(QString);

private:
    void ini7za();
    void clearupktemp();
    void createtar(QStringList upkfilelist,QString rootfilepath);
    void creategz(int exitcode,QProcess::ExitStatus exitstatus);
    void createupk(int exitcode,QProcess::ExitStatus exitstatus);
    quint32 verstrtonum(QString str);       //版本字符转数字
    void createconfig();


    QProcess *m_process;
    QString upkname;
    QString upkversion;
    QString rootfilepath;
};

#endif // FILE_UPK_H
