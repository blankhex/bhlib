#include <BH/Bench.h>
#include <BH/Algo.h>


#define NUM_ENTRIES 1000


static int testArray[NUM_ENTRIES];
static int tempArray[NUM_ENTRIES];
static int pivotValue;


static int intEqual(const void *a, const void *b)
{
    int ia, ib;
    ia = *(const int*)a;
    ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}


static void algoSetup(void)
{
    int i;
    for (i = 0; i < NUM_ENTRIES; ++i)
    {
        testArray[i] = NUM_ENTRIES - i;
        tempArray[i] = NUM_ENTRIES - i;
    }
    pivotValue = NUM_ENTRIES / 2;
}


BH_BENCH_TEST(Swap)
{
    int a = 123;
    int b = 456;
    algoSetup();

    while (BH_BenchIter(state))
    {
        BH_Swap(&a, &b, sizeof(int));
        BH_BenchDoNotOptimize(a);
        BH_BenchDoNotOptimize(b);
        BH_Swap(&a, &b, sizeof(int));
    }
}


BH_BENCH_TEST(Partition)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        void *pivot, *result;
        for (int i = 0; i < NUM_ENTRIES; ++i)
            testArray[i] = tempArray[i];

        pivot = &pivotValue;
        result = BH_Partition(pivot, testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testArray);
    }
}


BH_BENCH_TEST(Sort)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        int i;
        for (i = 0; i < NUM_ENTRIES; ++i)
            testArray[i] = tempArray[i];

        BH_Sort(testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(testArray);
    }
}


BH_BENCH_TEST(HeapMake)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        int i;
        for (i = 0; i < NUM_ENTRIES; ++i)
            testArray[i] = tempArray[i];

        BH_HeapMake(testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(testArray);
    }
}


BH_BENCH_TEST(HeapRemove)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        int i;
        for (i = 0; i < NUM_ENTRIES; ++i)
            testArray[i] = tempArray[i];
        BH_HeapMake(testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_HeapRemove(testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(testArray);
    }
}


BH_BENCH_TEST(HeapInsert)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        int i, value;

        for (i = 0; i < NUM_ENTRIES - 1; ++i)
            testArray[i] = tempArray[i];
        testArray[NUM_ENTRIES - 1] = 0;
        BH_HeapMake(testArray, NUM_ENTRIES - 1, sizeof(int), intEqual);

        value = 250;
        BH_HeapInsert(&value, testArray, NUM_ENTRIES - 1, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(testArray);
    }
}


BH_BENCH_TEST(HeapReplace)
{
    algoSetup();

    while (BH_BenchIter(state))
    {
        int i, value;

        for (i = 0; i < NUM_ENTRIES; ++i)
            testArray[i] = tempArray[i];
        BH_HeapMake(testArray, NUM_ENTRIES, sizeof(int), intEqual);

        value = 100;
        BH_HeapReplace(&value, testArray, NUM_ENTRIES, sizeof(int), intEqual);
        BH_BenchDoNotOptimize(testArray);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Swap);
    BH_BENCH_ADD(Partition);
    BH_BENCH_ADD(Sort);
    BH_BENCH_ADD(HeapMake);
    BH_BENCH_ADD(HeapRemove);
    BH_BENCH_ADD(HeapInsert);
    BH_BENCH_ADD(HeapReplace);

    return BH_BenchRun();
}
