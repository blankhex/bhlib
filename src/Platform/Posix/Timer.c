#include <BH/Timer.h>

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


#define TYPE_OLD_REALTIME   0x0000
#define TYPE_NEW_REALTIME   0x0001
#define TYPE_MONOTONIC      0x0002


struct BH_Timer
{
    int type;
    int64_t sec;
    int64_t nsec;
};


static int checkAvailableTimer(void)
{
#if (_POSIX_TIMERS > 0) || defined(BH_USE_CLOCK_GETTIME)
    struct timespec ts;

    if (!clock_gettime(CLOCK_MONOTONIC, &ts))
        return TYPE_MONOTONIC;

    if (!clock_gettime(CLOCK_REALTIME, &ts))
        return TYPE_NEW_REALTIME;
#endif

    return TYPE_OLD_REALTIME;
}


static void getTimer(int type,
                     int64_t *sec,
                     int64_t *nsec)
{
    struct timespec ts;
    struct timeval tv;

    switch (type)
    {
#if (_POSIX_TIMERS > 0) || defined(BH_USE_CLOCK_GETTIME)
    case TYPE_MONOTONIC:
        clock_gettime(CLOCK_MONOTONIC, &ts);
        *sec = ts.tv_sec;
        *nsec = ts.tv_nsec;
        break;

    case TYPE_NEW_REALTIME:
        clock_gettime(CLOCK_REALTIME, &ts);
        *sec = ts.tv_sec;
        *nsec = ts.tv_nsec;
        break;
#endif

    default:
    case TYPE_OLD_REALTIME:
        gettimeofday(&tv, NULL);
        *sec = tv.tv_sec;
        *nsec = tv.tv_usec * (uint64_t)1000;
        break;
    }
}


BH_Timer *BH_TimerNew(void)
{
    BH_Timer *result;

    result = malloc(sizeof(*result));
    if (result)
    {
        result->type = checkAvailableTimer();
        BH_TimerStart(result);
    }

    return result;
}


void BH_TimerFree(BH_Timer *timer)
{
    free(timer);
}


int BH_TimerIsMonotonic(BH_Timer *timer)
{
    return timer->type == TYPE_MONOTONIC;
}


void BH_TimerStart(BH_Timer *timer)
{
    getTimer(timer->type, &timer->sec, &timer->nsec);
}


int64_t BH_TimerRestart(BH_Timer *timer)
{
    int64_t oldSec, oldNsec;

    oldSec = timer->sec; oldNsec = timer->nsec;

    getTimer(timer->type, &timer->sec, &timer->nsec);
    oldSec = timer->sec - oldSec;
    oldNsec = timer->nsec - oldNsec;

    return (oldSec * 1000) + (oldNsec / 1000000);
}


int64_t BH_TimerMilliseconds(BH_Timer *timer)
{
    int64_t newSec, newNsec;

    getTimer(timer->type, &newSec, &newNsec);
    newSec -= timer->sec;
    newNsec -= timer->nsec;

    return (newSec * 1000) + (newNsec / 1000000);
}


int64_t BH_TimerNanoseconds(BH_Timer *timer)
{
    int64_t newSec, newNsec;

    getTimer(timer->type, &newSec, &newNsec);
    newSec -= timer->sec;
    newNsec -= timer->nsec;

    return (newSec * 1000000000) + newNsec;
}
