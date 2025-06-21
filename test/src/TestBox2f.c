#include <BH/Math/Box2f.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(Union)
{
    float aMin[2], aMax[2], bMin[2], bMax[2], rMin[2], rMax[2];

    aMin[0] = 1.0f; aMin[1] = 2.0f;
    aMax[0] = 5.0f; aMax[1] = 5.0f;
    bMin[0] = 0.0f; bMin[1] = 0.0f;
    bMax[0] = 4.0f; bMax[1] = 4.0f;

    BH_Box2fUnion(aMin, aMax, bMin, bMax, rMin, rMax);
    BH_VERIFY_DELTA(rMin[0], 0.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMin[1], 0.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[0], 5.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[1], 5.0000f,  ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Intersect)
{
    float aMin[2], aMax[2], bMin[2], bMax[2], rMin[2], rMax[2];

    aMin[0] = 1.0f; aMin[1] = 2.0f;
    aMax[0] = 5.0f; aMax[1] = 5.0f;
    bMin[0] = 0.0f; bMin[1] = 0.0f;
    bMax[0] = 4.0f; bMax[1] = 4.0f;

    BH_VERIFY(BH_Box2fIntersect(aMin, aMax, bMin, bMax, rMin, rMax) == BH_OK);
    BH_VERIFY_DELTA(rMin[0], 1.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMin[1], 2.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[0], 4.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[1], 4.0000f,  ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Contains)
{
    float aMin[2], aMax[2], point[2];

    aMin[0] = 1.0f; aMin[1] = 2.0f;
    aMax[0] = 5.0f; aMax[1] = 5.0f;

    point[0] = 0.0f; point[1] = 0.0f;
    BH_VERIFY(BH_Box2fContains(aMin, aMax, point) != BH_OK);

    point[0] = 1.0f; point[1] = 2.0f;
    BH_VERIFY(BH_Box2fContains(aMin, aMax, point) == BH_OK);

    point[0] = 4.0f; point[1] = 4.0f;
    BH_VERIFY(BH_Box2fContains(aMin, aMax, point) == BH_OK);

    point[0] = 6.0f; point[1] = 6.0f;
    BH_VERIFY(BH_Box2fContains(aMin, aMax, point) != BH_OK);

    return 0;
}


BH_UNIT_TEST(Enclose)
{
    float points[4], rMin[2], rMax[2];

    points[0] = 5.0f; points[1] = 5.0f;
    points[2] = 1.0f; points[3] = 2.0f;

    BH_VERIFY(BH_Box2fEnclose(NULL, 0, NULL, NULL) != BH_OK);
    BH_VERIFY(BH_Box2fEnclose(points, 2, rMin, rMax) == BH_OK);
    BH_VERIFY_DELTA(rMin[0], 1.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMin[1], 2.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[0], 5.0000f,  ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(rMax[1], 5.0000f,  ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Union);
    BH_UNIT_ADD(Intersect);
    BH_UNIT_ADD(Contains);
    BH_UNIT_ADD(Enclose);

    return BH_UnitRun();
}
