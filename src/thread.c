#include <bh/thread.h>

static void *bh_thread_run(void *data)
{
    bh_thread_t *thread;

    thread = (bh_thread_t *)data;
    thread->func(thread->data);

    return NULL;
}

int bh_thread_init(bh_thread_t *thread,
                   bh_thread_cb_t *func,
                   void *data)
{
    thread->func = func;
    thread->data = data;
    return pthread_create(&thread->handle, NULL, bh_thread_run, thread);
}

int bh_thread_join(bh_thread_t *thread)
{
    return pthread_join(&thread->handle, NULL);
}

int bh_thread_detach(bh_thread_t *thread)
{
    return pthread_detach(&thread->handle);
}

void bh_thread_destroy(bh_thread_t *thread)
{
    bh_thread_join(thread);
}

int bh_mutex_init(bh_mutex_t *mutex)
{
    return pthread_mutex_init(&mutex->handle, NULL);
}

int bh_mutex_lock(bh_mutex_t *mutex)
{
    return pthread_mutex_lock(&mutex->handle);
}

int bh_mutex_try_lock(bh_mutex_t *mutex)
{
    return pthread_mutex_trylock(&mutex->handle);
}

int bh_mutex_unlock(bh_mutex_t *mutex)
{
    return pthread_mutex_unlock(&mutex->handle);
}

void bh_mutex_destroy(bh_mutex_t *mutex)
{
    return pthread_mutex_destroy(&mutex->handle);
}

int bh_cond_init(bh_cond_t *cond)
{
    return pthread_cond_init(&cond->handle, NULL);
}

int bh_cond_wait(bh_cond_t *cond,
                 bh_mutex_t *mutex)
{
    return pthread_cond_wait(&cond->handle, &mutex->handle);
}

int bh_cond_wait_for(bh_cond_t *cond,
                     bh_mutex_t *mutex,
                     unsigned long timeout)
{
    struct timespec ts;
    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout - ts.tv_sec * 1000) * 1000000;

    return pthread_cond_timedwait(&cond->handle, &mutex->handle, &ts);
}

int bh_cond_signal(bh_cond_t *cond)
{
    return pthread_cond_signal(&cond->handle);
}

int bh_cond_broadcast(bh_cond_t *cond)
{
    return pthread_cond_broadcast(&cond->handle);
}

void bh_cond_destroy(bh_cond_t *cond)
{
    pthread_cond_destroy(&cond->handle);
}