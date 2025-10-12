#include <BH/Math/Vec3i.h>
#include <BH/Unit.h>


BH_UNIT_TEST(Add)
{
    int a[3], b[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;

    BH_Vec3iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);
    BH_VERIFY(r[2] == 10);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    int a[3], b[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;

    BH_Vec3iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);
    BH_VERIFY(r[2] == -4);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    int a[3], b[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;

    BH_Vec3iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);
    BH_VERIFY(r[2] == 21);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    int a[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;

    BH_Vec3iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);
    BH_VERIFY(r[2] == 30);

    return 0;
}


BH_UNIT_TEST(MulAdd)
{
    int a[3], b[3], c[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;
    c[0] = 4; c[1] = 3; c[2] = 2;

    BH_Vec3iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);
    BH_VERIFY(r[2] == 23);

    return 0;
}


BH_UNIT_TEST(Negate)
{
    int a[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;

    BH_Vec3iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);
    BH_VERIFY(r[2] == -3);

    return 0;
}


BH_UNIT_TEST(Min)
{
    int a[3], b[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;

    BH_Vec3iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);

    BH_Vec3iMin(b, a, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);

    return 0;
}


BH_UNIT_TEST(Max)
{
    int a[3], b[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;

    BH_Vec3iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);

    BH_Vec3iMax(b, a, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);

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
    BH_UNIT_ADD(Min);
    BH_UNIT_ADD(Max);

    return BH_UnitRun();
}
