#include "Thread.h"

#include <process.h>


struct BH_ThreadContext
{
    BH_ThreadCallback callback;
    void *data;
};


static unsigned __stdcall threadRun(void *context)
{

    BH_ThreadCallback callback;
    void *data;

    callback = ((struct BH_ThreadContext *)context)->callback;
    data = ((struct BH_ThreadContext *)context)->data;
    free(context);

    callback(data);
    BH_TssCleanup();

    _endthreadex(0);
}


static int threadInit(BH_Thread *thread,
                      size_t stack,
                      BH_ThreadCallback callback,
                      void *data)
{
    struct BH_ThreadContext *context;

    context = malloc(sizeof(*context));
    if (!context)
        return BH_ERROR;
    context->callback = callback;
    context->data = data;

    thread->handle = (HANDLE)_beginthreadex(NULL, stack, BH_ThreadRun, context, 0, NULL);
    if (!thread->handle)
    {
        free(context);
        return BH_ERROR;
    }

    return BH_OK;
}


BH_Thread *BH_ThreadNew(size_t stack,
                        BH_ThreadCallback callback,
                        void *data)
{
    BH_Thread *thread;

    thread = malloc(sizeof(BH_Thread));
    if (thread && threadInit(thread, stack, callback, data))
    {
        free(thread);
        return NULL;
    }

    return thread;
}


int BH_ThreadJoin(BH_Thread *thread)
{
    /* Join the thread */
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
    free(thread);

    return BH_OK;
}


int BH_ThreadDetach(BH_Thread *thread)
{
    /* Detach from thread */
    CloseHandle(thread->handle);
    free(thread);

    return BH_OK;
}
