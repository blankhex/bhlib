#ifndef BH_MATH_QUAT_H
#define BH_MATH_QUAT_H

#include "../Common.h"
#include "Vec4f.h"


#define BH_Quat4fAdd(a, b, out) \
    BH_Vec4fAdd(a, b, out)


#define BH_Quat4fSub(a, b, out) \
    BH_Vec4fSub(a, b, out)


#define BH_Quat4fScale(a, b, out) \
    BH_Vec4fScale(a, b, out)


#define BH_Quat4fNegate(in, out) \
    BH_Vec4fNegate(in, out)


#define BH_Quat4fDot(a, b) \
    BH_Vec4fDot(a, b)


#define BH_Quat4fLength(in) \
    BH_Vec4fLength(in)


#define BH_Quat4fNormal(in, out) \
    BH_Vec4fNormal(in, out)


#define BH_Quat4fLerp(a, b, t, out) \
    BH_Vec4fLerp(a, b, t, out)


void BH_Quat4fIdentity(float out[4]);


void BH_Quat4fConjugate(const float in[4],
                        float out[4]);


void BH_Quat4fInverse(const float in[4],
                      float out[4]);


void BH_Quat4fMul(const float a[4],
                  const float b[4],
                  float out[4]);


void BH_Quat4fSlerp(const float a[4],
                    const float b[4],
                    float t,
                    float out[4]);


void BH_Quat4fFromEuler(float roll,
                        float pitch,
                        float yaw,
                        float out[4]);


void BH_Quat4fFromAxis(const float axis[3],
                       float angle,
                       float out[4]);


void BH_Quat4fToEuler(const float in[4],
                      float *roll,
                      float *pitch,
                      float *yaw);


void BH_Quat4fToAxis(const float in[4],
                     float axis[3],
                     float *angle);


void BH_Quat4fToMat4f(const float in[4],
                      float out[16]);


#endif /* BH_MATH_QUAT */
