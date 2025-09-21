#include <BH/Timer.h>


BH_Timer *BH_TimerNew(void)
{
    return NULL;
}


void BH_TimerFree(BH_Timer *timer)
{
    BH_UNUSED(timer);
}


int BH_TimerIsMonotonic(BH_Timer *timer)
{
    BH_UNUSED(timer);
    return 0;
}


void BH_TimerStart(BH_Timer *timer)
{
    BH_UNUSED(timer);
}


int64_t BH_TimerRestart(BH_Timer *timer)
{
    BH_UNUSED(timer);

    return 0;
}


int64_t BH_TimerMilliseconds(BH_Timer *timer)
{
    BH_UNUSED(timer);

    return 0;
}


int64_t BH_TimerNanoseconds(BH_Timer *timer)
{
    BH_UNUSED(timer);

    return 0;
}
