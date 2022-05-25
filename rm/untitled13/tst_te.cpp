#include <QtTest>
#include <QCoreApplication>
#include <QTestEventList>
#include <QTest>
#include <QtGui>

// add necessary includes here

class te : public QObject
{
    Q_OBJECT

public:
    te();
    ~te();

private slots:
    void test_case1();
    void test_case1_data();

};

te::te()
{

}

te::~te()
{

}

void te::test_case1()
{
    QFETCH(QTestEventList, event);

    QFETCH(QString, result);

    QLineEdit lineEdit;

    event.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), result);
}

void te::test_case1_data()
{
    QTest::addColumn<QTestEventList>("event");

    QTest::addColumn<QString>("result");


    QTestEventList list1;

    list1.addKeyClicks("hello world");

    QTest::newRow("item 0 ")<<list1<<QString("hello world");


    QTestEventList list2;

    list2.addKeyClicks("abs0");

    list2.addKeyClick(Qt::Key_Backspace);

    QTest::newRow("item 1")<<list2<<QString("abs");
}

QTEST_MAIN(te)

#include "tst_te.moc"
