#include <BH/Math.h>
#include <string.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


void BH_Box2fUnion(const float aMin[2],
                   const float aMax[2],
                   const float bMin[2],
                   const float bMax[2],
                   float outMin[2],
                   float outMax[2])
{
    BH_Vec2fMin(aMin, bMin, outMin);
    BH_Vec2fMax(aMax, bMax, outMax);
}


int BH_Box2fIntersect(const float aMin[2],
                      const float aMax[2],
                      const float bMin[2],
                      const float bMax[2],
                      float outMin[2],
                      float outMax[2])
{
    BH_Vec2fMax(aMin, bMin, outMin);
    BH_Vec2fMin(aMax, bMax, outMax);

    if (outMin[0] >= outMax[0] || outMin[1] >= outMax[1])
        return BH_ERROR;

    return BH_OK;
}


int BH_Box2fContains(const float aMin[2],
                     const float aMax[2],
                     const float point[2])
{
    if (point[0] < aMin[0] || point[1] < aMin[1])
        return BH_ERROR;

    if (point[0] > aMax[0] || point[1] > aMax[1])
        return BH_ERROR;

    return BH_OK;
}


int BH_Box2fEnclose(const float *points,
                    size_t size,
                    float outMin[2],
                    float outMax[2])
{
    float tmp1[2], tmp2[2];
    size_t i;

    if (!size)
        return BH_ERROR;

    memcpy(tmp1, points, sizeof(tmp1));
    memcpy(tmp2, points, sizeof(tmp2));

    for (i = 1; i < size; i++)
    {
        BH_Vec2fMin(tmp1, points + i * 2, tmp1);
        BH_Vec2fMax(tmp2, points + i * 2, tmp2);
    }

    memcpy(outMin, tmp1, sizeof(tmp1));
    memcpy(outMax, tmp2, sizeof(tmp2));
    return BH_OK;
}
