#include <BH/Math/Ray3f.h>
#include <BH/Math/Vec3f.h>
#include <BH/Math/Box3f.h>
#include <BH/Math/Plane.h>
#include <string.h>
#include <math.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


int BH_Ray3fIntersectPlane(const float start[3],
                           const float direction[3],
                           const float plane[4],
                           float *t,
                           float out[3])
{
    float tmp1[3];
    float denom, time;

    /* Calculate intersection time */
    denom = BH_Vec3fDot(direction, plane);
    time = (plane[3] - BH_Vec3fDot(plane, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (fabsf(denom) < EPSILON || time < 0.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec3fScale(direction, time, tmp1);
    BH_Vec3fAdd(start, tmp1, out);
    *t = time;
    return BH_OK;
}


int BH_Ray3fIntersectTriangle(const float start[3],
                              const float direction[3],
                              const float a[3],
                              const float b[3],
                              const float c[3],
                              float *t,
                              float out[3])
{
    float plane[4];
    float tmp1[3], tmp2[3], tmp3[3];
    float time;

    /* Compute plane */
    if (BH_PlaneFromPoints(a, b, c, plane))
        return BH_ERROR;

    /* Compute intersection point in ray against plane */
    if (BH_Ray3fIntersectPlane(start, direction, plane, &time, tmp3))
        return BH_ERROR;

    /* Check if point inside rectangle */
    BH_Vec3fSub(b, a, tmp1);
    BH_Vec3fSub(tmp3, a, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    BH_Vec3fSub(c, b, tmp1);
    BH_Vec3fSub(tmp3, b, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    BH_Vec3fSub(a, c, tmp1);
    BH_Vec3fSub(tmp3, c, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    /* Copy intersection point */
    memcpy(out, tmp3, sizeof(tmp3));
    *t = time;
    return BH_OK;
}


int BH_Segment3fIntersectPlane(const float start[3],
                               const float end[3],
                               const float plane[4],
                               float *t,
                               float out[3])
{
    float tmp[3];
    float denom, time;

    /* Calculate intersection time */
    BH_Vec3fSub(end, start, tmp);
    denom = BH_Vec3fDot(tmp, plane);
    time = (plane[3] - BH_Vec3fDot(plane, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (fabsf(denom) < EPSILON || time < 0.0f || time > 1.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec3fScale(tmp, time, tmp);
    BH_Vec3fAdd(start, tmp, out);
    *t = time;
    return BH_OK;
}


int BH_Segment3fIntersectTriangle(const float start[3],
                                  const float end[3],
                                  const float a[3],
                                  const float b[3],
                                  const float c[3],
                                  float *t,
                                  float out[3])
{
    float plane[4];
    float tmp1[3], tmp2[3], tmp3[3];
    float time;

    /* Compute plane */
    if (BH_PlaneFromPoints(a, b, c, plane))
        return BH_ERROR;

    /* Compute intersection point in ray against plane */
    if (BH_Segment3fIntersectPlane(start, end, plane, &time, tmp3))
        return BH_ERROR;

    /* Check if point inside rectangle */
    BH_Vec3fSub(b, a, tmp1);
    BH_Vec3fSub(tmp3, a, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    BH_Vec3fSub(c, b, tmp1);
    BH_Vec3fSub(tmp3, b, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    BH_Vec3fSub(a, c, tmp1);
    BH_Vec3fSub(tmp3, c, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fDot(tmp1, plane) < 0.0f)
        return BH_ERROR;

    /* Copy intersection point */
    memcpy(out, tmp3, sizeof(tmp3));
    *t = time;
    return BH_OK;
}


int BH_Ray3fIntersectBox3f(const float aStart[3],
                           const float aDirection[3],
                           const float bMin[3],
                           const float bMax[3],
                           float *t,
                           float out[3])
{
    float timeNear, timeFar, hitNear, hitFar, denom, tmp;
    int i;

    timeNear = -1.0f / 0.0f;
    timeFar  =  1.0f / 0.0f;

    /* Check if origin inside box */
    if (!BH_Box3fContains(bMin, bMax, aStart))
    {
        memcpy(out, aStart, sizeof(float) * 3);
        *t = 0.0f;
        return BH_OK;
    }

    /* Check each axis for the minimal and maximum intersection time */
    for (i = 0; i < 3; i++)
    {
        if (fabsf(aDirection[i]) < EPSILON)
        {
            if (aStart[i] < bMin[i] || aStart[i] > bMax[i])
                return BH_ERROR;
            continue;
        }

        denom = 1.0f / aDirection[i];
        hitNear = (bMin[i] - aStart[i]) * denom;
        hitFar  = (bMax[i] - aStart[i]) * denom;

        if (hitNear > hitFar)
        {
            tmp = hitNear;
            hitNear = hitFar;
            hitFar = tmp;
        }

        if (hitNear > timeNear)
            timeNear = hitNear;
        if (hitFar < timeFar)
            timeFar = hitFar;

        if (timeNear > timeFar || timeFar < 0.0f)
            return BH_ERROR;
    }

    out[0] = aStart[0] + aDirection[0] * timeNear;
    out[1] = aStart[1] + aDirection[1] * timeNear;
    out[2] = aStart[2] + aDirection[2] * timeNear;
    *t = timeNear;

    return BH_OK;
}


int BH_Segment3fIntersectBox3f(const float aStart[3],
                               const float aEnd[3],
                               const float bMin[3],
                               const float bMax[3],
                               float *t,
                               float out[3])
{
    float tmp[3];
    float time;

    BH_Vec3fSub(aEnd, aStart, tmp);
    if (BH_Ray3fIntersectBox3f(aStart, tmp, bMin, bMax, &time, out))
        return BH_ERROR;

    if (time > 1.0f)
        return BH_ERROR;

    *t = time;
    return BH_OK;
}
