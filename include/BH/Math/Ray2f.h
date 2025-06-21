#ifndef BH_MATH_RAY2F_H
#define BH_MATH_RAY2F_H

#include "../Common.h"


int BH_Ray2fIntersectLine(const float start[2],
                          const float direction[2],
                          const float line[3],
                          float *t,
                          float out[2]);


int BH_Ray2fIntersectTime(const float aStart[2],
                          const float aDirection[2],
                          const float bStart[2],
                          const float bDirection[2],
                          float *time1,
                          float *time2);


int BH_Ray2fIntersectRay(const float aStart[2],
                         const float aDirection[2],
                         const float bStart[2],
                         const float bDirection[2],
                         float *t,
                         float out[2]);


int BH_Ray2fIntersectSegment(const float aStart[2],
                             const float aDirection[2],
                             const float bStart[2],
                             const float bEnd[2],
                             float *t,
                             float out[2]);


int BH_Segment2fIntersectLine(const float start[2],
                              const float end[2],
                              const float line[3],
                              float *t,
                              float out[2]);


int BH_Segment2fIntersectSegment(const float aStart[2],
                                 const float aEnd[2],
                                 const float bStart[2],
                                 const float bEnd[2],
                                 float *t,
                                 float out[2]);


int BH_Ray2fIntersectBox2f(const float aStart[2],
                           const float aDirection[2],
                           const float bMin[2],
                           const float bMax[2],
                           float *t,
                           float out[2]);


int BH_Segment2fIntersectBox2f(const float aStart[2],
                               const float aEnd[2],
                               const float bMin[2],
                               const float bMax[2],
                               float *t,
                               float out[2]);


#endif /* BH_MATH_RAY2F_H */
