#include <BH/Math.h>


float BH_Lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}


void BH_Triangle3fBarycentric(const float *a,
                              const float *b,
                              const float *c,
                              const float *point,
                              float *out)
{
    float tmp1[3], tmp2[3], tmp3[3];
    float t11, t12, t22, t31, t32, denom;

    BH_Vec3fSub(b, a, tmp1);
    BH_Vec3fSub(c, a, tmp2);
    BH_Vec3fSub(point, a, tmp3);

    t11 = BH_Vec3fDot(tmp1, tmp1);
    t12 = BH_Vec3fDot(tmp1, tmp2);
    t22 = BH_Vec3fDot(tmp2, tmp2);
    t31 = BH_Vec3fDot(tmp3, tmp1);
    t32 = BH_Vec3fDot(tmp3, tmp2);
    denom = 1.0f / (t11 * t22 - t12 * t12);

    out[1] = (t22 * t31 - t12 * t32) * denom;
    out[2] = (t11 * t32 - t12 * t31) * denom;
    out[0] = 1.0f - out[1] - out[2];
}
