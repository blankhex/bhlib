#include <BH/Bench.h>
#include <BH/Math/Vec2i.h>


static int vecA[2] = {5, -3};
static int vecB[2] = {2, 7};
static int vecC[2] = {4, 1};
static int vecOut[2];


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iAdd(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iSub(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iMul(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Scale)
{
    const int s = 3;
    while (BH_BenchIter(state))
    {
        BH_Vec2iScale(vecA, s, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(MulAdd)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iMulAdd(vecA, vecB, vecC, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Negate)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iNegate(vecA, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Min)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iMin(vecA, vecB, vecOut);
        BH_BenchDoNotOptimize(vecOut);
    }
}


BH_BENCH_TEST(Max)
{
    while (BH_BenchIter(state))
    {
        BH_Vec2iMax(vecA, vecB, vecOut);
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
