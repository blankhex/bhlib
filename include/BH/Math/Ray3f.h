#ifndef BH_MATH_RAY3F_H
#define BH_MATH_RAY3F_H

#include "../Common.h"


int BH_Ray3fIntersectPlane(const float start[3],
                           const float direction[3],
                           const float plane[4],
                           float *t,
                           float out[3]);


int BH_Ray3fIntersectTriangle(const float start[3],
                              const float direction[3],
                              const float a[3],
                              const float b[3],
                              const float c[3],
                              float *t,
                              float out[3]);


int BH_Segment3fIntersectPlane(const float start[3],
                               const float end[3],
                               const float plane[4],
                               float *t,
                               float out[3]);


int BH_Segment3fIntersectTriangle(const float start[3],
                                  const float end[3],
                                  const float a[3],
                                  const float b[3],
                                  const float c[3],
                                  float *t,
                                  float out[3]);


int BH_Ray3fIntersectBox3f(const float aStart[3],
                           const float aDirection[3],
                           const float bMin[3],
                           const float bMax[3],
                           float *t,
                           float out[3]);


int BH_Segment3fIntersectBox3f(const float aStart[3],
                               const float aEnd[3],
                               const float bMin[3],
                               const float bMax[3],
                               float *t,
                               float out[3]);

#endif /* BH_MATH_RAY3F_H */
