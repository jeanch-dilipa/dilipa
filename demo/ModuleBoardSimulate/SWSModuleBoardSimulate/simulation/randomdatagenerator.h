#ifndef RANDOMDATAGENERATOR_H
#define RANDOMDATAGENERATOR_H

#include <QObject>
#include <QList>
#include <QTimer>

///随机数发生器，可以选择发生范围，精度，变动频率，可以将要变的引用设置到这里，直接更改变量

struct RandomTargetSt
{
    RandomTargetSt(float *target, float min = 0, float max = 0, int prec = 0, bool isFluct = false)
    {
        this->pTargetVal = target;
        this->min = min;
        this->max = max;
        this->prec = prec;
        this->isFluct = isFluct;
    }

    bool operator ==(RandomTargetSt other)
    {
        return (this->pTargetVal == other.pTargetVal);
    }

    float *pTargetVal = Q_NULLPTR; //目标变量地址
    float  min;                    //最小值
    float  max;                    //最大值
    uint   prec;                   //精度（小数点后几位）
    bool   isFluct;                //是否是波动模式（此时min与max代表上下波动值，目标变量填充最终的随机偏移量）
};

class RandomDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit RandomDataGenerator(QObject *parent = nullptr);
    ~RandomDataGenerator();

    void setGeneratorCycle(int time);          //设置随机数发生周期
    void addTarget(RandomTargetSt target);     //添加一个目标
    void removeTarget(RandomTargetSt target);  //删除一个目标
    void clearTarget();                        //清除所有目标

public slots:
    void slotGeneratorTimeout();               //产生随机数时间到

private:
    QList<RandomTargetSt> m_targetList;
    QTimer *m_generatorTimer;
};

#endif // RANDOMDATAGENERATOR_H
