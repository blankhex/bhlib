#ifndef BH_MATH_H
#define BH_MATH_H


#include "common.h"


/**
 * 2D floating point vector.
 */
typedef struct bh_point2f_s
{
    /** X component */
    float x;

    /** Y Component */
    float y;
} bh_point2f_t;


/**
 * 3D floating point vector.
 */
typedef struct bh_point3f_s
{
    /** X component */
    float x;

    /** Y component */
    float y;

    /** Z component */
    float z;
} bh_point3f_t;


/**
 * 4D floating point vector.
 */
typedef struct bh_point4f_s
{
    /** X component */
    float x;

    /** Y component */
    float y;

    /** Z component */
    float z;

    /** W component */
    float w;
} bh_point4f_t;


/**
 * 2D integer vector.
 */
typedef struct bh_point2i_s
{
    /** X component */
    int x;

    /** Y component */
    int y;
} bh_point2i_t;


/**
 * 3D integer vector.
 */
typedef struct bh_point3i_s
{
    /** X component */
    int x;

    /** Y component */
    int y;

    /** Z component */
    int z;
} bh_point3i_t;


/**
 * 4D integer vector.
 */
typedef struct bh_point4i_s
{
    /** X component */
    int x;

    /** Y component */
    int y;

    /** Z component */
    int z;

    /** W component */
    int w;
} bh_point4i_t;


/**
 * 3x3 floating point matrix.
 * 
 * Each vector represent one column of the matrix.
 */
typedef struct bh_matrix3f_s
{
    /** First column */
    bh_point3f_t x;

    /** Second column */
    bh_point3f_t y;

    /** Third colum */
    bh_point3f_t z;
} bh_matrix3f_t;


/**
 * 4x4 floating point matrix.
 * 
 * Each vector represent one column of the matrix.
 */
typedef struct bh_matrix4f_s
{
    /** First column */
    bh_point4f_t x;

    /** Second column */
    bh_point4f_t y;

    /** Third column */
    bh_point4f_t z;

    /** Forth column */
    bh_point4f_t w;
} bh_matrix4f_t;


/**
 * 2D floating point line.
 */
typedef struct bh_line2f_s
{
    /** Normal vector */
    bh_point2f_t normal;

    /** Distance from the origin */
    float distance;
} bh_line2f_t;


/**
 * 3D floating point plane.
 */
typedef struct bh_plane3f_s
{
    /** Normal vector */
    bh_point3f_t normal;

    /** Distance from the origin */
    float distance;
} bh_plane3f_t;


/**
 * 2D floating point ray.
 */
typedef struct bh_ray2f_s
{
    /** Origin */
    bh_point2f_t origin;

    /** Normal or direction */
    bh_point2f_t normal;
} bh_ray2f_t;


/**
 * 3D floating point ray.
 */
typedef struct bh_ray3f_s
{
    /** Origin */
    bh_point3f_t origin;

    /** Normal or direction */
    bh_point3f_t normal;
} bh_ray3f_t;


/**
 * 2D floating point AABB
 */
typedef struct bh_aabb2f_s
{
    /** Origin */
    bh_point2f_t origin;

    /** Size */
    bh_point2f_t size;
} bh_aabb2f_t;


/**
 * 3D floating point AABB
 */
typedef struct bh_aabb3f_s
{
    /** Origin */
    bh_point3f_t origin;

    /** Size */
    bh_point3f_t size;
} bh_aabb3f_t;


/**
 * 2D integer AABB
 */
typedef struct bh_aabb2i_s
{
    /** Origin */
    bh_point2i_t origin;

    /** Size */
    bh_point2i_t size;
} bh_aabb2i_t;


/**
 * 3D integer AABB
 */
typedef struct bh_aabb3i_s
{
    /** Origin */
    bh_point3i_t origin;

    /** Size */
    bh_point3i_t size;
} bh_aabb3i_t;


/**
 * Floating point quaternion
 */
