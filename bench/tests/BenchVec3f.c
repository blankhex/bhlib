#include <BH/Bench.h>
#include <BH/Math/Vec3f.h>


static float vecA[3] = {1.0f, 2.0f, 3.0f};
static float vecB[3] = {4.0f, -1.0f, 0.5f};
static float vecC[3] = {0.5f, 0.5f, 2.0f};
static float vecOut[3];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    static float scalar = 2.5f;
    while (BH_BenchIter(state))
    {
        BH_Vec3fScale(vecA, scalar, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Dot)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec3fDot(vecA, vecB);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Cross)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fCross(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Length)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec3fLength(vecA);
        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(Normal)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fNormal(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(NormalEx)
{
    float result;
    while (BH_BenchIter(state))
    {
        result = BH_Vec3fNormalEx(vecA, vecOut);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fMax(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Lerp)
{
    static float t = 0.75f;
    while (BH_BenchIter(state))
    {
        BH_Vec3fLerp(vecA, vecB, t, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Project)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3fProject(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Barycentric)
{
    static float v = 0.3f;
    static float w = 0.4f;
    while (BH_BenchIter(state))
    {
        BH_Vec3fBarycentric(vecA, vecB, vecC, v, w, vecOut);
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
