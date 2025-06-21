#include <BH/Math/Plane.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(FromPoints)
{
    float a[3], b[3], c[3], r[4];

    a[0] = 1; a[1] = -2; a[2] = 1;
    b[0] = 4; b[1] = -2; b[2] = -2;
    c[0] = 4; c[1] = 1; c[2] = 4;

    BH_VERIFY(BH_PlaneFromPoints(a, b, c, r) == BH_OK);

    BH_VERIFY_DELTA(r[0],-0.4082f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 0.8165f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],-0.4082f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],-2.4495f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Degenerate)
{
    float a[3], b[3], c[3], r[4];

    a[0] = 1; a[1] = -2; a[2] = 1;
    b[0] = 1; b[1] = -2; b[2] = 1;
    c[0] = 4; c[1] = 1; c[2] = 4;

    BH_VERIFY(BH_PlaneFromPoints(a, b, c, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(Distance)
{
    float a[3], b[3], c[3], r[4];

    a[0] = 1; a[1] = -2; a[2] = 1;
    b[0] = 4; b[1] = -2; b[2] = -2;
    c[0] = 4; c[1] = 1; c[2] = 4;

    BH_VERIFY(BH_PlaneFromPoints(a, b, c, r) == BH_OK);

    BH_VERIFY_DELTA(BH_PlaneDistance(r, a), 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_PlaneDistance(r, b), 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_PlaneDistance(r, c), 0.0000f, ACCEPTABLE_DELTA);

    a[0] = 3; a[1] = 4; a[2] = 5;
    b[0] = 2; b[1] = -1; b[2] = 6;
    BH_VERIFY_DELTA(BH_PlaneDistance(r, a), 2.4495f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(BH_PlaneDistance(r, b), -1.6330f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(ClosestPoint)
{
    float a[3], b[3], c[3], r[4];

    a[0] = 1; a[1] = -2; a[2] = 1;
    b[0] = 4; b[1] = -2; b[2] = -2;
    c[0] = 4; c[1] = 1; c[2] = 4;

    BH_VERIFY(BH_PlaneFromPoints(a, b, c, r) == BH_OK);

    b[0] = 3; b[1] = 4; b[2] = 5;

    BH_PlaneClosestPoint(r, b, c);
    BH_VERIFY_DELTA(c[0], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(c[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(c[2], 6.0000f, ACCEPTABLE_DELTA);

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
