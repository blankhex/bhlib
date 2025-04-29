#include <BH/Math.h>


void BH_Vec4iAdd(const int a[4],
                 const int b[4],
                 int out[4])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}


void BH_Vec4iSub(const int a[4],
                 const int b[4],
                 int out[4])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}


void BH_Vec4iMul(const int a[4],
                 const int b[4],
                 int out[4])
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}


void BH_Vec4iScale(const int a[4],
                   int b,
                   int out[4])
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
    out[3] = a[3] * b;
}


void BH_Vec4iMulAdd(const int a[4],
                    const int b[4],
                    const int c[4],
                    int out[4])
{
    out[0] = a[0] * b[0] + c[0];
    out[1] = a[1] * b[1] + c[1];
    out[2] = a[2] * b[2] + c[2];
    out[3] = a[3] * b[3] + c[3];
}


void BH_Vec4iNegate(const int in[4],
                    int out[4])
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = -in[3];
}


void BH_Vec4iMin(const int a[4],
                 const int b[4],
                 int out[4])
{
    if (a[0] < b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] < b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] < b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] < b[3]) out[3] = a[3]; else out[3] = b[3];
}


void BH_Vec4iMax(const int a[4],
                 const int b[4],
                 int out[4])
{
    if (a[0] > b[0]) out[0] = a[0]; else out[0] = b[0];
    if (a[1] > b[1]) out[1] = a[1]; else out[1] = b[1];
    if (a[2] > b[2]) out[2] = a[2]; else out[2] = b[2];
    if (a[3] > b[3]) out[3] = a[3]; else out[3] = b[3];
}
