#include <QtWidgets>
#include <QtTest/QtTest>

// add necessary includes here

class testgui : public QObject
{
    Q_OBJECT

private slots:
    void test_case1();

};

void testgui::test_case1()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_MAIN(testgui)

#include "tst_testgui.moc"
