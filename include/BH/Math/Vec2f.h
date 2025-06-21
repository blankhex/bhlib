#ifndef BH_MATH_VEC2F_H
#define BH_MATH_VEC2F_H

#include "../Common.h"

void BH_Vec2fAdd(const float a[2],
                 const float b[2],
                 float out[2]);


void BH_Vec2fSub(const float a[2],
                 const float b[2],
                 float out[2]);


void BH_Vec2fMul(const float a[2],
                 const float b[2],
                 float out[2]);


void BH_Vec2fScale(const float a[2],
                   float b,
                   float out[2]);


void BH_Vec2fMulAdd(const float a[2],
                    const float b[2],
                    const float c[2],
                    float out[2]);


void BH_Vec2fNegate(const float in[2],
                    float out[2]);


float BH_Vec2fDot(const float a[2],
                  const float b[2]);


float BH_Vec2fCross(const float a[2],
                    const float b[2]);


float BH_Vec2fLength(const float in[2]);


void BH_Vec2fNormal(const float in[2],
                    float out[2]);


float BH_Vec2fNormalEx(const float in[2],
                       float out[2]);


void BH_Vec2fMin(const float a[2],
                 const float b[2],
                 float out[2]);


void BH_Vec2fMax(const float a[2],
                 const float b[2],
                 float out[2]);


void BH_Vec2fLerp(const float a[2],
                  const float b[2],
                  float t,
                  float out[2]);


void BH_Vec2fProject(const float a[2],
                     const float b[2],
                     float out[2]);


void BH_Vec2fBarycentric(const float a[2],
                         const float b[2],
                         const float c[2],
                         float v,
                         float w,
                         float out[2]);


#endif /* BH_MATH_VEC2F */
