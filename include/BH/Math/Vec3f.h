#ifndef BH_MATH_VEC3F_H
#define BH_MATH_VEC3F_H

#include "../Common.h"


void BH_Vec3fAdd(const float a[3],
                 const float b[3],
                 float out[3]);


void BH_Vec3fSub(const float a[3],
                 const float b[3],
                 float out[3]);


void BH_Vec3fMul(const float a[3],
                 const float b[3],
                 float out[3]);


void BH_Vec3fScale(const float a[3],
                   float b,
                   float out[3]);


void BH_Vec3fMulAdd(const float a[3],
                    const float b[3],
                    const float c[3],
                    float out[3]);


void BH_Vec3fNegate(const float in[3],
                    float out[3]);


float BH_Vec3fDot(const float a[3],
                  const float b[3]);


void BH_Vec3fCross(const float a[3],
                   const float b[3],
                   float out[3]);


float BH_Vec3fLength(const float in[3]);


void BH_Vec3fNormal(const float in[3],
                    float out[3]);


float BH_Vec3fNormalEx(const float in[3],
                       float out[3]);


void BH_Vec3fMin(const float a[3],
                 const float b[3],
                 float out[3]);


void BH_Vec3fMax(const float a[3],
                 const float b[3],
                 float out[3]);


void BH_Vec3fLerp(const float a[3],
                  const float b[3],
                  float t,
                  float out[3]);


void BH_Vec3fProject(const float a[3],
                     const float b[3],
                     float out[3]);


void BH_Vec3fBarycentric(const float a[3],
                         const float b[3],
                         const float c[3],
                         float v,
                         float w,
                         float out[3]);


#endif /* BH_MATH_VEC3F_H */
