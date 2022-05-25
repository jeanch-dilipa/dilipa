#ifndef SYSTEMSELFCHECKITEM_H
#define SYSTEMSELFCHECKITEM_H

/*系统自检项目*/
typedef enum
{
    CHECK_ITEM_OF_WATER_SYSTEM                                                               = 0x00000001,                   //供水
    CHECK_ITEM_OF_BALANCE_SYSTEM                                                             = 0x00000002,                   //平衡腔
    CHECK_ITEM_OF_HEAT_SYSTEM                                                                = 0x00000004,                   //加热系统
    CHECK_ITEM_OF_MIXED_SYSTEM                                                               = 0x00000008,                   //配液系统
    CHECK_ITEM_OF_SUBPRESSURE_SYSTEM                                                         = 0x00000010,                   //负压
    CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM                                                     = 0x00000020,                   //超滤
//    CHECK_ITEM_OF_WEIGHT_SYSTEM                                                              = 0x00000040,                   //称重系统

    CHECK_ITEM_OF_BLOOD_SYSTEM                                                               = 0x00000080,                   //血路系统
    CHECK_ITEM_OF_HEPARIN_SYSTEM                                                             = 0x00000100,                   //抗凝系统
    CHECK_ITEM_OF_MONITOR_SYSTEM                                                             = 0x00000200,                   //监测系统
    CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM                                                         = 0x00000400,                   //阻流夹监测
    CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM                                                      = 0x00000800,                   //补液系统
    CHECK_ITEM_OF_ENDOTOXIN_SYSTEM                                                           = 0x00001000,                   //内毒素滤器
//    CHECK_ITEM_OF_SPEAKER_SYSTEM                                                             = 0x00002000,                    //声音系统

    /*平衡系统自检具体步骤*/
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11                                         = 0x00004000,                   //平衡腔自检第11步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21                                         = 0x00008000,                   //平衡腔自检第21步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1                                       = 0x00008001,                   //平衡腔自检第21-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2                                       = 0x00008002,                   //平衡腔自检第21-2步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22                                         = 0x00010000,                   //平衡腔自检第22步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1                                       = 0x00010001,                   //平衡腔自检第22-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2                                       = 0x00010002,                   //平衡腔自检第22-2步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_31                                         = 0x00020000,                   //平衡腔自检第31步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32                                         = 0x00040000,                   //平衡腔自检第32步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_1                                       = 0x00040001,                   //平衡腔自检第32-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2                                       = 0x00040002,                   //平衡腔自检第32-2步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3                                       = 0x00040003,                   //平衡腔自检第32-3步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4                                       = 0x00040004,                   //平衡腔自检第32-4步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5                                       = 0x00040005,                   //平衡腔自检第32-5步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6                                       = 0x00040006,                   //平衡腔自检第32-6步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33                                         = 0x00080000,                   //平衡腔自检第33步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_1                                       = 0x00080001,                   //平衡腔自检第33-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2                                       = 0x00080002,                   //平衡腔自检第33-2步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3                                       = 0x00080003,                   //平衡腔自检第33-3步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4                                       = 0x00080004,                   //平衡腔自检第33-4步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5                                       = 0x00080005,                   //平衡腔自检第33-5步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6                                       = 0x00080006,                   //平衡腔自检第33-6步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_34                                         = 0x00100000,                   //平衡腔自检第34步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_34_1                                       = 0x00100001,                   //平衡腔自检第34-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_34_2                                       = 0x00100002,                   //平衡腔自检第34-2步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_34_3                                       = 0x00100003,                   //平衡腔自检第34-3步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_34_4                                       = 0x00100004,                   //平衡腔自检第34-4步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_35                                         = 0x00200000,                   //平衡腔自检第35步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_35_1                                       = 0x00200001,                   //平衡腔自检第35-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_35_2                                       = 0x00200002,                   //平衡腔自检第35-2步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_35_3                                       = 0x00200003,                   //平衡腔自检第35-3步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_35_4                                       = 0x00200004,                   //平衡腔自检第35-4步

    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36                                         = 0x00400000,                   //平衡腔自检第36步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1                                       = 0x00400001,                   //平衡腔自检第36-1步
    CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2                                       = 0x00400002,                   //平衡腔自检第36-2步

    /*内毒素自检具体步骤*/
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11                                        = 0x00800000,                   //内毒素自检第11步

    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12                                        = 0x01000000,                   //内毒素自检第12步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1                                      = 0x01000001,                   //内毒素自检第12-1步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2                                      = 0x01000002,                   //内毒素自检第12-2步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3                                      = 0x01000003,                   //内毒素自检第12-3步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4                                      = 0x01000004,                   //内毒素自检第12-4步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5                                      = 0x01000005,                   //内毒素自检第12-5步

    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13                                        = 0x02000000,                   //内毒素自检第13步

    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14                                        = 0x04000000,                   //内毒素自检第14步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14_1                                      = 0x04000001,                   //内毒素自检第14-1步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14_2                                      = 0x04000002,                   //内毒素自检第14-2步

    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15                                        = 0x08000000,                   //内毒素自检第15步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1                                      = 0x08000001,                   //内毒素自检第15-1步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2                                      = 0x08000002,                   //内毒素自检第15-2步
    CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_3                                      = 0x08000003                    //内毒素自检第15-3步

}SystemSelfCheckItemType;


