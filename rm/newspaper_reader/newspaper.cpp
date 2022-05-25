#include "newspaper.h"

newspaper::newspaper(const QString name):m_name(name)
{

}

void newspaper::send()
{
    emit newspape(m_name);
}