typedef bh_point4f_t bh_quat_t;


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_add(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_sub(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_mul(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_scale(const bh_point4f_t *a,
                               float b,
                               bh_point4f_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_madd(const bh_point4f_t *a,
                              const bh_point4f_t *b,
                              const bh_point4f_t *c,
                              bh_point4f_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_negate(const bh_point4f_t *in,
                                bh_point4f_t *result);


/**
 * Calculates the dot product of two vectors.
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns the dot product.
 */
float bh_point4f_dot(const bh_point4f_t *a,
                     const bh_point4f_t *b);


/**
 * Calculates the dot product of two vectors with w component.
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns the dot product.
 */
float bh_point4f_dot3(const bh_point4f_t *a,
                      const bh_point4f_t *b);


/**
 * Calculates the cross product of two vectors without w component. 
 * 
 * result = a x b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_cross(const bh_point4f_t *a,
                               const bh_point4f_t *b,
                               bh_point4f_t *result);


/**
 * Calculates the length of the vector.
 * 
 * \param in  Value
 * 
 * \return Returns the length.
 */
float bh_point4f_length(const bh_point4f_t *in);


/**
 * Normilizes the vector.
 * 
 * result = in / |in|
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_normal(const bh_point4f_t *in,
                                bh_point4f_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_min(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_max(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_lerp(const bh_point4f_t *a,
                              const bh_point4f_t *b,
                              float t,
                              bh_point4f_t *result);


/**
 * Calculates spherical linear interpolation between two vectors.
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_point4f_slerp(const bh_point4f_t *a,
                               const bh_point4f_t *b,
                               float t,
                               bh_point4f_t *result);


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_add(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_sub(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_mul(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_scale(const bh_point3f_t *a,
                               float b,
                               bh_point3f_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_madd(const bh_point3f_t *a,
                              const bh_point3f_t *b,
                              const bh_point3f_t *c,
                              bh_point3f_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_negate(const bh_point3f_t *in,
                                bh_point3f_t *result);


/**
 * Calculates the dot product of two vectors.
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns the dot product.
 */
float bh_point3f_dot(const bh_point3f_t *a,
                     const bh_point3f_t *b);


/**
 * Calculates the cross product of two vectors. 
 * 
 * result = a x b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_cross(const bh_point3f_t *a,
                               const bh_point3f_t *b,
                               bh_point3f_t *result);


/**
 * Calculates the length of the vector.
 * 
 * \param in  Value
 * 
 * \return Returns the length.
 */
float bh_point3f_length(const bh_point3f_t *in);


/**
 * Normilizes the vector.
 * 
 * result = in / |in|
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_normal(const bh_point3f_t *in,
                                bh_point3f_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_min(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_max(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_lerp(const bh_point3f_t *a,
                              const bh_point3f_t *b,
                              float t,
                              bh_point3f_t *result);


/**
 * Calculates spherical linear interpolation between two vectors.
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_point3f_slerp(const bh_point3f_t *a,
                               const bh_point3f_t *b,
                               float t,
                               bh_point3f_t *result);


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_add(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_sub(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_mul(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_scale(const bh_point2f_t *a,
                               float b,
                               bh_point2f_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_madd(const bh_point2f_t *a,
                              const bh_point2f_t *b,
                              const bh_point2f_t *c,
                              bh_point2f_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_negate(const bh_point2f_t *in,
                                bh_point2f_t *result);


/**
 * Calculates the dot product of two vectors.
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns the dot product.
 */
float bh_point2f_dot(const bh_point2f_t *a,
                     const bh_point2f_t *b);


/**
 * Calculates the cross product of two vectors and returns its z component. 
 * 
 * result = a x b
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns z component of the result vector.
 */
float bh_point2f_cross(const bh_point2f_t *a,
                       const bh_point2f_t *b);


/**
 * Calculates the length of the vector.
 * 
 * \param in  Value
 * 
 * \return Returns the length.
 */
float bh_point2f_length(const bh_point2f_t *in);


/**
 * Normilizes the vector.
 * 
 * result = in / |in|
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_normal(const bh_point2f_t *in,
                                bh_point2f_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_min(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_max(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_lerp(const bh_point2f_t *a,
                              const bh_point2f_t *b,
                              float t,
                              bh_point2f_t *result);


/**
 * Calculates spherical linear interpolation between two vectors.
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_point2f_slerp(const bh_point2f_t *a,
                               const bh_point2f_t *b,
                               float t,
                               bh_point2f_t *result);


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_add(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_sub(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_mul(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_scale(const bh_point4i_t *a,
                               int b,
                               bh_point4i_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_madd(const bh_point4i_t *a,
                              const bh_point4i_t *b,
                              const bh_point4i_t *c,
                              bh_point4i_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_negate(const bh_point4i_t *in,
                                bh_point4i_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_min(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_max(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4i_t *bh_point4i_lerp(const bh_point4i_t *a,
                              const bh_point4i_t *b,
                              float t,
                              bh_point4i_t *result);


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_add(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_sub(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_mul(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_scale(const bh_point3i_t *a,
                               int b,
                               bh_point3i_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_madd(const bh_point3i_t *a,
                              const bh_point3i_t *b,
                              const bh_point3i_t *c,
                              bh_point3i_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_negate(const bh_point3i_t *in,
                                bh_point3i_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_min(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_max(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3i_t *bh_point3i_lerp(const bh_point3i_t *a,
                              const bh_point3i_t *b,
                              float t,
                              bh_point3i_t *result);


/**
 * Adds components of two vectors.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_add(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


/**
 * Subtracts components of two vectors.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_sub(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


/**
 * Multiplies components of two vectors.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_mul(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


/**
 * Scales the vector.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_scale(const bh_point2i_t *a,
                               int b,
                               bh_point2i_t *result);


/**
 * Multiplies and adds three vectors.
 * 
 * result = a * b + c
 * 
 * \param a       Value
 * \param b       Value
 * \param c       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_madd(const bh_point2i_t *a,
                              const bh_point2i_t *b,
                              const bh_point2i_t *c,
                              bh_point2i_t *result);


/**
 * Negates the vector.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_negate(const bh_point2i_t *in,
                                bh_point2i_t *result);


/**
 * Calculates vector, containing minimum components of two vectors.
 * 
 * result = min(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_min(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


/**
 * Calculates vector, containing maximum components of two vectors.
 * 
 * result = max(a, b)
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_max(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


/**
 * Calculates linear interpolation between two vectors.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2i_t *bh_point2i_lerp(const bh_point2i_t *a,
                              const bh_point2i_t *b,
                              float t,
                              bh_point2i_t *result);


/**
 * Adds components of two quaternions.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_add     bh_point4f_add


/**
 * Subtracts components of two quaternions.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_sub     bh_point4f_sub


/**
 * Scales the quaternion.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_scale   bh_point4f_scale


/**
 * Negates the quaternion.
 * 
 * result = -in
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_negate  bh_point4f_negate


/**
 * Calculates the dot product of two quaternions.
 * 
 * \param a  Value
 * \param b  Value
 * 
 * \return Returns the dot product.
 */
#define bh_quat_dot     bh_point4f_dot


/**
 * Calculates the length of the quaternion.
 * 
 * \param in  Value
 * 
 * \return Returns the length.
 */
#define bh_quat_length  bh_point4f_length


/**
 * Normilizes the quaternion.
 * 
 * result = in / |in|
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_normal  bh_point4f_normal


/**
 * Calculates linear interpolation between two quaternions.
 * 
 * result = a + (b - a) * t
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_lerp    bh_point4f_lerp


/**
 * Calculates spherical linear interpolation between two quaternions.
 * 
 * \param a       Value
 * \param b       Value
 * \param t       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
#define bh_quat_slerp   bh_point4f_slerp


/**
 * Sets quaternions to identity.
 * 
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_identity(bh_quat_t *result);


/**
 * Conjugates the quaternion.
 * 
 * result = (-in.x, -in.y, -in.z, in.w)
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_conjugate(const bh_quat_t *in,
                             bh_quat_t *result);


/**
 * Calculates the inverse of the quaternion.
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_inverse(const bh_quat_t *in,
                           bh_quat_t *result);


/**
 * Multiplies two quaternions.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_mul(const bh_quat_t *a,
                       const bh_quat_t *b,
                       bh_quat_t *result);


/**
 * Sets quaternion from euler angles (roll, pitch, yaw).
 * 
 * Order of the rotation is ZYX (yaw, pitch, roll).
 * 
 * \param roll    Roll
 * \param pitch   Pitch
 * \param yaw     Yaw
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_set_euler(float roll,
                             float pitch,
                             float yaw,
                             bh_quat_t *result);


/**
 * Sets quaternion from axis of rotation and angle.
 * 
 * \param axis    Axis
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_quat_t *bh_quat_set_rotation(const bh_point3f_t *axis,
                                float angle,
                                bh_quat_t *result);


/**
 * Calculates euler angles (roll, pitch, yaw) from quaternion.
 * 
 * Order of the rotation is ZYX (yaw, pitch, roll).
 * 
 * \param in     Value
 * \param roll   Roll
 * \param pitch  Pitch
 * \param yaw    Yaw
 */
void bh_quat_euler(const bh_quat_t *in,
                   float *roll,
                   float *pitch,
                   float *yaw);


/**
 * Calculates axis of rotation and angle from quaternion.
 * 
 * \param in     Value
 * \param axis   Axis
 * \param angle  Angle
 */
void bh_quat_rotation(const bh_quat_t *in,
                      bh_point3f_t *axis,
                      float *angle);


/**
 * Calculates rotation matrix from quaternion.
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_quat_matrix(const bh_quat_t *in,
                              bh_matrix4f_t *result);


/**
 * Sets matrix to identity.
 * 
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_identity(bh_matrix4f_t *result);


/**
 * Adds two matricies.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_add(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


/**
 * Subtracts two matricies.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_sub(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


/**
 * Multiplies two matricies.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_mul(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


/**
 * Scales the matrix.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_scale(const bh_matrix4f_t *a,
                                 float b,
                                 bh_matrix4f_t *result);


/**
 * Transposes the matrix.
 * 
 * result = a^T
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_transpose(const bh_matrix4f_t *in,
                                     bh_matrix4f_t *result);


/**
 * Calculates the trace of the matrix.
 *
 * \param in  Value
 * 
 * \return Returns trace value.
 */
float bh_matrix4f_trace(const bh_matrix4f_t *in);


/**
 * Calculates the determinant of the matrix.
 * 
 * \param in  Value
 * 
 * \return Returns determinant value.
 */
float bh_matrix4f_determinant(const bh_matrix4f_t *in);


/**
 * Calculates the inverse of the matrix.
 * 
 * If matrix has no inverse - identity matrix will be returned.
 * 
 * result = in^-1
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return On success, returns inverse of the matrix.
 * \return On failure, returns identity matrix.
 */
bh_matrix4f_t *bh_matrix4f_inverse(const bh_matrix4f_t *in,
                                   bh_matrix4f_t *result);


/**
 * Calculates scaling matrix.
 * 
 * \param x       X scale
 * \param y       Y scale
 * \param z       Z scale
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_scaling(float x,
                                   float y,
                                   float z,
                                   bh_matrix4f_t *result);


/**
 * Calculates translation matrix.
 * 
 * \param x       X scale
 * \param y       Y scale
 * \param z       Z scale
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_translation(float x,
                                       float y,
                                       float z,
                                       bh_matrix4f_t *result);


/**
 * Calculates x-rotation matrix (or rotation around x axis).
 * 
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation_x(float angle,
                                      bh_matrix4f_t *result);


/**
 * Calculates y-rotation matrix (or rotation around y axis).
 * 
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation_y(float angle,
                                      bh_matrix4f_t *result);


/**
 * Calculates z-rotation matrix (or rotation around z axis).
 * 
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation_z(float angle,
                                      bh_matrix4f_t *result);


/**
 * Calculates rotation matrix around axis.
 * 
 * \param axis    Axis
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation(const bh_point3f_t *axis,
                                    float angle,
                                    bh_matrix4f_t *result);


/**
 * Calculates rotation matrix from euler angles (roll, pitch, yaw).
 * 
 * Order of the rotation is ZYX (yaw, pitch, roll).
 * 
 * \param roll    Roll
 * \param pitch   Pitch
 * \param yaw     Yaw
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation_euler(float roll,
                                          float pitch,
                                          float yaw,
                                          bh_matrix4f_t *result);


/**
 * Calculates rotation matrix from quaternion.
 * 
 * \param rotation  Quaternion
 * \param result    Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_rotation_quat(bh_quat_t *rotation,
                                         bh_matrix4f_t *result);


/**
 * Calculates orthographic projection matrix.
 * 
 * \param x_min   Min x
 * \param x_max   Max x
 * \param y_min   Min y
 * \param y_max   Max y
 * \param z_min   Min z
 * \param z_max   Max z
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_ortho(float x_min,
                                 float x_max,
                                 float y_min,
                                 float y_max,
                                 float z_min,
                                 float z_max,
                                 bh_matrix4f_t *result);


/**
 * Calculates perspective projection matrix.
 * 
 * \param fov     Field of view
 * \param aspect  Aspect ratio
 * \param z_min   Min z
 * \param z_max   Max z
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_perspective(float fov,
                                       float aspect,
                                       float z_min,
                                       float z_max,
                                       bh_matrix4f_t *result);


/**
 * Calculates camera view matrix.
 * 
 * \param camera  Position
 * \param at      Target
 * \param up      Up
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix4f_t *bh_matrix4f_lookat(const bh_point3f_t *camera,
                                  const bh_point3f_t *at,
                                  const bh_point3f_t *up,
                                  bh_matrix4f_t *result);


/**
 * Applies matrix to vector.
 * 
 * \param a       Matrix
 * \param b       Vector
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_matrix4f_transform_point3f(const bh_matrix4f_t *a,
                                            const bh_point3f_t *b,
                                            bh_point3f_t *result);


/**
 * Applies matrix to vector.
 * 
 * \param a       Matrix
 * \param b       Vector
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point4f_t *bh_matrix4f_transform_point4f(const bh_matrix4f_t *a,
                                            const bh_point4f_t *b,
                                            bh_point4f_t *result);


/**
 * Sets matrix to identity.
 * 
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_identity(bh_matrix3f_t *result);


/**
 * Adds two matricies.
 * 
 * result = a + b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_add(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


/**
 * Subtracts two matricies.
 * 
 * result = a - b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_sub(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


/**
 * Multiplies two matricies.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_mul(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


/**
 * Scales the matrix.
 * 
 * result = a * b
 * 
 * \param a       Value
 * \param b       Factor
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_scale(const bh_matrix3f_t *a,
                                 float b,
                                 bh_matrix3f_t *result);


/**
 * Transposes the matrix.
 * 
 * result = a^T
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_transpose(const bh_matrix3f_t *in,
                                     bh_matrix3f_t *result);


/**
 * Calculates the trace of the matrix.
 *
 * \param in  Value
 * 
 * \return Returns trace value.
 */
float bh_matrix3f_trace(const bh_matrix3f_t *in);


/**
 * Calculates the determinant of the matrix.
 * 
 * \param in  Value
 * 
 * \return Returns determinant value.
 */
float bh_matrix3f_determinant(const bh_matrix3f_t *in);


/**
 * Calculates the inverse of the matrix.
 * 
 * If matrix has no inverse - identity matrix will be returned.
 * 
 * result = in^-1
 * 
 * \param in      Value
 * \param result  Result
 * 
 * \return On success, returns inverse of the matrix.
 * \return On failure, returns identity matrix.
 */
bh_matrix3f_t *bh_matrix3f_inverse(const bh_matrix3f_t *in,
                                   bh_matrix3f_t *result);


/**
 * Calculates scaling matrix.
 * 
 * \param x       X scale
 * \param y       Y scale
 * \param z       Z scale
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_scaling(float x,
                                   float y,
                                   bh_matrix3f_t *result);


/**
 * Calculates translation matrix.
 * 
 * \param x       X scale
 * \param y       Y scale
 * \param z       Z scale
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_translation(float x,
                                       float y,
                                       bh_matrix3f_t *result);


/**
 * Calculates rotation matrix.
 * 
 * \param angle   Angle
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_matrix3f_t *bh_matrix3f_rotation(float angle,
                                    bh_matrix3f_t *result);


/**
 * Applies matrix to vector.
 * 
 * \param a       Matrix
 * \param b       Vector
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point2f_t *bh_matrix3f_transform_point2f(const bh_matrix3f_t *a,
                                            const bh_point2f_t *b,
                                            bh_point2f_t *result);


/**
 * Applies matrix to vector.
 * 
 * \param a       Matrix
 * \param b       Vector
 * \param result  Result
 * 
 * \return Returns pointer to the result.
 */
bh_point3f_t *bh_matrix3f_transform_point3f(const bh_matrix3f_t *a,
                                            const bh_point3f_t *b,
                                            bh_point3f_t *result);


#endif /* BH_MATH_H */
