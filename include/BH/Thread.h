#ifndef BH_THREAD_H
#define BH_THREAD_H


#include "Common.h"


#define BH_MAX_TSS      128


typedef struct BH_Lock BH_Lock;
typedef struct BH_Thread BH_Thread;
typedef struct BH_Mutex BH_Mutex;
typedef struct BH_Semaphore BH_Semaphore;
typedef struct BH_Condition BH_Condition;
typedef int (*BH_ThreadCallback)(void *);



BH_Thread *BH_ThreadNew(size_t stack,
                        BH_ThreadCallback callback,
                        void *data);



int BH_ThreadJoin(BH_Thread *thread);



int BH_ThreadDetach(BH_Thread *thread);



BH_Mutex *BH_MutexNew(void);



void BH_MutexFree(BH_Mutex *mutex);



int BH_MutexLock(BH_Mutex *mutex);



int BH_MutexUnlock(BH_Mutex *mutex);



int BH_MutexLockTry(BH_Mutex *mutex);



BH_Semaphore *BH_SemaphoreNew(int value);



void BH_SemaphoreFree(BH_Semaphore *semaphore);



int BH_SemaphorePost(BH_Semaphore *semaphore);



int BH_SemaphoreWait(BH_Semaphore *semaphore);



int BH_SemaphoreWaitTry(BH_Semaphore *semaphore);



int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout);



BH_Condition *BH_ConditionNew(void);



void BH_ConditionFree(BH_Condition *condition);



int BH_ConditionWait(BH_Condition *condition,
                     BH_Mutex *mutex);



int BH_ConditionWaitFor(BH_Condition *condition,
                        BH_Mutex *mutex,
                        uint32_t timeout);



int BH_ConditionSignal(BH_Condition *condition);



int BH_ConditionBroadcast(BH_Condition *condition);



void BH_SpinlockLock(int *lock);



int BH_SpinlockLockTry(int *lock);



void BH_SpinlockUnlock(int *lock);



int BH_TssCreate(BH_GenericCallback callback);



void *BH_TssRead(int index);



void BH_TssWrite(int index,
                 void *value);


#endif /* BH_THREAD_H */
