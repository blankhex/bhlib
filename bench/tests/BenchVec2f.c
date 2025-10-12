#include "BH/Bench.h"
#include "BH/Math/Vec2f.h"


static float vecA[2] = {1.0f, 2.0f};
static float vecB[2] = {3.0f, -1.0f};
static float vecC[2] = {0.5f, 4.0f};
static float vecZero[2] = {0.0f, 0.0f};
static float vecLarge[2] = {1e6f, -1e6f};
static float vecOut[2];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    const float scale = 2.5f;
    while (BH_BenchIter(state))
    {
        BH_Vec2fScale(vecA, scale, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Dot)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec2fDot(vecA, vecB);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Cross)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec2fCross(vecA, vecB);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Length)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec2fLength(vecA);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Normal)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fNormal(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(NormalEx)
{
    float length;
    while (BH_BenchIter(state))
    {
        length = BH_Vec2fNormalEx(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
        BH_BenchDoNotOptimize(length);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fMax(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Lerp)
{
    const float t = 0.3f;
    while (BH_BenchIter(state))
    {
        BH_Vec2fLerp(vecA, vecB, t, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Project)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2fProject(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Barycentric)
{
    const float v = 0.2f, w = 0.3f;
    while (BH_BenchIter(state))
    {
        BH_Vec2fBarycentric(vecA, vecB, vecC, v, w, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Add);
    BH_BENCH_ADD(Sub);
    BH_BENCH_ADD(Mul);
    BH_BENCH_ADD(Scale);
    BH_BENCH_ADD(MulAdd);
    BH_BENCH_ADD(Negate);
    BH_BENCH_ADD(Dot);
    BH_BENCH_ADD(Cross);
    BH_BENCH_ADD(Length);
    BH_BENCH_ADD(Normal);
    BH_BENCH_ADD(NormalEx);
    BH_BENCH_ADD(Min);
    BH_BENCH_ADD(Max);
    BH_BENCH_ADD(Lerp);
    BH_BENCH_ADD(Project);
    BH_BENCH_ADD(Barycentric);

    return BH_BenchRun();
}
