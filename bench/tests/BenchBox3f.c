#include "BH/Bench.h"
#include "BH/Math/Box3f.h"


static float boxAMin[3] = {1.0f, 2.0f, 3.0f};
static float boxAMax[3] = {6.0f, 7.0f, 8.0f};
static float boxBMin[3] = {4.0f, 5.0f, 2.0f};
static float boxBMax[3] = {9.0f, 10.0f, 6.0f};
static float pointInside[3] = {3.0f, 4.0f, 5.0f};
static float pointList[] =
{
    1.0f, 2.0f, 3.0f,
    5.0f, 1.0f, 7.0f,
    2.0f, 6.0f, 4.0f,
    8.0f, 3.0f, 5.0f,
    4.0f, 4.0f, 1.0f
};
static size_t pointCount = 5;
static float outMin[3];
static float outMax[3];


BH_BENCH_TEST(Union)
{
    while (BH_BenchIter(state))
    {
        BH_Box3fUnion(boxAMin, boxAMax, boxBMin, boxBMax, outMin, outMax);
        BH_BenchDoNotOptimize(outMin);
        BH_BenchDoNotOptimize(outMax);
    }
}


BH_BENCH_TEST(Intersect)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Box3fIntersect(boxAMin, boxAMax, boxBMin, boxBMax, outMin, outMax);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outMin);
        BH_BenchDoNotOptimize(outMax);
    }
}


BH_BENCH_TEST(Contains)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Box3fContains(boxAMin, boxAMax, pointInside);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Enclose)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Box3fEnclose(pointList, pointCount, outMin, outMax);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outMin);
        BH_BenchDoNotOptimize(outMax);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Union);
    BH_BENCH_ADD(Intersect);
    BH_BENCH_ADD(Contains);
    BH_BENCH_ADD(Enclose);

    return BH_BenchRun();
}
