#include <BH/Math/Mat4f.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(Identity)
{
    float r[16];

    BH_Mat4fIdentity(r);
    BH_VERIFY(r[0] == 1.0f);
    BH_VERIFY(r[1] == 0.0f);
    BH_VERIFY(r[2] == 0.0f);
    BH_VERIFY(r[3] == 0.0f);

    BH_VERIFY(r[4] == 0.0f);
    BH_VERIFY(r[5] == 1.0f);
    BH_VERIFY(r[6] == 0.0f);
    BH_VERIFY(r[7] == 0.0f);

    BH_VERIFY(r[8] == 0.0f);
    BH_VERIFY(r[9] == 0.0f);
    BH_VERIFY(r[10] == 1.0f);
    BH_VERIFY(r[11] == 0.0f);

    BH_VERIFY(r[12] == 0.0f);
    BH_VERIFY(r[13] == 0.0f);
    BH_VERIFY(r[14] == 0.0f);
    BH_VERIFY(r[15] == 1.0f);

    return 0;
}


BH_UNIT_TEST(Add)
{
    float a[16], b[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_Mat4fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 14.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    float a[16], b[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_Mat4fSub(a, b, r);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], -4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], -2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], -1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    float a[16], b[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_Mat4fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 78.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 27.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 60.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 28.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 24.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 22.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 75.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 29.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 53.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 26.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    float a[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    BH_Mat4fScale(a, 10, r);
    BH_VERIFY_DELTA(r[0], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 20.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 40.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 70.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 30.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Transpose)
{
    float a[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    BH_Mat4fTranspose(a, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 7.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 3.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Trace)
{
    float a[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    BH_VERIFY_DELTA(BH_Mat4fTrace(a), 12.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Det)
{
    float a[16], b[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_VERIFY_DELTA(BH_Mat4fDet(a), 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_Mat4fDet(b), 0.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Inverse)
{
    float a[16], b[16], r[16];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_VERIFY(BH_Mat4fInverse(a, r) == BH_OK);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  1.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.6000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], -0.4000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], -0.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], -0.4000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  0.6000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat4fInverse(b, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(Translation)
{
    float r[16];

    BH_Mat4fFromTranslation(1.0f, 2.0f, 3.0f, r);
    BH_VERIFY_DELTA(r[0],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Scaling)
{
    float r[16];

    BH_Mat4fFromScale(1.0f, 2.0f, 3.0f, r);
    BH_VERIFY_DELTA(r[0],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Apply)
{
    float a[16];
    float b[4];

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 2.0f; b[1] = -1.0f; b[2] = 4.0f; b[3] = 0.0f;

    BH_Mat4fApplyVec4f(a, b, b);
    BH_VERIFY_DELTA(b[0], 17.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[1],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[2], 15.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[3],  4.0000f, ACCEPTABLE_DELTA);

    b[0] = 2.0f; b[1] = -1.0f; b[2] = 4.0f;
    BH_Mat4fApplyVec3f(a, b, b);
    BH_VERIFY_DELTA(b[0], 24.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[1],  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[2], 20.0000f, ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Identity);
    BH_UNIT_ADD(Add);
    BH_UNIT_ADD(Sub);
    BH_UNIT_ADD(Mul);
    BH_UNIT_ADD(Scale);
    BH_UNIT_ADD(Transpose);
    BH_UNIT_ADD(Trace);
    BH_UNIT_ADD(Det);
    BH_UNIT_ADD(Inverse);
    BH_UNIT_ADD(Translation);
    BH_UNIT_ADD(Scaling);
    BH_UNIT_ADD(Apply);

    return BH_UnitRun();
}
