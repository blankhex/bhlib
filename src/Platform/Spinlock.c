#include <BH/Thread.h>


#if defined(__clang__) || defined(__GNUC__)
/* Using built-ins */
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


void BH_SpinlockLock(int *lock)
{
#if defined(__clang__) || defined(__GNUC__)
    while (__sync_lock_test_and_set(lock, 1));
#elif defined(_WIN32)
    while (InterlockedExchange(lock, 1));
#else
    #error "Spinlocks are not supported"
#endif
}


int BH_SpinlockLockTry(int *lock)
{
#if defined(__clang__) || defined(__GNUC__)
    if (__sync_lock_test_and_set(lock, 1))
        return BH_ERROR;
    return BH_OK;
#elif defined(_WIN32)
    if (InterlockedExchange(lock, 1))
        return BH_ERROR;
    return BH_OK;
#else
    #error "Spinlocks are not supported"
    return BH_NOIMPL;
#endif
}


void BH_SpinlockUnlock(int *lock)
{
#if defined(__clang__) || defined(__GNUC__)
    __sync_lock_release(lock);
#elif defined(_WIN32)
    InterlockedExchange(lock, 0);
#else
    #error "Spinlocks are not supported"
#endif
}
