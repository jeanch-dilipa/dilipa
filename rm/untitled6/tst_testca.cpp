#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class testca : public QObject
{
    Q_OBJECT

public:
    testca();
    ~testca();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_case1_data();

};

testca::testca()
{
}

testca::~testca()
{
}

void testca::initTestCase()
{
    qDebug()<<"start";
}

void testca::cleanupTestCase()
{
    qDebug()<<"stop";
}

void testca::test_case1()
{
    QFETCH(QString,str);
    QFETCH(QString,chr);
    QCOMPARE(str,chr);
    QVERIFY2(true,"failure");
}

void testca::test_case1_data()
{
    QTest::addColumn<QString>("str");
    QTest::addColumn<QString>("chr");
    QTest::addRow("1")<<"jagh"<<"jagh";
    QTest::addRow("2")<<"kdgd"<<"kdgd";
    QTest::addRow("3")<<"jagh"<<"kdgd";
    QTest::addRow("4")<<"jagh"<<"kdgd";
}

QTEST_MAIN(testca)

#include "tst_testca.moc"
