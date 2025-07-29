#ifndef BH_PLATFORM_POSIX_TIMESPEC_H
#define BH_PLATFORM_POSIX_TIMESPEC_H


#include <Config.h>
#include <BH/Thread.h>
#include <sys/time.h>
#include <time.h>


static int convertToTimespec(struct timespec *ts,
                              uint32_t timeout)
{
#if (_POSIX_TIMERS > 0) || defined(BH_USE_CLOCK_GETTIME)
    if (clock_gettime(CLOCK_REALTIME, ts))
        return BH_ERROR;
#else
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        return BH_ERROR;

    ts->tv_sec = tv.tv_sec;
    ts->tv_nsec = tv.tv_usec * 1000;
#endif

    /* Calculate absoulute time for timed wait */
    ts->tv_sec += timeout / 1000;
    ts->tv_nsec += (timeout % 1000) * 1000000;

    while (ts->tv_nsec >= 1000000000) {
        ts->tv_nsec -= 1000000000;
        ts->tv_sec += 1;
    }
    return BH_OK;
}

#endif /* BH_PLATFORM_POSIX_TIMESPEC_H */