/*系统自检状态及结果*/
typedef enum
{
    SELF_CHECK_DEFAULT                                                                        = 0,
    SELF_CHECK_ON_THE_WAY                                                                     = 1,                           //正在自检
    SELF_CHECK_CORRECT                                                                        = 2,                           //自检通过
    SELF_CHECK_ERROR                                                                          = 3,                           //自检出错
}SystemSelfCheckResultStatusType;


/*自检相关控制变量*/
#define SYSTEM_SELF_CHECK_ABSTATUS_CHECK_TIME                                                 60                             //AB吸管检测时间间隔

#define SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME                                                     1                              //单步判断时间间隔

#define SYSTEM_SELF_CHECK_WATER_CHECK_MAX_TIME                                                11                             //供水系统自检时间
#define FEED_WATER_SELF_CHECK_TIMES                                                           5                              //最大供水检测次数

#define SYSTEM_SELF_CHECK_MONITOR_CHECK_MAX_TIME                                              1                              //监测系统自检时间

#define SYSTEM_SELF_CHECK_BLOOD_CHECK_MAX_TIME                                                50                             //血路系统自检时间

#define SYSTEM_SELF_CHECK_FLUID_CHECK_MAX_TIME                                                50                             //补液系统自检时间

#define SYSTEM_SELF_CHECK_HEPARIN_CHECK_MAX_TIME_SINGLE                                       120                            //抗凝系统自检时间_SINGLE
#define SYSTEM_SELF_CHECK_HEPARIN_CHECK_MAX_TIME_TOTAL                                        240                            //抗凝系统自检时间_TOTAL

#define SYSTEM_SELF_CHECK_CHOKED_CHECK_MAX_TIME_SINGLE                                        1                              //阻流夹自检时间_SINGLE
#define SYSTEM_SELF_CHECK_CHOKED_CHECK_MAX_TIME_TOTAL                                         2                              //阻流夹自检时间_TOTAL

#define SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME                                              331                            //平衡腔自检时间

#define SYSTEM_SELF_CHECK_SUSTION_TIME_21_1                                                   20                             //平衡腔单步检测持续时间间隔_21_1
#define SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_1                                               200                            //平衡腔自检21_1YG2压力
#define SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_1                                               200                            //平衡腔自检21_1YG4压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_21_2                                                   20                             //平衡腔单步检测持续时间间隔_21_2
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_21_2                                      70                             //平衡腔自检21_2DP电压
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_21_2                                      65                             //平衡腔自检21_2YP电压
#define SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_2                                               105                            //平衡腔自检21_2YG2压力
#define SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_2                                               105                            //平衡腔自检21_2YG4压力
#define BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_21_2                                              5                              //平衡腔自检21_2YG2、YG4连续出错次数

#define SYSTEM_SELF_CHECK_SUSTION_TIME_22_2                                                   20                             //平衡腔单步检测持续时间间隔_22_2
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_22_2                                      70                             //平衡腔自检22_2DP电压
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_22_2                                      65                             //平衡腔自检22_2YP电压
#define SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_22_2                                               105                            //平衡腔自检22_2YG2压力
#define SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_22_2                                               105                            //平衡腔自检22_2YG4压力
#define BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_22_2                                              5                              //平衡腔自检22_2YG2、YG4连续出错次数

#define SYSTEM_SELF_CHECK_SUSTION_TIME_31                                                     25                             //平衡腔单步检测持续时间间隔_31

#define SYSTEM_SELF_CHECK_SUSTION_TIME_32_2                                                   30                             //平衡腔单步检测持续时间间隔_32_2
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_32_2                                      80                             //平衡腔自检32_2DP电压
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_2                                               1100                           //平衡腔自检32_2YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_32_3                                                   3                              //平衡腔单步检测读取时间_32_3
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_3                                               900                            //平衡腔自检32_3YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_32_4                                                   25                             //平衡腔单步检测持续时间间隔_32_4
#define SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_32_4                                            60                             //平衡腔自检32_4YG3泄露压力
#define SYSTEM_SELF_CHECK_OPEN_V6_V8_TIME_32_4                                                3                              //平衡腔_32_4开V6、V8等待时间

#define SYSTEM_SELF_CHECK_SUSTION_TIME_32_5                                                   3                              //平衡腔单步检测读取时间_32_5
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_5                                               900                            //平衡腔自检32_5YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_32_6                                                   25                             //平衡腔单步检测持续时间间隔_32_6
#define SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_32_6                                            60                             //平衡腔自检32_6YG3泄露压力

#define SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_2                                                8                              //平衡腔_33_2读YG4等待时间
#define SYSTEM_SELF_CHECK_SUSTION_TIME_33_2                                                   30                             //平衡腔单步检测持续时间间隔_33_2
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_33_2                                      80                             //平衡腔自检33_2YP电压
#define SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_33_2                                               100                            //平衡腔自检33_2YG4压力
#define SYSTEM_SELF_CHECK_CLOSE_V5_V7_TIME_33_2                                               5                              //平衡腔_33_2关V5、V7等待时间
#define SYSTEM_SELF_CHECK_STOP_YP_TIME_33_2                                                   3                              //平衡腔_33_2停YP等待时间

