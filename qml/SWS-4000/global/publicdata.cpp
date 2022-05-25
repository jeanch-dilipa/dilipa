#include "publicdata.h"

publicData g_data;

/*
功能描述：publicData类构造函数
输    入：/
输    出：/
*/
publicData::publicData(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL || DEBUG_MODEL_PUBLICDATA
    QString debugstr="publicData::publicData(QObject *parent) : QObject(parent):构造函数";
    qdebug<<debugstr;
#endif

    m_rootWindowWidth = rootWindowWidth;
    m_rootWindowHeight = rootWindowHight;
    module = INITModelBoard;
}
/*
功能描述：publicData类析构函数
输    入：/
输    出：/
*/
publicData::~publicData()
{
    module->demodelboard();
}
