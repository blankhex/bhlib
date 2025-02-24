#include <BH/Math.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(Add)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fSub(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -4.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fMul(a, b, r);
    BH_VERIFY_DELTA(r[0],  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 12.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 21.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    float a[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;

    BH_Vec3fScale(a, 10.0000f, r);
    BH_VERIFY_DELTA(r[0], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 30.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(MulAdd)
{
    float a[3], b[3], c[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;
    c[0] = 1.5000f; c[1] = 2.5000f; c[2] = 3.5000f;

    BH_Vec3fMulAdd(a, b, c, r);
    BH_VERIFY_DELTA(r[0],  6.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 14.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 24.5000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Negate)
{
    float a[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;

    BH_Vec3fNegate(a, r);
    BH_VERIFY_DELTA(r[0], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Dot)
{
    float a[3], b[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;
    BH_VERIFY_DELTA(BH_Vec3fDot(a, b), 38.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Cross)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fCross(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -4.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Length)
{
    float a[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    BH_VERIFY_DELTA(BH_Vec3fLength(a), sqrt(14.0000f), ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Normal)
{
    float a[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;

    BH_Vec3fNormal(a, r);
    BH_VERIFY_DELTA(r[0], 1.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(BH_Vec3fNormalEx(a, r), sqrt(14.0000f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[0], 1.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f / sqrt(14.0000f), ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Min)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fMin(a, b, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fMin(b, a, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Max)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fMax(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fMax(b, a, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Lerp)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;

    BH_Vec3fLerp(a, b, 0.0000f, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(a, b, 0.5000f, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(a, b, 1.0000f, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Project)
{
    float a[3], b[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 4.0000f; b[1] = 3.0000f; b[2] = 2.0000f;

    BH_Vec3fProject(a, b, r);
    BH_VERIFY_DELTA(r[0], 2.2069f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 1.6552f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 1.1034f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Barycentric)
{
    float a[3], b[3], c[3], r[3];

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 5.0000f; b[1] = 6.0000f; b[2] = 7.0000f;
    c[0] = 1.5000f; c[1] = 2.5000f; c[2] = 3.5000f;

    BH_Vec3fBarycentric(a, b, c, 0.5f, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 3.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 4.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.2500f, ACCEPTABLE_DELTA);

    BH_Vec3fBarycentric(a, b, c, 0.25f, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 2.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 3.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 4.2500f, ACCEPTABLE_DELTA);

    a[0] = 1.0000f; a[1] = 2.0000f; a[2] = 3.0000f;
    b[0] = 4.0000f; b[1] = 3.0000f; b[2] = 2.0000f;
    c[0] = 4.0000f; c[1] = 4.0000f; c[2] = 4.0000f;

    BH_Vec3fBarycentric(a, b, c, 0.0f, 0.0f, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fBarycentric(a, b, c, 0.5f, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 3.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fBarycentric(a, b, c, 0.25f, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 3.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 3.2500f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.2500f, ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Add);
    BH_UNIT_ADD(Sub);
    BH_UNIT_ADD(Mul);
    BH_UNIT_ADD(Scale);
    BH_UNIT_ADD(MulAdd);
    BH_UNIT_ADD(Negate);
    BH_UNIT_ADD(Dot);
    BH_UNIT_ADD(Cross);
    BH_UNIT_ADD(Length);
    BH_UNIT_ADD(Normal);
    BH_UNIT_ADD(Min);
    BH_UNIT_ADD(Max);
    BH_UNIT_ADD(Lerp);
    BH_UNIT_ADD(Project);
    BH_UNIT_ADD(Barycentric);

    return BH_UnitRun();
}
