#include <BH/Math.h>

#include <math.h>
#include <string.h>


void BH_Vec4fAdd(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}


void BH_Vec4fSub(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}


void BH_Vec4fMul(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}


void BH_Vec4fScale(const float *a,
                   const float b,
                   float *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
    out[3] = a[3] * b;
}


void BH_Vec4fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
    out[3] = a[3] * b[3] + c[3];
}


void BH_Vec4fNegate(const float *in,
                    float *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = -in[3];
}


float BH_Vec4fDot(const float *a,
                  const float *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}


float BH_Vec4fLength(const float *in)
{
    return sqrt(BH_Vec4fDot(in, in));
}


void BH_Vec4fNormal(const float *in,
                    float *out)
{
    BH_Vec4fScale(in, 1.0f / BH_Vec4fLength(in), out);
}


float BH_Vec4fNormalEx(const float *in,
                       float *out)
{
    float length;

    length = BH_Vec4fLength(in);
    BH_Vec4fScale(in, 1.0f / length, out);
    return length;
}


void BH_Vec4fMin(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] < b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4fMax(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] > b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out)
{
    float tmp[4];

    BH_Vec4fSub(b, a, tmp);
    BH_Vec4fScale(tmp, t, tmp);
    BH_Vec4fAdd(a, tmp, out);
}


void BH_Vec4fProject(const float *a,
                     const float *b,
                     float *out)
{
    float amount;

    amount = BH_Vec4fDot(a, b) / BH_Vec4fDot(b, b);
    BH_Vec4fScale(b, amount, out);
}


void BH_Vec4fBarycentric(const float *a,
                         const float *b,
                         const float *c,
                         float v,
                         float w,
                         float *out)
{
    float tmp1[4], tmp2[4];
    float u;

    u = 1.0f - v - w;
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = u; BH_Vec4fMul(a, tmp1, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = v; BH_Vec4fMulAdd(b, tmp1, tmp2, tmp2);
    tmp1[0] = tmp1[1] = tmp1[2] = tmp1[3] = w; BH_Vec4fMulAdd(c, tmp1, tmp2, out);
}


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
    return sqrt(BH_Vec3fDot(in, in));
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


void BH_Vec2fAdd(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}


void BH_Vec2fSub(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}


void BH_Vec2fMul(const float *a,
                 const float *b,
                 float *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}


void BH_Vec2fScale(const float *a,
                   const float b,
                   float *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
}


void BH_Vec2fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
}


void BH_Vec2fNegate(const float *in,
                    float *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
}


float BH_Vec2fDot(const float *a,
                  const float *b)
{
    return a[0] * b[0] + a[1] * b[1];
}


float BH_Vec2fCross(const float *a,
                    const float *b)
{
    return a[0] * b[1] - a[1] * b[0];
}


float BH_Vec2fLength(const float *in)
{
    return sqrt(BH_Vec2fDot(in, in));
}


void BH_Vec2fNormal(const float *in,
                    float *out)
{
    BH_Vec2fScale(in, 1.0f / BH_Vec2fLength(in), out);
}


float BH_Vec2fNormalEx(const float *in,
                       float *out)
{
    float length;

    length = BH_Vec2fLength(in);
    BH_Vec2fScale(in, 1.0f / length, out);
    return length;
}


void BH_Vec2fMin(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Vec2fMax(const float *a,
                 const float *b,
                 float *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Vec2fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out)
{
    float tmp[2];

    BH_Vec2fSub(b, a, tmp);
    BH_Vec2fScale(tmp, t, tmp);
    BH_Vec2fAdd(a, tmp, out);
}


void BH_Vec2fProject(const float *a,
                     const float *b,
                     float *out)
{
    float amount;

    amount = BH_Vec2fDot(a, b) / BH_Vec2fDot(b, b);
    BH_Vec2fScale(b, amount, out);
}


void BH_Vec2fBarycentric(const float *a,
                         const float *b,
                         const float *c,
                         float v,
                         float w,
                         float *out)
{
    float tmp1[2], tmp2[2];
    float u;

    u = 1.0f - v - w;
    tmp1[0] = tmp1[1] = u; BH_Vec2fMul(a, tmp1, tmp2);
    tmp1[0] = tmp1[1] = v; BH_Vec2fMulAdd(b, tmp1, tmp2, tmp2);
    tmp1[0] = tmp1[1] = w; BH_Vec2fMulAdd(c, tmp1, tmp2, out);
}


float BH_Lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}


void BH_Vec4iAdd(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}


void BH_Vec4iSub(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}


void BH_Vec4iMul(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}


void BH_Vec4iScale(const int *a,
                   int b,
                   int *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
    out[3] = a[3] * b;
}


void BH_Vec4iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
    out[3] = a[3] * b[3] + c[3];
}


void BH_Vec4iNegate(const int *in,
                    int *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = -in[3];
}


void BH_Vec4iMin(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] < b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4iMax(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] > b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec3iAdd(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}


