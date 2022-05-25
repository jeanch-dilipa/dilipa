#include "mainwidget.h"

#include <QFileDialog>
#include <QString>
#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QProcess>
#include <QMimeData>

#define APP_VERSION "V2.0" /*软件版本*/

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->initUi();

    connect(m_addFileBtn, SIGNAL(clicked()), this, SLOT(SLOTaddFileBtnClicked()));
    connect(m_subFileBtn, SIGNAL(clicked()), this, SLOT(SLOTsubFileBtnClicked()));
    connect(m_generatorBtn, SIGNAL(clicked()), this, SLOT(SLOTgeneratorBtnClicked()));
    connect(m_addFileAction, SIGNAL(triggered()), this, SLOT(SLOTaddFileBtnClicked()));
    connect(m_subFileAction, SIGNAL(triggered()), this, SLOT(SLOTsubFileBtnClicked()));
    connect(m_setMd5PathAction, SIGNAL(triggered()), this, SLOT(SLOTsetMd5PathActionTriggered()));
    connect(m_generatorFileOpenBtn, SIGNAL(clicked()), this, SLOT(SLOTgeneratorFileOpenBtnClicked()));

    m_generateMd5Thread = new GenerateMd5Thread();
    connect(this, SIGNAL(signalGenerateMd5(QStringList,QString)), m_generateMd5Thread, SLOT(slotGenerateMd5(QStringList,QString)));
    connect(m_generateMd5Thread, SIGNAL(signalGenerateProcess(int,int,bool,QString)), this, SLOT(SLOTGenerateProcess(int,int,bool,QString)));

    m_fileListWidget->setAcceptDrops(true);
    m_fileListWidget->installEventFilter(this);

    handleBtnEnable();
}

MainWidget::~MainWidget()
{
    if(m_generateMd5Thread->isRunning())
    {
        m_generateMd5Thread->quit();
        m_generateMd5Thread->wait();
    }
    delete m_generateMd5Thread;
}

bool MainWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_fileListWidget)
    {
        if(event->type() == QEvent::DragEnter) //拖拽进入
        {
            QDragEnterEvent *dragEnterEvent = static_cast<QDragEnterEvent *> (event);
            dragEnterEvent->setDropAction(Qt::CopyAction);
            dragEnterEvent->accept();
            return true;
        }
        else if(event->type() == QEvent::Drop) //拖拽放下
        {
            QDropEvent *dropEvent = static_cast<QDropEvent *> (event);

            bool isFileOldSelectEmpty = m_currentSelectFileList.isEmpty();

            QList<QUrl> fileUrls = dropEvent->mimeData()->urls();
            foreach (QUrl url, fileUrls)
            {
                QString fileName = url.toLocalFile();
                if(QFileInfo(fileName).isFile())
                {
                    if(!m_currentSelectFileList.contains(fileName))
                    {
                          m_currentSelectFileList.append(fileName);
                    }
                }
            }

            refreshListWidgetItem(isFileOldSelectEmpty);
            return true;
        }

    }

    return false;
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        if(m_currentSelectFileList.isEmpty() == false)
        {
            SLOTsubFileBtnClicked();
        }
    }

    QWidget::keyPressEvent(event);
}

void MainWidget::initUi()
{
    m_fileListWidget = new QListWidget(this);
    m_addFileBtn = new QPushButton(this);
    m_subFileBtn = new QPushButton(this);
    m_generatorBtn = new QPushButton(this);
    m_generatorFileOpenBtn = new QPushButton(this);
    m_hintMsgLabel = new CustomLabel(this);
    m_targetLabel = new QLabel(this);
    m_vLayout = new QVBoxLayout(this);
    m_hLayout_2 = new QHBoxLayout();
    m_hLayout_1 = new QHBoxLayout();
    m_generatorFileLineEdit = new QLineEdit(this);

    m_targetLabel->setText(tr("生成目标："));

    m_addFileBtn->setIcon(QIcon(":/icon_add.png"));
    m_subFileBtn->setIcon(QIcon(":/icon_sub.png"));
    m_addFileBtn->setToolTip(tr("添加文件"));
    m_subFileBtn->setToolTip(tr("移除文件"));

    m_hLayout_1->addWidget(m_targetLabel);
    m_hLayout_1->addWidget(m_generatorFileLineEdit);
    m_hLayout_1->addWidget(m_generatorFileOpenBtn);

    m_hLayout_2->addWidget(m_hintMsgLabel);
    m_hLayout_2->addStretch();
    m_hLayout_2->addWidget(m_addFileBtn);
    m_hLayout_2->addWidget(m_subFileBtn);
    m_hLayout_2->addWidget(m_generatorBtn);

    m_vLayout->addWidget(m_fileListWidget);
    m_vLayout->addLayout(m_hLayout_1);
    m_vLayout->addLayout(m_hLayout_2);

    m_generatorFileOpenBtn->setText(tr("打开"));
    m_generatorBtn->setText(tr("生成"));

    this->setWindowTitle(tr("SWS-MD5生成器_")+APP_VERSION);
    this->resize(600, 350);

    m_addFileAction = new QAction(QIcon(":/icon_add.png"), tr("添加"), m_fileListWidget);
    m_subFileAction = new QAction(QIcon(":/icon_sub.png"), tr("移除"), m_fileListWidget);
    m_setMd5PathAction = new QAction(QIcon(":/icon_right.png"), tr("设置目标文件到本目录"), m_fileListWidget);
    m_fileListWidget->addAction(m_addFileAction);
    m_fileListWidget->addAction(m_subFileAction);
    m_fileListWidget->addAction(m_setMd5PathAction);
    m_fileListWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fileListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //可以按Ctrl多选
}

