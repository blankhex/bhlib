#include "Thread.h"

#include <stdlib.h>
#include <errno.h>
#include <time.h>


#if (_POSIX_SEMAPHORES >= 200112L)
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
#else
BH_Semaphore *BH_SemaphoreNew(int value)
{
    BH_Semaphore *semaphore;

    /* Allocate space for mutex and initialize it */
    semaphore = malloc(sizeof(BH_Semaphore));
    if (semaphore)
    {
        semaphore->count = value;
        semaphore->waiters = 0;

        if (pthread_mutex_init(&semaphore->mutex, NULL))
        {
            free(semaphore);
            return NULL;
        }

        if (pthread_cond_init(&semaphore->condition, NULL))
        {
            pthread_mutex_destroy(&semaphore->mutex);
            free(semaphore);
            return NULL;
        }
    }

    return semaphore;
}


void BH_SemaphoreFree(BH_Semaphore *semaphore)
{
    /* Destroy condition variable and mutex */
    pthread_cond_destroy(&semaphore->condition);
    pthread_mutex_destroy(&semaphore->mutex);
    free(semaphore);
}


int BH_SemaphorePost(BH_Semaphore *semaphore)
{
    /* Increase semaphore value */
    pthread_mutex_lock(&semaphore->mutex);
    semaphore->count++;
    if (semaphore->waiters)
        pthread_cond_signal(&semaphore->condition);
    pthread_mutex_unlock(&semaphore->mutex);

    return BH_OK;
}


int BH_SemaphoreWait(BH_Semaphore *semaphore)
{
    int result;

    /* Wait until semaphore count is not zero */
    result = BH_ERROR;
    pthread_mutex_lock(&semaphore->mutex);
    semaphore->waiters++;
    while (!semaphore->count)
        pthread_cond_wait(&semaphore->condition, &semaphore->mutex);
    semaphore->waiters--;
    semaphore->count--;
    pthread_mutex_unlock(&semaphore->mutex);

    return result;
}


int BH_SemaphoreWaitTry(BH_Semaphore *semaphore)
{
    int result;

    result = BH_OK;

    /* Check if semaphore count is not zero and decrement it */
    pthread_mutex_lock(&semaphore->mutex);
    if (!semaphore->count)
        result = BH_ERROR;
    else
        semaphore->count--;
    pthread_mutex_unlock(&semaphore->mutex);

    return result;
}


int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout)
{
    int result;
    struct timespec ts;

    /* Setup timeout */
    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout - ts.tv_sec * 1000) * 1000000;
    result = BH_OK;

    /* Wait until semaphore count is not zero or timeout */
    pthread_mutex_lock(&semaphore->mutex);
    semaphore->waiters++;
    while (!semaphore->count && result == BH_OK)
    {
        switch (pthread_cond_timedwait(&semaphore->condition, &semaphore->mutex, &ts))
        {
        case 0: result = BH_OK; break;
        case ETIMEDOUT: result = BH_TIMEOUT; break;
        default: result = BH_ERROR; break;
        }
    }
    semaphore->waiters--;

    /* If everything went fine - decrement semaphore counter */
    if (!result)
        semaphore->count--;

    pthread_mutex_unlock(&semaphore->mutex);

    return result;
}
#endif
