#include <QApplication>
#include "interface/mainwindow.h"
#include "uart/uart485.h"
#include "simulation/simulationmanager.h"
#ifdef Q_OS_LINUX
#include <QStyleFactory>
#endif

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

#ifdef Q_OS_LINUX
    a.setStyle(QStyleFactory::create("fusion"));
#endif

    qRegisterMetaType<SerialParaType>("SerialParaType");

    //运行串口管理线程
    Uart485App->start();

    //运行数据模拟管理线程
    SimulationManager sim;
    sim.start();

    QObject::connect(Uart485App, &UART485::signalRecvWriteCmd, &sim, &SimulationManager::slotRecvWriteCmd);

    //主界面
    MainWindow mw;
    QObject::connect(&mw, &MainWindow::signalSaveSetToFile, &sim, &SimulationManager::slotSaveSetToFile);
    QObject::connect(&mw, &MainWindow::signalLoadSetFromFile, &sim, &SimulationManager::slotLoadSetFromFile);
    QObject::connect(&mw, &MainWindow::signalRemoveSetFile, &sim, &SimulationManager::slotRemoveSetFile);
    QObject::connect(&sim, &SimulationManager::signalLoadSetFileFinished, &mw, &MainWindow::slotLoadSetFileFinished);
    emit mw.signalLoadSetFromFile(); //开机自动加载设置
    mw.show();

    return a.exec();
}
