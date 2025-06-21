#ifndef BH_MATH_MISC_H
#define BH_MATH_MISC_H

#include "../Common.h"

float BH_Lerpf(float a, float b, float t);



void BH_Triangle3fBarycentric(const float a[3],
                              const float b[3],
                              const float c[3],
                              const float point[3],
                              float out[3]);


#endif /* BH_MATH_MISC */
