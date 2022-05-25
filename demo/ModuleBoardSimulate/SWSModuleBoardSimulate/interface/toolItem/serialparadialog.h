#ifndef SERIALPARADIALOG_H
#define SERIALPARADIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include "interface/commonItem/custommessagelabel.h"

class SerialParaDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SerialParaDialog(QWidget *parent = 0);
    ~SerialParaDialog();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void slotConnectBtnClicked();
    void slotConnectSate(bool isConnect);
    void slotCommuWayCbxChanged(int index); //通信方式下拉框选项修改

private:
    inline void initUI();  //初始化界面
    void updatePortName(); //更新串口名

private:
    QStackedWidget *m_stackWidget;
    QLabel *m_commuWayLbl;
    QLabel *m_baudRateLbl;
    QLabel *m_parityBitsLbl;
    QLabel *m_dataBitsLbl;
    QLabel *m_stopBitsLbl;
    QLabel *m_portNameLbl;
    QLabel *m_portNameLbl2;

    QComboBox *m_commuWayCbx;
    QComboBox *m_baudRateCbx;
    QComboBox *m_parityBitsCbx;
    QComboBox *m_dataBitsCbx;
    QComboBox *m_stopBitsCbx;
    QComboBox *m_portNameCbx;

    QLineEdit *m_portNameEdit;

    QPushButton *m_connectBtn;

    QGridLayout *m_gridLayout;
    QHBoxLayout *m_hLayout;
    QHBoxLayout *m_hLayout1;
    QHBoxLayout *m_hLayout2;
    QVBoxLayout *m_vLayout;

    CustomMessageLabel *m_msgLbl;

    QStringList m_portNameList; //当前的串口名列表
    int m_connectState = 0; //标记连接状态，0--未连接，1--连接中，2--已连接
};

#endif // SERIALPARADIALOG_H
