#ifndef BH_MATH_BOX3F_H
#define BH_MATH_BOX3F_H

#include "../Common.h"


void BH_Box3fUnion(const float aMin[3],
                   const float aMax[3],
                   const float bMin[3],
                   const float bMax[3],
                   float outMin[3],
                   float outMax[3]);



int BH_Box3fIntersect(const float aMin[3],
                      const float aMax[3],
                      const float bMin[3],
                      const float bMax[3],
                      float outMin[3],
                      float outMax[3]);



int BH_Box3fContains(const float aMin[3],
                     const float aMax[3],
                     const float point[3]);



int BH_Box3fEnclose(const float *points,
                    size_t size,
                    float outMin[3],
                    float outMax[3]);


#endif /* BH_MATH_BOX3F_H */
