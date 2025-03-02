#include "Thread.h"

#include <BH/Thread.h>
#include <stdlib.h>
#include <errno.h>


BH_Condition *BH_ConditionNew(void)
{
    BH_Condition *condition;

    /* Allocate space for mutex and initialize it */
    condition = malloc(sizeof(BH_Condition));
    if (condition && pthread_cond_init(&condition->handle, NULL))
    {
        free(condition);
        return NULL;
    }

    return condition;
}


void BH_ConditionFree(BH_Condition *condition)
{
    pthread_cond_destroy(&condition->handle);
    free(condition);
}


int BH_ConditionWait(BH_Condition *condition,
                     BH_Mutex *mutex)
{
    if (pthread_cond_wait(&condition->handle, &mutex->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_ConditionWaitFor(BH_Condition *condition,
                        BH_Mutex *mutex,
                        uint32_t timeout)
{
    struct timespec ts;

    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout - ts.tv_sec * 1000) * 1000000;

    switch (pthread_cond_timedwait(&condition->handle, &mutex->handle, &ts))
    {
    case 0: return BH_OK;
    case ETIMEDOUT: return BH_TIMEOUT;
    default: return BH_ERROR;
    }
}


int BH_ConditionSignal(BH_Condition *condition)
{
    if (pthread_cond_signal(&condition->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_ConditionBroadcast(BH_Condition *condition)
{
    if (pthread_cond_broadcast(&condition->handle))
        return BH_ERROR;

    return BH_OK;
}
