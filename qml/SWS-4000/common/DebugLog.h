#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QMutex>
#include <QTextStream>

/*调试相关*/
enum class logType
{
    FrontGreen,
    FrontBlack,
    FrontYellow,
    FrontRed,
    FrontBlue
};

static const char * logCommands[] =
{

    "\033[32m",
    "\033[30m",
    "\033[33m",
    "\033[31m",
    "\033[34m",
};

template <typename EnumType,typename IntType = int>
int enumToInt(EnumType enumValue)
{
    static_assert (std::is_enum<EnumType>::value,"EnumType must be enum");
    return static_cast<IntType>(enumValue);
}

static const QString messageTemp = QString("<dir class = \"%1\">%2</dir>\r\n");
static const char typeList[] = {'d','w','c','f','i'};
static const QString templateHtml = u8R"templateHtml(<?xml version="1.0" encoding="utf-8" standalone="yes"?>
                                    <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
                                    <html>
                                    <head>
                                        <title>TaoLogger</title>
                                        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
                                        <style type="text/css" id="logCss">
                                            body {
                                                background: #18242b;
                                                color: #afc6d1;
                                                margin-right: 20px;
                                                margin-left: 20px;
                                                font-size: 14px;
                                                font-family: Arial, sans-serif, sans;
                                            }

                                            a {
                                                text-decoration: none;
                                            }

                                            a:link {
                                                color: #a0b2bb;
                                            }

                                            a:active {
                                                color: #f59504;
                                            }

                                            a:visited {
                                                color: #adc7d4;
                                            }

                                            a:hover {
                                                color: #e49115;
                                            }

                                            h1 {
                                                text-align: center;
                                            }

                                            h2 {
                                                color: #ebe5e5;
                                            }

                                            .d,
                                            .w,
                                            .c,
                                            .f,
                                            .i {
                                                padding: 3px;
                                                overflow: auto;
                                            }

                                            .d {
                                                background-color: #0f1011;
                                                color: #a8c1ce;
                                            }

                                            .i {
                                                background-color: #294453;
                                                color: #a8c1ce;
                                            }

                                            .w {
                                                background-color: #7993a0;
                                                color: #1b2329;
                                            }

                                            .c {
                                                background-color: #ff952b;
                                                color: #1d2930;
                                            }

                                            .f {
                                                background-color: #fc0808;
                                                color: #19242b;
                                            }
                                        </style>
                                    </head>

                                    <body>
                                        <h1>TaoLogger</h1>
                                        <script type="text/JavaScript">
                                            function objHide(obj) {
                                                obj.style.display="none"
                                            }
                                            function objShow(obj) {
                                                obj.style.display="block"
                                            }
                                            function selectType() {
                                                var sel = document.getElementById("typeSelect");
                                                const hideList = new Set(['d', 'i', 'w', 'c', 'f']);
                                                if (sel.value === 'a') {
                                                    hideList.forEach(element => {
                                                        var list = document.querySelectorAll('.' + element);
                                                        list.forEach(objShow);
                                                    });
                                                } else {
                                                    var ss = hideList;
                                                    ss.delete(sel.value);
                                                    ss.forEach(element => {
                                                        var list = document.querySelectorAll('.' + element);
                                                        list.forEach(objHide);
                                                    });
                                                    var showList = document.querySelectorAll('.' + sel.value);
                                                    showList.forEach(objShow);
                                                }
                                            }
                                        </script>
                                        <select id="typeSelect" onchange="selectType()">
                                            <option value='a' selected="selected">All</option>
                                            <option value='d'>Debug</option>
                                            <option value='i'>Info</option>
                                            <option value='w'>Warning</option>
                                            <option value='c'>Critical</option>
                                            <option value='f'>Fatal</option>
                                        </select>

                                        <div class = "f">山有木兮木有枝，心悦君兮君不知</div>)templateHtml";
static QMutex mutex;
static QFile fileLog;
static QTextStream in(&fileLog);
static QTextStream out(stdout,QIODevice::WriteOnly);

void initLog(const QString &logPath,int logMaxCount)
{
    QDir dir(logPath);
    if(!dir.exists())
    {
        dir.mkpath(logPath);
    }

    QStringList infoList = dir.entryList(QDir::Files,QDir::Name);
    if(infoList.size() > logMaxCount)
    {
        dir.remove(infoList.first());
        infoList.removeFirst();
    }
}

void loadingLogs(const QString &logPath,const QtMsgType type,const QString &msg)
{
    QString contentDt = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString message = QString("%1__%2").arg(QTime::currentTime().toString("hh:mm:ss zzz")).arg(msg);
    QString htmlmessage = messageTemp.arg(typeList[static_cast<int>(type)]).arg(message);

    fileLog.setFileName(QString("%1/%2.html").arg(logPath).arg(contentDt));
    bool exist = fileLog.exists();
    in.setCodec("UTF-8");

    mutex.lock();
    if(!fileLog.open(QIODevice::Append))return;
    if(!exist)
    {
        in << templateHtml << Qt::endl;
    }
    in << htmlmessage << Qt::endl;
    fileLog.flush();
    fileLog.close();

    mutex.unlock();

    out << logCommands[enumToInt(type)] << msg << Qt::endl;
    out.flush();
}

#endif // DEBUGLOG_H
