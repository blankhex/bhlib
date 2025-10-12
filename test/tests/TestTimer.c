#include <BH/Unit.h>
#include <BH/Timer.h>
#include <BH/Thread.h>


BH_UNIT_TEST(General)
{
    BH_Timer *timer;

    BH_VERIFY((timer = BH_TimerNew()) != NULL);
    BH_ThreadSleep(5000);

    BH_VERIFY(BH_TimerMilliseconds(timer) >= 5000);
    BH_VERIFY(BH_TimerNanoseconds(timer) >= 5000000000);
    BH_VERIFY(BH_TimerRestart(timer) >= 5000);
    BH_VERIFY(BH_TimerRestart(timer) < 5000);

    BH_ThreadSleep(5000);
    BH_VERIFY(BH_TimerMilliseconds(timer) >= 5000);
    BH_TimerStart(timer);
    BH_VERIFY(BH_TimerMilliseconds(timer) < 5000);

    BH_TimerFree(timer);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(General);

    return BH_UnitRun();
}
