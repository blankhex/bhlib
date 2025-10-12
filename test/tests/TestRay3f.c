#include <BH/Math/Ray3f.h>
#include <BH/Math/Vec3f.h>
#include <BH/Math/Box3f.h>
#include <BH/Math/Plane.h>
#include <BH/Math/Misc.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(RayIntersectTriangle)
{
    float a[3], b[3], c[3], p[3], d[3], out[3], t;

    a[0] =-3.0000f; a[1] = 1.0000f; a[2] = 2.0000f;
    b[0] =-5.0000f; b[1] =-2.0000f; b[2] = 0.0000f;
    c[0] =-6.0000f; c[1] = 2.5000f; c[2] =-1.0000f;

    p[0] =-1.5000f; p[1] = 1.0000f; p[2] = 1.0000f;
    d[0] =-1.0000f; d[1] = 0.0000f; d[2] = 0.0000f;

    BH_VERIFY(BH_Ray3fIntersectTriangle(p, d, a, b, c, &t, out) == BH_OK);

    BH_VERIFY_DELTA(t, 2.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[0],-4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[2], 1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(SegmentIntersectTriangle)
{
    float a[3], b[3], c[3], d[3], f[3], out[3], t;

    a[0] =-3.0000f; a[1] = 1.0000f; a[2] = 2.0000f;
    b[0] =-5.0000f; b[1] =-2.0000f; b[2] = 0.0000f;
    c[0] =-6.0000f; c[1] = 2.5000f; c[2] =-1.0000f;

    d[0] =-1.5000f; d[1] = 1.0000f; d[2] = 1.0000f;
    f[0] =-6.0000f; f[1] = 1.0000f; f[2] = 1.0000f;

    BH_VERIFY(BH_Segment3fIntersectTriangle(d, f, a, b, c, &t, out) == BH_OK);
    BH_VERIFY_DELTA(out[0],-4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[2], 1.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(d, f, t, out);
    BH_VERIFY_DELTA(out[0],-4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[2], 1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Barycentric)
{
    float a[3], b[3], c[3], p[3], d[3], out[3], t;

    a[0] =-3.0000f; a[1] = 1.0000f; a[2] = 2.0000f;
    b[0] =-5.0000f; b[1] =-2.0000f; b[2] = 0.0000f;
    c[0] =-6.0000f; c[1] = 2.5000f; c[2] =-1.0000f;

    p[0] =-1.5000f; p[1] = 1.0000f; p[2] = 1.0000f;
    d[0] =-1.0000f; d[1] = 0.0000f; d[2] = 0.0000f;

    BH_VERIFY(BH_Ray3fIntersectTriangle(p, d, a, b, c, &t, out) == BH_OK);
    (void)t;

    BH_Triangle3fBarycentric(a, b, c, out, out);
    BH_VERIFY(out[0] >= 0.0f);
    BH_VERIFY(out[1] >= 0.0f);
    BH_VERIFY(out[2] >= 0.0f);

    BH_VERIFY(out[0] <= 1.0f);
    BH_VERIFY(out[1] <= 1.0f);
    BH_VERIFY(out[2] <= 1.0f);

    BH_VERIFY_DELTA(out[0] + out[1] + out[2], 1.0000f, ACCEPTABLE_DELTA);

    BH_Vec3fBarycentric(a, b, c, out[1], out[2], out);
    BH_VERIFY_DELTA(out[0],-4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(out[2], 1.0000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(RayBox)
{
    float start[3], direction[3], bMin[3], bMax[3], r[3];
    float time;

    bMin[0] =-2.0f; bMin[1] =-2.0f; bMin[2] =-2.0f;
    bMax[0] = 3.0f; bMax[1] = 3.0f; bMax[2] = 3.0f;

    start[0] = 0.0f; start[1] = 0.0f; start[2] = 0.0f;
    direction[0] = 1.0f; direction[1] = 0.0f; direction[2] = 0.0f;
    BH_VERIFY(BH_Ray3fIntersectBox3f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = -4.0f; start[1] = 0.0f; start[2] = 0.0f;
    BH_VERIFY(BH_Ray3fIntersectBox3f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 0.0f; start[2] = 0.0f;
    BH_VERIFY(BH_Ray3fIntersectBox3f(start, direction, bMin, bMax, &time, r) != BH_OK);

    start[0] = 4.0f; start[1] = 0.0f; start[2] = 0.0f;
    direction[0] = -1.0f; direction[1] = 0.0f; direction[2] = 0.0f;
    BH_VERIFY(BH_Ray3fIntersectBox3f(start, direction, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 4.0f; start[2] = 4.0f;
    direction[0] = -1.0f; direction[1] = 0.0f; direction[2] = 0.0f;
    BH_VERIFY(BH_Ray3fIntersectBox3f(start, direction, bMin, bMax, &time, r) != BH_OK);

    return 0;
}


BH_UNIT_TEST(SegmentBox)
{
    float start[3], end[3], bMin[3], bMax[3], r[3];
    float time;

    bMin[0] =-2.0f; bMin[1] =-2.0f; bMin[2] =-2.0f;
    bMax[0] = 3.0f; bMax[1] = 3.0f; bMax[2] = 3.0f;

    start[0] = 0.0f; start[1] = 0.0f; start[2] = 0.0f;
    end[0] = 5.0f; end[1] = 0.0f; end[2] = 0.0f;
    BH_VERIFY(BH_Segment3fIntersectBox3f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = -4.0f; start[1] = 0.0f; start[2] = 0.0f;
    BH_VERIFY(BH_Segment3fIntersectBox3f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 0.0f; start[2] = 0.0f;
    BH_VERIFY(BH_Segment3fIntersectBox3f(start, end, bMin, bMax, &time, r) != BH_OK);

    start[0] = 4.0f; start[1] = 0.0f; start[2] = 0.0f;
    end[0] = -5.0f; end[1] = 0.0f; end[2] = 0.0f;
    BH_VERIFY(BH_Segment3fIntersectBox3f(start, end, bMin, bMax, &time, r) == BH_OK);
    BH_VERIFY(BH_Box3fContains(bMin, bMax, r) == BH_OK);

    start[0] = 4.0f; start[1] = 4.0f; start[2] = 4.0f;
    end[0] = -5.0f; end[1] = 4.0f; end[2] = 0.0f;
    BH_VERIFY(BH_Segment3fIntersectBox3f(start, end, bMin, bMax, &time, r) != BH_OK);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(RayIntersectTriangle);
    BH_UNIT_ADD(SegmentIntersectTriangle);
    BH_UNIT_ADD(Barycentric);
    BH_UNIT_ADD(RayBox);
    BH_UNIT_ADD(SegmentBox);

    return BH_UnitRun();
}
