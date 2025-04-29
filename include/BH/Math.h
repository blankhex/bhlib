#ifndef BH_MATH_H
#define BH_MATH_H


#include "Common.h"


/**
 * Adds \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fAdd(const float a[4],
                 const float b[4],
                 float out[4]);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fSub(const float a[4],
                 const float b[4],
                 float out[4]);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMul(const float a[4],
                 const float b[4],
                 float out[4]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B value
 * \param out  Output vector
 */
void BH_Vec4fScale(const float a[4],
                   float b,
                   float out[4]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param c    C 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMulAdd(const float a[4],
                    const float b[4],
                    const float c[4],
                    float out[4]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fNegate(const float in[4],
                    float out[4]);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 4D vector
 * \param b  B 4D vector
 */
float BH_Vec4fDot(const float a[4],
                  const float b[4]);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 4D vector
 */
float BH_Vec4fLength(const float in[4]);


/**
 * Computes normal vector from the \a in and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fNormal(const float in[4],
                    float out[4]);


/**
 * Computes normal vector from the \a in stores result into \a out and returns
 * source length of the vector.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 *
 * \return Returns length prior to normalization
 */
float BH_Vec4fNormalEx(const float in[4],
                       float out[4]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMin(const float a[4],
                 const float b[4],
                 float out[4]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMax(const float a[4],
                 const float b[4],
                 float out[4]);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param t    Amount
 * \param out  Output 4D vector
 */
void BH_Vec4fLerp(const float a[4],
                  const float b[4],
                  float t,
                  float out[4]);


/**
 * Projects \a a vector onto \a b vector and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fProject(const float a[4],
                     const float b[4],
                     float out[4]);


/**
 * Computes point from barycentric coordiantes \a v, \a w  and points \a a,
 * \a b and \a c vectors.
 *
 * Output vector is calculated as A + v*(B-A) + w*(C-A).
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param c    C 4D vector
 * \param v    V barycentric coordinate
 * \param w    W barycentric coordinate
 * \param out  Output 4D vector
 */
void BH_Vec4fBarycentric(const float a[4],
                         const float b[4],
                         const float c[4],
                         float v,
                         float w,
                         float out[4]);


/**
 * Adds \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fAdd(const float a[3],
                 const float b[3],
                 float out[3]);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fSub(const float a[3],
                 const float b[3],
                 float out[3]);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMul(const float a[3],
                 const float b[3],
                 float out[3]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B value
 * \param out  Output 3D vector
 */
void BH_Vec3fScale(const float a[3],
                   float b,
                   float out[3]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param c    C 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMulAdd(const float a[3],
                    const float b[3],
                    const float c[3],
                    float out[3]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 *
 */
void BH_Vec3fNegate(const float in[3],
                    float out[3]);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 3D vector
 * \param b  B 3D vector
 */
float BH_Vec3fDot(const float a[3],
                  const float b[3]);


/**
 * Computes cross product of \a a and \a b vectors and stores
 * result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fCross(const float a[3],
                   const float b[3],
                   float out[3]);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 3D vector
 */
float BH_Vec3fLength(const float in[3]);


/**
 * Computes normal vector from the \a in and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fNormal(const float in[3],
                    float out[3]);


/**
 * Computes normal vector from the \a in stores result into \a out and returns
 * source length of the vector.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 *
 * \return Returns length prior to normalization
 */
float BH_Vec3fNormalEx(const float in[3],
                       float out[3]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMin(const float a[3],
                 const float b[3],
                 float out[3]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMax(const float a[3],
                 const float b[3],
                 float out[3]);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param t    Amount
 * \param out  Output 3D vector
 */
void BH_Vec3fLerp(const float a[3],
                  const float b[3],
                  float t,
                  float out[3]);


/**
 * Projects \a a vector onto \a b vector and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fProject(const float a[3],
                     const float b[3],
                     float out[3]);


/**
 * Computes point from barycentric coordiantes \a v, \a w  and points \a a,
 * \a b and \a c vectors.
 *
 * Output vector is calculated as A + v*(B-A) + w*(C-A).
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param c    C 3D vector
 * \param v    V barycentric coordinate
 * \param w    W barycentric coordinate
 * \param out  Output 3D vector
 */
void BH_Vec3fBarycentric(const float a[3],
                         const float b[3],
                         const float c[3],
                         float v,
                         float w,
                         float out[3]);


/**
 * Adds \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fAdd(const float a[2],
                 const float b[2],
                 float out[2]);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fSub(const float a[2],
                 const float b[2],
                 float out[2]);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMul(const float a[2],
                 const float b[2],
                 float out[2]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B value
 * \param out  Output 2D vector
 */
void BH_Vec2fScale(const float a[2],
                   float b,
                   float out[2]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param c    C 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMulAdd(const float a[2],
                    const float b[2],
                    const float c[2],
                    float out[2]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 *
 */
void BH_Vec2fNegate(const float in[2],
                    float out[2]);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 2D vector
 * \param b  B 2D vector
 */
float BH_Vec2fDot(const float a[2],
                  const float b[2]);


/**
 * Computes cross product of \a a and \a b vectors and returns the result.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 */
float BH_Vec2fCross(const float a[2],
                    const float b[2]);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 2D vector
 */
float BH_Vec2fLength(const float in[2]);


/**
 * Computes normal vector from the \a in and stores result into
 * \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fNormal(const float in[2],
                    float out[2]);


/**
 * Computes normal vector from the \a in stores result into \a out and returns
 * source length of the vector.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 *
 * \return Returns length prior to normalization
 */
float BH_Vec2fNormalEx(const float in[2],
                       float out[2]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMin(const float a[2],
                 const float b[2],
                 float out[2]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMax(const float a[2],
                 const float b[2],
                 float out[2]);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param t    Amount
 * \param out  Output 2D vector
 */
void BH_Vec2fLerp(const float a[2],
                  const float b[2],
                  float t,
                  float out[2]);


/**
 * Projects \a a vector onto \a b vector and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fProject(const float a[2],
                     const float b[2],
                     float out[2]);


/**
 * Computes point from barycentric coordiantes \a v, \a w  and points \a a,
 * \a b and \a c vectors.
 *
 * Output vector is calculated as A + v*(B-A) + w*(C-A).
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param c    C 2D vector
 * \param v    V barycentric coordinate
 * \param w    W barycentric coordinate
 * \param out  Output 2D vector
 */
void BH_Vec2fBarycentric(const float a[2],
                         const float b[2],
                         const float c[2],
                         float v,
                         float w,
                         float out[2]);


/**
 * Interpolates between \a a and \a b values by \a t amount and returns the
 * result.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param t    Amount
 * \param out  Output 2D vector
 */
float BH_Lerpf(float a, float b, float t);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iAdd(const int a[4],
                 const int b[4],
                 int out[4]);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iSub(const int a[4],
                 const int b[4],
                 int out[4]);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output vector
 */
void BH_Vec4iMul(const int a[4],
                 const int b[4],
                 int out[4]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B value
 * \param out  Output 4D vector
 */
void BH_Vec4iScale(const int a[4],
                   int b,
                   int out[4]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param c    C 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMulAdd(const int a[4],
                    const int b[4],
                    const int c[4],
                    int out[4]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iNegate(const int in[4],
                    int out[4]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMin(const int a[4],
                 const int b[4],
                 int out[4]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMax(const int a[4],
                 const int b[4],
                 int out[4]);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iAdd(const int a[3],
                 const int b[3],
                 int out[3]);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iSub(const int a[3],
                 const int b[3],
                 int out[3]);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMul(const int a[3],
                 const int b[3],
                 int out[3]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B value
 * \param out  Output 3D vector
 */
void BH_Vec3iScale(const int a[3],
                   int b,
                   int out[3]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param c    C 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMulAdd(const int a[3],
                    const int b[3],
                    const int c[3],
                    int out[3]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 *
 */
void BH_Vec3iNegate(const int in[3],
                    int out[3]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMin(const int a[3],
                 const int b[3],
                 int out[3]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMax(const int a[3],
                 const int b[3],
                 int out[3]);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iAdd(const int a[2],
                 const int b[2],
                 int out[2]);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iSub(const int a[2],
                 const int b[2],
                 int out[2]);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMul(const int a[2],
                 const int b[2],
                 int out[2]);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D value
 * \param out  Output 2D vector
 */
void BH_Vec2iScale(const int a[2],
                   int b,
                   int out[2]);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param c    C 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMulAdd(const int a[2],
                    const int b[2],
                    const int c[2],
                    int out[2]);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 *
 */
void BH_Vec2iNegate(const int in[2],
                    int out[2]);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMin(const int a[2],
                 const int b[2],
                 int out[2]);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMax(const int a[2],
                 const int b[2],
                 int out[2]);


/**
 * Adds \a a and \a b floating point quaternions and stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param out  Output quaternion
 */
#define BH_Quat4fAdd(a, b, out) \
    BH_Vec4fAdd(a, b, out)


/**
 * Subtracts \a a and \a b floating point quaternions and stores result into
 * \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param out  Output quaternion
 */
#define BH_Quat4fSub(a, b, out) \
    BH_Vec4fSub(a, b, out)


/**
 * Scales \a a quaternion by the value \a b and stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B value
 * \param out  Output quaternion
 */
#define BH_Quat4fScale(a, b, out) \
    BH_Vec4fScale(a, b, out)


/**
 * Negates \a in quaternion and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
#define BH_Quat4fNegate(in, out) \
    BH_Vec4fNegate(in, out)


/**
 * Computes dot product of \a a and \a b quaternions and returns the result.
 *
 * \param a  A quaternion
 * \param b  B quaternion
 */
#define BH_Quat4fDot(a, b) \
    BH_Vec4fDot(a, b)


/**
 * Computes length of the \a in quaternion and returns the result.
 *
 * \param in  Input quaternion
 */
#define BH_Quat4fLength(in) \
    BH_Vec4fLength(in)


/**
 * Computes normal quaternion from the \a in and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
#define BH_Quat4fNormal(in, out) \
    BH_Vec4fNormal(in, out)


/**
 * Interpolates between \a a and \a b quaternion by \a t amount and stores
 * result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param t    Amount
 * \param out  Output quaternion
 */
#define BH_Quat4fLerp(a, b, t, out) \
    BH_Vec4fLerp(a, b, t, out)


/**
 * Stores identity quaternion into \a out.
 *
 * \param out  Output quaternion.
 */
void BH_Quat4fIdentity(float out[4]);


/**
 * Conjugates the \a in quaternion and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fConjugate(const float in[4],
                        float out[4]);


/**
 * Computes the inverse of the \a in quaternion and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fInverse(const float in[4],
                      float out[4]);


/**
 * Multiplies the \a a and \a b quaternions and stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fMul(const float a[4],
                  const float b[4],
                  float out[4]);


/**
 * Spherically interpolates between \a a and \a b quaternions by \a t amount and
 * stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param t    Amount
 * \param out  Output quaternion
 */
void BH_Quat4fSlerp(const float a[4],
                    const float b[4],
                    float t,
                    float out[4]);


/**
 * Computes the quaternion that represents \a roll, \a pitch, \a yaw (euler
 * angles) and stores result into \a out.
 *
 * Order of the rotation is ZYX (yaw, pitch, roll)
 *
 * \param roll   Roll
 * \param pitch  Pitch
 * \param yaw    Yaw
 * \param out    Output quaternion
 */
void BH_Quat4fFromEuler(float roll,
                        float pitch,
                        float yaw,
                        float out[4]);


/**
 * Computes quaternion that represents rotation by angle \a angle around
 * axis \a axis and stores result into \a out.
 *
 * \param axis   Axis 3D vector
 * \param angle  Angle
 * \param out    Output quaternion
 */
void BH_Quat4fFromAxis(const float axis[3],
                       float angle,
                       float out[4]);


/**
 * Computes euler angles from quaternion \a in and stores result into \a roll,
 * \a pitch, \a yaw.
 *
 * Order of the rotation is ZYX (yaw, pitch, roll)
 *
 * \param in     Input quaternion
 * \param roll   Output roll
 * \param pitch  Output pitch
 * \param yaw    Output yaw
 */
void BH_Quat4fToEuler(const float in[4],
                      float *roll,
                      float *pitch,
                      float *yaw);


/**
 * Computes rotation around axis from quaternion \a in and stores result into
 * \a axis and \a angle.
 *
 * \param in     Input quaternion
 * \param axis   Output axis 3D vector
 * \param angle  Output angle
 */
void BH_Quat4fToAxis(const float in[4],
                     float axis[3],
                     float *angle);


/**
 * Computes 4x4 rotation matrix from quaternion \a in and stores result into
 * \a out.
 *
 * \param in     Input quaternion
 * \param out    Output 4x4 matrix
 */
void BH_Quat4fToMat4f(const float in[4],
                      float out[16]);


/**
 * Stores identity matrix into \a out.
 *
 * \param out  Output 4x4 matrix.
 */
void BH_Mat4fIdentity(float out[16]);


/**
 * Adds \a a and \a b floating point matricies and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fAdd(const float a[16],
                 const float b[16],
                 float out[16]);


/**
 * Subtracts \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fSub(const float a[16],
                 const float b[16],
                 float out[16]);


/**
 * Multiplies \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fMul(const float a[16],
                 const float b[16],
                 float out[16]);


/**
 * Scales \a a matrix by the value \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B value
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fScale(const float a[16],
                   float b,
                   float out[16]);


/**
 * Transposes matrix \a in and stores result into \a out.
 *
 * \param in   Input 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fTranspose(const float in[16],
                       float out[16]);


/**
 * Computes \a in matrix trace and returns the result.
 *
 * \param in  Input 4x4 matrix
 */
float BH_Mat4fTrace(const float in[16]);


/**
 * Computes \a in matrix determinant and returns the result.
 *
 * \param in  Input 4x4 matrix
 */
float BH_Mat4fDet(const float in[16]);


/**
 * Computes inverse of \a in matrix and stores result into \a out.
 *
 * \param in   Input 4x4 matrix
 * \param out  OUtput 4x4 matrix
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Mat4fInverse(const float in[16],
                    float out[16]);


/**
 * Computes scaling matrix from values \a x, \a y, \a z and stores result into
 * \a out.
 *
 * \param x    X scale
 * \param y    Y scale
 * \param z    Z scale
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fFromScale(float x,
                       float y,
                       float z,
                       float out[16]);


/**
 * Computes translation matrix from values \a x, \a y, \a z and stores result
 * into \a out.
 *
 * \param x    X translation
 * \param y    Y translation
 * \param z    Z translation
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fFromTranslation(float x,
                             float y,
                             float z,
                             float out[16]);


/**
 * Computes rotation matrix around x axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationX(float angle,
                           float out[16]);


/**
 * Computes rotation matrix around y axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationY(float angle,
                           float out[16]);


/**
 * Computes rotation matrix around z axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationZ(float angle,
                           float out[16]);


/**
 * Computes rotation matrix around axis \a axis with angle \a angle and stores
 * result \a out.
 *
 * \param axis   Axis 3D vector
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromAxis(const float axis[3],
                      float angle,
                      float out[16]);


/**
 * Computes the rotation matrix that represents \a roll, \a pitch, \a yaw (euler
 * angles) and stores result into \a out.
 *
 * Order of the rotation is ZYX (yaw, pitch, roll)
 *
 * \param roll   Roll
 * \param pitch  Pitch
 * \param yaw    Yaw
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromEuler(float roll,
                       float pitch,
                       float yaw,
                       float out[16]);


/**
 * Computes 4x4 rotation matrix from quaternion \a in and stores result into
 * \a out.
 *
 * \param in     Input quaternion
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromQuat4f(const float in[4],
                        float out[16]);


/**
 * Computes orthographic projection matrix and stores result into \a out.
 *
 * \param x_min  Min x value
 * \param x_max  Max x value
 * \param y_min  Min y value
 * \param y_max  Max y value
 * \param z_min  Min z value
 * \param z_max  Max z value
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromOrtho(float xMin,
                       float xMax,
                       float yMin,
                       float yMax,
                       float zMin,
                       float zMax,
                       float out[16]);


/**
 * Computes perspective projection matrix and stores result into \a out.
 *
 * \param fov     Field of view
 * \param aspect  Aspect ratio
 * \param z_min   Min z value
 * \param z_max   Max z value
 * \param out     Output 4x4 matrix
 */
void BH_Mat4fFromFrustum(float fov,
                         float aspect,
                         float zMin,
                         float zMax,
                         float out[16]);


/**
 * Computes camera view matrix and stores result into \a out.
 *
 * \param position  Position vector
 * \param at        Target vector
 * \param up        Up vector
 * \param out       Output 4x4 matrix
 */
void BH_Mat4fFromLookAt(const float position[3],
                        const float at[3],
                        const float up[3],
                        float out[16]);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Mat4fApplyVec4f(const float a[16],
                        const float b[4],
                        float out[4]);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Mat4fApplyVec3f(const float a[16],
                        const float b[3],
                        float out[3]);


/**
 * Stores identity matrix into \a out.
 *
 * \param out  Output 3x3 matrix.
 */
void BH_Mat3fIdentity(float out[9]);


/**
 * Adds \a a and \a b floating point matricies and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fAdd(const float a[9],
                 const float b[9],
                 float out[9]);


/**
 * Subtracts \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fSub(const float a[9],
                 const float b[9],
                 float out[9]);


/**
 * Multiplies \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fMul(const float a[9],
                 const float b[9],
                 float out[9]);


/**
 * Scales \a a matrix by the value \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B value
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fScale(const float a[9],
                   float b,
                   float out[9]);


/**
 * Transposes matrix \a in and stores result into \a out.
 *
 * \param in   Input 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fTranspose(const float in[9],
                       float out[9]);


/**
 * Computes \a in matrix trace and returns the result.
 *
 * \param in  Input 3x3 matrix
 */
float BH_Mat3fTrace(const float in[9]);


/**
 * Computes \a in matrix determinant and returns the result.
 *
 * \param in  Input 3x3 matrix
 */
float BH_Mat3fDet(const float in[9]);


/**
 * Computes inverse of \a in matrix and stores result into \a out.
 *
 * \param in   Input 3x3 matrix
 * \param out  OUtput 3x3 matrix
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Mat3fInverse(const float in[9],
                    float out[9]);


/**
 * Computes scaling matrix from values \a x, \a y and stores result into
 * \a out.
 *
 * \param x    X scale
 * \param y    Y scale
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fFromScale(float x,
                       float y,
                       float out[9]);


/**
 * Computes translation matrix from values \a x, \a y and stores result
 * into \a out.
 *
 * \param x    X translation
 * \param y    Y translation
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fFromTranslation(float x,
                             float y,
                             float out[9]);


/**
 * Computes rotation matrix around with angle \a angle and stores result \a out.
 *
 * \param angle  Angle
 * \param out    Output 3x3 matrix
 */
void BH_Mat3fFromRotation(float angle,
                          float out[9]);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Mat3fApplyVec3f(float a[9],
                        float b[3],
                        float out[3]);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Mat3fApplyVec2f(float a[9],
                        float b[2],
                        float out[2]);


/**
 * Computes plane from points \a a, \a b, \a c and stores result into \a out.
 *
 * X, Y, Z components of the \a out vector are plane normal, W component is a
 * distance from the origin (0,0,0) to the plane.
 *
 * It is assumed, that points provided in clockwise order.
 *
 * If points form degenerate triangle, this function will return error.
 *
 * \param a     A 3D vector
 * \param b     B 3D vector
 * \param c     C 3D vector
 * \param out   Output 4D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error-code.
 */
int BH_PlaneFromPoints(const float a[3],
                       const float b[3],
                       const float c[3],
                       float out[4]);


/**
 * Computes distance from \a plane to the \a point and returns result.
 *
 * \param plane  Plane 4D vector
 * \param point  Point 3D vector
 *
 * \return Returns distance from plane to point.
 */
float BH_PlaneDistance(const float plane[4],
                       const float point[3]);


/**
 * Computes closest point on the \a plane to the \a point and stores result
 * into \a out.
 *
 * \param plane  Plane 4D vector
 * \param point  Point 3D vector
 * \param out    Output 3D vector
 */
void BH_PlaneClosestPoint(const float plane[4],
                          const float point[3],
                          float out[3]);


/**
 * Computes time of intersection \a t between ray (given \a start and
 * \a direction) and \a plane and stores intersection point into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param start      Start 3D vector
 * \param direction  Direction 3D vector
 * \param plane      Plane 4D vector
 * \param t          Time of intersection
 * \param out        Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray3fIntersectPlane(const float start[3],
                           const float direction[3],
                           const float plane[4],
                           float *t,
                           float out[3]);


/**
 * Computes time of intersection \a t between ray (given \a start and
 * \a direction) and triangle formed by \a a, \a b, \a c points and intersection
 * point into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param start      Start 3D vector
 * \param direction  Direction 3D vector
 * \param a          A 3D vector
 * \param b          B 3D vector
 * \param c          C 3D vector
 * \param t          Time of intersection
 * \param out        Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray3fIntersectTriangle(const float start[3],
                              const float direction[3],
                              const float a[3],
                              const float b[3],
                              const float c[3],
                              float *t,
                              float out[3]);


/**
 * Computes time of intesection \a t between line segment (given \a a and \a b
 * points) and \a plane and stores intersection point into \a out.
 *
 * The returned intersection time \a t is for the segment.
 *
 * \param a      A 3D vector
 * \param b      B 3D vector
 * \param plane  Plane 4D vector
 * \param t      Time of intersection
 * \param out    Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment3fIntersectPlane(const float start[3],
                               const float end[3],
                               const float plane[4],
                               float *t,
                               float out[3]);


/**
 * Computes time of intersection \a t between segment (given \a start and
 * \a end) and triangle formed by \a a, \a b, \a c points and intersection
 * point into \a out.
 *
 * The returned intersection time \a t is for the segment.
 *
 * \param start      Start 3D vector
 * \param direction  Direction 3D vector
 * \param a          A 3D vector
 * \param b          B 3D vector
 * \param c          C 3D vector
 * \param t          Time of intersection
 * \param out        Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment3fIntersectTriangle(const float start[3],
                                  const float end[3],
                                  const float a[3],
                                  const float b[3],
                                  const float c[3],
                                  float *t,
                                  float out[3]);


/**
 * Computes barycentric coordinates from \a point and triangle made of \a a,
 * \a b, \a c points and stores result into \a out.
 *
 * \param a      A 3D vector
 * \param b      B 3D vector
 * \param c      C 3D vector
 * \param point  Point 3D vector
 * \param out    Output 3D vector
 */
void BH_Triangle3fBarycentric(const float a[3],
                              const float b[3],
                              const float c[3],
                              const float point[3],
                              float out[3]);


/**
 * Computes line from \a a and \a b points and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_LineFromPoints(const float a[2],
                      const float b[2],
                      float out[3]);


/**
 * Computes distance from \a line to the \a point and returns result.
 *
 * \param line   Line 3D vector
 * \param point  Point 2D vector
 *
 * \return Returns distance from plane to point.
 */
float BH_LineDistance(const float line[3],
                      const float point[2]);


/**
 * Computes closest point on the \a line to the \a point and stores result into
 * \a out.
 *
 * \param line   Line 3D vector
 * \param point  Point 2D vector
 * \param out    Output 2D vector
 */
void BH_LineClosestPoint(const float line[3],
                         const float point[2],
                         float out[2]);


/**
 * Computes time of intersection \a t between ray (given \a start and
 * \a direction) and \a line and stores intersection point into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param start      Start 2D vector
 * \param direction  Direction 2D vector
 * \param line       Line 3D vector
 * \param t          Time of intersection
 * \param out        Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray2fIntersectLine(const float start[2],
                          const float direction[2],
                          const float line[3],
                          float *t,
                          float out[2]);


/**
 * Computes time of intersection \a time1 and \a time2 between one line (given
 * \a aStart and \a aDirection) and other line (given \a bStart and
 * \a bDirection).
 *
 * \param aStart      A Start 2D vector
 * \param aDirection  A Direction 2D vector
 * \param bStart      B Start 2D vector
 * \param bDirection  B Direction 2D vector
 * \param time1       Time of intersection of first line
 * \param time2       Time of intersection of second line
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray2fIntersectTime(const float aStart[2],
                          const float aDirection[2],
                          const float bStart[2],
                          const float bDirection[2],
                          float *time1,
                          float *time2);


/**
 * Computes time of intersection \a t between one ray (given \a aStart and
 * \a aDirection) and other ray (given \a bStart and \a bDirection) and stores
 * intersection point into \a out.
 *
 * The returned intersection time \a t is for the first ray.
 *
 * \param aStart      A Start 2D vector
 * \param aDirection  A Direction 2D vector
 * \param bStart      B Start 2D vector
 * \param bDirection  B Direction 2D vector
 * \param t           Time of intersection
 * \param out         Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray2fIntersectRay(const float aStart[2],
                         const float aDirection[2],
                         const float bStart[2],
                         const float bDirection[2],
                         float *t,
                         float out[2]);


/**
 * Computes time of intersection \a t between one ray (given \a aStart and
 * \a aDirection) and segment (given \a bStart and \a bEnd) and stores result
 * into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param aStart      A Start 2D vector
 * \param aDirection  A Direction 2D vector
 * \param bStart      B Start 2D vector
 * \param bEnd        B End 2D vector
 * \param t           Time of intersection
 * \param out         Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray2fIntersectSegment(const float aStart[2],
                             const float aDirection[2],
                             const float bStart[2],
                             const float bEnd[2],
                             float *t,
                             float out[2]);


/**
 * Computes time of intersection \a t between segment (given \a start and
 * \a end) and \a line and stores intersection point into \a out.
 *
 * The returned intersection time \a t is for the segment.
 *
 * \param start      Start 2D vector
 * \param end        End 2D vector
 * \param line       Line 3D vector
 * \param t          Time of intersection
 * \param out        Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment2fIntersectLine(const float start[2],
                              const float end[2],
                              const float line[3],
                              float *t,
                              float out[2]);


/**
 * Computes time of intersection \a t between one segment (given \a aStart and
 * \a aEnd) and other sergment (given \a bStart and \a bEnd) and stores
 * intersection point into \a out.
 *
 * The returned intersection time \a t is for the first segment.
 *
 * \param aStart     A Start 2D vector
 * \param aEnd       A End 2D vector
 * \param bStart     B Start 2D vector
 * \param bEnd       B End 2D vector
 * \param t          Time of intersection
 * \param out        Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment2fIntersectSegment(const float aStart[2],
                                 const float aEnd[2],
                                 const float bStart[2],
                                 const float bEnd[2],
                                 float *t,
                                 float out[2]);


/**
 * Computes union of two 3D boxes (given by \a aMin, \a aMax, \a bMin, \a bMax)
 * and stores the result into \a outMin, \a outMax.
 *
 * \param aMin    A minimal 3D vector
 * \param aMax    A maximal 3D vector
 * \param bMin    B minimal 3D vector
 * \param bMax    B maximal 3D vector
 * \param outMin  Output minimal 3D vector
 * \param outMax  Output maximal 3D vector
 */
void BH_Box3fUnion(const float aMin[3],
                   const float aMax[3],
                   const float bMin[3],
                   const float bMax[3],
                   float outMin[3],
                   float outMax[3]);


/**
 * Computes intersection of two 3D boxes (given by \a aMin, \a aMax, \a bMin,
 * \a bMax), stores the result into \a outMin, \a outMax and returns
 * intersection test result.
 *
 * \param aMin    A minimal 3D vector
 * \param aMax    A maximal 3D vector
 * \param bMin    B minimal 3D vector
 * \param bMax    B maximal 3D vector
 * \param outMin  Output minimal 3D vector
 * \param outMax  Output maximal 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box3fIntersect(const float aMin[3],
                      const float aMax[3],
                      const float bMin[3],
                      const float bMax[3],
                      float outMin[3],
                      float outMax[3]);


/**
 * Checks if \a point is inside the box (given by \a aMin, \a aMax) and returns
 * the result of the check.
 *
 * \param aMin   A minimal 3D vector
 * \param aMax   A maximal 3D vector
 * \param point  Point 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box3fContains(const float aMin[3],
                     const float aMax[3],
                     const float point[3]);


/**
 * Computes bounding box for the \a points of \a size elements and stores the
 * result into \a outMin, \a outMax.
 *
 * \param points  Array of 3D points
 * \param size    Array size
 * \param outMin  Output minimal 3D vector
 * \param outMax  Output maximal 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box3fEnclose(const float *points,
                    size_t size,
                    float outMin[3],
                    float outMax[3]);


/**
 * Computes union of two 2D boxes (given by \a aMin, \a aMax, \a bMin, \a bMax)
 * and stores the result into \a outMin, \a outMax.
 *
 * \param aMin    A minimal 2D vector
 * \param aMax    A maximal 2D vector
 * \param bMin    B minimal 2D vector
 * \param bMax    B maximal 2D vector
 * \param outMin  Output minimal 2D vector
 * \param outMax  Output maximal 2D vector
 */
void BH_Box2fUnion(const float aMin[2],
                   const float aMax[2],
                   const float bMin[2],
                   const float bMax[2],
                   float outMin[2],
                   float outMax[2]);


/**
 * Computes intersection of two 2D boxes (given by \a aMin, \a aMax, \a bMin,
 * \a bMax), stores the result into \a outMin, \a outMax and returns
 * intersection test result.
 *
 * \param aMin    A minimal 2D vector
 * \param aMax    A maximal 2D vector
 * \param bMin    B minimal 2D vector
 * \param bMax    B maximal 2D vector
 * \param outMin  Output minimal 2D vector
 * \param outMax  Output maximal 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box2fIntersect(const float aMin[2],
                      const float aMax[2],
                      const float bMin[2],
                      const float bMax[2],
                      float outMin[2],
                      float outMax[2]);


/**
 * Checks if \a point is inside the box (given by \a aMin, \a aMax) and returns
 * the result of the check.
 *
 * \param aMin   A minimal 2D vector
 * \param aMax   A maximal 2D vector
 * \param point  Point 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box2fContains(const float aMin[2],
                     const float aMax[2],
                     const float point[2]);


/**
 * Computes bounding box for the \a points of \a size elements and stores the
 * result into \a outMin, \a outMax.
 *
 * \param points  Array of 2D points
 * \param size    Array size
 * \param outMin  Output minimal 2D vector
 * \param outMax  Output maximal 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Box2fEnclose(const float *points,
                    size_t size,
                    float outMin[2],
                    float outMax[2]);


/**
 * Computes time of intersection \a t between ray (given \a aStart and
 * \a aDirection) and 3D box (given \a bMin, \a bMax) and stores intersection
 * point into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param aStart      Start 3D vector
 * \param aDirection  Direction 3D vector
 * \param bMin        A 3D vector
 * \param bMax        B 3D vector
 * \param t           Time of intersection
 * \param out         Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray3fIntersectBox3f(const float aStart[3],
                           const float aDirection[3],
                           const float bMin[3],
                           const float bMax[3],
                           float *t,
                           float out[3]);


/**
 * Computes time of intersection \a t between segment (given \a aStart and
 * \a aEnd) and 3D box (given \a bMin, \a bMax) and stores intersection point
 * into \a out.
 *
 * The returned intersection time \a t is for the segment.
 *
 * \param aStart  Start 3D vector
 * \param aEnd    End 3D vector
 * \param bMin    A 3D vector
 * \param bMax    B 3D vector
 * \param t       Time of intersection
 * \param out     Output 3D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment3fIntersectBox3f(const float aStart[3],
                               const float aEnd[3],
                               const float bMin[3],
                               const float bMax[3],
                               float *t,
                               float out[3]);


/**
 * Computes time of intersection \a t between ray (given \a aStart and
 * \a aDirection) and 2D box (given \a bMin, \a bMax) and stores intersection
 * point into \a out.
 *
 * The returned intersection time \a t is for the ray.
 *
 * \param aStart      Start 2D vector
 * \param aDirection  Direction 2D vector
 * \param bMin        A 2D vector
 * \param bMax        B 2D vector
 * \param t           Time of intersection
 * \param out         Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Ray2fIntersectBox2f(const float aStart[2],
                           const float aDirection[2],
                           const float bMin[2],
                           const float bMax[2],
                           float *t,
                           float out[2]);


/**
 * Computes time of intersection \a t between segment (given \a aStart and
 * \a aEnd) and 2D box (given \a bMin, \a bMax) and stores intersection point
 * into \a out.
 *
 * The returned intersection time \a t is for the segment.
 *
 * \param aStart  Start 2D vector
 * \param aEnd    End 2D vector
 * \param bMin    A 2D vector
 * \param bMax    B 2D vector
 * \param t       Time of intersection
 * \param out     Output 2D vector
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Segment2fIntersectBox2f(const float aStart[2],
                               const float aEnd[2],
                               const float bMin[2],
                               const float bMax[2],
                               float *t,
                               float out[2]);


#endif /* BH_MATH_H */
