#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QString>
#include <QMutex>
#include <QMutexLocker>

class TestClass
{
public:
    static TestClass *initTestClass(const QString* name);
    TestClass() = delete;
    TestClass(const TestClass&) = delete;

    QString getM_name();

protected:
    explicit TestClass(const QString* name);

private:
    const QString*              m_name;

    static TestClass*    s_test_class;
    static QMutex*       s_lock;
};

#endif // TESTCLASS_H
