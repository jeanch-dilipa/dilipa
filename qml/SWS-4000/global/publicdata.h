#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QObject>

#include "common/common.h"
#include "controllayer/modelboard.h"
#include "controllayer/sqlbase.h"

template <typename T>

struct ParaInit
{
    T m_value;
    T m_snap;
    T m_def;
    T m_min;
    T m_max;

    ParaInit():m_value(0),m_min(0),m_max(0){}
    bool init(T value,T snap,T def,T min,T max)
    {
        if(value >= min && value <= max)
        {
            m_value = value;
            m_snap = snap;
            m_def = def;
            m_min = min;
            m_max = max;
            return true;
        }
        return false;
    }
    bool init_min_max(T min,T max)
    {
        if(min <= max)
        {
            m_min = min;
            m_max = max;
            return true;
        }
        return false;
    }
};

struct Parameter
{
    ParaInit<quint16>                                                           dislysateTemp;                                                                  //透析液温度
};
struct SystemParameter
{
    ParaInit<quint8>                                                            qpVoltage;                                                                      //除气泵电压
    ParaInit<qint16>                                                            temp_Comp;                                                                      //温度补偿
};
struct Alarm
{
    ParaInit<qint16>                                                            tempAlarmHight;                                                                  //温度报警上限
    ParaInit<qint16>                                                            tempAlarmLow;                                                                    //温度报警下限
    ParaInit<qint16>                                                            apAlarmHight;                                                                    //动脉压报警上限
    ParaInit<qint16>                                                            apAlarmLow;                                                                      //动脉压报警下限
    ParaInit<qint16>                                                            vpAlarmHight;                                                                    //静脉压报警上限
    ParaInit<qint16>                                                            vpAlarmLow;                                                                      //静脉压报警下限
    ParaInit<qint16>                                                            tmpAlarmHight;                                                                   //跨膜压报警上限
    ParaInit<qint16>                                                            tmpAlarmLow;                                                                     //跨膜压报警下限
};

class publicData : public QObject
{
    Q_OBJECT
/*注册属性*/
    Q_PROPERTY(int m_rootWindowWidth READ m_rootWindowWidthRead WRITE m_rootWindowWidthWrite NOTIFY m_rootWindowWidthChange)
    Q_PROPERTY(int m_rootWindowHeight READ m_rootWindowHeightRead WRITE m_rootWindowHeightWrite NOTIFY m_rootWindowHeightChange)

public:
    explicit publicData(QObject *parent = nullptr);
    ~publicData();

/*属性访问方法*/
    int m_rootWindowWidthRead(){return m_rootWindowWidth;}
    void m_rootWindowWidthWrite(int m_rootWindowWidth){this->m_rootWindowWidth = m_rootWindowWidth;}
    int m_rootWindowHeightRead(){return m_rootWindowHeight;}
    void m_rootWindowHeightWrite(int m_rootWindowHeight){this->m_rootWindowHeight = m_rootWindowHeight;}

signals:
/*属性改变信号*/
    void m_rootWindowWidthChange();
    void m_rootWindowHeightChange();

public:
/*属性定义*/
    int                                                                         m_rootWindowWidth;                                                              //主界面宽度
    int                                                                         m_rootWindowHeight;                                                             //主界面高度

    modelboard                                                                 *module;                                                                         //模块参数
//    sqlbase                                                                     sqlbase;                                                                        //数据库
    Parameter                                                                   parameter;                                                                      //基本参数
    SystemParameter                                                             systemParameter;                                                                //系统参数
    Alarm                                                                       alarm;                                                                          //报警参数
};
extern publicData g_data;

#endif // PUBLICDATA_H
