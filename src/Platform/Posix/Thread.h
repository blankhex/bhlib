#ifndef BH_PLATFORM_POSIX_THREAD_H
#define BH_PLATFORM_POSIX_THREAD_H


#include <pthread.h>
#include <semaphore.h>


struct BH_Condition
{
    pthread_cond_t handle;
};


struct BH_Mutex
{
    pthread_mutex_t handle;
};


struct BH_Semaphore
{
    sem_t handle;
};


struct BH_Thread
{
    pthread_t handle;
};


void BH_TssCleanup(void);

#endif /* BH_PLATFORM_POSIX_THREAD_H */
