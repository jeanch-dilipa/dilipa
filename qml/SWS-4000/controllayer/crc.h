
/*******************************************************************************
Copyright (c) 2012,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    crc.h
作者：    lp
版本：    V1.0
日期：    2012-03-30
摘要：    CRC类的头文件
********************************************************************************/

#ifndef CRC_H
#define CRC_H

class CRC
{
public:
        CRC(unsigned char *base, unsigned short len);
        ~CRC();

public:
        unsigned short Sum();

private:
        unsigned char                   *m_frame;
        unsigned short                  m_length;
        static const unsigned char      s_aucCRCHi[];
        static const unsigned char      s_aucCRCLo[];
        bool                            m_canDoCrc;
};

#endif /* CRC_H_ */
