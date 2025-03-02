#include "Thread.h"

#include <BH/Thread.h>


BH_Mutex *BH_MutexNew(void)
{
    BH_Mutex *mutex;

    /* Allocate space for mutex and initialize it */
    mutex = malloc(sizeof(BH_Mutex));
    if (mutex && !InitializeCriticalSectionAndSpinCount(&mutex->handle, 0x400))
    {
        free(mutex);
        return NULL;
    }

    return mutex;
}


void BH_MutexFree(BH_Mutex *mutex)
{
    DeleteCriticalSection(&mutex->handle);
    free(mutex);
}


int BH_MutexLock(BH_Mutex *mutex)
{
    EnterCriticalSection(&mutex->handle);

    return BH_OK;
}


int BH_MutexUnlock(BH_Mutex *mutex)
{
    LeaveCriticalSection(&mutex->handle);

    return BH_OK;
}


int BH_MutexLockTry(BH_Mutex *mutex)
{
    if (!TryEnterCriticalSection(&mutex->handle))
        return BH_ERROR;

    return BH_OK;
}
