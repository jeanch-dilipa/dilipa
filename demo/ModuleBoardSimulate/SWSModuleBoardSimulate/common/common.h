#ifndef COMMON_H
#define COMMON_H

#define SOFT_VERSION "V1.12"

//定义机器类型
enum MachineType
{
    AutoDetectMachine = 0x00,  //自动检测机型，作为设置机型使用
    NoneMachine       = 0x00,  //未检测到机型，自动检测机型时使用
    SWS4000           = 0x01,
    SWS6000           = 0x02,
    AllMachine        = (SWS4000 | SWS6000)
};

#endif // COMMON_H
