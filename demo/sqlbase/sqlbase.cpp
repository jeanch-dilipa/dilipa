/****************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.

文件名称：	sqlbase.cpp
摘     要 ：	Sqlbase类实现，定义使用SWS6000中各个数据库的简单方法

当前版本：    V1.0
作   者：	ccy
完成日期：	2014-02-24
******************************************************************************/
#include "sqlbase.h"


/**********************************************************************************
函数名：         Sqlbase()
功能描述：       Sqlbase类的构造函数，在此初始化一些私有变量
输入参数：       db_name------数据库名
输出参数：       无
返回值：        无
***********************************************************************************/
Sqlbase::Sqlbase(const QString &db_name)

{

    QString name = db_name;

    if(db.contains(name))
        db = QSqlDatabase::database(name);
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(name);

    if (!db.open())
    {
        qDebug() << QString("open sql error  ") << db.lastError();

    }

    query = QSqlQuery(db);


}

/**********************************************************************************
函数名：         Query()
功能描述：       查询数据库
输入参数：       command----数据库语句
输出参数：       无
返回值：        query查询结果
***********************************************************************************/
QSqlQuery Sqlbase::Query(const QString &command)
{
    bool ok = Exec(command);

    if(!ok)
    {
        QSqlError err = query.lastError();
        qDebug() << err.text();
    }

    return query;
}

/**********************************************************************************
函数名：         Exec()
功能描述：       执行数据库语句
输入参数：       command----数据库语句
输出参数：       无
返回值：       bool   true---正确执行，false---执行错误
**********************************************************************************/
bool Sqlbase::Exec(const QString &command)
{
    bool ok;
    ok = query.exec(command);

    if(!ok)
    {
        QSqlError err = query.lastError();
        qDebug() << err.text();
    }

    return ok;
}

