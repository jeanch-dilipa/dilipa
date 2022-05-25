#include "randomdatagenerator.h"
#include <cmath>

RandomDataGenerator::RandomDataGenerator(QObject *parent) : QObject(parent)
{
    m_generatorTimer = new QTimer(this);
    connect(m_generatorTimer, &QTimer::timeout, this, &RandomDataGenerator::slotGeneratorTimeout);
    m_generatorTimer->setInterval(1000); //默认1s
}

RandomDataGenerator::~RandomDataGenerator()
{
    if(m_generatorTimer->isActive())
    {
        m_generatorTimer->stop();
    }
}

void RandomDataGenerator::setGeneratorCycle(int time)
{
    m_generatorTimer->setInterval(time);
}

void RandomDataGenerator::addTarget(RandomTargetSt target)
{
    if(!m_targetList.contains(target) && (target.pTargetVal != Q_NULLPTR))
    {
        m_targetList.append(target);

        if(!m_generatorTimer->isActive())
        {
            m_generatorTimer->start();
        }
    }
}

void RandomDataGenerator::removeTarget(RandomTargetSt target)
{
    m_targetList.removeAll(target);

    if(!m_targetList.isEmpty())
    {
        if(!m_generatorTimer->isActive())
        {
            m_generatorTimer->start();
        }
    }
    else
    {
        if(m_generatorTimer->isActive())
        {
            m_generatorTimer->stop();
        }
    }
}

void RandomDataGenerator::clearTarget()
{
    m_targetList.clear();
    if(m_generatorTimer->isActive())
    {
        m_generatorTimer->stop();
    }
}

void RandomDataGenerator::slotGeneratorTimeout()
{
    foreach(RandomTargetSt target, m_targetList)
    {
        if(!target.isFluct)
        {   //产生一个范围内的随机数
            if(target.max > target.min)
            {
                quint32 randomNum = qrand();
                quint32 range = (target.max - target.min) * pow(10, target.prec) + 1;
                *target.pTargetVal = target.min + (randomNum % range)/pow(10, target.prec);
            }
            else
            {
                *target.pTargetVal = target.min;
            }
        }
        else
        {   //基于某个变量的值上下波动
            if(target.min != 0 || target.max != 0)
            {
                quint32 randomNum = qrand();
                quint32 range = (target.min + target.max) * pow(10, target.prec) + 1;
                *target.pTargetVal = (randomNum % range)/pow(10, target.prec) - target.min;
            }
            else
            {
                *target.pTargetVal = 0;
            }
        }
    }
}
