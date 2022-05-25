#include <QtTest>
#include <QCoreApplication>
#include "QtWidgets/QLineEdit"

class tgui : public QObject
{
    Q_OBJECT

public:
    tgui();
    ~tgui();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

tgui::tgui()
{

}

tgui::~tgui()
{

}

void tgui::initTestCase()
{

}

void tgui::cleanupTestCase()
{

}

void tgui::test_case1()
{
    QLineEdit *lineEdit;
    //QTest::keyClick();
    QCOMPARE(lineEdit->text(),'a');
}

QTEST_MAIN(tgui)

#include "tst_tgui.moc"
