#include "dialogs.h"
#include "ui_dialogs.h"
#include "uidialog.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QUrl>
#include <QColor>
#include <QColorDialog>
#include <QRgb>
#include <QMenu>
#include <QFont>
#include <QFontDialog>
#include <QInputDialog>
#include <QTimer>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

dialogs::dialogs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dialogs)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
//    this->setAcceptDrops(false);
    this->setWindowOpacity(0.5);
//    ui->showtext->setAcceptDrops(true);
//    QTimer::singleShot(1000,this,&dialogs::on_getcolor_clicked);
}

void dialogs::mouseMoveEvent(QMouseEvent *event)
{
    if(ismouse)
        move(event->pos()-point+this->pos());
//    qDebug()<<event->pos()<<point<<this->pos();
}

void dialogs::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        ismouse=true;
    point=event->pos();
}

void dialogs::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    ismouse=false;
}

//void dialogs::dropEvent(QDropEvent *event)
//{
//    QList<QUrl> qurl=event->mimeData()->urls();
//    if(qurl.isEmpty())
//        return;
//    foreach(QUrl url,qurl)
//    {
//        QString str=url.toString().right(5);
//        qDebug()<<str;
//        ui->showtext->appendPlainText(url.toLocalFile());

//    }

//}

//void dialogs::dragEnterEvent(QDragEnterEvent *event)
//{
//    //如果为文件，则支持拖放
//    if (event->mimeData()->hasUrls())
//        event->acceptProposedAction();
//}

dialogs::~dialogs()
{
    delete ui;
}

void dialogs::on_close_clicked()
{
    this->close();
}

void dialogs::on_clear_clicked()
{
    ui->showtext->clear();
    qDebug()<<this->width()<<this->height();
}

void dialogs::on_openfile_clicked()
{
    QString path=QDir::currentPath();
    QString filename=QFileDialog::getOpenFileName(this,"openfile",path,"*.*");
    if(!filename.isEmpty())
        ui->showtext->appendPlainText(filename);
//    QFile file(filename);
//    file.open(QIODevice::ReadOnly);
}

void dialogs::on_openfiles_clicked()
{
    QString path=QDir::currentPath();
    QStringList filename=QFileDialog::getOpenFileNames(this,"openfiles",path,"*.*");
    if(!filename.isEmpty())
        foreach(QString str,filename)
            ui->showtext->appendPlainText(str);
}

void dialogs::on_savefile_clicked()
{
    QString path=QDir::currentPath();
    QString filename=QFileDialog::getSaveFileName(this,"savefile",path,"*");
    if(!filename.isEmpty())
        ui->showtext->appendPlainText(filename);
}

void dialogs::on_existdirectory_clicked()
{
    QString path=QApplication::applicationDirPath();
    QString dirfilename=QFileDialog::getExistingDirectory(this,"existdirectory",path,QFileDialog::ShowDirsOnly);
    if(!dirfilename.isEmpty())
        ui->showtext->appendPlainText(dirfilename);
}

void dialogs::on_openurlfile_clicked()
{
    QString path=QDir::currentPath();
    QUrl urlfile=QFileDialog::getOpenFileUrl(this,"openurlfile",path,"*");
    if(!urlfile.isEmpty())
        ui->showtext->appendPlainText(urlfile.toString());
}

void dialogs::on_getcolor_clicked()
{
    QPalette pale=ui->showtext->palette();
    ui->showtext->appendPlainText(QString::number(qRgb(pale.color(QPalette::Base).red(),pale.color(QPalette::Base).green(),pale.color(QPalette::Base).blue()),16));
    QColor color=QColorDialog::getColor(pale.color(QPalette::Base),this,"getcolor");
    if(color.isValid())
    {
        pale.setColor(QPalette::Base,color);
        ui->showtext->setPalette(pale);
    }
    ui->showtext->appendPlainText(QString::number(qRgb(color.red(),color.green(),color.blue()),16));
}

void dialogs::on_showtext_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu=ui->showtext->createStandardContextMenu();
    menu->exec(pos);
}

void dialogs::on_getfont_clicked()
{
    QFont inifont=ui->showtext->font();
    bool isfont=false;
    QFont font=QFontDialog::getFont(&isfont,inifont);
    if(isfont)
        ui->showtext->setFont(font);
}

void dialogs::on_gettext_clicked()
{
    bool isok=false;
    QString str=QInputDialog::getText(this,"text输入","请输入：",QLineEdit::Normal,"text",&isok);
    if(isok&&!str.isEmpty())
        ui->showtext->appendPlainText(str);
}

void dialogs::on_getint_clicked()
{
    bool isok=false;
    int input=QInputDialog::getInt(this,"INT输入","请输入：",ui->showtext->font().pointSize(),1,100,1,&isok);
    if(isok)
    {
        QFont font=ui->showtext->font();
        font.setPointSize(input);
        ui->showtext->setFont(font);
    }
}

void dialogs::on_getdouble_clicked()
{
    bool isok=false;
    double number=QInputDialog::getDouble(this,"DOUBLE输入","请输入：",12.3,-10,20,6,&isok);
//    QString str=QString::number(number,'g',3);
    ui->showtext->appendPlainText(QString::asprintf("%.6f",number));
}

void dialogs::on_getitem_clicked()
{
    bool isok=false;
    QStringList item;
    item<<"a"<<"b"<<"c"<<"d"<<"e";
    QString str=QInputDialog::getItem(this,"选择项","请选择：",item,1,true,&isok);
    if(isok&!str.isEmpty())
        ui->showtext->appendPlainText(str);
}

void dialogs::on_getmultitext_clicked()
{
    bool isok=false;
    QString str=QInputDialog::getMultiLineText(this,"多行文本","请输入：","多行文本",&isok);
    if(isok&!str.isEmpty())
        ui->showtext->appendPlainText(str);
}

void dialogs::on_information_clicked()
{
    QMessageBox::StandardButton stb= QMessageBox::information(this,"information","信息",QMessageBox::Ok|QMessageBox::Yes|QMessageBox::Close,QMessageBox::NoButton);
    if(stb==QMessageBox::Ok)
        ui->showtext->appendPlainText("ok");
//    if(stb==QMessageBox::Yes)
}

void dialogs::on_question_clicked()
{
    QMessageBox::StandardButtons stb=QMessageBox::question(this,"question","问题",QMessageBox::No|QMessageBox::Yes);
    if(stb==QMessageBox::Yes)
        ui->showtext->appendPlainText("yes");
}

void dialogs::on_warning_clicked()
{
    QMessageBox::StandardButtons stb=QMessageBox::warning(this,"warning","警告",QMessageBox::No|QMessageBox::Yes);
    if(stb==QMessageBox::Yes)
        ui->showtext->appendPlainText("yes");
}

void dialogs::on_critical_clicked()
{
    QMessageBox::StandardButtons stb=QMessageBox::critical(this,"critical","危险",QMessageBox::No|QMessageBox::Yes);
    if(stb==QMessageBox::Yes)
        ui->showtext->appendPlainText("yes");
}

void dialogs::on_about_clicked()
{
    QMessageBox::about(this,"关于","关于");
}

void dialogs::on_aboutqt_clicked()
{
    QMessageBox::aboutQt(this,"aboutqt");
}

void dialogs::on_uidialog_clicked()
{
    uiDialog *ud=new uiDialog(this);
    ud->setWindowOpacity(0.8);
    int ret=ud->exec();
    if(ret==QDialog::Accepted)
        ui->showtext->appendPlainText(ud->str);
    else
        ui->showtext->appendPlainText("error");
}
