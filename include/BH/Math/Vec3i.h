#ifndef BH_MATH_VEC3I_H
#define BH_MATH_VEC3I_H

#include "../Common.h"

void BH_Vec3iAdd(const int a[3],
                 const int b[3],
                 int out[3]);



void BH_Vec3iSub(const int a[3],
                 const int b[3],
                 int out[3]);



void BH_Vec3iMul(const int a[3],
                 const int b[3],
                 int out[3]);



void BH_Vec3iScale(const int a[3],
                   int b,
                   int out[3]);



void BH_Vec3iMulAdd(const int a[3],
                    const int b[3],
                    const int c[3],
                    int out[3]);



void BH_Vec3iNegate(const int in[3],
                    int out[3]);



void BH_Vec3iMin(const int a[3],
                 const int b[3],
                 int out[3]);



void BH_Vec3iMax(const int a[3],
                 const int b[3],
                 int out[3]);


#endif /* BH_MATH_VEC3I */
