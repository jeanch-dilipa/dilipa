#include <QtTest>
#include <QCoreApplication>
#include "win.h"
// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_case1_data();

};

test::test()
{

}

test::~test()
{

}

void test::initTestCase()
{

}

void test::cleanupTestCase()
{

}

void test::test_case1()
{
    QFETCH(QString,a);
    win *w=new win();
    QCOMPARE(w->printf(),a);
}

void test::test_case1_data()
{
    QTest::addColumn<QString>("a");
    QTest::addRow("1")<<"hash";
    QTest::addRow("2")<<"dsjg";
    QTest::addRow("3")<<"sdfd";
    QTest::addRow("4")<<"fgvdf";

}

QTEST_MAIN(test)

#include "tst_test.moc"
