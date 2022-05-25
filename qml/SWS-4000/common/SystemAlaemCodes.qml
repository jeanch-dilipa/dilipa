import QtQml 2.3

QtObject
{
    enum SystemAlarmCodeType
    {
        SYSTEM_ERROR_CODE_DEFAULT                                            = 0,                     //无报警
        SYSTEM_ERROR_CODE_MODULE_BORD_ERROR                                  = 1,                     //全部模块板通信错误
        SYSTEM_ERROR_CODE_DATABASE_OPEN_ERROR                                = 2,                     //数据库打开失败
        SYSTEM_ERROR_CODE_DATABASE_READ_ERROR                                = 3,                     //数据库操作失败
        SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B                  = 4,                     //请将A、B液吸管插入A、B液中
        SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A                      = 5,                     //请将A液吸管插入A液中
        SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B                      = 6,                     //请将B液吸管插入B液中
        SYSTEM_ERROR_CODE_JQ_YJ1_JK_SELF_CHECK                               = 7,                     //进水罐故障
        SYSTEM_ERROR_CODE_FEED_WATER_SELF_CHECK                              = 8,                     //供水不足
        SYSTEM_ERROR_CODE_GAS_SELF_CHECK                                     = 9,                     //空气检测出错
        SYSTEM_ERROR_CODE_BLOOD_LEAK_SELF_CHECK                              = 10,                    //漏血监测自检出错
        SYSTEM_ERROR_CODE_BLOOD_SELF_CHECK                                   = 11,                    //血液监测自检出错
        SYSTEM_ERROR_CODE_BLOOD_PUMP_SELF_CHECK                              = 12,                    //血路系统自检出错
        SYSTEM_ERROR_CODE_FLUID_INFUSION_PUMP_SELF_CHECK                     = 13,                    //补液系统自检出错
        SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_BOM                    = 14,                    //肝素泵自检不能到底
        SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_TOP                    = 15,                    //肝素泵自检不能到顶
        SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK                     = 16,                    //阻流夹自检错误
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100                    = 17,                    //YJ2和YJ3常亮，请检查负压罐是否有故障
        SYSTEM_NOTICE_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100                   = 18,                    //请可靠连接透析器接头到机器上
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP112                    = 19,                    //XV1故障
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP114                    = 20,                    //XV2故障
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP101                    = 21,                    //请检查齿轮泵DP到电磁阀SV13之间的管路是否堵塞
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP103                    = 22,                    //请检查电磁阀V1、V5是否堵塞
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP102                    = 23,                    //请检查机器外部废液管路是否堵塞或折叠
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP105                    = 24,                    //请检查机器外部废液管路是否堵塞或者折叠
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP107                    = 25,                    //请检查与透析器接头连接的管路是否折叠
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP106                    = 26,                    //请检查电磁阀V3、V7是否堵塞
        SYSTEM_ERROR_CODE_PRESSURE_ERR                                       = 27,                    //压力传感器误差大
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110                    = 28,                    //齿轮泵DP异常
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108                    = 29,                    //V5、V6、V7、V8、SV13、SV14泄漏或周围管路泄漏
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113                    = 30,                    //V2、V4泄漏
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP109                    = 31,                    //齿轮泵YP坏
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111                    = 32,                    //V1、V3、SV3、SV5、SV6、SV11或膜片泄漏
        SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP116                    = 33,                    //超滤泵异常
        SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN120                   = 34,                    //齿轮泵YP坏
        SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121                   = 35,                    //内毒素滤器或与其连接处泄漏了吗？
        SYSTEM_ERROR_CODE_DIALYSATE_TEMPERATURE_SELF_CHECK                   = 36                    //检查加热系统是否正常工作
    }
}
