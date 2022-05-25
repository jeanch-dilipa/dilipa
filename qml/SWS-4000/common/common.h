/*窗口属性定义*/
#define rootWindowWidth  1024
#define rootWindowHight  768

/*程序版本定义*/
#define VERSION          "V4.9.01 A"

/*调试模式定义*/
#define DEBUG_MODEL                            0
#define DEBUG_MODEL_DISPATCHER                 0
#define DEBUG_MODEL_STARTINTERFACE             0
#define DEBUG_MODEL_SYSTEMSELFCHECK            0
#define DEBUG_MODEL_DETECT                     0
#define DEBUG_MODEL_CORRECT                    0
#define DEBUG_MODEL_ALARMCONTROL               0
#define DEBUG_MODEL_SERIALPORTCONTROL          0
#define DEBUG_MODEL_SQLBASE                    0
#define DEBUG_MODEL_PUBLICDATA                 0
#define DEBUG_MODEL_MODELBOARD                 0
#define DEBUG_MODEL_DATADEALTHREAD             0

#include <QDebug>
#define qdebug (qDebug())

/*运行支持文件定义*/
#define SQL_DATA_RUN_FILE_NAME                                      "F:\\dilipa\\qt\\qml\\SWS-4000\\Databases\\646de5778298733bb12f35bc1c37d95c.sqlite"      //运行状态数据库
//#define SQL_DATA_BASE_FILE_NAME                                     "F:\\dilipa\\qt\\qml\\SWS-4000\\Databases\\sws4000.db"                                   //数据库