/**********************************************************************************
函数名：         Exec()
功能描述：       执行数据库语句
输入参数：       cmdList----数据库语句集
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::Exec(const QList<QString> &cmdList)
{
    db.transaction();

    for(int i = 0 ; i < cmdList.size() ; i++)
        Exec(cmdList.at(i));

    db.commit();
}

/**********************************************************************************
函数名：         createHistoryAlarmDBTable()
功能描述：       创建历史报警表
输入参数：       无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::createHistoryAlarmDBTable( )
{
    QString cmd;
    cmd=QString("CREATE TABLE IF NOT EXISTS %1(id INTEGER PRIMARY KEY AUTOINCREMENT, mode INT , runTime DOUBLE ,alarmTime INT,alarmDate VARCHAR,alarmNum VARCHAR,A_conductivity INT,B_conductivity INT,C_conductivity INT,APumpSpeed INT,BPumpSpeed INT,inFluidPre INT,outFluidPre INT,QPSpeed INT   ,DPSpeed INT,YPSpeed INT,dialyzateFluidPre INT,dialyzateFluidFlow INT,radiotubeStatus INT,WG1 INT,WG5 INT);").arg(DB_HistoryAlarmTable);

    Exec(cmd);

}

/**********************************************************************************
函数名：         saveHistoryAlarmDataFromDBTable()
功能描述：       保存历史报警数据到数据库
输入参数：       alarm----结构体historyAlarm
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::saveHistoryAlarmDataToDB(struct HistoryAlarm alarm)
{
    createHistoryAlarmDBTable();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.date().toString("yyyy-MM-dd");
    QString time = dateTime.time().toString("hh:mm:ss");

    QString cmd=QString("INSERT INTO %1 (mode,runTime,alarmTime,alarmDATE,alarmNum,A_conductivity,B_conductivity,C_conductivity,APumpSpeed,BPumpSpeed,inFluidPre,outFluidPre,QPSpeed,DPSpeed,YPSpeed,dialyzateFluidPre,dialyzateFluidFlow,radiotubeStatus,WG1,WG5) VALUES(%2,%3,'%4','%5',%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21);").arg(DB_HistoryAlarmTable).arg(alarm.mode).arg(alarm.runTime).arg(time).arg(date).arg(alarm.alarmNum).arg(alarm.A_conductivity).arg(alarm.B_conductivity).arg(alarm.C_conductivity).arg(alarm.APumpSpeed).arg(alarm.BPumpSpeed).arg(alarm.inFluidPre).arg(alarm.outFluidPre).arg(alarm.QPSpeed).arg(alarm.DPSpeed).arg(alarm.YPSpeed).arg(alarm.dialyzateFluidPre).arg(alarm.dialyzateFluidFlow).arg(alarm.radiotubeStatus).arg(alarm.WG1).arg(alarm.WG5);

    Exec(cmd);

}

/**********************************************************************************
函数名：         getHistoryAlarmDataFromDBTable()
功能描述：       从数据库中获取历史报警数据
输入参数：   alarmdate----报警日期值
                    offset----偏移值
输出参数：       historydata
返回值：        QVector<historyAlarm>
**********************************************************************************/
QMultiMap<QString,HistoryAlarm>Sqlbase::getHistoryAlarmDataFromDBTable(QString alarmdate,const int offset)
{
    QMultiMap<QString,HistoryAlarm>historydata;
    //QVector<HistoryAlarm>historydata;
    HistoryAlarm alarm;

    createHistoryAlarmDBTable();

    QString cmd = QString("SELECT * FROM %1 WHERE alarmDate = '%2' limit %3 offset %4;").arg(DB_HistoryAlarmTable).arg(alarmdate).arg(QString::number(ALARMNUM)).arg(QString::number(offset*ALARMNUM));    //不确定能按顺序读取历史报警表字段
    QSqlQuery query = Query(cmd);


    while(query.next())
    {
       int id=query.value(0).toInt();
        alarm.mode=query.value(1).toInt();
        alarm.runTime=query.value(2).toInt();

        QTime time1 = query.value(3).toTime();
        QString time = time1.toString("hh:mm:ss");
        QDate date2 = query.value(4).toDate();
        QString date = date2.toString("yyyy-MM-dd");

        alarm.alarmNum=query.value(5).toInt();
        alarm.A_conductivity=query.value(6).toInt();
        alarm.B_conductivity=query.value(7).toInt();
        alarm.C_conductivity=query.value(8).toInt();
        alarm.APumpSpeed=query.value(9).toInt();
        alarm.BPumpSpeed=query.value(10).toInt();
        alarm.inFluidPre=query.value(11).toInt();
        alarm.outFluidPre=query.value(12).toInt();
        alarm.QPSpeed=query.value(13).toInt();
        alarm.DPSpeed=query.value(14).toInt();
        alarm.YPSpeed=query.value(15).toInt();
        alarm.dialyzateFluidPre=query.value(16).toInt();
        alarm.dialyzateFluidFlow=query.value(17).toInt();
        alarm.radiotubeStatus=query.value(18).toInt();
        alarm.WG1=query.value(19).toInt();
        alarm.WG5=query.value(20).toInt();

        historydata.insert(time,alarm);
    }

    return historydata;
}

