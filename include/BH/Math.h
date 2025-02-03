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
void BH_Vec4fAdd(const float *a,
                 const float *b,
                 float *out);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fSub(const float *a,
                 const float *b,
                 float *out);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMul(const float *a,
                 const float *b,
                 float *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B value
 * \param out  Output vector
 */
void BH_Vec4fScale(const float *a,
                   float b,
                   float *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param c    C 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fNegate(const float *in,
                    float *out);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 4D vector
 * \param b  B 4D vector
 */
float BH_Vec4fDot(const float *a,
                  const float *b);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 4D vector
 */
float BH_Vec4fLength(const float *in);


/**
 * Computes normal vector from the \a in and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fNormal(const float *in,
                    float *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMin(const float *a,
                 const float *b,
                 float *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4fMax(const float *a,
                 const float *b,
                 float *out);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param t    Amount
 * \param out  Output 4D vector
 */
void BH_Vec4fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out);


/**
 * Adds \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fAdd(const float *a,
                 const float *b,
                 float *out);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fSub(const float *a,
                 const float *b,
                 float *out);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMul(const float *a,
                 const float *b,
                 float *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B value
 * \param out  Output 3D vector
 */
void BH_Vec3fScale(const float *a,
                   float b,
                   float *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param c    C 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 *
 */
void BH_Vec3fNegate(const float *in,
                    float *out);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 3D vector
 * \param b  B 3D vector
 */
float BH_Vec3fDot(const float *a,
                  const float *b);


/**
 * Computes cross product of \a a and \a b vectors and stores
 * result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fCross(const float *a,
                   const float *b,
                   float *out);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 3D vector
 */
float BH_Vec3fLength(const float *in);


/**
 * Computes normal vector from the \a in and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fNormal(const float *in,
                    float *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMin(const float *a,
                 const float *b,
                 float *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3fMax(const float *a,
                 const float *b,
                 float *out);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param t    Amount
 * \param out  Output 3D vector
 */
void BH_Vec3fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out);


/**
 * Adds \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fAdd(const float *a,
                 const float *b,
                 float *out);


/**
 * Subtracts \a a and \a b floating point vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fSub(const float *a,
                 const float *b,
                 float *out);


/**
 * Multiplies \a a and \a b floating point vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMul(const float *a,
                 const float *b,
                 float *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B value
 * \param out  Output 2D vector
 */
void BH_Vec2fScale(const float *a,
                   float b,
                   float *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param c    C 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMulAdd(const float *a,
                    const float *b,
                    const float *c,
                    float *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 *
 */
void BH_Vec2fNegate(const float *in,
                    float *out);


/**
 * Computes dot product of \a a and \a b vectors and returns the result.
 *
 * \param a  A 2D vector
 * \param b  B 2D vector
 */
float BH_Vec2fDot(const float *a,
                  const float *b);


/**
 * Computes cross product of \a a and \a b vectors and returns the result.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 */
float BH_Vec2fCross(const float *a,
                    const float *b);


/**
 * Computes length of the \a in vector and returns the result.
 *
 * \param in  Input 2D vector
 */
float BH_Vec2fLength(const float *in);


/**
 * Computes normal vector from the \a in and stores result into
 * \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fNormal(const float *in,
                    float *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMin(const float *a,
                 const float *b,
                 float *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2fMax(const float *a,
                 const float *b,
                 float *out);


/**
 * Interpolates between \a a and \a b vector by \a t amount and stores result
 * into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param t    Amount
 * \param out  Output 2D vector
 */
void BH_Vec2fLerp(const float *a,
                  const float *b,
                  float t,
                  float *out);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iAdd(const int *a,
                 const int *b,
                 int *out);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iSub(const int *a,
                 const int *b,
                 int *out);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output vector
 */
void BH_Vec4iMul(const int *a,
                 const int *b,
                 int *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B value
 * \param out  Output 4D vector
 */
void BH_Vec4iScale(const int *a,
                   int b,
                   int *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param c    C 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iNegate(const int *in,
                    int *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMin(const int *a,
                 const int *b,
                 int *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 4D vector
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Vec4iMax(const int *a,
                 const int *b,
                 int *out);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iAdd(const int *a,
                 const int *b,
                 int *out);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iSub(const int *a,
                 const int *b,
                 int *out);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMul(const int *a,
                 const int *b,
                 int *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B value
 * \param out  Output 3D vector
 */
void BH_Vec3iScale(const int *a,
                   int b,
                   int *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param c    C 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 3D vector
 * \param out  Output 3D vector
 *
 */
void BH_Vec3iNegate(const int *in,
                    int *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMin(const int *a,
                 const int *b,
                 int *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 3D vector
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Vec3iMax(const int *a,
                 const int *b,
                 int *out);


/**
 * Adds \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iAdd(const int *a,
                 const int *b,
                 int *out);


/**
 * Subtracts \a a and \a b integer vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iSub(const int *a,
                 const int *b,
                 int *out);


/**
 * Multiplies \a a and \a b integers vectors and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMul(const int *a,
                 const int *b,
                 int *out);


/**
 * Scales \a a vector by the value \a b and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D value
 * \param out  Output 2D vector
 */
void BH_Vec2iScale(const int *a,
                   int b,
                   int *out);


/**
 * Multiples \a a and \a b vectors, adds to \a c and stores result into \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param c    C 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMulAdd(const int *a,
                    const int *b,
                    const int *c,
                    int *out);


/**
 * Negates \a in vector and stores result into \a out.
 *
 * \param in   Input 2D vector
 * \param out  Output 2D vector
 *
 */
void BH_Vec2iNegate(const int *in,
                    int *out);


/**
 * Computes minimum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMin(const int *a,
                 const int *b,
                 int *out);


/**
 * Computes maximum vector from the \a a and \a b vectors and stores result into
 * \a out.
 *
 * \param a    A 2D vector
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Vec2iMax(const int *a,
                 const int *b,
                 int *out);


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
void BH_Quat4fIdentity(float *out);


/**
 * Conjugates the \a in quaternion and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fConjugate(const float *in,
                        float *out);


/**
 * Computes the inverse of the \a in quaternion and stores result into \a out.
 *
 * \param in   Input quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fInverse(const float *in,
                      float *out);


/**
 * Multiplies the \a a and \a b quaternions and stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param out  Output quaternion
 */
void BH_Quat4fMul(const float *a,
                  const float *b,
                  float *out);


/**
 * Spherically interpolates between \a a and \a b quaternions by \a t amount and
 * stores result into \a out.
 *
 * \param a    A quaternion
 * \param b    B quaternion
 * \param t    Amount
 * \param out  Output quaternion
 */
void BH_Quat4fSlerp(const float *a,
                    const float *b,
                    float t,
                    float *out);


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
                        float *out);


/**
 * Computes quaternion that represents rotation by angle \a angle around
 * axis \a axis and stores result into \a out.
 *
 * \param axis   Axis 3D vector
 * \param angle  Angle
 * \param out    Output quaternion
 */
void BH_Quat4fFromAxis(const float *axis,
                       float angle,
                       float *out);


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
void BH_Quat4fToEuler(const float *in,
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
void BH_Quat4fToAxis(const float *in,
                     float *axis,
                     float *angle);


/**
 * Computes 4x4 rotation matrix from quaternion \a in and stores result into
 * \a out.
 *
 * \param in     Input quaternion
 * \param out    Output 4x4 matrix
 */
void BH_Quat4fToMat4f(const float *in,
                      float *out);


/**
 * Stores identity matrix into \a out.
 *
 * \param out  Output 4x4 matrix.
 */
void BH_Mat4fIdentity(float *out);


/**
 * Adds \a a and \a b floating point matricies and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fAdd(const float *a,
                 const float *b,
                 float *out);


/**
 * Subtracts \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fSub(const float *a,
                 const float *b,
                 float *out);


/**
 * Multiplies \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fMul(const float *a,
                 const float *b,
                 float *out);


/**
 * Scales \a a matrix by the value \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B value
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fScale(const float *a,
                   float b,
                   float *out);


/**
 * Transposes matrix \a in and stores result into \a out.
 *
 * \param in   Input 4x4 matrix
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fTranspose(const float *in,
                       float *out);


/**
 * Computes \a in matrix trace and returns the result.
 *
 * \param in  Input 4x4 matrix
 */
float BH_Mat4fTrace(const float *in);


/**
 * Computes \a in matrix determinant and returns the result.
 *
 * \param in  Input 4x4 matrix
 */
float BH_Mat4fDet(const float *in);


/**
 * Computes inverse of \a in matrix and stores result into \a out.
 *
 * \param in   Input 4x4 matrix
 * \param out  OUtput 4x4 matrix
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Mat4fInverse(const float *in,
                    float *out);


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
                       float *out);


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
                             float *out);


/**
 * Computes rotation matrix around x axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationX(float angle,
                           float *out);


/**
 * Computes rotation matrix around y axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationY(float angle,
                           float *out);


/**
 * Computes rotation matrix around z axis with angle \a angle and stores
 * result \a out.
 *
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromRotationZ(float angle,
                           float *out);


/**
 * Computes rotation matrix around axis \a axis with angle \a angle and stores
 * result \a out.
 *
 * \param axis   Axis 3D vector
 * \param angle  Angle
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromAxis(const float *axis,
                      float angle,
                      float *out);


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
                       float *out);


/**
 * Computes 4x4 rotation matrix from quaternion \a in and stores result into
 * \a out.
 *
 * \param in     Input quaternion
 * \param out    Output 4x4 matrix
 */
void BH_Mat4fFromQuat4f(const float *in,
                        float *out);


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
                       float *out);


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
                         float *out);


/**
 * Computes camera view matrix and stores result into \a out.
 *
 * \param pos  Position vector
 * \param at   Target vector
 * \param up   Up vector
 * \param out  Output 4x4 matrix
 */
void BH_Mat4fFromLookAt(const float *pos,
                        const float *at,
                        const float *up,
                        float *out);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 4D vector
 * \param out  Output 4D vector
 */
void BH_Mat4fApplyVec4f(const float *a,
                        const float *b,
                        float *out);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 4x4 matrix
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Mat4fApplyVec3f(const float *a,
                        const float *b,
                        float *out);


/**
 * Stores identity matrix into \a out.
 *
 * \param out  Output 3x3 matrix.
 */
void BH_Mat3fIdentity(float *out);


/**
 * Adds \a a and \a b floating point matricies and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fAdd(const float *a,
                 const float *b,
                 float *out);


/**
 * Subtracts \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fSub(const float *a,
                 const float *b,
                 float *out);


/**
 * Multiplies \a a and \a b floating point matricies and stores result into
 * \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fMul(const float *a,
                 const float *b,
                 float *out);


/**
 * Scales \a a matrix by the value \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B value
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fScale(const float *a,
                   float b,
                   float *out);


/**
 * Transposes matrix \a in and stores result into \a out.
 *
 * \param in   Input 3x3 matrix
 * \param out  Output 3x3 matrix
 */
void BH_Mat3fTranspose(const float *in,
                       float *out);


/**
 * Computes \a in matrix trace and returns the result.
 *
 * \param in  Input 3x3 matrix
 */
float BH_Mat3fTrace(const float *in);


/**
 * Computes \a in matrix determinant and returns the result.
 *
 * \param in  Input 3x3 matrix
 */
float BH_Mat3fDet(const float *in);


/**
 * Computes inverse of \a in matrix and stores result into \a out.
 *
 * \param in   Input 3x3 matrix
 * \param out  OUtput 3x3 matrix
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_Mat3fInverse(const float *in,
                    float *out);


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
                       float *out);


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
                             float *out);


/**
 * Computes rotation matrix around with angle \a angle and stores result \a out.
 *
 * \param angle  Angle
 * \param out    Output 3x3 matrix
 */
void BH_Mat3fFromRotation(float angle,
                          float *out);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 3D vector
 * \param out  Output 3D vector
 */
void BH_Mat3fApplyVec3f(float *a,
                        float *b,
                        float *out);


/**
 * Multiplies matrix \a a by vector \a b and stores result into \a out.
 *
 * \param a    A 3x3 matrix
 * \param b    B 2D vector
 * \param out  Output 2D vector
 */
void BH_Mat3fApplyVec2f(float *a,
                        float *b,
                        float *out);


#endif /* BH_MATH_H */
