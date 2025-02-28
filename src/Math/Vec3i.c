#include <BH/Math.h>


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
