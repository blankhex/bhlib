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


/**
 * Creates new thread with specified \a stack size, thread \a callback
 * function and \a data.
 *
 * \param stack     Stack size
 * \param callback  Callback function
 * \param data      User data
 *
 * \return On success, returns thread pointer.
 * \return On failure, returns NULL pointer.
 */
BH_Thread *BH_ThreadNew(size_t stack,
                        BH_ThreadCallback callback,
                        void *data);


/**
 * Joins the specified \a thread.
 *
 * \param thread  Thread
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ThreadJoin(BH_Thread *thread);


/**
 * Detaches the specified \a thread.
 *
 * \param thread  Thread
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ThreadDetach(BH_Thread *thread);


/**
 * Creates new mutex.
 *
 * \return On success, returns mutex pointer.
 * \return On failure, returns NULL pointer.
 */
BH_Mutex *BH_MutexNew(void);


/**
 * Frees the \a mutex.
 *
 * \param mutex  Mutex
 */
void BH_MutexFree(BH_Mutex *mutex);


/**
 * Locks the \a mutex.
 *
 * \param mutex  Mutex
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_MutexLock(BH_Mutex *mutex);


/**
 * Unlocks the \a mutex.
 *
 * \param mutex  Mutex
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_MutexUnlock(BH_Mutex *mutex);


/**
 * Tries to lock the \a mutex.
 *
 * \param mutex  Mutex
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_MutexLockTry(BH_Mutex *mutex);


/**
 * Creates new semaphore.
 *
 * \param value  Semaphore value
 *
 * \return On success, returns thread pointer.
 * \return On failure, returns NULL pointer.
 */
BH_Semaphore *BH_SemaphoreNew(int value);


/**
 * Frees the \a semaphore.
 *
 * \param semaphore  Semaphore
 */
void BH_SemaphoreFree(BH_Semaphore *semaphore);


/**
 * Posts/increments the \a semaphore.
 *
 * \param semaphore  Semaphore
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_SemaphorePost(BH_Semaphore *semaphore);


/**
 * Waits/decrements the \a semaphore.
 *
 * \param semaphore  Semaphore
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_SemaphoreWait(BH_Semaphore *semaphore);


/**
 * Tries to wait/decrement the \a semaphore.
 *
 * \param semaphore  Semaphore
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_SemaphoreWaitTry(BH_Semaphore *semaphore);


/**
 * Waits/decrements the \a semaphore with \a timeout.
 *
 * If timeout occures, return code will be BH_TIMEOUT.
 *
 * \param semaphore  Semaphore
 * \param timeout    Timeout in milliseconds
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_SemaphoreWaitFor(BH_Semaphore *semaphore,
                        uint32_t timeout);


/**
 * Creates new condition variable.
 *
 * \return On success, returns condition variable pointer.
 * \return On failure, returns NULL pointer.
 */
BH_Condition *BH_ConditionNew(void);


/**
 * Frees the \a condition variable.
 *
 * \param condition  Condition
 */
void BH_ConditionFree(BH_Condition *condition);


/**
 * Unlocks the \a mutex and waits for the \a condition variable.
 *
 * \param condition  Condition variable
 * \param mutex      Mutex
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ConditionWait(BH_Condition *condition,
                     BH_Mutex *mutex);


/**
 * Unlocks the \a mutex and waits for the \a condition variable with \a timeout.
 *
 * If timeout occures, return code will be BH_TIMEOUT.
 *
 * \param condition  Condition variable
 * \param mutex      Mutex
 * \param timeout    Timeout in milliseconds
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ConditionWaitFor(BH_Condition *condition,
                        BH_Mutex *mutex,
                        uint32_t timeout);


/**
 * Signals the \a condition variable.
 *
 * \param condition  Condition variable
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ConditionSignal(BH_Condition *condition);


/**
 * Broadcasts the \a condition variable.
 *
 * \param condition  Condition variable
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_ConditionBroadcast(BH_Condition *condition);


/**
 * Locks the \a spinlock.
 *
 * \param lock  Spinlock
 */
void BH_SpinlockLock(int *lock);


/**
 * Tries to lock the \a spinlock.
 *
 * \param lock  Spinlock
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_SpinlockLockTry(int *lock);


/**
 * Unlocks the \a spinlock.
 *
 * \param lock  Spinlock
 */
void BH_SpinlockUnlock(int *lock);


/**
 * Create new TSS/TLS slot index and destruction \a callback.
 *
 * \param callback  Destruction callback
 *
 * \return On success, returns slot index.
 * \return On failure, returns error code.
 */
int BH_TssCreate(BH_GenericCallback callback);


/**
 * Reads the value associated with the TSS \a index.
 *
 * \param index  TSS index
 *
 * \return Index value
 */
void *BH_TssRead(int index);


/**
 * Writes the \a value to the TSS \a index.
 *
 * \param index  TSS index to
 * \param value  Value
 */
void BH_TssWrite(int index,
                 void *value);


#endif /* BH_THREAD_H */
