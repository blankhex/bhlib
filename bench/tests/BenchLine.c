#include "BH/Bench.h"
#include "BH/Math/Line.h"


static float pointA[2] = {1.0f, 2.0f};
static float pointB[2] = {4.0f, 6.0f};
static float lineNormal[3] = {3.0f, -4.0f, 5.0f};
static float outLine[3];
static float outPoint[2];


BH_BENCH_TEST(FromPoints)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_LineFromPoints(pointA, pointB, outLine);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outLine);
    }
}


BH_BENCH_TEST(Distance)
{
    while (BH_BenchIter(state))
    {
        float result;
        result = BH_LineDistance(lineNormal, pointA);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(ClosestPoint)
{
    while (BH_BenchIter(state))
    {
        BH_LineClosestPoint(lineNormal, pointA, outPoint);
        BH_BenchDoNotOptimize(outPoint);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(FromPoints);
    BH_BENCH_ADD(Distance);
    BH_BENCH_ADD(ClosestPoint);

    return BH_BenchRun();
}
