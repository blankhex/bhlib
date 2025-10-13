#include <BH/Bench.h>
#include <BH/Math/Mat3f.h>


static float matA[9] =
{
    1.0f, 0.5f, 0.0f,
    0.2f, 2.0f, 0.3f,
    0.0f, 0.1f, 1.5f
};
static float matB[9] =
{
    0.8f, 0.0f, 0.2f,
    0.1f, 1.2f, 0.4f,
    0.3f, 0.0f, 0.9f
};
static float outMat[9];
static float outInv[9];
static float vec3[3] = {1.5f, 2.5f, 1.0f};
static float vec2[2] = {3.0f, 4.0f};
static float outVec3[3];
static float outVec2[2];


BH_BENCH_TEST(Identity)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fIdentity(outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fAdd(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fSub(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fMul(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Scale)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fScale(matA, 2.5f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Transpose)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fTranspose(matA, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Trace)
{
    while (BH_BenchIter(state))
    {
        float trace;
        trace = BH_Mat3fTrace(matA);
        BH_BenchDoNotOptimize(trace);
    }
}


BH_BENCH_TEST(Det)
{
    while (BH_BenchIter(state))
    {
        float det;
        det = BH_Mat3fDet(matA);
        BH_BenchDoNotOptimize(det);
    }
}


BH_BENCH_TEST(Inverse)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Mat3fInverse(matA, outInv);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outInv);
    }
}


BH_BENCH_TEST(FromScale)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fFromScale(2.0f, 3.0f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromTranslation)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fFromTranslation(4.0f, -2.0f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromRotation)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fFromRotation(0.7854f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(ApplyVec3f)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fApplyVec3f(matA, vec3, outVec3);
        BH_BenchDoNotOptimize(outVec3);
    }
}


BH_BENCH_TEST(ApplyVec2f)
{
    while (BH_BenchIter(state))
    {
        BH_Mat3fApplyVec2f(matA, vec2, outVec2);
        BH_BenchDoNotOptimize(outVec2);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Identity);
    BH_BENCH_ADD(Add);
    BH_BENCH_ADD(Sub);
    BH_BENCH_ADD(Mul);
    BH_BENCH_ADD(Scale);
    BH_BENCH_ADD(Transpose);
    BH_BENCH_ADD(Trace);
    BH_BENCH_ADD(Det);
    BH_BENCH_ADD(Inverse);
    BH_BENCH_ADD(FromScale);
    BH_BENCH_ADD(FromTranslation);
    BH_BENCH_ADD(FromRotation);
    BH_BENCH_ADD(ApplyVec3f);
    BH_BENCH_ADD(ApplyVec2f);

    return BH_BenchRun();
}
