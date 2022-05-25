#include "aclass.h"

aclass::aclass()
{
}

int aclass::Add(int i, const int j)
{
    i = getNewNum(i);
    return i+j;
}

int aclass::getNewNum(const int i)
{
    return i+5;
}