/**********************************************************************************
函数名：         deleteHistoryAlarmData()
功能描述：       根据日期删除历史报警数据
输入参数：     alarmdate----报警日期值
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deleteHistoryAlarmData(const int alarmdate)
{
    QString cmd = QString("DELETE FROM %1 WHERE alarmDate = %2;").arg(DB_HistoryAlarmTable).arg(QString::number(alarmdate));

    Exec(cmd);
}

/**********************************************************************************
函数名：         deleteHistoryAlarmData()
功能描述：       清空历史报警数据
输入参数：     无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deleteHistoryAlarmData()
{
    QString cmd = QString("DELETE FROM %1;").arg(DB_HistoryAlarmTable);

    Exec(cmd);
}

/**********************************************************************************
函数名：         updateParameterDBData()
功能描述：       更新系统参数值
输入参数：       table_name----表名      name----参数名     value----更改值
                  button----保存值按钮
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::updateParameterDBData(const QString &table_name, const QString name, const int value ,bool button)
{
    QList<QString> cmdList;
    QString cmd;

    if(button)
    {
        QString cmd1;
        QString cmd2;

        cmd1 = QString("UPDATE %1 SET saveValue = %2 WHERE name = %3").arg(table_name).arg(QString::number(value)).arg(name);
        cmd2 = QString("UPDATE %1 SET realValue = %2 WHERE name = %3").arg(table_name).arg(QString::number(value)).arg(name);

        cmdList.append(cmd1);
        cmdList.append(cmd2);
    }
    else
    {
        cmd = QString("UPDATE %1 SET realValue = %2 WHERE name = '%3'  ").arg(table_name).arg(QString::number(value)).arg(name);
    }

    Exec(cmdList);
    Exec(cmd);
}

/**********************************************************************************
函数名：         getParameterDataFromDBTable()
功能描述：       获取系统参数数据
输入参数：       table_name----表名       key----获取字段关键字
输出参数：       data
返回值：        QVector <pValue>
**********************************************************************************/
QVector <ParamValue> Sqlbase::getParameterDataFromDBTable(const QString &table_name,const QString key)
{
    QVector <ParamValue> data;

    QString cmd = QString("SELECT name,%1 FROM %2;").arg(key).arg(table_name);
    QSqlQuery query = Query(cmd);

    while(query.next())
    {

        ParamValue p;
        p.name = query.value(0).toInt();
        p.defalutValue=query.value(1).toInt();
        p.saveValue=query.value(2).toInt();
        p.realValue=query.value(3).toInt();

        data.push_back(p);
        qDebug()<<p.name<<p.defalutValue<<p.saveValue<<p.realValue;

    }
    return data;
}

/**********************************************************************************
函数名：         createCureRTDBTable()
功能描述：       创建治疗参数表
输入参数：       table_name----表名
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::createCureRTDBTable()
{
    QString cmd = QString("CREATE TABLE IF NOT EXISTS %1(name INTEGER PRIMARY KEY , value INT) ;").arg(DB_CureRealTimeTable);

    Exec(cmd );
}

/**********************************************************************************
函数名：         saveCureRTDataToDB()
功能描述：       将治疗过程的实时参数保存到数据库
输入参数：       name----name字段
                             value----value字段
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::saveCureRTDataToDB(const int name,int value)
{
    createCureRTDBTable();

    QString cmd=QString("INSERT OR REPLACE INTO %1 VALUES(%2,%3);").arg(DB_CureRealTimeTable).arg(QString::number(name)).arg(QString::number(value));

    Exec(cmd);
}

/**********************************************************************************
函数名：         getCureRTDataFromDBTable()
功能描述：       获取治疗过程的实时参数
输入参数：          无
输出参数：       RTcure
返回值：        QMultiMap<QString,int>
**********************************************************************************/
QMultiMap<QString,int>  Sqlbase::getCureRTDataFromDBTable()
{
        QMultiMap<QString,int>RTcure;

        QString cmd = QString("SELECT name , value FROM %1;").arg(DB_CureRealTimeTable);
        QSqlQuery query =Query(cmd);

        while(query.next())
        {
            QString name = query.value(0).toString();
            int value = query.value(1).toInt();

            RTcure.insert(name,value);

            qDebug()<<name<<value;
        }

    return RTcure;
}

