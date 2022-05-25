import QtQuick 2.0

QtObject
{
    enum Card_type
    {
        Unopencard = 0x0000,         //未开卡
        Patientcard = 0x6170,        //患者卡
        Maintenancecard = 0x6e65     //维护卡
    }
    enum Gender_type
    {
        Unknown = 0,         //未知
        Man     = 1,         //男
        Woman   = 2          //女
    }
}
