#include <BH/Math/Mat3f.h>
#include <BH/Math/Vec3f.h>
#include <string.h>
#include <math.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


void BH_Mat3fIdentity(float out[9])
{
    static const float ident[9] =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    memcpy(out, ident, sizeof(ident));
}


void BH_Mat3fAdd(const float a[9],
                 const float b[9],
                 float out[9])
{
    BH_Vec3fAdd(&a[0], &b[0], &out[0]);
    BH_Vec3fAdd(&a[3], &b[3], &out[3]);
    BH_Vec3fAdd(&a[6], &b[6], &out[6]);
}


void BH_Mat3fSub(const float a[9],
                 const float b[9],
                 float out[9])
{
    BH_Vec3fSub(&a[0], &b[0], &out[0]);
    BH_Vec3fSub(&a[3], &b[3], &out[3]);
    BH_Vec3fSub(&a[6], &b[6], &out[6]);
}


void BH_Mat3fMul(const float a[9],
                 const float b[9],
                 float out[9])
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


void BH_Mat3fScale(const float a[9],
                   float b,
                   float out[9])
{
    BH_Vec3fScale(&a[0], b, &out[0]);
    BH_Vec3fScale(&a[3], b, &out[3]);
    BH_Vec3fScale(&a[6], b, &out[6]);
}


void BH_Mat3fTranspose(const float in[9],
                       float out[9])
{
    float tmp[9];

    tmp[0] = in[0]; tmp[3] = in[1]; tmp[6] = in[2];
    tmp[1] = in[3]; tmp[4] = in[4]; tmp[7] = in[5];
    tmp[2] = in[6]; tmp[5] = in[7]; tmp[8] = in[8];

    memcpy(out, tmp, sizeof(tmp));
}


float BH_Mat3fTrace(const float in[9])
{
    return in[0] + in[4] + in[8];
}


float BH_Mat3fDet(const float in[9])
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


int BH_Mat3fInverse(const float in[9],
                    float out[9])
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

    if (fabsf(det) < EPSILON)
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
                       float out[9])
{
    BH_Mat3fIdentity(out);
    out[0] = x;
    out[4] = y;
}


void BH_Mat3fFromTranslation(float x,
                             float y,
                             float out[9])
{
    BH_Mat3fIdentity(out);
    out[6] = x;
    out[7] = y;
}


void BH_Mat3fFromRotation(float angle,
                          float out[9])
{
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    BH_Mat3fIdentity(out);
    out[0] = c;
    out[1] = s;
    out[3] = -s;
    out[4] = c;
}


void BH_Mat3fApplyVec3f(float a[9],
                        float b[3],
                        float out[3])
{
    float tmp[3], row[3];

    row[0] = row[1] = row[2] = b[0]; BH_Vec3fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = b[1]; BH_Vec3fMulAdd(&a[3], row, tmp, tmp);
    row[0] = row[1] = row[2] = b[2]; BH_Vec3fMulAdd(&a[6], row, tmp, tmp);

    memcpy(out, tmp, sizeof(tmp));
}


void BH_Mat3fApplyVec2f(float a[9],
                        float b[2],
                        float out[2])
{
    float tmp[3], row[3];

    row[0] = row[1] = row[2] = b[0]; BH_Vec3fMul(&a[0], row, tmp);
    row[0] = row[1] = row[2] = b[1]; BH_Vec3fMulAdd(&a[3], row, tmp, tmp);
    row[0] = row[1] = row[2] = 1.0f; BH_Vec3fMulAdd(&a[6], row, tmp, tmp);

    memcpy(out, tmp, sizeof(float) * 2);
}
