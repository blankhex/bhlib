#include "BH/Bench.h"
#include "BH/Math/Vec4f.h"


static float vecA[4] = {1.0f, 2.0f, 3.0f, 4.0f};
static float vecB[4] = {4.0f, -1.0f, 0.5f, 2.0f};
static float vecC[4] = {0.5f, 0.5f, 2.0f, 1.0f};
static float vecOut[4];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    float scalar = 2.5f;

    while (BH_BenchIter(state))
    {
        BH_Vec4fScale(vecA, scalar, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Dot)
{
    while (BH_BenchIter(state))
    {
        float result = BH_Vec4fDot(vecA, vecB);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Length)
{
    while (BH_BenchIter(state))
    {
        float result = BH_Vec4fLength(vecA);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Normal)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fNormal(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(NormalEx)
{
    while (BH_BenchIter(state))
    {
        float result = BH_Vec4fNormalEx(vecA, vecOut);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fMax(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Lerp)
{
    float t = 0.75f;

    while (BH_BenchIter(state))
    {
        BH_Vec4fLerp(vecA, vecB, t, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Project)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4fProject(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Barycentric)
{
    float v = 0.3f;
    float w = 0.4f;

    while (BH_BenchIter(state))
    {
        BH_Vec4fBarycentric(vecA, vecB, vecC, v, w, vecOut);
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
