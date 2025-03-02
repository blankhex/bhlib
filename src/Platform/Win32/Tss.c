#include "Thread.h"

#include <BH/Thread.h>
#include <stdlib.h>
#include <string.h>


static int tssCleanupLock = 0;
static int tssCleanupSize = 0;
static BH_GenericCallback tssCleanupData[BH_MAX_TSS];


static int tssLock = 0;
static int tssReady = 0;
static DWORD tssKey;


static void __stdcall BH_TssKeyCleanup(void *data)
{
    int i;

    /* Lock cleanup table and call cleanups */
    BH_SpinlockLock(&tssCleanupLock);
    for (i = 0; i < tssCleanupSize; i++)
        tssCleanupData[i](((void **)data)[i]);
    BH_SpinlockUnlock(&tssCleanupLock);

    free(data);
}


static void **BH_TssDataFetch(void)
{
    void **result;

    /* Get or setup TSS data */
    BH_SpinlockLock(&tssLock);
    if (!tssReady)
    {
        tssKey = FlsAlloc(BH_TssKeyCleanup);
        if (tssKey == FLS_OUT_OF_INDEXES)
            abort();
        tssReady = 1;
    }
    BH_SpinlockUnlock(&tssLock);

    /* Get or setup TSS data */
    result = FlsGetValue(tssKey);
    if (!result)
    {
        result = malloc(sizeof(void *) * BH_MAX_TSS);
        if (!result)
            abort();

        memset(result, 0, sizeof(sizeof(void *) * BH_MAX_TSS));
        if (FlsSetValue(tssKey, result))
            abort();
    }

    return result;
}


void BH_TssCleanup(void)
{
    BH_TssKeyCleanup(BH_TssDataFetch());
}


int BH_TssCreate(BH_GenericCallback callback)
{
    int result;

    /* Lock info and set up cleanup function */
    BH_SpinlockLock(&tssCleanupLock);
    if (tssCleanupSize < BH_MAX_TSS)
    {
        tssCleanupData[tssCleanupSize] = callback;
        result = tssCleanupSize++;
    }
    else
        result = BH_ERROR;
    BH_SpinlockUnlock(&tssCleanupLock);

    return result;
}


void *BH_TssRead(int index)
{
    return BH_TssDataFetch()[index];
}


void BH_TssWrite(int index,
                 void *value)
{
    BH_TssDataFetch()[index] = value;
}
