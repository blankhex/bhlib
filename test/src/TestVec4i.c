#include <BH/Math/Vec4i.h>
#include <BH/Unit.h>


BH_UNIT_TEST(Add)
{
    int a[4], b[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;

    BH_Vec4iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);
    BH_VERIFY(r[2] == 10);
    BH_VERIFY(r[3] == 12);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    int a[4], b[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;

    BH_Vec4iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);
    BH_VERIFY(r[2] == -4);
    BH_VERIFY(r[3] == -4);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    int a[4], b[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;

    BH_Vec4iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);
    BH_VERIFY(r[2] == 21);
    BH_VERIFY(r[3] == 32);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    int a[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;

    BH_Vec4iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);
    BH_VERIFY(r[2] == 30);
    BH_VERIFY(r[3] == 40);

    return 0;
}


BH_UNIT_TEST(MulAdd)
{
    int a[4], b[4], c[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;
    c[0] = 4; c[1] = 3; c[2] = 2; c[3] = 1;

    BH_Vec4iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);
    BH_VERIFY(r[2] == 23);
    BH_VERIFY(r[3] == 33);

    return 0;
}


BH_UNIT_TEST(Negate)
{
    int a[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;

    BH_Vec4iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);
    BH_VERIFY(r[2] == -3);
    BH_VERIFY(r[3] == -4);

    return 0;
}


BH_UNIT_TEST(Min)
{
    int a[4], b[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;

    BH_Vec4iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);
    BH_VERIFY(r[3] == 4);

    BH_Vec4iMin(b, a, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);
    BH_VERIFY(r[3] == 4);

    return 0;
}


BH_UNIT_TEST(Max)
{
    int a[4], b[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;

    BH_Vec4iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);
    BH_VERIFY(r[3] == 8);

    BH_Vec4iMax(b, a, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);
    BH_VERIFY(r[3] == 8);

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
