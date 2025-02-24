#include <BH/Math.h>
#include <BH/Unit.h>


BH_UNIT_TEST(Add)
{
    int a[2], b[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;

    BH_Vec2iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);

    return 0;
}


BH_UNIT_TEST(Sub)
{
    int a[2], b[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;

    BH_Vec2iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);

    return 0;
}


BH_UNIT_TEST(Mul)
{
    int a[2], b[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;

    BH_Vec2iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);

    return 0;
}


BH_UNIT_TEST(Scale)
{
    int a[2], r[2];

    a[0] = 1; a[1] = 2;

    BH_Vec2iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);

    return 0;
}


BH_UNIT_TEST(MulAdd)
{
    int a[2], b[2], c[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;
    c[0] = 4; c[1] = 3;

    BH_Vec2iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);

    return 0;
}


BH_UNIT_TEST(Negate)
{
    int a[2], r[2];

    a[0] = 1; a[1] = 2;

    BH_Vec2iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);

    return 0;
}


BH_UNIT_TEST(Min)
{
    int a[2], b[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;

    BH_Vec2iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);

    BH_Vec2iMin(b, a, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);

    return 0;
}


BH_UNIT_TEST(Max)
{
    int a[2], b[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;

    BH_Vec2iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);

    BH_Vec2iMax(b, a, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);

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
