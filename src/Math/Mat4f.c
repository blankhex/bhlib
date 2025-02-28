#include <BH/Math.h>
#include <string.h>
#include <math.h>


#define EPSILON 0.00001f
#define PI      3.14159265358979323846f


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

    if (fabsf(det) < EPSILON)
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

    c = cosf(angle);
    s = sinf(angle);

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

    c = cosf(angle);
    s = sinf(angle);

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

    c = cosf(angle);
    s = sinf(angle);

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

    if (fabsf(length) < EPSILON)
        return;

    x = axis[0] / length;
    y = axis[1] / length;
    z = axis[2] / length;

    c = cosf(angle);
    s = sinf(angle);
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

    rs = sinf(roll);
    rc = cosf(roll);
    ps = sinf(pitch);
    pc = cosf(pitch);
    ys = sinf(yaw);
    yc = cosf(yaw);

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
