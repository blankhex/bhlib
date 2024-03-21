#include <bh/thread.h>

int bh_tpool_job(bh_tpool_t *pool,
                 bh_thread_cb_t job,
                 void *data)
{
    (void)pool;
    (void)job;
    (void)data;

    return -1;
}

int bh_tpool_join(bh_tpool_t *pool)
{
    (void)pool;

    return -1;
}

void bh_tpool_destroy(bh_tpool_t *pool)
{
    (void)pool;
}
