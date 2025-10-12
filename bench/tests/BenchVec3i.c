#include "BH/Bench.h"
#include "BH/Math/Vec3i.h"


static int vecA[3] = {1, 2, 3};
static int vecB[3] = {4, -1, 5};
static int vecC[3] = {2, 3, -1};
static int vecOut[3];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    int scalar = 3;

    while (BH_BenchIter(state))
    {
        BH_Vec3iScale(vecA, scalar, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec3iMax(vecA, vecB, vecOut);
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
    BH_BENCH_ADD(Min);
    BH_BENCH_ADD(Max);

    return BH_BenchRun();
}
