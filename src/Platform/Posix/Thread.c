#include "Thread.h"

#include <limits.h>
#include <stdlib.h>


struct BH_ThreadContext
{
    BH_ThreadCallback callback;
    void *data;
};


static void *BH_ThreadRun(void *context)
{
    BH_ThreadCallback callback;
    void *data, *result;

    callback = ((struct BH_ThreadContext *)context)->callback;
    data = ((struct BH_ThreadContext *)context)->data;
    free(context);

    callback(data);
    BH_TssCleanup();

    pthread_exit(0);
}


static int BH_ThreadInit(BH_Thread *thread,
                         size_t stack,
                         BH_ThreadCallback callback,
                         void *data)
{
    struct BH_ThreadContext *context;
    pthread_attr_t attributes;
    int result;

    context = malloc(sizeof(*context));
    if (!context)
        return BH_ERROR;
    context->callback = callback;
    context->data = data;

    /* Create thread with specified stack size */
    pthread_attr_init(&attributes);

    if (!stack)
        result = pthread_create(&thread->handle, NULL, BH_ThreadRun, context);
    else
    {
        if (stack < PTHREAD_STACK_MIN)
            stack = PTHREAD_STACK_MIN;
        pthread_attr_setstacksize(&attributes, stack);
        result = pthread_create(&thread->handle, &attributes, BH_ThreadRun, context);
    }

    pthread_attr_destroy(&attributes);
    return result;
}


BH_Thread *BH_ThreadNew(size_t stack,
                        BH_ThreadCallback callback,
                        void *data)
{
    BH_Thread *thread;

    thread = malloc(sizeof(BH_Thread));
    if (thread && BH_ThreadInit(thread, stack, callback, data))
    {
        free(thread);
        return NULL;
    }

    return thread;
}


int BH_ThreadJoin(BH_Thread *thread)
{
    if (pthread_join(thread->handle, NULL))
        return BH_ERROR;

    free(thread);
    return BH_OK;
}


int BH_ThreadDetach(BH_Thread *thread)
{
    if (pthread_detach(thread->handle))
        return BH_ERROR;

    free(thread);
    return BH_OK;
}
