#include "Thread.h"


BH_Thread *BH_ThreadNew(size_t stack,
                        BH_ThreadCallback callback,
                        void *data)
{
    BH_UNUSED(stack);
    BH_UNUSED(callback);
    BH_UNUSED(data);

    return NULL;
}


int BH_ThreadJoin(BH_Thread *thread)
{
    BH_UNUSED(thread);

    return BH_NOIMPL;
}


int BH_ThreadDetach(BH_Thread *thread)
{
    BH_UNUSED(thread);

    return BH_NOIMPL;
}


void BH_ThreadSleep(uint32_t timeout)
{
    BH_UNUSED(timeout);
}
