#include <BH/Math.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(FromPoints)
{
    float a[2], b[2], r[3];

    a[0] = -8.0f; a[1] = 1.0f;
    b[0] = -2.0f; b[1] = 3.0f;

    BH_VERIFY(BH_LineFromPoints(a, b, r) == BH_OK);
    BH_VERIFY_DELTA(r[0],-0.3162f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 0.9487f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.4785f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Degenerate)
{
    float a[2], b[2], r[3];

    a[0] = -8.0f; a[1] = 1.0f;
    b[0] = -8.0f; b[1] = 1.0f;

    BH_VERIFY(BH_LineFromPoints(a, b, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(Distance)
{
    float a[2], b[2], r[3];

    a[0] = -8.0f; a[1] = 1.0f;
    b[0] = -2.0f; b[1] = 3.0f;

    BH_VERIFY(BH_LineFromPoints(a, b, r) == BH_OK);
    BH_VERIFY_DELTA(BH_LineDistance(r, a), 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_LineDistance(r, b), 0.0000f, ACCEPTABLE_DELTA);

    a[0] = -7.0f; a[1] = 4.0f;
    BH_VERIFY_DELTA(BH_LineDistance(r, a), 2.5298f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(ClosestPoint)
{
    float a[2], b[2], r[3];

    a[0] = -8.0f; a[1] = 1.0f;
    b[0] = -2.0f; b[1] = 3.0f;

    BH_VERIFY(BH_LineFromPoints(a, b, r) == BH_OK);

    a[0] = -7.0f; a[1] = 4.0f;
    BH_LineClosestPoint(r, a, b);
    BH_VERIFY_DELTA(b[0],-6.2000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(b[1], 1.6000f, ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(FromPoints);
    BH_UNIT_ADD(Degenerate);
    BH_UNIT_ADD(Distance);
    BH_UNIT_ADD(ClosestPoint);

    return BH_UnitRun();
}
