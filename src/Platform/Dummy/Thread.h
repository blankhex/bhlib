#ifndef BH_PLATFORM_DUMMY_THREAD_H
#define BH_PLATFORM_DUMMY_THREAD_H


#include <BH/Thread.h>


struct BH_Condition
{
    int implement;
    int me;
};


struct BH_Mutex
{
    int implement;
    int me;
};


struct BH_Semaphore
{
    int implement;
    int me;
};


struct BH_Thread
{
    int implement;
    int me;
};


#endif /* BH_PLATFORM_DUMMY_THREAD_H */
