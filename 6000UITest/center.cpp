#include "center.h"
#include "ui_center.h"

Center::Center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Center)
{
    ui->setupUi(this);

    pal.setColor(QPalette::Background,QColor(230,234,235));
    setPalette(pal);

    ma = new MainWidget(ui->progress_Widget);
    APpre = new PressureMonitor(ui->AP_Widget);
    VPpre = new PressureMonitor(ui->VP_Widget,QColor("#F2E6E6"),QColor("#FF8385"),-700,500,-500,300,-400,"VP");
    TEMPpre = new PressureMonitor(ui->TEMP_Widget,QColor("#E6F2EE"),QColor("#47D187"),-700,500,-300,-100,-200,"TEMP");
}

Center::~Center()
{
    delete ui;
}