void MainWidget::SLOTgeneratorFileOpenBtnClicked()
{
    QString md5FileName = m_generatorFileLineEdit->text();

    if(md5FileName.isEmpty())
    {
        m_hintMsgLabel->showMessage(tr("文件名不能为空!"));
        return ;
    }

    if(QFile::exists(md5FileName))
    {
#ifdef Q_OS_LINUX
        QProcess::execute(QString("gedit"), QStringList(md5FileName));
#else
        QProcess::execute(QString("explorer ") + md5FileName);
#endif
    }
    else
    {
        m_hintMsgLabel->showMessage(tr("文件不存在!"));
    }
}

void MainWidget::SLOTsetMd5PathActionTriggered()
{
    autoGeneratorMd5Path(m_fileListWidget->currentItem()->text());
}

void MainWidget::autoGeneratorMd5Path(const QString &fileName)
{
    //自动生成md5文件路径
    QStringList splitList;
    if(!fileName.isEmpty())
    {
        splitList = fileName.split('/');
    }
    else if(!m_currentSelectFileList.isEmpty())
    {
         splitList = m_currentSelectFileList.at(0).split('/');
    }

    if(!splitList.isEmpty())
    {
        splitList.removeLast();
        QString joinStr = "\\";
#ifdef Q_OS_LINUX
        joinStr = "/"; //Linux下用正斜杠，Windows下用反斜杠（反斜杠才能用explorer打开）
#endif
        QString md5Path = splitList.join(joinStr);
        m_generatorFileLineEdit->setText(md5Path + joinStr + "md5.txt");
    }
}

void MainWidget::handleBtnEnable()
{
    m_generatorBtn->setDisabled(m_currentSelectFileList.isEmpty());
    m_subFileBtn->setDisabled(m_currentSelectFileList.isEmpty());
    m_subFileAction->setDisabled(m_currentSelectFileList.isEmpty());
    m_setMd5PathAction->setDisabled(m_currentSelectFileList.isEmpty());
}

void MainWidget::SLOTaddFileBtnClicked()
{
    QStringList selectResult = QFileDialog::getOpenFileNames(this, tr("选择文件"));

    bool isFileOldSelectEmpty = m_currentSelectFileList.isEmpty();

    foreach (QString file, selectResult) {
        if((file.contains("md5.txt", Qt::CaseInsensitive) == false)
            &&(m_currentSelectFileList.contains(file) == false))
        {
            m_currentSelectFileList.append(file);
        }
    }

    refreshListWidgetItem(isFileOldSelectEmpty);
}

void MainWidget::SLOTsubFileBtnClicked()
{
    QList<QListWidgetItem *> selectItems = m_fileListWidget->selectedItems();

    if(selectItems.isEmpty() == false)
    {
        foreach(QListWidgetItem *item, selectItems)
        {
            m_currentSelectFileList.removeOne(item->text());
            m_fileListWidget->takeItem(m_fileListWidget->row(item));
        }

        handleBtnEnable();

        m_hintMsgLabel->clear();
    }
}

void MainWidget::SLOTgeneratorBtnClicked()
{
    if(m_currentSelectFileList.isEmpty())
    {
        return ;
    }

    m_generatorBtn->setDisabled(true);
    m_hintMsgLabel->showMessage(tr("生成中..."), -1);
    m_generateMd5Thread->start(); //开启线程
    emit signalGenerateMd5(m_currentSelectFileList, m_generatorFileLineEdit->text());
}

void MainWidget::SLOTGenerateProcess(int sucessNum, int totalNum, bool finish, QString errorString)
{
    if(finish)
    {
        m_generateMd5Thread->quit();
        m_generatorBtn->setEnabled(true);

        if(errorString.isEmpty())
        {
            m_hintMsgLabel->showMessage(tr("完成     ") + QString(" %1/%2 ").arg(sucessNum).arg(totalNum) + tr("(成功/总数)"), -1);
        }
        else
        {
            m_hintMsgLabel->showMessage(errorString);
        }
    }
    else //没有完成，更新进度
    {
        m_hintMsgLabel->showMessage(tr("生成中...") + QString(" %1/%2 ").arg(sucessNum).arg(totalNum) + tr("(成功/总数)"), -1);
    }
}

void MainWidget::refreshListWidgetItem(bool generateMd5Path)
{
    m_fileListWidget->clear();
    m_fileListWidget->addItems(m_currentSelectFileList);

    handleBtnEnable();

    if(generateMd5Path) //如果原来是空的，现在新增了，就重新生成md5文件路径
    {
        autoGeneratorMd5Path();
    }

    m_hintMsgLabel->clear();
}
