#ifndef BH_BENCH_H
#define BH_BENCH_H

typedef struct BH_Bench BH_Bench;
typedef void (*BH_BenchCallback)(BH_Bench *);


#define BH_BENCH_TEST(name) \
    static void bench##name(BH_Bench *state)


#define BH_BENCH_ADD(name) \
    BH_BenchAdd(#name, bench##name)


void BH_BenchAdd(const char *name,
                 BH_BenchCallback cb);


int BH_BenchIter(BH_Bench *state);


int BH_BenchRun(void);

#endif /* BH_BENCH_H */
