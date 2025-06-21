#ifndef BH_MATH_BOX2F_H
#define BH_MATH_BOX2F_H

#include "../Common.h"


void BH_Box2fUnion(const float aMin[2],
                   const float aMax[2],
                   const float bMin[2],
                   const float bMax[2],
                   float outMin[2],
                   float outMax[2]);



int BH_Box2fIntersect(const float aMin[2],
                      const float aMax[2],
                      const float bMin[2],
                      const float bMax[2],
                      float outMin[2],
                      float outMax[2]);



int BH_Box2fContains(const float aMin[2],
                     const float aMax[2],
                     const float point[2]);



int BH_Box2fEnclose(const float *points,
                    size_t size,
                    float outMin[2],
                    float outMax[2]);


#endif /* BH_MATH_BOX2F_H */
