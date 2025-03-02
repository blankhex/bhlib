#include "Thread.h"

#include <BH/Thread.h>


BH_Condition *BH_ConditionNew(void)
{
    return NULL;
}


void BH_ConditionFree(BH_Condition *condition)
{
    BH_UNUSED(condition);
}


int BH_ConditionWait(BH_Condition *condition,
                     BH_Mutex *mutex)
{
    BH_UNUSED(condition);
    BH_UNUSED(mutex);

    return BH_NOIMPL;
}


int BH_ConditionWaitFor(BH_Condition *condition,
                        BH_Mutex *mutex,
                        uint32_t timeout)
{
    BH_UNUSED(condition);
    BH_UNUSED(mutex);
    BH_UNUSED(timeout);

    return BH_NOIMPL;
}


int BH_ConditionSignal(BH_Condition *condition)
{
    BH_UNUSED(condition);

    return BH_NOIMPL;
}


int BH_ConditionBroadcast(BH_Condition *condition)
{
    BH_UNUSED(condition);

    return BH_NOIMPL;
}
