#ifndef BH_MATH_VEC4F_H
#define BH_MATH_VEC4F_H

#include "../Common.h"


void BH_Vec4fAdd(const float a[4],
                 const float b[4],
                 float out[4]);


void BH_Vec4fSub(const float a[4],
                 const float b[4],
                 float out[4]);


void BH_Vec4fMul(const float a[4],
                 const float b[4],
                 float out[4]);


void BH_Vec4fScale(const float a[4],
                   float b,
                   float out[4]);


void BH_Vec4fMulAdd(const float a[4],
                    const float b[4],
                    const float c[4],
                    float out[4]);


void BH_Vec4fNegate(const float in[4],
                    float out[4]);


float BH_Vec4fDot(const float a[4],
                  const float b[4]);


float BH_Vec4fLength(const float in[4]);


void BH_Vec4fNormal(const float in[4],
                    float out[4]);


float BH_Vec4fNormalEx(const float in[4],
                       float out[4]);


void BH_Vec4fMin(const float a[4],
                 const float b[4],
                 float out[4]);


void BH_Vec4fMax(const float a[4],
                 const float b[4],
                 float out[4]);


void BH_Vec4fLerp(const float a[4],
                  const float b[4],
                  float t,
                  float out[4]);


void BH_Vec4fProject(const float a[4],
                     const float b[4],
                     float out[4]);


void BH_Vec4fBarycentric(const float a[4],
                         const float b[4],
                         const float c[4],
                         float v,
                         float w,
                         float out[4]);

#endif /* BH_MATH_VEC4F */
