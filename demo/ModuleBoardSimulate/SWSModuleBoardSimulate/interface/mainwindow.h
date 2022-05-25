#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>

class QPushButton;
class SerialParaDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalSaveSetToFile(QString fileName = "");   //保存设置到文件
    void signalLoadSetFromFile(QString fileName = ""); //从文件加载设置
    void signalRemoveSetFile();                        //清除设置文件

protected:
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void slotActionGroupTriggered(QAction *action);  //机型设置菜单项被触发
    void slotLoadSetFileFinished();                  //加载设置文件完成

private slots:
    void slotCloseWindow();                          //关闭窗口
    void slotConnectStateLabelClicked();             //显示连接状态的Label被点击
    void slotConnectSate(bool, QString);             //接收到连接状态改变
    void slotMachineTypeChanged();                   //机器类型被改变
    void slotMachineTypeClicked();                   //机型被点击
    void on_menuBtn_clicked(bool checked);           //菜单按钮
    void slotSaveActionTriggered();                  //保存设置
    void slotClearActionTriggered();                 //清除设置
    void slotImportActionTriggered();                //导入设置
    void slotExportActionTriggered();                //导出设置

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_sysTrayIcon; //系统托盘图标
    SerialParaDialog *m_serialParaDialog = Q_NULLPTR;  //串口参数对话框
    QMenu *m_sysTrayMenu;        //系统托盘菜单
    QMenu *m_machineSetMenu;     //机型设置菜单
    QMenu *m_setMenu;            //设置菜单
    bool m_clearSetFlag = false; //标记清除设置文件（关机不自动保存设置）
};

#endif // MAINWINDOW_H
