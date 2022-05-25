#include <QtTest/QtTest>
#include <QTest>
#include "QtWidgets/QtWidgets"
#include "QTestEvent"
#include "QTestEventList"
// add necessary includes here

class TestQstring : public QObject
{
    Q_OBJECT

public:
    TestQstring();
    ~TestQstring();

private slots:
    void test_case1();
    void toLower();
    void toLower_data();

    void toUpper();

    void toTestUI();
    void toTestUI_data();
};

TestQstring::TestQstring()
{

}

TestQstring::~TestQstring()
{

}

void TestQstring::test_case1()
{

}


void TestQstring::toUpper()
{
    QString str = "test";
    QVERIFY(str.toUpper() == "TEST");
    QVERIFY(str.toUpper() == "test");
    QVERIFY(str.toUpper() == "Test");
}

void TestQstring::toLower()
{
    QFETCH(QString, string);
    QFETCH(QString, result);
    QVERIFY(string.toLower() == result);
}

void TestQstring::toLower_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    QTest::newRow("allLower") << "test" << "test";
    QTest::newRow("mixed") << "Test" << "Test";
    QTest::newRow("allUpper") << "TEST" << "test";
}

void TestQstring::toTestUI()
{
    QFETCH(QTestEventList, e);
    QFETCH(QString, result);

    QLineEdit oLineEdit;
    e.simulate(&oLineEdit);
    QVERIFY(oLineEdit.text() == result);
}

void TestQstring::toTestUI_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("result");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("input a") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("input a and backspace") << list2 << "";
}


QTEST_APPLESS_MAIN(TestQstring)

#include "tst_testqstring.moc"
