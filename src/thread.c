#include <bh/thread.h>

int bh_thread_init(bh_thread_t *thread,
                   bh_thread_cb_t func,
                   void *data)
{
    (void)thread;
    (void)func;
    (void)data;

    return -1;
}

int bh_thread_join(bh_thread_t *thread)
{
    (void)thread;

    return -1;
}

int bh_thread_detach(bh_thread_t *thread)
{
    (void)thread;

    return -1;
}

void bh_thread_destroy(bh_thread_t *thread)
{
    (void)thread;
}

int bh_mutex_init(bh_mutex_t *mutex)
{
    (void)mutex;

    return -1;
}

int bh_mutex_lock(bh_mutex_t *mutex)
{
    (void)mutex;

    return -1;
}

int bh_mutex_try_lock(bh_mutex_t *mutex)
{
    (void)mutex;

    return -1;
}

int bh_mutex_unlock(bh_mutex_t *mutex)
{
    (void)mutex;

    return -1;
}

void bh_mutex_destroy(bh_mutex_t *mutex)
{
    (void)mutex;
}

int bh_cond_init(bh_cond_t *cond)
{
    (void)cond;

    return -1;
}

int bh_cond_wait(bh_cond_t *cond,
                 bh_mutex_t *mutex)
{
    (void)cond;
    (void)mutex;

    return -1;
}

int bh_cond_wait_for(bh_cond_t *cond,
                     bh_mutex_t *mutex,
                     unsigned long timeout)
{
    (void)cond;
    (void)mutex;
    (void)timeout;

    return -1;
}

int bh_cond_signal(bh_cond_t *cond)
{
    (void)cond;
    return -1;
}

int bh_cond_broadcast(bh_cond_t *cond)
{
    (void)cond;

    return -1;
}

void bh_cond_destroy(bh_cond_t *cond)
{
    (void)cond;
}
