#include "testclass.h"

TestClass *TestClass::s_test_class = nullptr;
QMutex *TestClass::s_lock = nullptr;

TestClass::TestClass(const QString* name)
{
    m_name = name;
}

QString TestClass::getM_name()
{
    return *m_name;
}

TestClass *TestClass::initTestClass(const QString* name)
{
    if(nullptr != s_test_class)
    {
        QMutexLocker locker(s_lock);
        if(nullptr != s_test_class)   //线程安全需要不处理CppCheck警告
        {
            s_test_class = new TestClass(name);
        }
    }

    return s_test_class;
}
