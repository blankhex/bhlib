#include "Thread.h"

#include <BH/Thread.h>


BH_Semaphore *BH_SemaphoreNew(int value)
{
    BH_Semaphore *semaphore;

    /* Allocate space for mutex and initialize it */
    semaphore = malloc(sizeof(BH_Semaphore));
    if (semaphore)
    {
        semaphore->handle = CreateSemaphore(NULL, value, 0x7FFF, NULL);
        if (!semaphore->handle)
        {
            free(semaphore);
            return NULL;
        }
    }

    return semaphore;
}


void BH_SemaphoreFree(BH_Semaphore *semaphore)
{
    CloseHandle(semaphore->handle);
    free(semaphore);
}


int BH_SemaphorePost(BH_Semaphore *semaphore)
{
    if (!ReleaseSemaphore(semaphore->handle, 1, NULL))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWait(BH_Semaphore *semaphore)
{
    if (WaitForSingleObject(semaphore->handle, INFINITE))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWaitTry(BH_Semaphore *semaphore)
{
    if (WaitForSingleObject(semaphore->handle, 0))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout)
{
    switch (WaitForSingleObject(semaphore->handle, timeout))
    {
    case 0: return BH_OK;
    case WAIT_TIMEOUT: return BH_TIMEOUT;
    default: return BH_ERROR;
    }
}
