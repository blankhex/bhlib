#ifndef BH_BENCH_H
#define BH_BENCH_H


#include <BH/Common.h>


typedef struct BH_Bench BH_Bench;
typedef void (*BH_BenchCallback)(BH_Bench *);


#define BH_BENCH_TEST(name) \
    static void bench##name(BH_Bench *state)


#define BH_BENCH_ADD(name) \
    BH_BenchAdd(#name, bench##name)


void BH_BenchAdd(const char *name,
                 BH_BenchCallback cb);


int BH_BenchIter(BH_Bench *state);


void BH_BenchSubcount(BH_Bench *state,
                      size_t count);


int BH_BenchRun(void);


#if defined(__GNUC__) || defined(__clang__)
#define BH_BenchDoNotOptimize(arg) \
    do { \
        __asm__ __volatile__("" : : "r"(*((char volatile*) &arg)) : "memory"); \
    } while (0)
#else
    #define BH_BenchDoNotOptimize(arg) \
        do { \
            volatile void* _ptr = (void*)&(arg); \
            (void)_ptr; \
        } while (0)
#endif


#endif /* BH_BENCH_H */
