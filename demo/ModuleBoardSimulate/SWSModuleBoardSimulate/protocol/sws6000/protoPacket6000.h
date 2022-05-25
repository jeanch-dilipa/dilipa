#include "bloodtrailboardprotocol.h"
#include "ureasensorboardprotocol.h"
#include "liquiddriverboarprotocol.h"
#include "mixultraboardprotocol.h"
#include "heparinpumpboardprotocol.h"
#include "powerboardprotocol.h"
#include "monitoringboardprotocol.h"
#include "bloodtempvolumeboardprotocol.h"
#include "airdetectormoduletypes.h"

//血路板
struct BloodTrailBoardData
{
    TDB_WR0   wr0;    //自检命令
    TDB_WR1   wr1;    //血泵控制命令
    TDB_WR2   wr2;    //补液泵控制命令
    TDB_WR3   wr3;    //阻流夹及静脉壶控制命令
    TDB_WR4   wr4;    //动静脉压力校正命令
    TDB_WR9   wr9;    //升级命令

    TDB_RD0   rd0;    //自检信息
    TDB_RD1   rd1;    //血泵运行参数
    TDB_RD2   rd2;    //补液泵运行参数
    TDB_RD3   rd3;    //传感器及阻流夹状态
    TDB_RD4   rd4;    //动静脉压传感器信息
    TDB_RD5   rd5;    //监控静脉压信息
    TDB_RD7   rd7;    //软硬件版本信息
    TDB_RD8   rd8;    //升级状态信息
};

//水路驱动板
struct LiquidDriverBoardData
{
    LDB_WR0   wr0;    //水路控制命令
    LDB_WR1   wr1;    //加热控制命令
    LDB_WR2   wr2;    //温度校正命令
    LDB_WR3   wr3;    //液压传感器校正命令
    LDB_WR9   wr9;    //升级命令信息

    LDB_RD0   rd0;    //报警标志及传感器信息
    LDB_RD1   rd1;    //水路运行状态参数
    LDB_RD2   rd2;    //温度传感器 WG1/WG5 信息
    LDB_RD3   rd3;    //液压传感器 YG1/YG3 信息
    LDB_RD4   rd4;    //液压传感器 YG2/YG4 信息
    LDB_RD7   rd7;    //版本信息
    LDB_RD8   rd8;    //升级状态信息
};

//配液超滤板
struct MixUltraBoardData
{
    CPB_WR0   wr0;    //配液控制命令
    CPB_WR1   wr1;    //超滤泵控制命令
    CPB_WR2   wr2;    //电导校正控制命令
    CPB_WR9   wr9;    //升级命令信息

    CPB_RD0   rd0;    //配液运行参数
    CPB_RD1   rd1;    //A、B泵运行参数
    CPB_RD2   rd2;    //超率泵运行参数
    CPB_RD3   rd3;    //A电导信息
    CPB_RD4   rd4;    //B电导信息
    CPB_RD5   rd5;    //C电导信息
    CPB_RD6   rd6;    //D电导信息
    CPB_RD7   rd7;    //软硬件版本信息
    CPB_RD8   rd8;    //升级状态信息
};

//肝素板
struct HeparinPumpBoardData
{
    HPB_WR0   wr0;    //控制
    HPB_WR1   wr1;    //追加
    HPB_WR9   wr9;    //升级命令信息

    HPB_RD0   rd0;    //肝素泵运行参数
    HPB_RD1   rd1;    //肝素泵校正信息
    HPB_RD7   rd7;    //版本信息
    HPB_RD8   rd8;    //升级状态信息
};

//电源板
struct PowerBoardData
{
    PB_WR0    wr0;    //电源控制及定时开机命令
    PB_WR9    wr9;    //升级命令信息

    PB_RD0    rd0;    //电源运行参数
    PB_RD7    rd7;    //软硬件版本信息
    PB_RD8    rd8;    //升级状态信息
};

//实时清除率监测板（4000、6000通用）
struct UreaSensorBoardData
{
    US_WR0    wr0;    //实时清除率检测模块控制命令
    US_WR9    wr9;    //升级命令信息

    US_RD0    rd0;    //模块数据
    US_RD7    rd7;    //软硬件版本信息
    US_RD8    rd8;    //升级状态信息
};

//血温血容量板（4000、6000通用）
struct BloodTempVolumeBoardData
{
    BTVSB_WR0 wr0;    //血温传感器校正命令
    BTVSB_WR1 wr1;    //血容量控制命令
    BTVSB_WR2 wr2;    //血容量校正命令
    BTVSB_WR9 wr9;    //升级命令信息

    BTVSB_RD0 rd0;    //血温传感器信息
    BTVSB_RD1 rd1;    //血温传感器校正信息
    BTVSB_RD2 rd2;    //血容量传感器信息
    BTVSB_RD3 rd3;    //血容量传感器校正信息
    BTVSB_RD7 rd7;    //软硬件版本信息
    BTVSB_RD8 rd8;    //升级状态信息
};

//监控板
struct MonitorBoardData
{
    MB_WR0    wr0;    //控制
    MB_WR9    wr9;    //升级命令信息

    MB_RD7    rd7;    //版本信息
    MB_RD8    rd8;    //升级状态信息
};

//空气监测模块板
struct AirDetectorData
{
    AIR_DETECTOR_WR0 wr0;
    AIR_DETECTOR_WR7 wr7;

    AIR_DETECTOR_RD0 rd0;
    AIR_DETECTOR_RD7 rd7;
};

/*6000型模块板数据*/
struct ModuleData6000
{
    BloodTrailBoardData   btd;  //血路板
    LiquidDriverBoardData ldd;  //水路驱动板
    MixUltraBoardData     cpd;  //配液超滤板
    HeparinPumpBoardData  hpd;  //肝素板
    PowerBoardData        pbd;  //电源板
    UreaSensorBoardData   usd;  //实施清除率监测板
    MonitorBoardData      mbd;  //监控板
    AirDetectorData       add;  //空气监测板
};
