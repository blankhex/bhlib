#include <BH/Math.h>
#include <math.h>


void BH_Vec4fAdd(const float a[4],
                 const float b[4],
                 float out[4])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}


void BH_Vec4fSub(const float a[4],
                 const float b[4],
                 float out[4])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}


void BH_Vec4fMul(const float a[4],
                 const float b[4],
                 float out[4])
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}


void BH_Vec4fScale(const float a[4],
                   float b,
                   float out[4])
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
    out[3] = a[3] * b;
}


void BH_Vec4fMulAdd(const float a[4],
                    const float b[4],
                    const float c[4],
                    float out[4])
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
    out[3] = a[3] * b[3] + c[3];
}


void BH_Vec4fNegate(const float in[4],
                    float out[4])
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = -in[3];
}


float BH_Vec4fDot(const float a[4],
                  const float b[4])
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}


float BH_Vec4fLength(const float in[4])
{
    return sqrtf(BH_Vec4fDot(in, in));
}


void BH_Vec4fNormal(const float in[4],
                    float out[4])
{
    BH_Vec4fScale(in, 1.0f / BH_Vec4fLength(in), out);
}


float BH_Vec4fNormalEx(const float in[4],
                       float out[4])
{
    float length;

    length = BH_Vec4fLength(in);
    BH_Vec4fScale(in, 1.0f / length, out);
    return length;
}


void BH_Vec4fMin(const float a[4],
                 const float b[4],
                 float out[4])
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] < b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4fMax(const float a[4],
                 const float b[4],
                 float out[4])
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] > b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4fLerp(const float a[4],
                  const float b[4],
                  float t,
                  float out[4])
{
    float tmp[4];

    BH_Vec4fSub(b, a, tmp);
    BH_Vec4fScale(tmp, t, tmp);
    BH_Vec4fAdd(a, tmp, out);
}


void BH_Vec4fProject(const float a[4],
                     const float b[4],
                     float out[4])
{
    float amount;

    amount = BH_Vec4fDot(a, b) / BH_Vec4fDot(b, b);
    BH_Vec4fScale(b, amount, out);
}


void BH_Vec4fBarycentric(const float a[4],
                         const float b[4],
                         const float c[4],
                         float v,
                         float w,
                         float out[4])
{
    float tmp1[4], tmp2[4];
    float u;

    u = 1.0f - v - w;
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = u; BH_Vec4fMul(a, tmp1, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = v; BH_Vec4fMulAdd(b, tmp1, tmp2, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = w; BH_Vec4fMulAdd(c, tmp1, tmp2, out);
}
