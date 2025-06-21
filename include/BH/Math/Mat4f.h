#ifndef BH_MATH_MAT4F_H
#define BH_MATH_MAT4F_H

#include "../Common.h"


void BH_Mat4fIdentity(float out[16]);



void BH_Mat4fAdd(const float a[16],
                 const float b[16],
                 float out[16]);



void BH_Mat4fSub(const float a[16],
                 const float b[16],
                 float out[16]);



void BH_Mat4fMul(const float a[16],
                 const float b[16],
                 float out[16]);



void BH_Mat4fScale(const float a[16],
                   float b,
                   float out[16]);



void BH_Mat4fTranspose(const float in[16],
                       float out[16]);



float BH_Mat4fTrace(const float in[16]);



float BH_Mat4fDet(const float in[16]);



int BH_Mat4fInverse(const float in[16],
                    float out[16]);



void BH_Mat4fFromScale(float x,
                       float y,
                       float z,
                       float out[16]);



void BH_Mat4fFromTranslation(float x,
                             float y,
                             float z,
                             float out[16]);



void BH_Mat4fFromRotationX(float angle,
                           float out[16]);



void BH_Mat4fFromRotationY(float angle,
                           float out[16]);



void BH_Mat4fFromRotationZ(float angle,
                           float out[16]);



void BH_Mat4fFromAxis(const float axis[3],
                      float angle,
                      float out[16]);



void BH_Mat4fFromEuler(float roll,
                       float pitch,
                       float yaw,
                       float out[16]);



void BH_Mat4fFromQuat4f(const float in[4],
                        float out[16]);



void BH_Mat4fFromOrtho(float xMin,
                       float xMax,
                       float yMin,
                       float yMax,
                       float zMin,
                       float zMax,
                       float out[16]);



void BH_Mat4fFromFrustum(float fov,
                         float aspect,
                         float zMin,
                         float zMax,
                         float out[16]);



void BH_Mat4fFromLookAt(const float position[3],
                        const float at[3],
                        const float up[3],
                        float out[16]);



void BH_Mat4fApplyVec4f(const float a[16],
                        const float b[4],
                        float out[4]);



void BH_Mat4fApplyVec3f(const float a[16],
                        const float b[3],
                        float out[3]);


#endif /* BH_MATH_MAT4F */
