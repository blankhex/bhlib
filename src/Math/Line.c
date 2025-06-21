#include <BH/Math/Line.h>
#include <BH/Math/Vec2f.h>
#include <string.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


int BH_LineFromPoints(const float a[2],
                      const float b[2],
                      float out[3])
{
    float tmp[2];

    tmp[0] = a[1] - b[1];
    tmp[1] = b[0] - a[0];
    if (BH_Vec2fNormalEx(tmp, tmp) < EPSILON)
        return BH_ERROR;

    out[2] = BH_Vec2fDot(tmp, a);
    memcpy(out, tmp, sizeof(tmp));
    return BH_OK;
}


float BH_LineDistance(const float line[3],
                      const float point[2])
{
    return BH_Vec2fDot(line, point) - line[2];
}


void BH_LineClosestPoint(const float line[3],
                         const float point[2],
                         float out[2])
{
    float tmp[2];

    BH_Vec2fScale(line, BH_LineDistance(line, point), tmp);
    BH_Vec2fSub(point, tmp, out);
}
