#include <BH/Math.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(RayIntersectLine)
{
    float a[2], b[2], p[2], d[2], r[3];
    float time;

    a[0] = 4.0000f; a[1] = 9.0000f;
    b[0] = 2.0000f; b[1] = 5.0000f;

    p[0] = -5.0000f; p[1] = 3.0000f;
    d[0] =  0.8944f; d[1] = 0.4472f;

    BH_VERIFY(BH_LineFromPoints(a, b, r) == BH_OK);
    BH_VERIFY(BH_Ray2fIntersectLine(p, d, r, &time, r) == BH_OK);

    BH_VERIFY_DELTA(time, 8.9443f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fScale(d, time, r);
    BH_Vec2fAdd(p, r, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    d[0] = -2.0000f; d[1] = -4.0000f;
    BH_VERIFY(BH_LineFromPoints(a, b, r) == BH_OK);
    BH_VERIFY(BH_Ray2fIntersectLine(p, d, r, &time, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(RayIntersectRay)
{
    float p1[2], d1[2], p2[2], d2[2], r[2];
    float time;

    p1[0] = -5.0000f; p1[1] = 3.0000f;
    d1[0] =  0.8944f; d1[1] = 0.4472f;

    p2[0] =  4.0000f; p2[1] = 9.0000f;
    d2[0] = -0.4472f; d2[1] =-0.8944f;

    BH_VERIFY(BH_Ray2fIntersectRay(p1, d1, p2, d2, &time, r) == BH_OK);

    BH_VERIFY_DELTA(time, 8.9443f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fScale(d1, time, r);
    BH_Vec2fAdd(p1, r, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Ray2fIntersectRay(p1, d1, p2, d1, &time, r) != BH_OK);

    d1[0] = 0.0000f; d1[1] = 1.0000f;
    BH_VERIFY(BH_Ray2fIntersectRay(p1, d1, p2, d2, &time, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(RayIntersectSegment)
{
    float p[2], d[2], a[2], b[2], r[2];
    float time;

    p[0] = -5.0000f; p[1] = 3.0000f;
    d[0] =  0.8944f; d[1] = 0.4472f;

    a[0] =  4.0000f; a[1] = 9.0000f;
    b[0] =  2.0000f; b[1] = 5.0000f;

    BH_VERIFY(BH_Ray2fIntersectSegment(p, d, a, b, &time, r) == BH_OK);

    BH_VERIFY_DELTA(time, 8.9443f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fScale(d, time, r);
    BH_Vec2fAdd(p, r, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    d[0] = -2.0000f; d[1] = -4.0000f;
    BH_VERIFY(BH_Ray2fIntersectSegment(p, d, a, b, &time, r) != BH_OK);

    d[0] = 1.0000f; d[1] = 0.0000f;
    BH_VERIFY(BH_Ray2fIntersectSegment(p, d, a, b, &time, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(SegmentIntersectLine)
{
    float a1[2], b1[2], a2[2], b2[2], r[3];
    float time;

    a1[0] = -5.0000f; a1[1] = 3.0000f;
    b1[0] =  5.0000f; b1[1] = 8.0000f;

    a2[0] = 4.0000f; a2[1] = 9.0000f;
    b2[0] = 2.0000f; b2[1] = 5.0000f;

    BH_VERIFY(BH_LineFromPoints(a2, b2, r) == BH_OK);
    BH_VERIFY(BH_Segment2fIntersectLine(a1, b1, r, &time, r) == BH_OK);

    BH_VERIFY_DELTA(time, 0.8000f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fLerp(a1, b1, time, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(SegmentIntersectSegment)
{
    float a1[2], b1[2], a2[2], b2[2], r[2];
    float time;

    a1[0] = -5.0000f; a1[1] = 3.0000f;
    b1[0] =  5.0000f; b1[1] = 8.0000f;

    a2[0] =  4.0000f; a2[1] = 9.0000f;
    b2[0] =  2.0000f; b2[1] = 5.0000f;

    BH_VERIFY(BH_Segment2fIntersectSegment(a1, b1, a2, b2, &time, r) == BH_OK);

    BH_VERIFY_DELTA(time, 0.8000f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fLerp(a1, b1, time, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Time)
{
    float a1[2], b1[2], a2[2], b2[2], r[2];
    float time1, time2;

    a1[0] = -5.0000f; a1[1] = 3.0000f;
    b1[0] = 10.0000f; b1[1] = 5.0000f;

    a2[0] =  4.0000f; a2[1] = 9.0000f;
    b2[0] = -2.0000f; b2[1] =-4.0000f;

    BH_VERIFY(BH_Ray2fIntersectTime(a1, b1, a2, b2, &time1, &time2) == BH_OK);

    BH_VERIFY_DELTA(time1, 0.8000f, ACCEPTABLE_DELTA * 10);
    BH_VERIFY_DELTA(time2, 0.5000f, ACCEPTABLE_DELTA * 10);

    BH_Vec2fScale(b1, time1, r);
    BH_Vec2fAdd(a1, r, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    BH_Vec2fScale(b2, time2, r);
    BH_Vec2fAdd(a2, r, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 7.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(RayBox)
{
    float start[2], direction[2], bMin[2], bMax[2], r[2];
    float time;

    bMin[0] =-2.0f; bMin[1] =-2.0f;
    bMax[0] = 3.0f; bMax[1] = 3.0f;

    start[0] = 0.0f; start[1] = 0.0f;
    direction[0] = 1.0f; direction[1] = 0.0f;
    BH_VERIFY(BH_Ray2fIntersectBox2f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = -4.0f; start[1] = 0.0f;
    BH_VERIFY(BH_Ray2fIntersectBox2f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 0.0f;
    BH_VERIFY(BH_Ray2fIntersectBox2f(start, direction, bMin, bMax, &time, r) != BH_OK);

    start[0] = 4.0f; start[1] = 0.0f;
    direction[0] = -1.0f; direction[1] = 0.0f;
    BH_VERIFY(BH_Ray2fIntersectBox2f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 4.0f;
    direction[0] = -1.0f; direction[1] = 0.0f;
    BH_VERIFY(BH_Ray2fIntersectBox2f(start, direction, bMin, bMax, &time, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(SegmentBox)
{
    float start[2], end[2], bMin[2], bMax[2], r[2];
    float time;

    bMin[0] =-2.0f; bMin[1] =-2.0f;
    bMax[0] = 3.0f; bMax[1] = 3.0f;

    start[0] = 0.0f; start[1] = 0.0f;
    end[0] = 5.0f; end[1] = 0.0f;
    BH_VERIFY(BH_Segment2fIntersectBox2f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = -4.0f; start[1] = 0.0f;
    BH_VERIFY(BH_Segment2fIntersectBox2f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 0.0f;
    BH_VERIFY(BH_Segment2fIntersectBox2f(start, end, bMin, bMax, &time, r) != BH_OK);

    start[0] = 4.0f; start[1] = 0.0f;
    end[0] = -5.0f; end[1] = 0.0f;
    BH_VERIFY(BH_Segment2fIntersectBox2f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box2fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 4.0f;
    end[0] = -5.0f; end[1] = 4.0f;
    BH_VERIFY(BH_Segment2fIntersectBox2f(start, end, bMin, bMax, &time, r) != BH_OK);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(RayIntersectLine);
    BH_UNIT_ADD(RayIntersectRay);
    BH_UNIT_ADD(RayIntersectSegment);
    BH_UNIT_ADD(SegmentIntersectLine);
    BH_UNIT_ADD(SegmentIntersectSegment);
    BH_UNIT_ADD(Time);
    BH_UNIT_ADD(RayBox);
    BH_UNIT_ADD(SegmentBox);

    return BH_UnitRun();
}
