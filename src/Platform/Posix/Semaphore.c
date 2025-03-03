#include "Thread.h"

#include <stdlib.h>
#include <errno.h>
#include <time.h>


BH_Semaphore *BH_SemaphoreNew(int value)
{
    BH_Semaphore *semaphore;

    /* Allocate space for mutex and initialize it */
    semaphore = malloc(sizeof(BH_Semaphore));
    if (semaphore && sem_init(&semaphore->handle, 0, value))
    {
        free(semaphore);
        return NULL;
    }

    return semaphore;
}


void BH_SemaphoreFree(BH_Semaphore *semaphore)
{
    sem_destroy(&semaphore->handle);
    free(semaphore);
}


int BH_SemaphorePost(BH_Semaphore *semaphore)
{
    if (sem_post(&semaphore->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWait(BH_Semaphore *semaphore)
{
    if (sem_wait(&semaphore->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWaitTry(BH_Semaphore *semaphore)
{
    if (sem_trywait(&semaphore->handle))
        return BH_ERROR;

    return BH_OK;
}


int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout)
{
    struct timespec ts;

    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout - ts.tv_sec * 1000) * 1000000;

    switch (sem_timedwait(&semaphore->handle, &ts))
    {
        case 0: return BH_OK;
        case ETIMEDOUT: return BH_TIMEOUT;
        default: return BH_ERROR;
    }
}
