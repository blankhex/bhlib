#include "Thread.h"


BH_Semaphore *BH_SemaphoreNew(int value)
{
    BH_UNUSED(value);

    return NULL;
}


void BH_SemaphoreFree(BH_Semaphore *semaphore)
{
    BH_UNUSED(semaphore);
}


int BH_SemaphorePost(BH_Semaphore *semaphore)
{
    BH_UNUSED(semaphore);

    return BH_NOIMPL;
}


int BH_SemaphoreWait(BH_Semaphore *semaphore)
{
    BH_UNUSED(semaphore);

    return BH_NOIMPL;
}


int BH_SemaphoreTryWait(BH_Semaphore *semaphore)
{
    BH_UNUSED(semaphore);

    return BH_NOIMPL;
}


int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout)
{
    BH_UNUSED(semaphore);
    BH_UNUSED(timeout);

    return BH_NOIMPL;
}
