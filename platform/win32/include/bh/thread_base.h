#ifndef BH_THREAD_BASE_H
#define BH_THREAD_BASE_H

#ifndef BH_THREAD_H
#error "Don't include this file directly"
#endif

#incldue <bh/ds.h>
#include <process.h>

typedef struct bh_thread_s
{
    HANDLE handle;
    bh_thread_cb_t func;
    void *data;
} bh_thread_t;

typedef struct bh_mutex_s
{
    CRITICAL_SECTION handle;
} bh_mutex_t;

typedef struct bh_cond_s
{
} bh_cond_t;

typedef struct bh_tpool_s
{
    bh_array_t threads;
    bh_array_t jobs;
    bh_mutex_t mutex;
    bh_cond_t cond;
} bh_tpool_t;

typedef uintptr_t (__cdecl *bh_thread_win_begin_cb_t)(void *,
                                                      unsigned,
                                                      unsigned (__stdcall *)(void *),
                                                      void *,
                                                      unsigned,
                                                      unsigned *);

typedef uintptr_t (__cdecl *bh_thread_win_end_cb_t)(unsigned);

int bh_thread_init_base(bh_thread_t *thread,
                        bh_thread_cb_t func,
                        void *data,
                        bh_thread_win_begin_cb_t begin,
                        bh_thread_win_end_cb_t end);

int bh_tpool_init_base(bh_tpool_t *pool,
                       size_t size,
                       bh_thread_win_begin_cb_t begin,
                       bh_thread_win_end_cb_t end);

#define bh_thread_init(thread, func, data) \
    bh_thread_init_base((thread), (func), (data), _beginthreadex, _endthreadex)

#define bh_tpool_init(pool, size) \
    bh_tpool_init_base((pool), (size), _beginthreadex, _endthreadex)

#endif /* BH_THREAD_BASE_H */

