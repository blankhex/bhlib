#ifndef BH_MATH_LINE_H
#define BH_MATH_LINE_H

#include "../Common.h"


int BH_LineFromPoints(const float a[2],
                      const float b[2],
                      float out[3]);


float BH_LineDistance(const float line[3],
                      const float point[2]);


void BH_LineClosestPoint(const float line[3],
                         const float point[2],
                         float out[2]);


#endif /* BH_MATH_LINE_H */
