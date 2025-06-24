#include "Thread.h"

#include <stdlib.h>
#include <errno.h>


BH_Mutex *BH_MutexNew(void)
{
    BH_Mutex *mutex;

    /* Allocate space for mutex and initialize it */
    mutex = malloc(sizeof(BH_Mutex));
    if (mutex && pthread_mutex_init(&mutex->handle, NULL))
    {
        free(mutex);
        return NULL;
    }

    return mutex;
}


void BH_MutexFree(BH_Mutex *mutex)
{
    pthread_mutex_destroy(&mutex->handle);
    free(mutex);
}


int BH_MutexLock(BH_Mutex *mutex)
{
    if (pthread_mutex_lock(&mutex->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_MutexUnlock(BH_Mutex *mutex)
{
    if (pthread_mutex_unlock(&mutex->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_MutexTryLock(BH_Mutex *mutex)
{
    switch (pthread_mutex_trylock(&mutex->handle))
    {
    case 0: return BH_OK;
    case EBUSY: return BH_TIMEOUT;
    default: return BH_ERROR;
    }
}
