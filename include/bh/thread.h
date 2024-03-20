#ifndef BH_THREAD_H
#define BH_THREAD_H

typedef void (*bh_thread_cb_t)(void *);

/* TODO: Replace this with CMake check */
#if defined(_WIN32)
#include <windows.h>

typedef struct bh_thread_s
{

} bh_thread_t;

typedef struct bh_mutex_s
{

} bh_mutex_t;

typedef struct bh_cond_s
{

} bh_cond_t;

#else
#include <pthread.h>

typedef struct bh_thread_s
{
    pthread_t handle;
    bh_thread_cb_t func;
    void *data;
} bh_thread_t;

typedef struct bh_mutex_s
{
    pthread_mutex_t handle;
} bh_mutex_t;

typedef struct bh_cons_s
{
    pthread_cond_t handle;
} bh_cond_t;
#endif

int bh_thread_init(bh_thread_t *thread,
                   bh_thread_cb_t *func,
                   void *data);

int bh_thread_join(bh_thread_t *thread);

int bh_thread_detach(bh_thread_t *thread);

void bh_thread_destroy(bh_thread_t *thread);

int bh_mutex_init(bh_mutex_t *mutex);

int bh_mutex_lock(bh_mutex_t *mutex);

int bh_mutex_try_lock(bh_mutex_t *mutex);

int bh_mutex_unlock(bh_mutex_t *mutex);

void bh_mutex_destroy(bh_mutex_t *mutex);

int bh_cond_init(bh_cond_t *cond);

int bh_cond_wait(bh_cond_t *cond,
                 bh_mutex_t *mutex);

int bh_cond_wait_for(bh_cond_t *cond,
                     bh_mutex_t *mutex,
                     unsigned long timeout);

int bh_cond_signal(bh_cond_t *cond);

int bh_cond_broadcast(bh_cond_t *cond);

void bh_cond_destroy(bh_cond_t *cond);

#endif /* BH_THREAD_H */