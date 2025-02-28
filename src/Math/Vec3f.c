#include <BH/Math.h>
#include <string.h>
#include <math.h>


void BH_Vec3fAdd(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}


void BH_Vec3fSub(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}


void BH_Vec3fMul(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}


void BH_Vec3fScale(const float *a,
                   const float b,
                   float *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
}


void BH_Vec3fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
}


void BH_Vec3fNegate(const float *in,
                    float *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
}


float BH_Vec3fDot(const float *a,
                  const float *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}


void BH_Vec3fCross(const float *a,
                   const float *b,
                   float *out)
{
    float tmp[3];

    tmp[0] = a[1] * b[2] - a[2] * b[1];
    tmp[1] = a[2] * b[0] - a[0] * b[2];
    tmp[2] = a[0] * b[1] - a[1] * b[0];
    memcpy(out, tmp, sizeof(tmp));
}


float BH_Vec3fLength(const float *in)
{
    return sqrtf(BH_Vec3fDot(in, in));
}


void BH_Vec3fNormal(const float *in,
                    float *out)
{
    BH_Vec3fScale(in, 1.0f / BH_Vec3fLength(in), out);
}


float BH_Vec3fNormalEx(const float *in,
                       float *out)
{
    float length;

    length = BH_Vec3fLength(in);
    BH_Vec3fScale(in, 1.0f / length, out);
    return length;
}


void BH_Vec3fMin(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
}


void BH_Vec3fMax(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
}


void BH_Vec3fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out)
{
    float tmp[3];

    BH_Vec3fSub(b, a, tmp);
    BH_Vec3fScale(tmp, t, tmp);
    BH_Vec3fAdd(a, tmp, out);
}


void BH_Vec3fProject(const float *a,
                     const float *b,
                     float *out)
{
    float amount;

    amount = BH_Vec3fDot(a, b) / BH_Vec3fDot(b, b);
    BH_Vec3fScale(b, amount, out);
}


void BH_Vec3fBarycentric(const float *a,
                         const float *b,
                         const float *c,
                         float v,
                         float w,
                         float *out)
{
    float tmp1[3], tmp2[3];
    float u;

    u = 1.0f - v - w;
    tmp1[0] = tmp1[1] = tmp1[2] = u; BH_Vec3fMul(a, tmp1, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = v; BH_Vec3fMulAdd(b, tmp1, tmp2, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = w; BH_Vec3fMulAdd(c, tmp1, tmp2, out);
}
