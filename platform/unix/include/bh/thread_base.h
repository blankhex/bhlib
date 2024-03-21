#ifndef BH_THREAD_BASE_H
#define BH_THREAD_BASE_H

#ifndef BH_THREAD_H
#error "Don't include this file directly!"
#endif

#include <pthread.h>
#include <bh/ds.h>

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

typedef struct bh_tpool_s
{
    bh_array_t threads;
    bh_array_t jobs;
    bh_mutex_t mutex;
    bh_cond_t cond;
} bh_tpool_t;

int bh_thread_init(bh_thread_t *thread,
                   bh_thread_cb_t func,
                   void *data);

int bh_tpool_init(bh_tpool_t *pool,
                  size_t size);

#endif /* BH_THREAD_BASE_H */
