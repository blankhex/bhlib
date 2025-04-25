#ifndef BH_PLATFORM_POSIX_THREAD_H
#define BH_PLATFORM_POSIX_THREAD_H


#include <BH/Thread.h>
#include <unistd.h>
#include <pthread.h>


struct BH_Condition
{
    pthread_cond_t handle;
};


struct BH_Mutex
{
    pthread_mutex_t handle;
};


#if (_POSIX_SEMAPHORES >= 200112L)
#include <semaphore.h>

struct BH_Semaphore
{
    sem_t handle;
};
#else
struct BH_Semaphore
{
    int count;
    int waiters;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
};
#endif


struct BH_Thread
{
    pthread_t handle;
};


void BH_TssCleanup(void);

#endif /* BH_PLATFORM_POSIX_THREAD_H */
