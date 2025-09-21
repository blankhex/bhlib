#include <BH/Timer.h>

#include <stdlib.h>
#include <windows.h>


#define TYPE_TICKS   0x0000
#define TYPE_COUNTER 0x0001


struct BH_Timer
{
    int type;
    LARGE_INTEGER frequency;
    int64_t sec;
    int64_t nsec;
};


static int checkAvailableTimer(LARGE_INTEGER *frequency)
{
    LARGE_INTEGER dummy;

    if (QueryPerformanceFrequency(frequency))
    {
        if (QueryPerformanceCounter(&dummy))
        {
            return TYPE_COUNTER;
        }
    }

    return TYPE_TICKS;
}


static void getTimer(int type,
                     LARGE_INTEGER *frequency,
                     int64_t *sec,
                     int64_t *nsec)
{
    LARGE_INTEGER newCount;
    int64_t newTicks;

    switch (type)
    {
    case TYPE_COUNTER:
        QueryPerformanceCounter(&newCount);
        *sec = newCount.QuadPart / frequency->QuadPart;
        *nsec = (newCount.QuadPart - *sec * frequency->QuadPart) * 1000000000 / frequency->QuadPart;
        break;

    default:
    case TYPE_TICKS:
        newTicks = GetTickCount64();
        *sec = newTicks / 1000;
        *nsec = (newTicks - *sec * 1000) * 1000000;
        break;
    }
}


BH_Timer *BH_TimerNew(void)
{
    BH_Timer *result;

    result = malloc(sizeof(*result));
    if (result)
    {
        result->type = checkAvailableTimer(&result->frequency);
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
    return timer->type == TYPE_COUNTER;
}


void BH_TimerStart(BH_Timer *timer)
{
    getTimer(timer->type, &timer->frequency, &timer->sec, &timer->nsec);
}


int64_t BH_TimerRestart(BH_Timer *timer)
{
    int64_t oldSec, oldNsec;

    oldSec = timer->sec; oldNsec = timer->nsec;

    getTimer(timer->type, &timer->frequency, &timer->sec, &timer->nsec);
    oldSec = timer->sec - oldSec;
    oldNsec = timer->nsec - oldNsec;

    return (oldSec * 1000) + (oldNsec / 1000000);
}


int64_t BH_TimerMilliseconds(BH_Timer *timer)
{
    int64_t newSec, newNsec;

    getTimer(timer->type, &timer->frequency, &newSec, &newNsec);
    newSec -= timer->sec;
    newNsec -= timer->nsec;

    return (newSec * 1000) + (newNsec / 1000000);
}


int64_t BH_TimerNanoseconds(BH_Timer *timer)
{
    int64_t newSec, newNsec;

    getTimer(timer->type, &timer->frequency, &newSec, &newNsec);
    newSec -= timer->sec;
    newNsec -= timer->nsec;

    return (newSec * 1000000000) + newNsec;
}
