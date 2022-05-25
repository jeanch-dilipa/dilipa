import QtQuick 2.0
import QtQml 2.3

QtObject
{
    enum ControlInterface
    {
        Selfinspection                                                                           = 0,                            //自检
        Schema                                                                                   = 1,                            //模式选择
        Intend                                                                                   = 2,                            //准备
        Install                                                                                  = 3,                            //参数设置
        Treat                                                                                    = 4,                            //治疗
        Deplane                                                                                  = 5,                            //下机
        Disinfection                                                                             = 6,                            //清洗消毒
        Correct                                                                                  = 7,                            //校正
        Detect                                                                                   = 8                             //检测
    }


    /*系统自检项目*/
    enum SystemSelfCheckItemType
    {
        CHECK_ITEM_OF_WATER_SYSTEM                                                               = 0x00000001,                   //供水
        CHECK_ITEM_OF_BALANCE_SYSTEM                                                             = 0x00000002,                   //平衡腔
        CHECK_ITEM_OF_HEAT_SYSTEM                                                                = 0x00000004,                   //加热系统
        CHECK_ITEM_OF_MIXED_SYSTEM                                                               = 0x00000008,                   //配液系统
        CHECK_ITEM_OF_SUBPRESSURE_SYSTEM                                                         = 0x00000010,                   //负压
        CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM                                                     = 0x00000020,                   //超滤
//        CHECK_ITEM_OF_WEIGHT_SYSTEM                                                              = 0x00000040,                   //称重系统

        CHECK_ITEM_OF_BLOOD_SYSTEM                                                               = 0x00000080,                   //血路系统
        CHECK_ITEM_OF_HEPARIN_SYSTEM                                                             = 0x00000100,                   //抗凝系统
        CHECK_ITEM_OF_MONITOR_SYSTEM                                                             = 0x00000200,                   //监测系统
        CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM                                                         = 0x00000400,                   //阻流夹监测
        CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM                                                      = 0x00000800,                   //补液系统
        CHECK_ITEM_OF_ENDOTOXIN_SYSTEM                                                           = 0x00001000,                   //内毒素滤器
//        CHECK_ITEM_OF_SPEAKER_SYSTEM                                                             = 0x00002000                    //声音系统

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

    }

    /*系统自检状态及结果*/
    enum SystemSelfCheckResultStatusType
    {
        SELF_CHECK_DEFAULT                                              = 0,
        SELF_CHECK_ON_THE_WAY                                           = 1,                           //正在自检
        SELF_CHECK_CORRECT                                              = 2,                           //自检通过
        SELF_CHECK_ERROR                                                = 3                            //自检出错
    }
}
