#include <BH/Bench.h>
#include <BH/Queue.h>


#define NUM_ENTRIES 1000


static int values[NUM_ENTRIES];
static BH_Queue *queue;
static void *frontValue;
static void *iter;
static void *iterValue;


static void setupData()
{
    int i;
    queue = BH_QueueNew();
    for (i = 0; i < NUM_ENTRIES; ++i)
    {
        values[i] = i + 1;
        BH_QueueInsert(queue, &values[i]);
    }
}


BH_BENCH_TEST(NewFree)
{
    while (BH_BenchIter(state))
    {
        queue = BH_QueueNew();
        BH_BenchDoNotOptimize(queue);
        if (queue) BH_QueueFree(queue);
    }
}


BH_BENCH_TEST(ReserveInsert)
{
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        int i;
        queue = BH_QueueNew();
        BH_QueueReserve(queue, NUM_ENTRIES);

        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            values[i] = i + 1;
            BH_QueueInsert(queue, &values[i]);
        }

        BH_BenchDoNotOptimize(queue);
        BH_QueueFree(queue);
    }
}


BH_BENCH_TEST(FrontRemove)
{
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        int i;
        queue = BH_QueueNew();
        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            values[i] = i + 1;
            BH_QueueInsert(queue, &values[i]);
        }

        for (i = 0; i < NUM_ENTRIES; ++i)
        {
            if (BH_QueueFront(queue, &frontValue) == 0)
            {
                BH_QueueRemove(queue);
            }
        }

        BH_BenchDoNotOptimize(frontValue);
        BH_BenchDoNotOptimize(queue);
        BH_QueueFree(queue);
    }
}


BH_BENCH_TEST(Iterate)
{
    setupData();
    BH_BenchSubcount(state, NUM_ENTRIES);
    while (BH_BenchIter(state))
    {
        iter = NULL;
        iterValue = NULL;
        while ((iter = BH_QueueIterNext(queue, iter)) != NULL)
        {
            iterValue = BH_QueueIterValue(iter);
        }
        BH_BenchDoNotOptimize(iterValue);
    }

    BH_QueueFree(queue);
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(NewFree);
    BH_BENCH_ADD(ReserveInsert);
    BH_BENCH_ADD(FrontRemove);
    BH_BENCH_ADD(Iterate);

    return BH_BenchRun();
}
