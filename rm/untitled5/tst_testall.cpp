#include <QtTest>

// add necessary includes here

class testall : public QObject
{
    Q_OBJECT

public:
    testall();
    ~testall();

private slots:
    void test_case1();
    void printf();

};

testall::testall()
{

}

testall::~testall()
{

}

void testall::test_case1()
{

}

void testall::printf()
{
    QString str="dsd";
    QBENCHMARK//简单性能测试
    {
        qDebug()<<str;
    }
    QVERIFY2(true,"failure");
}

QTEST_APPLESS_MAIN(testall)

#include "tst_testall.moc"
