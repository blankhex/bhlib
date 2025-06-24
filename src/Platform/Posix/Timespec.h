#ifndef BH_PLATFORM_POSIX_TIMESPEC_H
#define BH_PLATFORM_POSIX_TIMESPEC_H


#include <BH/Thread.h>
#include <time.h>


static void convertToTimespec(struct timespec *ts,
                              uint32_t timeout)
{
    /* Calculate absoulute time for timed wait */
    clock_gettime(CLOCK_REALTIME, ts);
    ts->tv_sec += timeout / 1000;
    ts->tv_nsec += (timeout % 1000) * 1000000;
    while (ts->tv_nsec >= 1000000000) {
        ts->tv_nsec -= 1000000000;
        ts->tv_sec += 1;
    }
}


#endif /* BH_PLATFORM_POSIX_TIMESPEC_H */
