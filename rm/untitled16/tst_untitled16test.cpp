#include <QString>
#include <QtWidgets>
#include <QtTest>

class Untitled16Test : public QObject
{
    Q_OBJECT

public:
    Untitled16Test();

private Q_SLOTS:
    void testCase1();
    void testCase1_data();
};

Untitled16Test::Untitled16Test()
{
}

void Untitled16Test::testCase1()
{
//    QLineEdit lineEdit;

//    QTest::keyClicks(&lineEdit, "hello world");

//    QCOMPARE(lineEdit.text(), QString("hello world"));

    QFETCH(QTestEventList,i);
    QFETCH(QString,o);
    QLineEdit line;
    i.simulate(&line);
//    if(line.text()!=o)
//    {
//        QSKIP("我不需要");
//    }

    QBENCHMARK
    {
        QCOMPARE(line.text(),o);
    }


}

void Untitled16Test::testCase1_data()
{
    QTest::addColumn<QTestEventList>("i");
    QTest::addColumn<QString>("o");

    QTestEventList list1;
    list1.addKeyClicks("a");
    QTest::addRow("char1")<<list1<<"a";

    QTestEventList list2;
    list2.addKeyClicks("a");
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::addRow("char2")<<list2<<" ";
}

QTEST_MAIN(Untitled16Test)

#include "tst_untitled16test.moc"
