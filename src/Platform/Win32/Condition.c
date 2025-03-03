#include "Thread.h"


BH_Condition *BH_ConditionNew(void)
{
    BH_Condition *condition;

    /* Allocate space for mutex and initialize it */
    condition = malloc(sizeof(BH_Condition));
    if (condition)
    {
        InitializeConditionVariable(&condition->handle);
    }

    return condition;
}


void BH_ConditionFree(BH_Condition *condition)
{
    BH_UNUSED(condition);
}


int BH_ConditionWait(BH_Condition *condition,
                     BH_Mutex *mutex)
{
    return BH_ConditionWaitFor(condition, mutex, INFINITE);
}


int BH_ConditionWaitFor(BH_Condition *condition,
                        BH_Mutex *mutex,
                        uint32_t timeout)
{
    switch (SleepConditionVariableCS(&condition->handle, &mutex->handle, timeout))
    {
        case 0: return BH_ERROR;
        case ERROR_TIMEOUT: return BH_TIMEOUT;
        default: return BH_OK;
    }
}


int BH_ConditionSignal(BH_Condition *condition)
{
    WakeConditionVariable(&condition->handle);
    return BH_OK;
}


int BH_ConditionBroadcast(BH_Condition *condition)
{
    WakeAllConditionVariable(&condition->handle);
    return BH_OK;
}
