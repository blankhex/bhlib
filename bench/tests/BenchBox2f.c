#include <BH/Bench.h>
#include <BH/Math/Box2f.h>



static float boxAMin[2] = {1.0f, 2.0f};
static float boxAMax[2] = {5.0f, 6.0f};
static float boxBMin[2] = {3.0f, 4.0f};
static float boxBMax[2] = {7.0f, 8.0f};
static float pointInside[2] = {3.0f, 4.0f};
static float pointList[] =
{
    1.0f, 2.0f,
    4.0f, 6.0f,
    2.0f, 3.0f,
    5.0f, 1.0f,
    3.0f, 7.0f
};
static size_t pointCount = 5;
static float outMin[2];
static float outMax[2];


BH_BENCH_TEST(Union)
{
    while (BH_BenchIter(state))
    {
        BH_Box2fUnion(boxAMin, boxAMax, boxBMin, boxBMax, outMin, outMax);
        BH_BenchDoNotOptimize(outMin);
        BH_BenchDoNotOptimize(outMax);
    }
}


BH_BENCH_TEST(Intersect)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Box2fIntersect(boxAMin, boxAMax, boxBMin, boxBMax, outMin, outMax);
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
        result = BH_Box2fContains(boxAMin, boxAMax, pointInside);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Enclose)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Box2fEnclose(pointList, pointCount, outMin, outMax);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outMin);
        BH_BenchDoNotOptimize(outMax);
    }
}


int main(void)
{
    BH_BENCH_ADD(Union);
    BH_BENCH_ADD(Intersect);
    BH_BENCH_ADD(Contains);
    BH_BENCH_ADD(Enclose);

    return BH_BenchRun();
}
