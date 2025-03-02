#ifndef BH_PLATFORM_WIN32_THREAD_H
#define BH_PLATFORM_WIN32_THREAD_H

#include <windows.h>


struct BH_Condition
{
    CONDITION_VARIABLE handle;
};


struct BH_Mutex
{
    CRITICAL_SECTION handle;
};


struct BH_Semaphore
{
    HANDLE handle;
};


struct BH_Thread
{
    HANDLE handle;
};


void BH_TssCleanup(void);


#endif /* BH_PLATFORM_WIN32_THREAD_H */
