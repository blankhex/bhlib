#include <BH/Math.h>
#include <string.h>
#include <math.h>

#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


int BH_Ray2fIntersectLine(const float *start,
                          const float *direction,
                          const float *line,
                          float *t,
                          float *out)
{
    float tmp1[2];
    float denom, time;

    /* Calculate intersection time */
    denom = BH_Vec2fDot(direction, line);
    time = (line[2] - BH_Vec2fDot(line, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (fabsf(denom) < EPSILON || time < 0.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec2fScale(direction, time, tmp1);
    BH_Vec2fAdd(start, tmp1, out);
    *t = time;
    return BH_OK;
}


int BH_Ray2fIntersectTime(const float *aStart,
                          const float *aDirection,
                          const float *bStart,
                          const float *bDirection,
                          float *time1,
                          float *time2)
{
    float tmp1[2], tmp2[2], tmp3[2];
    float denom;

    /* Rotate directions by 90 degrees and caluclate denom */
    tmp1[0] = -aDirection[1]; tmp1[1] = aDirection[0];
    tmp2[0] = -bDirection[1]; tmp2[1] = bDirection[0];
    denom = BH_Vec2fDot(tmp1, bDirection);

    if (fabsf(denom) < EPSILON)
        return BH_ERROR;

    /* Calculate segments offset and intersection times */
    BH_Vec2fSub(aStart, bStart, tmp3);
    *time1 = BH_Vec2fDot(tmp3, tmp2) / denom;
    *time2 = BH_Vec2fDot(tmp3, tmp1) / denom;

    return BH_OK;
}


int BH_Ray2fIntersectRay(const float *aStart,
                         const float *aDirection,
                         const float *bStart,
                         const float *bDirection,
                         float *t,
                         float *out)
{
    float tmp[2];
    float time1, time2;

    if (BH_Ray2fIntersectTime(aStart, aDirection, bStart, bDirection, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time2 < 0.0f)
        return BH_ERROR;

    BH_Vec2fScale(aDirection, time1, tmp);
    BH_Vec2fAdd(aStart, tmp, out);
    *t = time1;
    return BH_OK;
}


int BH_Ray2fIntersectSegment(const float *aStart,
                             const float *aDirection,
                             const float *bStart,
                             const float *bEnd,
                             float *t,
                             float *out)
{
    float tmp[2];
    float time1, time2;

    BH_Vec2fSub(bEnd, bStart, tmp);
    if (BH_Ray2fIntersectTime(aStart, aDirection, bStart, tmp, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time2 < 0.0f || time2 > 1.0f)
        return BH_ERROR;

    BH_Vec2fScale(aDirection, time1, tmp);
    BH_Vec2fAdd(aStart, tmp, out);
    *t = time1;
    return BH_OK;
}


int BH_Segment2fIntersectLine(const float *start,
                              const float *end,
                              const float *line,
                              float *t,
                              float *out)
{
    float tmp[2];
    float denom, time;

    /* Calculate intersection time */
    BH_Vec2fSub(end, start, tmp);
    denom = BH_Vec2fDot(tmp, line);
    time = (line[2] - BH_Vec2fDot(line, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (fabsf(denom) < EPSILON || time < 0.0f || time > 1.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec2fScale(tmp, time, tmp);
    BH_Vec2fAdd(start, tmp, out);
    *t = time;
    return BH_OK;
}


int BH_Segment2fIntersectSegment(const float *aStart,
                                 const float *aEnd,
                                 const float *bStart,
                                 const float *bEnd,
                                 float *t,
                                 float *out)
{
    float tmp1[2], tmp2[2];
    float time1, time2;

    BH_Vec2fSub(aEnd, aStart, tmp1);
    BH_Vec2fSub(bEnd, bStart, tmp2);
    if (BH_Ray2fIntersectTime(aStart, tmp1, bStart, tmp2, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time1 > 1.0f || time2 < 0.0f || time2 > 1.0f)
        return BH_ERROR;

    BH_Vec2fLerp(aStart, aEnd, time1, out);
    *t = time1;

    return BH_OK;
}

int BH_Ray2fIntersectBox2f(const float *aStart,
                           const float *aDirection,
                           const float *bMin,
                           const float *bMax,
                           float *t,
                           float *out)
{
    float timeNear, timeFar, hitNear, hitFar, denom, tmp;
    int i;

    timeNear = -1.0f / 0.0f;
    timeFar  =  1.0f / 0.0f;

    /* Check if origin inside box */
    if (!BH_Box2fContains(bMin, bMax, aStart))
    {
        memcpy(out, aStart, sizeof(float) * 2);
        *t = 0.0f;
        return BH_OK;
    }

    /* Check each axis for the minimal and maximum intersection time */
    for (i = 0; i < 2; i++)
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
    *t = timeNear;

    return BH_OK;
}


int BH_Segment2fIntersectBox2f(const float *aStart,
                               const float *aEnd,
                               const float *bMin,
                               const float *bMax,
                               float *t,
                               float *out)
{
    float tmp[3];
    float time;

    BH_Vec2fSub(aEnd, aStart, tmp);
    if (BH_Ray2fIntersectBox2f(aStart, tmp, bMin, bMax, &time, out))
        return BH_ERROR;

    if (time > 1.0f)
        return BH_ERROR;

    *t = time;
    return BH_OK;
}
