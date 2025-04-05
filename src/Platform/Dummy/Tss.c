#include "Thread.h"


int BH_TssCreate(BH_GenericCallback callback)
{
    BH_UNUSED(callback);
    return 0;
}


void *BH_TssRead(int index)
{
    BH_UNUSED(index);
    return NULL;
}


void BH_TssWrite(int index,
                 void *value)
{
    BH_UNUSED(index);
    BH_UNUSED(value);
}
