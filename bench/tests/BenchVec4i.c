#include "BH/Bench.h"
#include "BH/Math/Vec4i.h"


static int vecA[4] = {1, 2, 3, 4};
static int vecB[4] = {4, -1, 5, 2};
static int vecC[4] = {2, 3, -1, 1};
static int vecOut[4];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    int scalar = 3;

    while (BH_BenchIter(state))
    {
        BH_Vec4iScale(vecA, scalar, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec4iMax(vecA, vecB, vecOut);
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
