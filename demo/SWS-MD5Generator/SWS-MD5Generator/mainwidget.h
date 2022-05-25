#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QLineEdit>
#include <QStatusBar>
#include <QTimer>
#include "generatemd5thread.h"

//自定义的QLabel，定时自动清除信息
class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent) : QLabel(parent), m_timer(new QTimer(this))
    {
        m_timer->setSingleShot(true);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(clear()));
    }

    void showMessage(const QString &text, int timeoutms = 3000)
    {
        setText(text);

        if(timeoutms > 0)
        {
            m_timer->start(timeoutms);
        }
        else
        {
            m_timer->stop();
        }
    }

private:
    QTimer *m_timer;
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    bool eventFilter(QObject * obj, QEvent * event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void signalGenerateMd5(QStringList srcFileList, QString dstFile);

private slots:
    void SLOTaddFileBtnClicked();
    void SLOTsubFileBtnClicked();
    void SLOTgeneratorBtnClicked();
    void SLOTgeneratorFileOpenBtnClicked();
    void SLOTsetMd5PathActionTriggered();
    void SLOTGenerateProcess(int sucessNum, int totalNum, bool finish, QString errorString);

private:
    void refreshListWidgetItem(bool generateMd5Path = false);
    void autoGeneratorMd5Path(const QString &fileName = "");
    void handleBtnEnable();

private:
    void initUi();
    QListWidget *m_fileListWidget;
    QPushButton *m_addFileBtn;
    QPushButton *m_subFileBtn;
    QPushButton *m_generatorBtn;
    QPushButton *m_generatorFileOpenBtn;
    CustomLabel *m_hintMsgLabel;
    QLabel *m_targetLabel;
    QHBoxLayout *m_hLayout_1;
    QHBoxLayout *m_hLayout_2;
    QVBoxLayout *m_vLayout;
    QAction *m_addFileAction;
    QAction *m_subFileAction;
    QAction *m_setMd5PathAction;
    QLineEdit *m_generatorFileLineEdit;

    QStringList m_currentSelectFileList;
    GenerateMd5Thread *m_generateMd5Thread;
};

#endif // MAINWIDGET_H
