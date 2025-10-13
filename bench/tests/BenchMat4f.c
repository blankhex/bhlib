#include <BH/Bench.h>
#include <BH/Math/Mat4f.h>


static float matA[16] =
{
    1.0f, 0.2f, 0.0f, 0.0f,
    0.1f, 1.5f, 0.3f, 0.0f,
    0.0f, 0.0f, 2.0f, 0.0f,
    1.0f, 2.0f, 3.0f, 1.0f
};
static float matB[16] =
{
    0.9f, 0.0f, 0.1f, 0.0f,
    0.0f, 1.1f, 0.0f, 0.0f,
    0.2f, 0.3f, 0.8f, 0.0f,
    0.5f, 1.0f, 1.5f, 1.0f
};
static float outMat[16];
static float outInv[16];
static float vec4[4] = {1.0f, 2.0f, 3.0f, 1.0f};
static float vec3[3] = {4.0f, 5.0f, 6.0f};
static float outVec4[4];
static float outVec3[3];
static float quat[4] = {0.707f, 0.0f, 0.0f, 0.707f};
static float axis[3] = {0.577f, 0.577f, 0.577f};
static float camPos[3] = {0.0f, 0.0f, 5.0f};
static float camAt[3]  = {0.0f, 0.0f, 0.0f};
static float camUp[3]  = {0.0f, 1.0f, 0.0f};


BH_BENCH_TEST(Identity)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fIdentity(outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Add)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fAdd(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Sub)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fSub(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Mul)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fMul(matA, matB, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Scale)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fScale(matA, 1.5f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Transpose)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fTranspose(matA, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(Trace)
{
    while (BH_BenchIter(state))
    {
        float trace;
        trace = BH_Mat4fTrace(matA);
        BH_BenchDoNotOptimize(trace);
    }
}


BH_BENCH_TEST(Det)
{
    while (BH_BenchIter(state))
    {
        float det;
        det = BH_Mat4fDet(matA);
        BH_BenchDoNotOptimize(det);
    }
}


BH_BENCH_TEST(Inverse)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_Mat4fInverse(matA, outInv);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(outInv);
    }
}


BH_BENCH_TEST(FromScale)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromScale(2.0f, 3.0f, 4.0f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromTranslation)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromTranslation(1.0f, -1.0f, 2.5f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromRotationX)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromRotationX(0.7854f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromRotationY)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromRotationY(0.7854f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromRotationZ)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromRotationZ(0.7854f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromAxis)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromAxis(axis, 1.0472f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromEuler)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromEuler(0.3f, 0.4f, 0.5f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromQuat4f)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromQuat4f(quat, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromOrtho)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromOrtho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromFrustum)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromFrustum(60.0f, 1.77f, 0.1f, 100.0f, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(FromLookAt)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fFromLookAt(camPos, camAt, camUp, outMat);
        BH_BenchDoNotOptimize(outMat);
    }
}


BH_BENCH_TEST(ApplyVec4f)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fApplyVec4f(matA, vec4, outVec4);
        BH_BenchDoNotOptimize(outVec4);
    }
}


BH_BENCH_TEST(ApplyVec3f)
{
    while (BH_BenchIter(state))
    {
        BH_Mat4fApplyVec3f(matA, vec3, outVec3);
        BH_BenchDoNotOptimize(outVec3);
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
    BH_BENCH_ADD(FromRotationX);
    BH_BENCH_ADD(FromRotationY);
    BH_BENCH_ADD(FromRotationZ);
    BH_BENCH_ADD(FromAxis);
    BH_BENCH_ADD(FromEuler);
    BH_BENCH_ADD(FromQuat4f);
    BH_BENCH_ADD(FromOrtho);
    BH_BENCH_ADD(FromFrustum);
    BH_BENCH_ADD(FromLookAt);
    BH_BENCH_ADD(ApplyVec4f);
    BH_BENCH_ADD(ApplyVec3f);

    return BH_BenchRun();
}
