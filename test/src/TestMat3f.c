#include <BH/Math/Mat3f.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(Identity)
{
    float r[9];

    BH_Mat3fIdentity(r);
    BH_VERIFY(r[0] == 1.0f);
    BH_VERIFY(r[1] == 0.0f);
    BH_VERIFY(r[2] == 0.0f);

    BH_VERIFY(r[3] == 0.0f);
    BH_VERIFY(r[4] == 1.0f);
    BH_VERIFY(r[5] == 0.0f);

    BH_VERIFY(r[6] == 0.0f);
    BH_VERIFY(r[7] == 0.0f);
    BH_VERIFY(r[8] == 1.0f);

    return 0;
}


BH_UNIT_TEST(Add)
{
    float a[9], b[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_Mat3fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 8.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    float a[9], b[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_Mat3fSub(a, b, r);
    BH_VERIFY_DELTA(r[0],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  1.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 0.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    float a[9], b[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_Mat3fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 21.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 27.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 12.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 18.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    float a[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    BH_Mat3fScale(a, 10, r);
    BH_VERIFY_DELTA(r[0], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 30.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 40.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Transpose)
{
    float a[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    BH_Mat3fTranspose(a, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 4.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Trace)
{
    float a[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    BH_VERIFY_DELTA(BH_Mat3fTrace(a), 9.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Det)
{
    float a[9], b[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_VERIFY_DELTA(BH_Mat3fDet(a), 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_Mat3fDet(b), 0.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Inverse)
{
    float a[9], b[9], r[9];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_VERIFY(BH_Mat3fInverse(a, r) == BH_OK);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  1.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.3333f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], -2.3333f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], -0.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat3fInverse(b, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(Translation)
{
    float r[9];

    BH_Mat3fFromTranslation(1.0f, 2.0f, r);
    BH_VERIFY_DELTA(r[0],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8],  1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Scaling)
{
    float r[9];

    BH_Mat3fFromScale(1.0f, 2.0f, r);
    BH_VERIFY_DELTA(r[0],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8],  1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Apply)
{
    float a[9];
    float b[3];

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[1] = -1.0f; b[2] = 4.0f;

    BH_Mat3fApplyVec3f(a, b, b);
    BH_VERIFY_DELTA(b[0], 17.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[2], 15.0000f, ACCEPTABLE_DELTA);

    b[0] = 2.0f; b[1] = -1.0f;
    BH_Mat3fApplyVec2f(a, b, b);
    BH_VERIFY_DELTA(b[0], 11.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[1], 6.0000f, ACCEPTABLE_DELTA);

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