#define SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_3                                                8                              //平衡腔_33_3读YG3等待时间
#define SYSTEM_SELF_CHECK_SUSTION_TIME_33_3                                                   30                             //平衡腔单步检测持续时间间隔_33_3
#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_33_3                                      85                             //平衡腔自检33_3DP电压
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_33_3                                               1000                           //平衡腔自检33_3YG3压力
#define SYSTEM_SELF_CHECK_CLOSE_SV5_SV11_TIME_33_3                                            5                              //平衡腔_33_3关SV5、SV11等待时间
#define SYSTEM_SELF_CHECK_STOP_DP_TIME_33_3                                                   3                              //平衡腔_33_3停DP等待时间

#define SYSTEM_SELF_CHECK_OPEN_V5_V7_TIME_33_4                                                3                              //平衡腔_33_4开V5、V7等待时间

#define SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_5                                                6                              //平衡腔_33_5读YG3等待时间
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_33_5                                               900                            //平衡腔自检33_5YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_33_6                                                   25                             //平衡腔单步检测持续时间间隔_33_6
#define SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_33_6                                            60                             //平衡腔自检33_6YG3泄露压力

#define SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_36_1                                                2                              //平衡腔_36_1读YG3等待时间

#define SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FLOW_36_2                                 4000                           //平衡腔_36_2超滤流量
#define SYSTEM_SELF_CHECK_STOP_HYPERFILTRATION_PUMP_TIME_36_2                                 30                             //平衡腔_36_2停超滤等待时间
#define SYSTEM_SELF_CHECK_YG3_CHANGE_PRESSURE_36_2                                            100                            //平衡腔自检36_2YG3压力变化

#define SYSTEM_SELF_CHECK_SUBPRESSURE_CHECK_MAX_TIME                                          331                            //负压系统自检时间

#define SYSTEM_SELF_CHECK_ULTRATILTRATION_CHECK_MAX_TIME                                      38                             //超滤自检时间

#define SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME                                            322                            //内毒素自检时间
#define BALANCE_CHECK_ENDOTOXIN_JUDGE_TIMES                                                   3                              //内毒素自检连续次数
#define SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_CONTAINUE_TIME_11                                   10                             //内毒素自检时间_11

#define SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_12_1                                      55                             //内毒素自检12_1YP电压
#define SYSTEM_SELF_CHECK_SUSTION_TIME_12_1                                                   90                             //内毒素自检持续时间间隔_12_1
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_1                                              -50                             //内毒素自检12_1YG3压力

#define SYSTEM_SELF_CHECK_OPEN_SV15_TIME_12_2                                                 10                             //内毒素自检12_2开SV15等待时间
#define SYSTEM_SELF_CHECK_SUSTION_TIME_12_2                                                   90                             //内毒素自检持续时间间隔_12_2
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_2                                              -450                            //内毒素自检12_2YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_12_3                                                   5                              //内毒素自检持续时间间隔_12_3

#define SYSTEM_SELF_CHECK_SUSTION_TIME_12_4                                                   15                             //内毒素自检持续时间间隔_12_4
#define SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FPR_12_4                                  400                            //内毒素自检12_4超滤流量
#define SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FPH_12_4                                  3200                           //内毒素自检12_4超滤流量

#define SYSTEM_SELF_CHECK_SUSTION_TIME_12_5                                                   60                             //内毒素自检持续时间间隔_12_5
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_5                                              -350                            //内毒素自检12_5YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_13                                                     2                              //内毒素自检持续时间间隔_13
#define SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_13                                                -250                            //内毒素自检13YG3压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_14                                                     30                             //内毒素自检持续时间间隔_14
#define SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_14                                              70                             //内毒素自检14YG3泄露压力

#define SYSTEM_SELF_CHECK_SUSTION_TIME_15_1                                                   40                             //内毒素自检持续时间间隔_15_1

#define SYSTEM_SELF_CHECK_SUSTION_TIME_15_2                                                   20                             //内毒素自检持续时间间隔_15_2

#define SYSTEM_SELF_CHECK_HEAT_CHECK_MAX_TIME                                                 200                            //加热自检时间
#define SYSTEM_SELF_CHECK_HEAT_CHECK_TARGET_TEMP                                              410                            //加热温度
#define SYSTEM_SELF_CHECK_HEAT_CHECK_MIN_TEMP                                                 340                            //加热有效温度
#define SYSTEM_SELF_CHECK_HEAT_CHECK_CHANGE_TEMP                                              20                             //加热变化温度
#define SYSTEM_SELF_CHECK_HEAT_CHECK_OVER_TIME                                                300                            //加热自检超时时间

#define SYSTEM_SELF_CHECK_MIXED_CHECK_MAX_TIME                                                100                            //配液自检时间

#define SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME                                       5                              //自检压力释放持续时间



#endif // SYSTEMSELFCHECKITEM_H