/**********************************************************************************
函数名：         createPatientCureDBTable()
功能描述：       创建患者治疗参数表
输入参数：       无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::createPatientCureDBTable( )
{
    QString cmd;
    cmd=QString("CREATE TABLE IF NOT EXISTS %1(id INTEGER PRIMARY KEY AUTOINCREMENT,id_card INT,UfObj INT,CureTime INT,TempHps INT,FlowHEP INT,TotalSF INT,TempSF INT,FlowHDs INT,NaRatio INT,HCO3Ratio INT,StopTimHEP INT,NoHEP INT,ModeSF INT,CurveUF INT,CurveNa INT,CurveHCO3 INT,CurveCom INT,CurveHE INT,CurveTempHd INT,CurveFlowHds INT,UfRateMax INT,FHEP INT,primeTime INT,primeTotal INT,centralSupply INT,useFilter INT);").arg(DB_PatientCureParameterTable);

    Exec(cmd);

}

/**********************************************************************************
函数名：         saveCurePDataToDB()
功能描述：       保存患者治疗参数到数据库
输入参数：       cure----结构体cureP
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::saveCurePDataToDB(struct CureP cure)
{
    createPatientCureDBTable();

    QString cmd=QString("INSERT INTO %1  (id_card,UfObj,CureTime,TempHps,FlowHEP,TotalSF,TempSF,FlowHDs,NaRatio,HCO3Ratio,StopTimHEP,NoHEP,ModeSF,CurveUF,CurveNa,CurveHCO3,CurveCom,CurveHE,CurveTempHd,CurveFlowHds,UfRateMax,FHEP,primeTime,primeTotal,centralSupply,useFilter) VALUES(%2,%3,'%4',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27);").arg(DB_PatientCureParameterTable).arg(cure.id_card).arg(cure.UfObj).arg(cure.CureTime).arg(cure.TempHps).arg(cure.FlowHEP).arg(cure.TotalSF).arg(cure.TempSF).arg(cure.FlowHDs).arg(cure.NaRatio).arg(cure.HCO3Ratio).arg(cure.StopTimHEP).arg(cure.NoHEP).arg(cure.ModeSF).arg(cure.CurveUF).arg(cure.CurveNa).arg(cure.CurveHCO3).arg(cure.CurveCom).arg(cure.CurveHE).arg(cure.CurveTempHd).arg(cure.CurveFlowHds).arg(cure.UfRateMax).arg(cure.FHEP).arg(cure.primeTime).arg(cure.primeTotal).arg(cure.centralSupply).arg(cure.useFilter);

    Exec(cmd);

}

/**********************************************************************************
函数名：         getCurePDataFromDBTable()
功能描述：       从数据库中获取患者治疗参数数据
输入参数：       id_card----身份证号
输出参数：       data
返回值：        QVector<cureP>
**********************************************************************************/
QVector <CureP>Sqlbase::getCurePDataFromDBTable(const int id_card)
{
    QVector<CureP>data;
    CureP cure;

    createPatientCureDBTable();

    QString cmd = QString("SELECT * FROM %1 WHERE id_card = %2;").arg(DB_PatientCureParameterTable).arg(QString::number(id_card));    //不确定能按顺序读取表字段
    QSqlQuery query = Query(cmd);

    while(query.next())
    {
        cure.id_card=query.value(1).toInt();
        cure.UfObj=query.value(2).toInt();
        cure.CureTime=query.value(3).toInt();
        cure.TempHps=query.value(4).toInt();
        cure.FlowHEP=query.value(5).toInt();
        cure.TotalSF=query.value(6).toInt();
        cure.TempSF=query.value(7).toInt();
        cure.FlowHDs=query.value(8).toInt();
        cure.NaRatio=query.value(9).toInt();
        cure.HCO3Ratio=query.value(10).toInt();
        cure.StopTimHEP=query.value(11).toInt();
        cure.NoHEP=query.value(12).toInt();
        cure.ModeSF=query.value(13).toInt();
        cure.CurveUF=query.value(14).toInt();
        cure.CurveNa=query.value(15).toInt();
        cure.CurveHCO3=query.value(16).toInt();
        cure.CurveCom=query.value(17).toInt();
        cure.CurveHE=query.value(18).toInt();
        cure.CurveTempHd=query.value(19).toInt();
        cure.CurveFlowHds=query.value(20).toInt();
        cure.UfRateMax=query.value(21).toInt();
        cure.FHEP=query.value(22).toInt();
        cure.primeTime=query.value(23).toInt();
        cure.primeTotal=query.value(24).toInt();
        cure.centralSupply=query.value(25).toInt();
        cure.useFilter=query.value(26).toInt();

        data.push_back(cure);
    }

    return data;
}

