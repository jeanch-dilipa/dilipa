#include "sqlbase.h"
#include <iostream>
#include <QTime>
#include <QDate>
#include <QtCore/QCoreApplication>


int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);

  //  HistoryAlarm hb={695,2,2,1,0,1,5,1,1,7,1,1,1,1,1,1,1,10};

    //HistoryAlarm hb={9,3,2,2,1,0,1,5,1,1,7,1,1,1,1,1,1,1,10};

//    historyAlarm hc={7,3,2,"15", "2014",2,1,0,1,5,1,1,7,1,1,1,1,1,1,1,10};

  //  CureP cure={695,5,4,1,2,6,5,4,9,2,1,4,5,3,2,1,5,4,1,5,8,7,5,9,5};
    Patient_info info={456789,"bede","boy",5,7,1,"chongqing"};
    Sqlbase sq(SQL_DATA_BASE_FILE_NAME);

//   sq.saveHistoryAlarmDataToDB(hb);
    //    sq.updateDBData(10,1);
//    sq.updateSystemParameterDBData(DB_SystemParamerTable,"wg1",6,0);
   // sq.getParameterDataFromDBTable(DB_SystemParamerTable,"saveValue");
    //   sq.deletehistoryAlarmData();
 //   sq.getHistoryAlarmDataFromDBTable("2014-02-20",1);
 //     sq.saveCureRTDataToDB(2,999);
 //   sq.getCureRTDataFromDBTable();
 //sq.saveCurePDataToDB(cure);
  //  sq.getCurePDataFromDBTable(1);
 //  sq.deleteCurePData(0);
  sq.savePatientInfoDataToDB(info);
 //   sq.getPatientInfoDataFromDBTable(4);
   // sq.updatePatientInfoDBData("li",4);
 //sq.deletehistoryAlarmData(DB_HistoryAlarmTable,SQL_HISTROY_ALARM_DATA_FILE);
 //   sq.getHistoryAlarmDataFromDBTable(SQL_HISTROY_ALARM_DATA_FILE,DB_HistoryAlarmTable,"2014-02-20",1);

  //  sq.getCommonCurePDataFromDBTable(DB_CommonCureParameterTable,2,SQL_PATIENT_PARAMETER_DATA_FILE);
 //   sq.saveCureRTDataToDB(4,1);
 //   sq.getCureRTDataFromDBTable(DB_CureRealTimeTable);
 // sq.saveCurePDataToDB(DB_PatientCureParameterTable,cure);
  //  sq.getCurePDataFromDBTable(DB_PatientCureParameterTable,1);
 //  sq.deleteCurePData(DB_PatientCureParameterTable,0);
  //  sq.savePatientInfoDataToDB(info);
 //   sq.getPatientInfoDataFromDBTable(DB_PatientInfoTable,4);
   // sq.updatePatientInfoDBData(DB_PatientInfoTable,"li",4);


    a.exec();

}
