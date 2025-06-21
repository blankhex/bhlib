#include <BH/Math/Plane.h>
#include <BH/Math/Vec3f.h>
#include <string.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


int BH_PlaneFromPoints(const float a[3],
                       const float b[3],
                       const float c[3],
                       float out[4])
{
    float tmp1[3], tmp2[3];

    BH_Vec3fSub(b, a, tmp1);
    BH_Vec3fSub(c, a, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fNormalEx(tmp1, tmp1) < EPSILON)
        return BH_ERROR;

    out[3] = BH_Vec3fDot(a, tmp1);
    memcpy(out, tmp1, sizeof(tmp1));
    return BH_OK;
}


float BH_PlaneDistance(const float plane[4],
                       const float point[3])
{
    return BH_Vec3fDot(plane, point) - plane[3];
}


void BH_PlaneClosestPoint(const float plane[4],
                          const float point[3],
                          float out[3])
{
    float tmp[3];

    BH_Vec3fScale(plane, BH_PlaneDistance(plane, point), tmp);
    BH_Vec3fSub(point, tmp, out);
}