/**********************************************************************************
函数名：         deleteCurePData()
功能描述：       根据日期删除患者治疗参数数据
输入参数：     id_card----身份证号
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deleteCurePData(const int id_card)
{
    QString cmd = QString("DELETE FROM %1 WHERE id_card = %2;").arg(DB_PatientCureParameterTable).arg(QString::number(id_card));

    Exec(cmd);
}

/**********************************************************************************
函数名：         deleteCurePData()
功能描述：       清空患者治疗参数数据
输入参数：      无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deleteCurePData()
{
    QString cmd = QString("DELETE FROM %1;").arg(DB_PatientCureParameterTable);

    Exec(cmd);
}

/**********************************************************************************
函数名：         CreatePatientInfoDBTable()
功能描述：       创建患者信息表
输入参数：       无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::createPatientInfoDBTable( )
{
    QString cmd;
    cmd=QString("CREATE TABLE IF NOT EXISTS %1(id_card INTEGER PRIMARY KEY,name VARCHAR,sex VARCHAR,height INT,age INT,tel INT,address TEXT);").arg(DB_PatientInfoTable);

    Exec(cmd);

}

/**********************************************************************************
函数名：         SavePatientInfoDataToDB()
功能描述：       保存患者信息到数据库
输入参数：     info----patient_info结构体对象
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::savePatientInfoDataToDB(Patient_info info)
{
    createPatientInfoDBTable();

    QString cmd=QString("INSERT OR REPLACE INTO %1 (id_card,name,sex,height,age,tel,address)VALUES(%2,'%3','%4',%5,%6,%7,'%8');").arg(DB_PatientInfoTable).arg(info.id_card).arg(info.name).arg(info.sex).arg(info.height).arg(info.age).arg(info.tel).arg(info.address);

    Exec(cmd);


}

/**********************************************************************************
函数名：         deletePatientInfoData()
功能描述：       根据身份证删除患者信息
输入参数：     id_card----身份证
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deletePatientInfoData(const int id_card)
{
    QString cmd = QString("DELETE FROM %1 WHERE id_card = %2;").arg(DB_PatientInfoTable).arg(QString::number(id_card));

    Exec(cmd);
}

/**********************************************************************************
函数名：         deletePatientInfoData()
功能描述：       清空患者信息
输入参数：     无
输出参数：       无
返回值：        无
**********************************************************************************/
void Sqlbase::deletePatientInfoData()
{
    QString cmd = QString("DELETE FROM %1;").arg(DB_PatientInfoTable);

    Exec(cmd);
}

/**********************************************************************************
函数名：         getPatientInfoDataFromDBTable()
功能描述：       根据身份证获取患者信息
输入参数：     id_card----身份证
输出参数：       data
返回值：        QVector <patient_info>
**********************************************************************************/
QVector<Patient_info>Sqlbase::getPatientInfoDataFromDBTable(const int id_card)
{
    QVector<Patient_info>data;
    Patient_info info;

    QString cmd = QString("SELECT * FROM %1 WHERE id_card = %2;").arg(DB_PatientInfoTable).arg(QString::number(id_card));
    QSqlQuery query = Query(cmd);

    while(query.next())
    {
        info.name=query.value(1).toString();
        info.sex=query.value(2).toString();
        info.id_card=query.value(3).toInt();
        info.height=query.value(4).toInt();
        info.age=query.value(5).toInt();
        info.tel=query.value(6).toInt();
        info.address=query.value(7).toString();

        data.push_back(info);
    }

    return data;

}

/**********************************************************************************
*   destruct function
**********************************************************************************/
Sqlbase::~Sqlbase()
{
    if(db.isOpen())
        db.close();

    QSqlDatabase::removeDatabase("QSQLITE");
    
}
