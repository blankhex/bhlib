#include "Thread.h"

#include <BH/Thread.h>


BH_Mutex *BH_MutexNew(void)
{
    return NULL;
}


void BH_MutexFree(BH_Mutex *mutex)
{
    BH_UNUSED(mutex);
}


int BH_MutexLock(BH_Mutex *mutex)
{
    BH_UNUSED(mutex);

    return BH_NOIMPL;
}


int BH_MutexUnlock(BH_Mutex *mutex)
{
    BH_UNUSED(mutex);

    return BH_NOIMPL;
}


int BH_MutexLockTry(BH_Mutex *mutex)
{
    BH_UNUSED(mutex);

    return BH_NOIMPL;
}
