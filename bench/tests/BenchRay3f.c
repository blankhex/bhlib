#include <BH/Bench.h>
#include <BH/Math/Ray3f.h>


static float rayStart[3] = {0.0f, 0.0f, 0.0f};
static float rayDir[3] = {1.0f, 1.0f, 1.0f};
static float segStart[3] = {-2.0f, -2.0f, -2.0f};
static float segEnd[3] = {2.0f, 2.0f, 2.0f};
static float planeEq[4] = {1.0f, 1.0f, 1.0f, -3.0f};
static float triA[3] = {1.0f, 1.0f, 1.0f};
static float triB[3] = {2.0f, 1.0f, 0.0f};
static float triC[3] = {0.0f, 2.0f, 1.0f};
static float boxMin[3] = {1.0f, 1.0f, 1.0f};
static float boxMax[3] = {3.0f, 3.0f, 3.0f};
static float outPoint[3];


BH_BENCH_TEST(IntersectPlane)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray3fIntersectPlane(rayStart, rayDir, planeEq, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(IntersectTriangle)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray3fIntersectTriangle(rayStart, rayDir, triA, triB, triC, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectPlane)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment3fIntersectPlane(segStart, segEnd, planeEq, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectTriangle)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment3fIntersectTriangle(segStart, segEnd, triA, triB, triC, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(IntersectBox3f)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray3fIntersectBox3f(rayStart, rayDir, boxMin, boxMax, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectBox3f)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment3fIntersectBox3f(segStart, segEnd, boxMin, boxMax, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(IntersectPlane);
    BH_BENCH_ADD(IntersectTriangle);
    BH_BENCH_ADD(SegmentIntersectPlane);
    BH_BENCH_ADD(SegmentIntersectTriangle);
    BH_BENCH_ADD(IntersectBox3f);
    BH_BENCH_ADD(SegmentIntersectBox3f);

    return BH_BenchRun();
}
