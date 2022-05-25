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
