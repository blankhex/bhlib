#ifndef BH_THREAD_H
#define BH_THREAD_H

#include <bh/bh.h>

typedef void (*bh_thread_cb_t)(void *);

#ifdef BH_USE_THREADS
/* Include thread implementation details */
#include <bh/thread_base.h>

#else
/* Otherwise implement stabs */

typedef struct bh_thread_s
{
    void *handle;
} bh_thread_t;

typedef struct bh_mutex_s
{
    void *handle;
} bh_mutex_t;

typedef struct bh_cond_s
{
    void *handle;
} bh_cond_t;

typedef struct bh_tpool_s
{
    void *handle;
} bh_tpool_t;

/**
 * Initialize thread.
 *
 * @param thread  Pointer to the thread
 * @param func    Thread function
 * @parma data    Thread data
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_thread_join, bh_thread_detach, bh_thread_destroy
 */
int bh_thread_init(bh_thread_t *thread,
                   bh_thread_cb_t func,
                   void *data);

/**
 * Initialize thread pool.
 *
 * @param pool  Pointer to the thread pool
 * @param size  Amount of threads
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_tpool_job, bh_tpool_join, bh_tpool_destroy
 */
int bh_tpool_init(bh_tpool_t *pool,
                  size_t size);

#endif

/**
 * Join thread.
 *
 * @param thread  Pointer to the thread
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_thread_detach
 */
int bh_thread_join(bh_thread_t *thread);

/**
 * Detach thread.
 *
 * @param thread  Pointer to the thread
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_thread_join
 */
int bh_thread_detach(bh_thread_t *thread);

/**
 * Destroy thread.
 *
 * @param thread  Pointer to the thread
 */
void bh_thread_destroy(bh_thread_t *thread);

/**
 * Initialize mutex.
 *
 * @param mutex  Pointer to the mutex
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_mutex_lock, bh_mutex_try_lock, bh_mutex_destroy
 */
int bh_mutex_init(bh_mutex_t *mutex);

/**
 * Lock mutex.
 *
 * @param mutex  Pointer to the mutex
 * @return 0 on success, non-zero otherwise
 *
 * @note Locking already locked mutex will block thread until mutex is released
 *
 * @sa bh_mutex_try_lock, bh_mutex_unlock
 */
int bh_mutex_lock(bh_mutex_t *mutex);

/**
 * Try to lock mutex.
 *
 * @param mutex  Pointer to the mutex
 * @return 0 on success, positive value if mutex is locked, negative value on error
 *
 * @sa bh_mutex_lock, bh_mutex_unlock
 */
int bh_mutex_try_lock(bh_mutex_t *mutex);

/**
 * Unlock mutex.
 *
 * @param mutex  Pointer to the mutex
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_mutex_lock, bh_mutex_try_lock
 */
int bh_mutex_unlock(bh_mutex_t *mutex);

/**
 * Destory mutex.
 *
 * @param mutex  Pointer ot the mutex
 */
void bh_mutex_destroy(bh_mutex_t *mutex);

/**
 * Initialize condition variable
 *
 * @param cond  Pointer to the condition variable
 * @return 0 on success, non-zero otherwise
 */
int bh_cond_init(bh_cond_t *cond);

/**
 * Block on conditional variable.
 *
 * @param cond   Pointer to the condition variable
 * @param mutex  Pointer to the mutex
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_cond_wait_for, bh_cond_signal, bh_cond_broadcast
 */
int bh_cond_wait(bh_cond_t *cond,
                 bh_mutex_t *mutex);

/**
 * Block on condtional variable for a period of the time.
 *
 * @param cond     Pointer to the condtion variable
 * @param mutex    Pointer to the mutex
 * @param timeout  Timeout in miliseconds
 * @return 0 on success, positive value on timeout, negative on error
 *
 * @sa bh_cond_wait, bh_cond_signal, bh_cond_broadcast
 */
int bh_cond_wait_for(bh_cond_t *cond,
                     bh_mutex_t *mutex,
                     unsigned long timeout);

/**
 * Unblock (notify) thread.
 *
 * @param cond  Pointer to the condition variable
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_cond_broadcast, bh_cond_wait, bh_cond_wait_for
 */
int bh_cond_signal(bh_cond_t *cond);

/**
 * Unblock all threads.
 *
 * @param cond  Pointer to the condtion variable
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_cond_signal, bh_cond_wait, bh_cond_wait_for
 */
int bh_cond_broadcast(bh_cond_t *cond);

/**
 * Destroy condition variable.
 *
 * @param cond  Pointer to the condtion variable
 */
void bh_cond_destroy(bh_cond_t *cond);

/**
 * Submit job to the thread pool.
 *
 * @param pool  Pointer to the thread pool
 * @param func  Job function
 * @param data  Job data
 * @return 0 on success, non-zero otherwsie
 *
 * @sa bh_tpool_join
 */
int bh_tpool_job(bh_tpool_t *pool,
                 bh_thread_cb_t func,
                 void *data);

/**
 * Join thread pool until all jobs are finished.
 *
 * @param pool  Pointer to the thread pool
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_tpool_job
 */
int bh_tpool_join(bh_tpool_t *pool);

/**
 * Destroy thread pool.
 *
 * @param pool  Pointer to the thread pool
 */
void bh_tpool_destroy(bh_tpool_t *pool);

#endif /* BH_THREAD_H */
