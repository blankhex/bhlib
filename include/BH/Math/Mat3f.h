#ifndef BH_MATH_MAT3F_H
#define BH_MATH_MAT3F_H

#include "../Common.h"


void BH_Mat3fIdentity(float out[9]);



void BH_Mat3fAdd(const float a[9],
                 const float b[9],
                 float out[9]);



void BH_Mat3fSub(const float a[9],
                 const float b[9],
                 float out[9]);



void BH_Mat3fMul(const float a[9],
                 const float b[9],
                 float out[9]);



void BH_Mat3fScale(const float a[9],
                   float b,
                   float out[9]);



void BH_Mat3fTranspose(const float in[9],
                       float out[9]);



float BH_Mat3fTrace(const float in[9]);



float BH_Mat3fDet(const float in[9]);



int BH_Mat3fInverse(const float in[9],
                    float out[9]);



void BH_Mat3fFromScale(float x,
                       float y,
                       float out[9]);



void BH_Mat3fFromTranslation(float x,
                             float y,
                             float out[9]);



void BH_Mat3fFromRotation(float angle,
                          float out[9]);



void BH_Mat3fApplyVec3f(float a[9],
                        float b[3],
                        float out[3]);



void BH_Mat3fApplyVec2f(float a[9],
                        float b[2],
                        float out[2]);


#endif /* BH_MATH_MAT3F */
