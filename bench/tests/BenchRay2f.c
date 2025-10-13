#include <BH/Bench.h>
#include <BH/Math/Ray2f.h>

static float rayAStart[2] = {1.0f, 1.0f};
static float rayADir[2] = {1.0f, 0.5f};
static float rayBStart[2] = {3.0f, 0.0f};
static float rayBDir[2] = {-0.5f, 1.0f};
static float lineEq[3] = {1.0f, 1.0f, -4.0f};
static float segStart[2] = {0.0f, 3.0f};
static float segEnd[2] = {5.0f, 2.0f};
static float boxMin[2] = {2.0f, 2.0f};
static float boxMax[2] = {6.0f, 5.0f};
static float outPoint[2];


BH_BENCH_TEST(IntersectLine)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray2fIntersectLine(rayAStart, rayADir, lineEq, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(IntersectTime)
{
    while (BH_BenchIter(state))
    {
        float time1, time2;
        int result;
        result = BH_Ray2fIntersectTime(rayAStart, rayADir, rayBStart, rayBDir, &time1, &time2);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(time1);
        BH_BenchDoNotOptimize(time2);
    }
}


BH_BENCH_TEST(IntersectRay)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray2fIntersectRay(rayAStart, rayADir, rayBStart, rayBDir, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(IntersectSegment)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray2fIntersectSegment(rayAStart, rayADir, segStart, segEnd, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectLine)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment2fIntersectLine(segStart, segEnd, lineEq, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectSegment)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment2fIntersectSegment(segStart, segEnd, rayAStart, rayBStart, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(IntersectBox2f)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Ray2fIntersectBox2f(rayAStart, rayADir, boxMin, boxMax, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


BH_BENCH_TEST(SegmentIntersectBox2f)
{
    while (BH_BenchIter(state))
    {
        float t;
        int result;
        result = BH_Segment2fIntersectBox2f(segStart, segEnd, boxMin, boxMax, &t, outPoint);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(t);
        BH_BenchDoNotOptimize(outPoint);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(IntersectLine);
    BH_BENCH_ADD(IntersectTime);
    BH_BENCH_ADD(IntersectRay);
    BH_BENCH_ADD(IntersectSegment);
    BH_BENCH_ADD(SegmentIntersectLine);
    BH_BENCH_ADD(SegmentIntersectSegment);
    BH_BENCH_ADD(IntersectBox2f);
    BH_BENCH_ADD(SegmentIntersectBox2f);

    return BH_BenchRun();
}
