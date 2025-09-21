#include <BH/Thread.h>
#include <BH/Unit.h>
#include <time.h>


BH_UNIT_TEST(Sleep)
{
    time_t start;

    start = time(NULL);
    BH_ThreadSleep(5000);
    BH_VERIFY(time(NULL) - start >= 5);

    return 0;
}


BH_UNIT_TEST(Mutex)
{
    BH_Mutex *mutex;

    BH_VERIFY((mutex = BH_MutexNew()) != NULL);
    BH_VERIFY(BH_MutexLock(mutex) == BH_OK);
    BH_VERIFY(BH_MutexTryLock(mutex) != BH_OK);
    BH_VERIFY(BH_MutexUnlock(mutex) == BH_OK);
    BH_VERIFY(BH_MutexTryLock(mutex) == BH_OK);
    BH_VERIFY(BH_MutexUnlock(mutex) == BH_OK);
    BH_MutexFree(mutex);

    return 0;
}


BH_UNIT_TEST(Semaphore)
{
    BH_Semaphore *semaphore;
    time_t start;

    start = time(NULL);
    BH_VERIFY((semaphore = BH_SemaphoreNew(1)) != NULL);
    BH_VERIFY(BH_SemaphoreWait(semaphore) == BH_OK);
    BH_VERIFY(BH_SemaphoreTryWait(semaphore) != BH_OK);
    BH_VERIFY(BH_SemaphoreWaitFor(semaphore, 5000) == BH_TIMEOUT);
    BH_VERIFY(BH_SemaphorePost(semaphore) == BH_OK);
    BH_VERIFY(BH_SemaphoreTryWait(semaphore) == BH_OK);
    BH_VERIFY(BH_SemaphorePost(semaphore) == BH_OK);
    BH_VERIFY(BH_SemaphoreWaitFor(semaphore, 5000) == BH_OK);
    BH_VERIFY(BH_SemaphorePost(semaphore) == BH_OK);
    BH_VERIFY(time(NULL) - start >= 5);
    BH_SemaphoreFree(semaphore);

    return 0;
}


BH_UNIT_TEST(Condition)
{
    BH_Condition *condition;
    BH_Mutex *mutex;
    time_t start;

    start = time(NULL);
    BH_VERIFY((condition = BH_ConditionNew()) != NULL);
    BH_VERIFY((mutex = BH_MutexNew()) != NULL);
    BH_VERIFY(BH_MutexLock(mutex) == BH_OK);
    BH_VERIFY(BH_ConditionWaitFor(condition, mutex, 5000) == BH_TIMEOUT);
    BH_VERIFY(BH_ConditionSignal(condition) == BH_OK);
    BH_VERIFY(BH_ConditionBroadcast(condition) == BH_OK);
    BH_VERIFY(BH_MutexUnlock(mutex) == BH_OK);
    BH_VERIFY(time(NULL) - start >= 5);
    BH_ConditionFree(condition);
    BH_MutexFree(mutex);

    return 0;
}


static int ThreadCallback(void *data)
{
    *(int *)data = 12345;

    return 0;
}


BH_UNIT_TEST(Thread)
{
    BH_Thread *thread;
    int data = 0;

    BH_VERIFY((thread = BH_ThreadNew(0, ThreadCallback, &data)) != NULL);
    BH_VERIFY(BH_ThreadJoin(thread) == BH_OK);
    BH_VERIFY(data == 12345);

    return 0;
}


BH_UNIT_TEST(Spinlock)
{
    int lock = 0;

    BH_SpinlockLock(&lock);
    BH_VERIFY(BH_SpinlockTryLock(&lock) != BH_OK);
    BH_SpinlockUnlock(&lock);
    BH_VERIFY(BH_SpinlockTryLock(&lock) == BH_OK);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Sleep);
    BH_UNIT_ADD(Mutex);
    BH_UNIT_ADD(Semaphore);
    BH_UNIT_ADD(Condition);
    BH_UNIT_ADD(Thread);
    BH_UNIT_ADD(Spinlock);

    return BH_UnitRun();
}