void BH_Vec3iSub(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}


void BH_Vec3iMul(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}


void BH_Vec3iScale(const int *a,
                   int b,
                   int *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
}


void BH_Vec3iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
}


void BH_Vec3iNegate(const int *in,
                    int *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
}


void BH_Vec3iMin(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
}


void BH_Vec3iMax(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
}


void BH_Vec2iAdd(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}


void BH_Vec2iSub(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}


void BH_Vec2iMul(const int *a,
                 const int *b,
                 int *out)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}


void BH_Vec2iScale(const int *a,
                   int b,
                   int *out)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
}


void BH_Vec2iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out)
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
}


void BH_Vec2iNegate(const int *in,
                    int *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
}


void BH_Vec2iMin(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Vec2iMax(const int *a,
                 const int *b,
                 int *out)
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
}


void BH_Quat4fIdentity(float *out)
{
    static const float ident[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    memcpy(out, ident, sizeof(ident));
}


void BH_Quat4fConjugate(const float *in,
                        float *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = in[3];
}


void BH_Quat4fInverse(const float *in,
                      float *out)
{
    float dot;

    dot = BH_Vec4fDot(in, in);
    BH_Quat4fConjugate(in, out);
    BH_Quat4fScale(out, 1.0f / dot, out);
}


void BH_Quat4fMul(const float *a,
                  const float *b,
                  float *out)
{
    float tmp1[4], tmp2[4], tmp3[4];
    float w;

    w = a[3] * b[3] - BH_Vec3fDot(a, b);
    BH_Vec4fScale(a, b[3], tmp1);
    BH_Vec4fScale(b, a[3], tmp2);
    BH_Vec3fCross(a, b, tmp3);
    BH_Vec4fAdd(tmp1, tmp2, out);
    BH_Vec4fAdd(tmp3, out, out);
    out[3] = w;
}


void BH_Quat4fSlerp(const float *a,
                    const float *b,
                    float t,
                    float *out)
{
    float angle, denom;
    float from[4], to[4];

    angle = acos(BH_Vec4fDot(a, b));
    if (angle == 0.0f)
    {
        BH_Vec4fLerp(a, b, t, out);
        return;
    }

    denom = 1.0f / sin(angle);
    BH_Vec4fScale(a, sin((1 - t) * angle) * denom, from);
    BH_Vec4fScale(b, sin(t * angle) * denom, to);
    BH_Vec4fAdd(from, to, out);
}


void BH_Quat4fFromEuler(float roll,
                        float pitch,
                        float yaw,
                        float *out)
{
    float cr, cp, cy, sr, sp, sy;

    cr = cos(roll / 2.0f);
    cp = cos(pitch / 2.0f);
    cy = cos(yaw / 2.0f);
    sr = sin(roll / 2.0f);
    sp = sin(pitch / 2.0f);
    sy = sin(yaw / 2.0f);

    out[0] = sr * cp * cy - cr * sp * sy;
    out[1] = cr * sp * cy + sr * cp * sy;
    out[2] = cr * cp * sy - sr * sp * cy;
    out[3] = cr * cp * cy + sr * sp * sy;
}


void BH_Quat4fFromAxis(const float *axis,
                       float angle,
                       float *out)
{
    float c, s;

    c = cos(angle / 2.0f);
    s = sin(angle / 2.0f);

    out[0] = axis[0] * s;
    out[1] = axis[1] * s;
    out[2] = axis[2] * s;
    out[3] = c;
}


void BH_Quat4fToEuler(const float *in,
                      float *roll,
                      float *pitch,
                      float *yaw)
{
    float ww, xw, yw, zw, xx, xy, xz, yy, yz, zz, angle;

    xx = in[0] * in[0];
    xy = in[0] * in[1];
    xz = in[0] * in[2];
    xw = in[0] * in[3];
    yy = in[1] * in[1];
    yz = in[1] * in[2];
    yw = in[1] * in[3];
    zz = in[2] * in[2];
    zw = in[2] * in[3];
    ww = in[3] * in[3];

    angle = 2.0f * (yw - xz);
    if (angle > 1.0f)
        angle = 1.0f;
    if (angle < -1.0f)
        angle = -1.0f;

    *pitch = asin(angle);

    if (*pitch == (M_PI / 2.0f))
    {
        *roll = 0.0f;
        *yaw = -2.0f * atan2(in[0], in[3]);
    }
    else if (*pitch == (M_PI / -2.0f))
    {
        *roll = 0.0f;
        *yaw = 2.0f * atan2(in[0], in[3]);
    }
    else
    {
        *roll = atan2(2.0f * (xw + yz), ww - xx - yy + zz);
        *yaw = atan2(2.0f * (zw + xy), ww + xx - yy - zz);
    }
}


void BH_Quat4fToAxis(const float *in,
                     float *axis,
                     float *angle)
{
    *angle = 2.0f * acos(in[3]);

    if (*angle == 0.0f)
    {
        axis[0] = 1.0f;
        axis[1] = 0.0f;
        axis[2] = 0.0f;
    }
    else
    {
        float tmp;

        tmp = sqrt(1.0f - in[3] * in[3]);
        axis[0] = in[0] / tmp;
        axis[1] = in[1] / tmp;
        axis[2] = in[2] / tmp;
    }
}


void BH_Quat4fToMat4f(const float *in,
                      float *out)
{
    float xx, xy, xz, xw, yy, yz, yw, zz, zw;

    xx = in[0] * in[0];
    xy = in[0] * in[1];
    xz = in[0] * in[2];
    xw = in[0] * in[3];
    yy = in[1] * in[1];
    yz = in[1] * in[2];
    yw = in[1] * in[3];
    zz = in[2] * in[2];
    zw = in[2] * in[3];

    BH_Mat4fIdentity(out);
    out[0] = 1.0f - 2.0f * (yy + zz);
    out[1] = 2.0f * (xy + zw);
    out[2] = 2.0f * (xz - yw);
    out[4] = 2.0f * (xy - zw);
    out[5] = 1.0f - 2.0f * (xx + zz);
    out[6] = 2.0f * (yz + xw);
    out[8] = 2.0f * (xz + yw);
    out[9] = 2.0f * (yz - xw);
    out[10] = 1.0f - 2.0f * (xx + yy);
}


void BH_Mat4fIdentity(float *out)
{
    const float ident[16] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    memcpy(out, ident, sizeof(ident));
}


void BH_Mat4fAdd(const float *a,
                 const float *b,
                 float *out)
{
    BH_Vec4fAdd(&a[0], &b[0], &out[0]);
    BH_Vec4fAdd(&a[4], &b[4], &out[4]);
    BH_Vec4fAdd(&a[8], &b[8], &out[8]);
    BH_Vec4fAdd(&a[12], &b[12], &out[12]);
}


void BH_Mat4fSub(const float *a,
                 const float *b,
                 float *out)
{
    BH_Vec4fSub(&a[0], &b[0], &out[0]);
    BH_Vec4fSub(&a[4], &b[4], &out[4]);
    BH_Vec4fSub(&a[8], &b[8], &out[8]);
    BH_Vec4fSub(&a[12], &b[12], &out[12]);
}


void BH_Mat4fMul(const float *a,
                 const float *b,
                 float *out)
{
    float tmp[16], row[4];

    row[0] = row[1] = row[2] = row[3] = b[0]; BH_Vec4fMul(&a[0], row, &tmp[0]);
    row[0] = row[1] = row[2] = row[3] = b[1]; BH_Vec4fMulAdd(&a[4], row, &tmp[0], &tmp[0]);
    row[0] = row[1] = row[2] = row[3] = b[2]; BH_Vec4fMulAdd(&a[8], row, &tmp[0], &tmp[0]);
    row[0] = row[1] = row[2] = row[3] = b[3]; BH_Vec4fMulAdd(&a[12], row, &tmp[0], &tmp[0]);

    row[0] = row[1] = row[2] = row[3] = b[4]; BH_Vec4fMul(&a[0], row, &tmp[4]);
    row[0] = row[1] = row[2] = row[3] = b[5]; BH_Vec4fMulAdd(&a[4], row, &tmp[4], &tmp[4]);
    row[0] = row[1] = row[2] = row[3] = b[6]; BH_Vec4fMulAdd(&a[8], row, &tmp[4], &tmp[4]);
    row[0] = row[1] = row[2] = row[3] = b[7]; BH_Vec4fMulAdd(&a[12], row, &tmp[4], &tmp[4]);

    row[0] = row[1] = row[2] = row[3] = b[8]; BH_Vec4fMul(&a[0], row, &tmp[8]);
    row[0] = row[1] = row[2] = row[3] = b[9]; BH_Vec4fMulAdd(&a[4], row, &tmp[8], &tmp[8]);
    row[0] = row[1] = row[2] = row[3] = b[10]; BH_Vec4fMulAdd(&a[8], row, &tmp[8], &tmp[8]);
    row[0] = row[1] = row[2] = row[3] = b[11]; BH_Vec4fMulAdd(&a[12], row, &tmp[8], &tmp[8]);

    row[0] = row[1] = row[2] = row[3] = b[12]; BH_Vec4fMul(&a[0], row, &tmp[12]);
    row[0] = row[1] = row[2] = row[3] = b[13]; BH_Vec4fMulAdd(&a[4], row, &tmp[12], &tmp[12]);
    row[0] = row[1] = row[2] = row[3] = b[14]; BH_Vec4fMulAdd(&a[8], row, &tmp[12], &tmp[12]);
    row[0] = row[1] = row[2] = row[3] = b[15]; BH_Vec4fMulAdd(&a[12], row, &tmp[12], &tmp[12]);

    memcpy(out, tmp, sizeof(tmp));
}


void BH_Mat4fScale(const float *a,
                   float b,
                   float *out)
{
    BH_Vec4fScale(&a[0], b, &out[0]);
    BH_Vec4fScale(&a[4], b, &out[4]);
    BH_Vec4fScale(&a[8], b, &out[8]);
    BH_Vec4fScale(&a[12], b, &out[12]);
}


void BH_Mat4fTranspose(const float *in,
                       float *out)
{
    float tmp[16];

    tmp[0] = in[0]; tmp[4] = in[1]; tmp[8] = in[2]; tmp[12] = in[3];
    tmp[1] = in[4]; tmp[5] = in[5]; tmp[9] = in[6]; tmp[13] = in[7];
    tmp[2] = in[8]; tmp[6] = in[9]; tmp[10] = in[10]; tmp[14] = in[11];
    tmp[3] = in[12]; tmp[7] = in[13]; tmp[11] = in[14]; tmp[15] = in[15];

    memcpy(out, tmp, sizeof(tmp));
}


float BH_Mat4fTrace(const float *in)
{
    return in[0] + in[5] + in[10] + in[15];
}


float BH_Mat4fDet(const float *in)
{
    float a, b, c, d, e, f, result;

    a = in[2]  * in[7]  - in[3]  * in[6];
    b = in[2]  * in[11] - in[3]  * in[10];
    c = in[2]  * in[15] - in[3]  * in[14];
    d = in[6]  * in[11] - in[7]  * in[10];
    e = in[6]  * in[15] - in[7]  * in[14];
    f = in[10] * in[15] - in[11] * in[14];

    result = 0.0f;
    result += in[0]  * (in[5] * f - in[9] * e + in[13] * d);
    result -= in[4]  * (in[1] * f - in[9] * c + in[13] * b);
    result += in[8]  * (in[1] * e - in[5] * c + in[13] * a);
    result -= in[12] * (in[1] * d - in[5] * b + in[9]  * a);

    return result;
}


int BH_Mat4fInverse(const float *in,
                    float *out)
{
    float a, b, c, d, e, f, det;
    float tmp[16];

    a = in[2]  * in[7]  - in[3]  * in[6];
    b = in[2]  * in[11] - in[3]  * in[10];
    c = in[2]  * in[15] - in[3]  * in[14];
    d = in[6]  * in[11] - in[7]  * in[10];
    e = in[6]  * in[15] - in[7]  * in[14];
    f = in[10] * in[15] - in[11] * in[14];

    tmp[0] =  (in[5] * f - in[9] * e + in[13] * d);
    tmp[1] = -(in[1] * f - in[9] * c + in[13] * b);
    tmp[2] =  (in[1] * e - in[5] * c + in[13] * a);
    tmp[3] = -(in[1] * d - in[5] * b + in[9]  * a);

    det = 0.0f;
    det += in[0]  * tmp[0];
    det += in[4]  * tmp[1];
    det += in[8]  * tmp[2];
    det += in[12] * tmp[3];

    if (det == 0.0f)
        return BH_ERROR;

    tmp[4] = -(in[4] * f - in[8] * e + in[12] * d);
    tmp[5] =  (in[0] * f - in[8] * c + in[12] * b);
    tmp[6] = -(in[0] * e - in[4] * c + in[12] * a);
    tmp[7] =  (in[0] * d - in[4] * b + in[8]  * a);

    a = in[1] * in[7]  - in[3]  * in[5];
    b = in[1] * in[11] - in[3]  * in[9];
    c = in[1] * in[15] - in[3]  * in[13];
    d = in[5] * in[11] - in[7]  * in[9];
    e = in[5] * in[15] - in[7]  * in[13];
    f = in[9] * in[15] - in[11] * in[13];

    tmp[8] =   (in[4] * f - in[8] * e + in[12] * d);
    tmp[9] =  -(in[0] * f - in[8] * c + in[12] * b);
    tmp[10] =  (in[0] * e - in[4] * c + in[12] * a);
    tmp[11] = -(in[0] * d - in[4] * b + in[8]  * a);

    a = in[1] * in[6]  - in[2]  * in[5];
    b = in[1] * in[10] - in[2]  * in[9];
    c = in[1] * in[14] - in[2]  * in[13];
    d = in[5] * in[10] - in[6]  * in[9];
    e = in[5] * in[14] - in[6]  * in[13];
    f = in[9] * in[14] - in[10] * in[13];

    tmp[12] = -(in[4] * f - in[8] * e + in[12] * d);
    tmp[13] =  (in[0] * f - in[8] * c + in[12] * b);
    tmp[14] = -(in[0] * e - in[4] * c + in[12] * a);
    tmp[15] =  (in[0] * d - in[4] * b + in[8]  * a);

    BH_Mat4fScale(tmp, 1.0f / det, out);
    return BH_OK;
}


void BH_Mat4fFromScale(float x,
                       float y,
                       float z,
                       float *out)
{
    BH_Mat4fIdentity(out);
    out[0] = x;
    out[5] = y;
    out[10] = z;
}


void BH_Mat4fFromTranslation(float x,
                             float y,
                             float z,
                             float *out)
{
    BH_Mat4fIdentity(out);
    out[12] = x;
    out[13] = y;
    out[14] = z;
}


void BH_Mat4fFromRotationX(float angle,
                           float *out)
{
    float c, s;

    c = cos(angle);
    s = sin(angle);

    BH_Mat4fIdentity(out);
    out[5] = c;
    out[6] = s;
    out[9] = -s;
    out[10] = c;
}


void BH_Mat4fFromRotationY(float angle,
                           float *out)
{
    float c, s;

    c = cos(angle);
    s = sin(angle);

    BH_Mat4fIdentity(out);
    out[0] = c;
    out[2] = -s;
    out[8] = s;
    out[10] = c;
}


void BH_Mat4fFromRotationZ(float angle,
                           float *out)
{
    float c, s;

    c = cos(angle);
    s = sin(angle);

    BH_Mat4fIdentity(out);
    out[0] = c;
    out[1] = s;
    out[4] = -s;
    out[5] = c;
}


void BH_Mat4fFromAxis(const float *axis,
                      float angle,
                      float *out)
{
    float x, y, z, length;
    float c, s, moc, xx, xy, xz, yy, yz, zz;

    length = BH_Vec3fLength(axis);
    BH_Mat4fIdentity(out);

    if (length == 0.0f)
        return;

    x = axis[0] / length;
    y = axis[1] / length;
    z = axis[2] / length;

    c = cos(angle);
    s = sin(angle);
    moc = 1.0f - c;

    xx = x * x;
    xy = x * y;
    xz = x * z;
    yy = y * y;
    yz = y * z;
    zz = z * z;

    out[0] = c + xx * moc;
    out[1] = xy * moc + z * s;
    out[2] = xz * moc - y * s;

    out[4] = xy * moc - z * s;
    out[5] = c + yy * moc;
    out[6] = yz * moc + x * s;

    out[8] = xz * moc + y * s;
    out[9] = yz * moc - x * s;
    out[10] = c + zz * moc;
}


void BH_Mat4fFromEuler(float roll,
                       float pitch,
                       float yaw,
                       float *out)
{
    float rs, rc, ys, yc, ps, pc;

    rs = sin(roll);
    rc = cos(roll);
    ps = sin(pitch);
    pc = cos(pitch);
    ys = sin(yaw);
    yc = cos(yaw);

    BH_Mat4fIdentity(out);
    out[0] = pc * yc;
    out[1] = pc * ys;
    out[2] = -ps;
    out[4] = ps * rs * yc - rc * ys;
    out[5] = ps * rs * ys + rc * yc;
    out[6] = pc * rs;
    out[8] = rs * ys + ps * rc * yc;
    out[9] = ps * rc * ys - rs * yc;
    out[10] = pc * rc;
}


void BH_Mat4fFromQuat4f(const float *in,
                        float *out)
{
    BH_Quat4fToMat4f(in, out);
}


void BH_Mat4fFromOrtho(float xMin,
                       float xMax,
                       float yMin,
                       float yMax,
                       float zMin,
                       float zMax,
                       float *out)
{
    float dx, dy, dz;

    dx = xMax - xMin;
    dy = yMax - yMin;
    dz = zMax - zMin;

    BH_Mat4fIdentity(out);

    out[0] = 2.0f / dx;
    out[5] = 2.0f / dy;
    out[10] = -2.0f / dz;
    out[12] = -(xMax + xMin) / dx;
    out[13] = -(yMax + yMin) / dy;
    out[14] = -(zMax + zMin) / dz;
}


void BH_Mat4fFromFrustum(float fov,
                         float aspect,
                         float zMin,
                         float zMax,
                         float *out)
{
    float t, dz;

    dz = zMax - zMin;
    t = tanf(fov / 2.0f);

    BH_Mat4fIdentity(out);

    out[0] = 1.0f / (aspect * t);
    out[5] = 1.0f / t;
    out[10] = -(zMax + zMin) / dz;
    out[11] = -1.0f;
    out[14] = -(2.0f * zMax * zMin) / dz;
    out[15] = 0.0f;
}


void BH_Mat4fFromLookAt(const float *position,
                        const float *at,
                        const float *up,
                        float *out)
{
    float cameraDir[3], cameraRight[3], cameraUp[3];

    BH_Vec3fSub(position, at, cameraDir);
    BH_Vec3fNormal(cameraDir, cameraDir);
    BH_Vec3fCross(up, cameraDir, cameraRight);
    BH_Vec3fNormal(cameraRight, cameraRight);
    BH_Vec3fCross(cameraDir, cameraRight, cameraUp);

    out[0] = cameraRight[0];
    out[1] = cameraUp[0];
    out[2] = cameraDir[0];
    out[3] = 0.0f;

    out[4] = cameraRight[1];
    out[5] = cameraUp[1];
    out[6] = cameraDir[1];
    out[7] = 0.0f;

    out[8] = cameraRight[2];
    out[9] = cameraUp[2];
    out[10] = cameraDir[2];
    out[11] = 0.0f;

    out[12] = -BH_Vec3fDot(cameraRight, position);
    out[13] = -BH_Vec3fDot(cameraUp, position);
    out[14] = -BH_Vec3fDot(cameraDir, position);
    out[15] = 1.0f;
}


void BH_Mat4fApplyVec4f(const float *a,
                        const float *b,
                        float *out)
{
    float tmp[4], row[4];

    row[0] = row[1] = row[2] = row[3] = b[0]; BH_Vec4fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = row[3] = b[1]; BH_Vec4fMulAdd(&a[4], row, tmp, tmp);
    row[0] = row[1] = row[2] = row[3] = b[2]; BH_Vec4fMulAdd(&a[8], row, tmp, tmp);
    row[0] = row[1] = row[2] = row[3] = b[3]; BH_Vec4fMulAdd(&a[12], row, tmp, tmp);

    memcpy(out, tmp, sizeof(tmp));
}


void BH_Mat4fApplyVec3f(const float *a,
                        const float *b,
                        float *out)
{
    float tmp[4], row[4];

    row[0] = row[1] = row[2] = row[3] = b[0]; BH_Vec4fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = row[3] = b[1]; BH_Vec4fMulAdd(&a[4], row, tmp, tmp);
    row[0] = row[1] = row[2] = row[3] = b[2]; BH_Vec4fMulAdd(&a[8], row, tmp, tmp);
    row[0] = row[1] = row[2] = row[3] = 1.0f; BH_Vec4fMulAdd(&a[12], row, tmp, tmp);

    memcpy(out, tmp, sizeof(float) * 3);
}


void BH_Mat3fIdentity(float *out)
{
    static const float ident[9] =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    memcpy(out, ident, sizeof(ident));
}


void BH_Mat3fAdd(const float *a,
                 const float *b,
                 float *out)
{
    BH_Vec3fAdd(&a[0], &b[0], &out[0]);
    BH_Vec3fAdd(&a[3], &b[3], &out[3]);
    BH_Vec3fAdd(&a[6], &b[6], &out[6]);
}


void BH_Mat3fSub(const float *a,
                 const float *b,
                 float *out)
{
    BH_Vec3fSub(&a[0], &b[0], &out[0]);
    BH_Vec3fSub(&a[3], &b[3], &out[3]);
    BH_Vec3fSub(&a[6], &b[6], &out[6]);
}


void BH_Mat3fMul(const float *a,
                 const float *b,
                 float *out)
{
    float tmp[9], row[3];

    row[0] = row[1] = row[2] = b[0]; BH_Vec3fMul(&a[0], row, &tmp[0]);
    row[0] = row[1] = row[2] = b[1]; BH_Vec3fMulAdd(&a[3], row, &tmp[0], &tmp[0]);
    row[0] = row[1] = row[2] = b[2]; BH_Vec3fMulAdd(&a[6], row, &tmp[0], &tmp[0]);

    row[0] = row[1] = row[2] = b[3]; BH_Vec3fMul(&a[0], row, &tmp[3]);
    row[0] = row[1] = row[2] = b[4]; BH_Vec3fMulAdd(&a[3], row, &tmp[3], &tmp[3]);
    row[0] = row[1] = row[2] = b[5]; BH_Vec3fMulAdd(&a[6], row, &tmp[3], &tmp[3]);

    row[0] = row[1] = row[2] = b[6]; BH_Vec3fMul(&a[0], row, &tmp[6]);
    row[0] = row[1] = row[2] = b[7]; BH_Vec3fMulAdd(&a[3], row, &tmp[6], &tmp[6]);
    row[0] = row[1] = row[2] = b[8]; BH_Vec3fMulAdd(&a[6], row, &tmp[6], &tmp[6]);

    memcpy(out, tmp, sizeof(tmp));
}


void BH_Mat3fScale(const float *a,
                   float b,
                   float *out)
{
    BH_Vec3fScale(&a[0], b, &out[0]);
    BH_Vec3fScale(&a[3], b, &out[3]);
    BH_Vec3fScale(&a[6], b, &out[6]);
}


void BH_Mat3fTranspose(const float *in,
                       float *out)
{
    float tmp[9];

    tmp[0] = in[0]; tmp[3] = in[1]; tmp[6] = in[2];
    tmp[1] = in[3]; tmp[4] = in[4]; tmp[7] = in[5];
    tmp[2] = in[6]; tmp[5] = in[7]; tmp[8] = in[8];

    memcpy(out, tmp, sizeof(tmp));
}


float BH_Mat3fTrace(const float *in)
{
    return in[0] + in[4] + in[8];
}


float BH_Mat3fDet(const float *in)
{
    float a, b, c, result;

    a = in[4] * in[8] - in[7] * in[5];
    b = in[1] * in[8] - in[7] * in[2];
    c = in[1] * in[5] - in[4] * in[2];

    result = 0.0f;
    result += in[0] * a;
    result -= in[3] * b;
    result += in[6] * c;

    return result;
}


int BH_Mat3fInverse(const float *in,
                    float *out)
{
    float a, b, c, det;
    float tmp[16];

    a = in[4] * in[8] - in[7] * in[5];
    b = in[1] * in[8] - in[7] * in[2];
    c = in[1] * in[5] - in[4] * in[2];

    tmp[0] =  a;
    tmp[1] = -b;
    tmp[2] =  c;

    det = 0.0f;
    det += in[0] * tmp[0];
    det += in[3] * tmp[1];
    det += in[6] * tmp[2];

    if (det == 0.0f)
        return BH_ERROR;

    a = in[3] * in[8] - in[6] * in[5];
    b = in[0] * in[8] - in[6] * in[2];
    c = in[0] * in[5] - in[3] * in[2];

    tmp[3] = -a;
    tmp[4] =  b;
    tmp[5] = -c;

    a = in[3] * in[7] - in[6] * in[4];
    b = in[0] * in[7] - in[6] * in[1];
    c = in[0] * in[4] - in[3] * in[1];

    tmp[6] =  a;
    tmp[7] = -b;
    tmp[8] =  c;

    BH_Mat3fScale(tmp, 1.0f / det, out);
    return BH_OK;
}


void BH_Mat3fFromScale(float x,
                       float y,
                       float *out)
{
    BH_Mat3fIdentity(out);
    out[0] = x;
    out[4] = y;
}


void BH_Mat3fFromTranslation(float x,
                             float y,
                             float *out)
{
    BH_Mat3fIdentity(out);
    out[6] = x;
    out[7] = y;
}


void BH_Mat3fFromRotation(float angle,
                          float *out)
{
    float c, s;

    c = cos(angle);
    s = sin(angle);

    BH_Mat3fIdentity(out);
    out[0] = c;
    out[1] = s;
    out[3] = -s;
    out[4] = c;
}


void BH_Mat3fApplyVec3f(float *a,
                        float *b,
                        float *out)
{
    float tmp[3], row[3];

    row[0] = row[1] = row[2] = b[0]; BH_Vec3fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = b[1]; BH_Vec3fMulAdd(&a[3], row, tmp, tmp);
    row[0] = row[1] = row[2] = b[2]; BH_Vec3fMulAdd(&a[6], row, tmp, tmp);

    memcpy(out, tmp, sizeof(tmp));
}


void BH_Mat3fApplyVec2f(float *a,
                        float *b,
                        float *out)
{
    float tmp[3], row[3];

    row[0] = row[1] = row[2] = b[0]; BH_Vec3fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = b[1]; BH_Vec3fMulAdd(&a[3], row, tmp, tmp);
    row[0] = row[1] = row[2] = 1.0f; BH_Vec3fMulAdd(&a[6], row, tmp, tmp);

    memcpy(out, tmp, sizeof(float) * 2);
}


int BH_PlaneFromPoints(const float *a,
                       const float *b,
                       const float *c,
                       float *out)
{
    float tmp1[3], tmp2[3];

    BH_Vec3fSub(b, a, tmp1);
    BH_Vec3fSub(c, a, tmp2);
    BH_Vec3fCross(tmp2, tmp1, tmp1);
    if (BH_Vec3fNormalEx(tmp1, tmp1) == 0.0f)
        return BH_ERROR;

    out[3] = BH_Vec3fDot(a, tmp1);
    memcpy(out, tmp1, sizeof(tmp1));
    return BH_OK;
}


float BH_PlaneDistance(const float *plane,
                       const float *point)
{
    return BH_Vec3fDot(plane, point) - plane[3];
}


void BH_PlaneClosestPoint(const float *plane,
                          const float *point,
                          float *out)
{
    float tmp[3];

    BH_Vec3fScale(plane, BH_PlaneDistance(plane, point), tmp);
    BH_Vec3fSub(point, tmp, out);
}


int BH_Ray3fIntersectPlane(const float *start,
                           const float *direction,
                           const float *plane,
                           float *t,
                           float *out)
{
    float tmp1[3];
    float denom, time;

    /* Calculate intersection time */
    denom = BH_Vec3fDot(direction, plane);
    time = (plane[3] - BH_Vec3fDot(plane, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (denom == 0.0f || time < 0.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec3fScale(direction, time, tmp1);
    BH_Vec3fAdd(start, tmp1, out);
    *t = time;
    return BH_OK;
}


int BH_Ray3fIntersectTriangle(const float *start,
                              const float *direction,
                              const float *a,
                              const float *b,
                              const float *c,
                              float *t,
                              float *out)
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


int BH_Segment3fIntersectPlane(const float *start,
                               const float *end,
                               const float *plane,
                               float *t,
                               float *out)
{
    float tmp[3];
    float denom, time;

    /* Calculate intersection time */
    BH_Vec3fSub(end, start, tmp);
    denom = BH_Vec3fDot(tmp, plane);
    time = (plane[3] - BH_Vec3fDot(plane, start)) / denom;

    /* Check for ray/plane parallel to each other or point is behing the ray. */
    if (denom == 0.0f || time < 0.0f || time > 1.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec3fScale(tmp, time, tmp);
    BH_Vec3fAdd(start, tmp, out);
    *t = time;
    return BH_OK;
}


int BH_Segment3fIntersectTriangle(const float *start,
                                  const float *end,
                                  const float *a,
                                  const float *b,
                                  const float *c,
                                  float *t,
                                  float *out)
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


int BH_LineFromPoints(const float *a,
                      const float *b,
                      float *out)
{
    float tmp[2];

    tmp[0] = a[1] - b[1];
    tmp[1] = b[0] - a[0];
    if (BH_Vec2fNormalEx(tmp, tmp) == 0.0f)
        return BH_ERROR;

    out[2] = BH_Vec2fDot(tmp, a);
    memcpy(out, tmp, sizeof(tmp));
    return BH_OK;
}


float BH_LineDistance(const float *line,
                      const float *point)
{
    return BH_Vec2fDot(line, point) - line[2];
}


void BH_LineClosestPoint(const float *line,
                         const float *point,
                         float *out)
{
    float tmp[2];

    BH_Vec2fScale(line, BH_LineDistance(line, point), tmp);
    BH_Vec2fSub(point, tmp, out);
}


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
    if (denom == 0.0f || time < 0.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec2fScale(direction, time, tmp1);
    BH_Vec2fAdd(start, tmp1, out);
    *t = time;
    return BH_OK;
}


int BH_Ray2fIntersectTime(const float *startA,
                          const float *directionA,
                          const float *startB,
                          const float *directionB,
                          float *time1,
                          float *time2)
{
    float tmp1[2], tmp2[2], tmp3[2];
    float denom;

    /* Rotate directions by 90 degrees and caluclate denom */
    tmp1[0] = -directionA[1]; tmp1[1] = directionA[0];
    tmp2[0] = -directionB[1]; tmp2[1] = directionB[0];
    denom = BH_Vec2fDot(tmp1, directionB);

    if (denom == 0.0f)
        return BH_ERROR;

    /* Calculate segments offset and intersection times */
    BH_Vec2fSub(startA, startB, tmp3);
    *time1 = BH_Vec2fDot(tmp3, tmp2) / denom;
    *time2 = BH_Vec2fDot(tmp3, tmp1) / denom;

    return BH_OK;
}


int BH_Ray2fIntersectRay(const float *startA,
                         const float *directionA,
                         const float *startB,
                         const float *directionB,
                         float *t,
                         float *out)
{
    float tmp[2];
    float time1, time2;

    if (BH_Ray2fIntersectTime(startA, directionA, startB, directionB, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time2 < 0.0f)
        return BH_ERROR;

    BH_Vec2fScale(directionA, time1, tmp);
    BH_Vec2fAdd(startA, tmp, out);
    *t = time1;
    return BH_OK;
}


int BH_Ray2fIntersectSegment(const float *startA,
                             const float *directionA,
                             const float *startB,
                             const float *endB,
                             float *t,
                             float *out)
{
    float tmp[2];
    float time1, time2;

    BH_Vec2fSub(endB, startB, tmp);
    if (BH_Ray2fIntersectTime(startA, directionA, startB, tmp, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time2 < 0.0f || time2 > 1.0f)
        return BH_ERROR;

    BH_Vec2fScale(directionA, time1, tmp);
    BH_Vec2fAdd(startA, tmp, out);
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
    if (denom == 0.0f || time < 0.0f || time > 1.0f)
        return BH_ERROR;

    /* Compute intersection point */
    BH_Vec2fScale(tmp, time, tmp);
    BH_Vec2fAdd(start, tmp, out);
    *t = time;
    return BH_OK;
}


int BH_Segment2fIntersectSegment(const float *startA,
                                 const float *endA,
                                 const float *startB,
                                 const float *endB,
                                 float *t,
                                 float *out)
{
    float tmp1[2], tmp2[2];
    float time1, time2;

    BH_Vec2fSub(endA, startA, tmp1);
    BH_Vec2fSub(endB, startB, tmp2);
    if (BH_Ray2fIntersectTime(startA, tmp1, startB, tmp2, &time1, &time2))
        return BH_ERROR;

    if (time1 < 0.0f || time1 > 1.0f || time2 < 0.0f || time2 > 1.0f)
        return BH_ERROR;

    BH_Vec2fLerp(startA, endA, time1, out);
    *t = time1;

    return BH_OK;
}
