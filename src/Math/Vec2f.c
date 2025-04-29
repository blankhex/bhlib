#include <BH/Math.h>
#include <math.h>


void BH_Vec2fAdd(const float a[2],
                 const float b[2],
                 float out[2])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}


void BH_Vec2fSub(const float a[2],
                 const float b[2],
                 float out[2])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}


void BH_Vec2fMul(const float a[2],
                 const float b[2],
                 float out[2])
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}


void BH_Vec2fScale(const float a[2],
                   float b,
                   float out[2])
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
}


void BH_Vec2fMulAdd(const float a[2],
                    const float b[2],
                    const float c[2],
                    float out[2])
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
}


void BH_Vec2fNegate(const float in[2],
                    float out[2])
{
    out[0] = -in[0];
    out[1] = -in[1];
}


float BH_Vec2fDot(const float a[2],
                  const float b[2])
{
    return a[0] * b[0] + a[1] * b[1];
}


float BH_Vec2fCross(const float a[2],
                    const float b[2])
{
    return a[0] * b[1] - a[1] * b[0];
}


float BH_Vec2fLength(const float in[2])
{
    return sqrtf(BH_Vec2fDot(in, in));
}


void BH_Vec2fNormal(const float in[2],
                    float out[2])
{
    BH_Vec2fScale(in, 1.0f / BH_Vec2fLength(in), out);
}


float BH_Vec2fNormalEx(const float in[2],
                       float out[2])
{
    float length;

    length = BH_Vec2fLength(in);
    BH_Vec2fScale(in, 1.0f / length, out);
    return length;
}


void BH_Vec2fMin(const float a[2],
                 const float b[2],
                 float out[2])
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Vec2fMax(const float a[2],
                 const float b[2],
                 float out[2])
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Vec2fLerp(const float a[2],
                  const float b[2],
                  float t,
                  float out[2])
{
    float tmp[2];

    BH_Vec2fSub(b, a, tmp);
    BH_Vec2fScale(tmp, t, tmp);
    BH_Vec2fAdd(a, tmp, out);
}


void BH_Vec2fProject(const float a[2],
                     const float b[2],
                     float out[2])
{
    float amount;

    amount = BH_Vec2fDot(a, b) / BH_Vec2fDot(b, b);
    BH_Vec2fScale(b, amount, out);
}


void BH_Vec2fBarycentric(const float a[2],
                         const float b[2],
                         const float c[2],
                         float v,
                         float w,
                         float out[2])
{
    float tmp1[2], tmp2[2];
    float u;

    u = 1.0f - v - w;
    tmp1[0] = tmp1[1] = u; BH_Vec2fMul(a, tmp1, tmp2);
    tmp1[0] = tmp1[1] = v; BH_Vec2fMulAdd(b, tmp1, tmp2, tmp2);
    tmp1[0] = tmp1[1] = w; BH_Vec2fMulAdd(c, tmp1, tmp2, out);
}
