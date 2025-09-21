#ifndef BH_TIMER_H
#define BH_TIMER_H


#include "Common.h"


typedef struct BH_Timer BH_Timer;


BH_Timer *BH_TimerNew(void);


void BH_TimerFree(BH_Timer *timer);


int BH_TimerIsMonotonic(BH_Timer *timer);


void BH_TimerStart(BH_Timer *timer);


int64_t BH_TimerRestart(BH_Timer *timer);


int64_t BH_TimerMilliseconds(BH_Timer *timer);


int64_t BH_TimerNanoseconds(BH_Timer *timer);


#endif /* BH_TIMER_H */
