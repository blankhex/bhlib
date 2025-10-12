#include <BH/Bench.h>
#include <BH/Timer.h>
#include <stdlib.h>
#include <stdio.h>


struct BH_Bench
{
    struct BH_Bench *next;
    const char *name;
    BH_BenchCallback cb;
    int started;
    size_t iterations;
};


static BH_Bench *root = NULL;
static BH_Timer *timer = NULL;


static void cleanup(void)
{
    BH_Bench *current;

    current = root;
    while (current)
    {
        BH_Bench *next = current->next;

        free(current);
        current = next;
    }
}


void BH_BenchAdd(const char *name,
                 BH_BenchCallback cb)
{
    BH_Bench *bench, *current;

    /* Allocate and fill new benchmark entry */
    bench = malloc(sizeof(*bench));
    if (!bench)
        return;

    bench->next = NULL;
    bench->name = name;
    bench->cb = cb;
    bench->started = 0;
    bench->iterations = 0;

    /* Append benchmark entry */
    current = root;
    while (current && current->next)
        current = current->next;

    if (current)
        current->next = bench;
    else
        root = bench;
}


int BH_BenchIter(BH_Bench *state)
{
    if (state->started)
    {
        int64_t millis;

        state->iterations++;
        millis = BH_TimerMilliseconds(timer);

        if (millis > 1000 && state->iterations > 10)
        {
            printf("%s\t%f ips\n", state->name, state->iterations / (millis / 1000.0f));
            return 0;
        }
    }
    else
    {
        state->started = 1;
        BH_TimerRestart(timer);
    }

    return 1;
}


int BH_BenchRun(void)
{
    BH_Bench *current;
    int result = 0;

    timer = BH_TimerNew();
    if (!timer)
    {
        printf("ERROR: Can't create timer for benchmarks");
        return -1;
    }

    printf("Running benchmarks...\n");
    current = root;
    while (current)
    {
        current->cb(current);
        current = current->next;
        fflush(stdout);
    }

    cleanup();
    return 0;
}
