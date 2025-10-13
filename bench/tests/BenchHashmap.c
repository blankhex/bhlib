#include <BH/Bench.h>
#include <BH/Hashmap.h>
#include <stdio.h>


#define NUM_ENTRIES 1000


static int keys[NUM_ENTRIES];
static char values[NUM_ENTRIES][16];
static BH_Hashmap *map;
static BH_Hashmap *warmMap;


int BH_IntEqual(const void *a, const void *b)
{
    return (*(const int*)a == *(const int*)b) ? 0 : 1;
}


size_t BH_IntHash(const void *key)
{
    int k = *(const int*)key;
    return (size_t)((k * 2654435761U) >> 8);
}


static void setupData(void)
{
    int i;
    for (i = 0; i < NUM_ENTRIES; ++i)
    {
        keys[i] = i + 1;
        sprintf(values[i], "value_%d", i + 1);
    }
}


static void setupWarmMap(void)
{
    int i;
    warmMap = BH_HashmapNew(BH_IntEqual, BH_IntHash);
    for (i = 0; i < NUM_ENTRIES; ++i)
    {
        BH_HashmapInsert(warmMap, &keys[i], values[i]);
    }
}


BH_BENCH_TEST(NewFree)
{
    while (BH_BenchIter(state))
    {
        map = BH_HashmapNew(BH_IntEqual, BH_IntHash);
        BH_BenchDoNotOptimize(map);
        BH_HashmapFree(map);
    }
}


BH_BENCH_TEST(ReserveInsert)
{
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        map = BH_HashmapNew(BH_IntEqual, BH_IntHash);
        BH_HashmapReserve(map, NUM_ENTRIES);

        for (int i = 0; i < NUM_ENTRIES; ++i)
        {
            BH_HashmapInsert(map, &keys[i], values[i]);
        }
        BH_HashmapClear(map);

        BH_BenchDoNotOptimize(map);
        BH_HashmapFree(map);
    }
}


BH_BENCH_TEST(Lookup)
{
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        int i;
        void *value = NULL;

        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            BH_HashmapAt(warmMap, &keys[i], &value);
        }
        BH_BenchDoNotOptimize(value);
    }
}


BH_BENCH_TEST(Remove)
{
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        int i;
        map = BH_HashmapNew(BH_IntEqual, BH_IntHash);

        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            BH_HashmapInsert(map, &keys[i], values[i]);
        }

        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            BH_HashmapRemove(map, &keys[i]);
        }

        BH_BenchDoNotOptimize(map);
        BH_HashmapFree(map);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    setupData();
    setupWarmMap();

    BH_BENCH_ADD(NewFree);
    BH_BENCH_ADD(ReserveInsert);
    BH_BENCH_ADD(Lookup);
    BH_BENCH_ADD(Remove);

    return BH_BenchRun();
}
