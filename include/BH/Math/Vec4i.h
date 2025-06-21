#ifndef BH_MATH_VEC4I_H
#define BH_MATH_VEC4I_H

#include "../Common.h"


void BH_Vec4iAdd(const int a[4],
                 const int b[4],
                 int out[4]);



void BH_Vec4iSub(const int a[4],
                 const int b[4],
                 int out[4]);



void BH_Vec4iMul(const int a[4],
                 const int b[4],
                 int out[4]);



void BH_Vec4iScale(const int a[4],
                   int b,
                   int out[4]);



void BH_Vec4iMulAdd(const int a[4],
                    const int b[4],
                    const int c[4],
                    int out[4]);



void BH_Vec4iNegate(const int in[4],
                    int out[4]);



void BH_Vec4iMin(const int a[4],
                 const int b[4],
                 int out[4]);



void BH_Vec4iMax(const int a[4],
                 const int b[4],
                 int out[4]);


#endif /* BH_MATH_VEC4I */
