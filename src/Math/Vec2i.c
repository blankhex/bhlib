#include <BH/Math.h>


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
