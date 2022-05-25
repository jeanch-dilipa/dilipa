#ifndef UART485_H
#define UART485_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>
#include <QMutex>
#include <QLocalSocket>

#define Uart485App (UART485::instance())

struct SerialParaType
{
    bool                    pipeCom;  //是否使用管道方式通信
    QSerialPort::BaudRate   baud;     //波特率
    QSerialPort::Parity     parity;   //校验位
    QSerialPort::DataBits   dataBits; //数据位
    QSerialPort::StopBits   stopBits; //停止位
    QString                 portName; //端口名
};

class UART485 : public QThread
{    
    Q_OBJECT
public:
    static UART485 *instance();
    static void deInstance();
    ~UART485();

protected:
    void run();

signals:
    //供外部触发（目的为跨线程）
    void connectToSerial(SerialParaType para);      //连接到串口
    void disconnectFromSerial();                    //断开串口

    //供内部触发
    void signalConnectSate(bool,QString name = ""); //发送连接状态和串口号
    void signalRecvWriteCmd(QByteArray);            //接收到写命令
    void signalMachineTypeChanged();                //机器类型改变

private slots:
    void slotConnectToSerial(SerialParaType para);  //连接到串口
    void slotDisconnectFromSerial();                //断开串口
    void slotErrorOccurred(QSerialPort::SerialPortError error); //串口出错
    void slotFrameOver();                           //断帧结束

private:
    explicit UART485();                             //私有化的构造函数
    void recvDataHandle(QByteArray &allData);       //接收数据处理
    QString printByteArray(const QByteArray &ba);   //字节打印十六进制（调试用）
    bool isBoardComOpen(int addr);                  //某板子的通讯是否打开
    void checkMachineTypeChanged(int addr);         //检查机器类型
    void tryToParsePacket(QList<QByteArray> &dstList, QByteArray &srcData); //尝试拆包

private:
    bool m_bPipeCom = false;                        //是否通过管道连接
    QSerialPort *m_serial;                          //串口
    QLocalSocket *m_socket;                         //管道
    QTimer *m_frameTimer;                           //断帧定时器
    QTimer *m_detectMachineOutTimer;                //识别机型超时定时器
    static UART485 *s_instance;                     //自己的实例
    static QMutex s_mutex;                          //互斥量
};

#endif // UART485_H
