/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   debug.h
    info:	System debugging interface
******************************************************************************/

#ifndef DEBUG_H
#define DEBUG_H

#include <QTextStream>
#include <iostream>
#include <QDir>
#include <QDate>
#include <QMutex>

Q_GLOBAL_STATIC(QMutex, s_mutex);
Q_GLOBAL_STATIC(QDir, s_dir);
Q_GLOBAL_STATIC(QFile, s_fileLog);
Q_GLOBAL_STATIC_WITH_ARGS(QTextStream, in, (s_fileLog));
Q_GLOBAL_STATIC_WITH_ARGS(QTextStream, out, (stdout, QIODevice::WriteOnly));
Q_GLOBAL_STATIC_WITH_ARGS(QString, MESSAGETEMP, ("<dir class = \"%1\">%2</dir>\r\n"));

static const char TYPELIST[] = {'d','w','c','f','i'};
static const char *LOGCOMMANDS[] ={"\033[32m", "\033[30m", "\033[33m", "\033[31m", "\033[34m"};
static const QString TEMPLATEHTML = u8R"templateHtml(<?xml version="1.0" encoding="utf-8" standalone="yes"?>
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

                                                      <dir class = "f">山有木兮木有枝，心悦君兮君不知</dir>)templateHtml";

/****************************************************************************
接口描述: 检测日志文件符合性
输   入: filePath---文件路径, maxNum---最大文件存储量
输   出: /
******************************************************************************/
void initLog(const QString &filePath, const quint16 &maxNum)
{
    s_dir->setPath(filePath);
    if(false == s_dir->exists())
    {
        s_dir->mkpath(filePath);
    }
    else
    {
        QStringList listInfo = s_dir->entryList(QDir::Files, QDir::Name);
        if(maxNum < listInfo.size())
        {
            s_dir->remove(listInfo.first());
        }
    }
}

/****************************************************************************
接口描述: 装载内容到日志文件
输   入: filePath---文件路径, type---记录类型, msg---记录内容
输   出: /
******************************************************************************/
void loadingLog(const QString &filePath, const QtMsgType &type, const QString &msg)
{
    QString currentDT = QDate::currentDate().toString("yyyy-MM-dd");
    QString message = QString("%1__%2").arg(QTime::currentTime().toString("hh:mm:ss zzz"), msg);
    QString htmlmsg = MESSAGETEMP->arg(TYPELIST[static_cast<int>(type)]).arg(message);

    s_mutex->lock();
    s_fileLog->setFileName(QString("%1/%2.html").arg(filePath, currentDT));
    bool isExist = s_fileLog->exists();
    in->setCodec("UTF-8");

    if(false == s_fileLog->open(QIODevice::Append))
    {
        s_mutex->unlock();
        return;
    }
    else
    {
        if(false == isExist)
        {
            *in << TEMPLATEHTML << Qt::endl;
        }

        *in << htmlmsg << Qt::endl;
        in->flush();
        s_fileLog->close();
        s_mutex->unlock();
    }

    *out << LOGCOMMANDS[static_cast<int>(type)] << msg << Qt::endl;
    out->flush();
}

/****************************************************************************
接口描述: 自定义消息处理器
输   入: type---消息类型, context---消息属性, msg---消息内容
输   出: /
******************************************************************************/
void customMessageHandler(const QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString info = "";
    switch (type)
    {
        case QtDebugMsg:
            info = QString("debugMsg %1 %2: %3").arg(context.file).arg(context.line).arg(msg);
            break;
        case QtWarningMsg:
            info = QString("warningMsg %1 %2: %3").arg(context.file).arg(context.line).arg(msg);
            break;
        case QtCriticalMsg:
            info = QString("criticalMsg %1 %2: %3").arg(context.file).arg(context.line).arg(msg);
            break;
        case QtFatalMsg:
            info = QString("fatalMsg %1 %2: %3").arg(context.file).arg(context.line).arg(msg);
            break;
        case QtInfoMsg:
            info = QString("infoMsg %1 %2: %3").arg(context.file).arg(context.line).arg(msg);
            break;
    }

    initLog(QDir::currentPath() + "/LOG", 3650);
    loadingLog(QDir::currentPath() + "/LOG", type, info);
}

#endif // DEBUG_H
