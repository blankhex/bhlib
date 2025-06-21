#ifndef BH_MATH_PLANE_H
#define BH_MATH_PLANE_H

#include "../Common.h"


int BH_PlaneFromPoints(const float a[3],
                       const float b[3],
                       const float c[3],
                       float out[4]);



float BH_PlaneDistance(const float plane[4],
                       const float point[3]);



void BH_PlaneClosestPoint(const float plane[4],
                          const float point[3],
                          float out[3]);


#endif /* BH_MATH_PLANE_H */
