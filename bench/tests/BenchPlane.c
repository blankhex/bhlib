#include <BH/Bench.h>
#include <BH/Math/Plane.h>


static float pointA[3] = {1.0f, 2.0f, 3.0f};
static float pointB[3] = {4.0f, 6.0f, 2.0f};
static float pointC[3] = {2.0f, 1.0f, -1.0f};
static float testPoint[3] = {5.0f, -3.0f, 7.0f};
static float planeNormal[4] = {1.0f, -2.0f, 1.0f, 4.0f};
static float outPlane[4];
static float outPoint[3];


BH_BENCH_TEST(FromPoints)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_PlaneFromPoints(pointA, pointB, pointC, outPlane);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outPlane);
    }
}


BH_BENCH_TEST(Distance)
{
    while (BH_BenchIter(state))
    {
        float result;
        result = BH_PlaneDistance(planeNormal, testPoint);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(ClosestPoint)
{
    while (BH_BenchIter(state))
    {
        BH_PlaneClosestPoint(planeNormal, testPoint, outPoint);
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
