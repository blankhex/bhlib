#ifndef BH_MATH_VEC2I_H
#define BH_MATH_VEC2I_H

#include "../Common.h"

void BH_Vec2iAdd(const int a[2],
                 const int b[2],
                 int out[2]);



void BH_Vec2iSub(const int a[2],
                 const int b[2],
                 int out[2]);



void BH_Vec2iMul(const int a[2],
                 const int b[2],
                 int out[2]);



void BH_Vec2iScale(const int a[2],
                   int b,
                   int out[2]);



void BH_Vec2iMulAdd(const int a[2],
                    const int b[2],
                    const int c[2],
                    int out[2]);



void BH_Vec2iNegate(const int in[2],
                    int out[2]);



void BH_Vec2iMin(const int a[2],
                 const int b[2],
                 int out[2]);



void BH_Vec2iMax(const int a[2],
                 const int b[2],
                 int out[2]);

#endif /* BH_MATH_VEC2I */
