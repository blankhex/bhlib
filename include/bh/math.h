#ifndef BH_MATH_H
#define BH_MATH_H


#include "common.h"


typedef struct bh_point2f_s
{
    float x;
    float y;
} bh_point2f_t;


typedef struct bh_point3f_s
{
    float x;
    float y;
    float z;
} bh_point3f_t;


typedef struct bh_point4f_s
{
    float x;
    float y;
    float z;
    float w;
} bh_point4f_t;


typedef struct bh_point2i_s
{
    int x;
    int y;
} bh_point2i_t;


typedef struct bh_point3i_s
{
    int x;
    int y;
    int z;
} bh_point3i_t;


typedef struct bh_point4i_s
{
    int x;
    int y;
    int z;
    int w;
} bh_point4i_t;


typedef struct bh_matrix3f_s
{
    bh_point3f_t x;
    bh_point3f_t y;
    bh_point3f_t z;
} bh_matrix3f_t;


typedef struct bh_matrix4f_s
{
    bh_point4f_t x;
    bh_point4f_t y;
    bh_point4f_t z;
    bh_point4f_t w;
} bh_matrix4f_t;


typedef struct bh_line2f_s
{
    bh_point2f_t normal;
    float distance;
} bh_line2f_t;


typedef struct bh_plane3f_s
{
    bh_point3f_t normal;
    float distance;
} bh_plane3f_t;


typedef struct bh_ray2f_s
{
    bh_point2f_t origin;
    bh_point2f_t normal;
} bh_ray2f_t;


typedef struct bh_ray3f_s
{
    bh_point3f_t origin;
    bh_point3f_t normal;
} bh_ray3f_t;


typedef struct bh_aabb2f_s
{
    bh_point2f_t origin;
    bh_point2f_t size;
} bh_aabb2f_t;


typedef struct bh_aabb3f_s
{
    bh_point3f_t origin;
    bh_point3f_t size;
} bh_aabb3f_t;


typedef struct bh_aabb2i_s
{
    bh_point2i_t origin;
    bh_point2i_t size;
} bh_aabb2i_t;


typedef struct bh_aabb3i_s
{
    bh_point3i_t origin;
    bh_point3i_t size;
} bh_aabb3i_t;


typedef bh_point4f_t bh_quat_t;


bh_point4f_t *bh_point4f_add(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


bh_point4f_t *bh_point4f_sub(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


bh_point4f_t *bh_point4f_mul(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


bh_point4f_t *bh_point4f_scale(const bh_point4f_t *a,
                               float b,
                               bh_point4f_t *result);


bh_point4f_t *bh_point4f_madd(const bh_point4f_t *a,
                              const bh_point4f_t *b,
                              const bh_point4f_t *c,
                              bh_point4f_t *result);


bh_point4f_t *bh_point4f_negate(const bh_point4f_t *in,
                                bh_point4f_t *result);


float bh_point4f_dot(const bh_point4f_t *a,
                     const bh_point4f_t *b);


float bh_point4f_dot3(const bh_point4f_t *a,
                      const bh_point4f_t *b);


bh_point4f_t *bh_point4f_cross(const bh_point4f_t *a,
                               const bh_point4f_t *b,
                               bh_point4f_t *result);


float bh_point4f_length(const bh_point4f_t *in);


bh_point4f_t *bh_point4f_normal(const bh_point4f_t *in,
                                bh_point4f_t *result);


bh_point4f_t *bh_point4f_min(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


bh_point4f_t *bh_point4f_max(const bh_point4f_t *a,
                             const bh_point4f_t *b,
                             bh_point4f_t *result);


bh_point4f_t *bh_point4f_lerp(const bh_point4f_t *a,
                              const bh_point4f_t *b,
                              float t,
                              bh_point4f_t *result);


bh_point4f_t *bh_point4f_slerp(const bh_point4f_t *a,
                               const bh_point4f_t *b,
                               float t,
                               bh_point4f_t *result);


bh_point3f_t *bh_point3f_add(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


bh_point3f_t *bh_point3f_sub(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


bh_point3f_t *bh_point3f_mul(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


bh_point3f_t *bh_point3f_scale(const bh_point3f_t *a,
                               float b,
                               bh_point3f_t *result);


bh_point3f_t *bh_point3f_madd(const bh_point3f_t *a,
                              const bh_point3f_t *b,
                              const bh_point3f_t *c,
                              bh_point3f_t *result);


bh_point3f_t *bh_point3f_negate(const bh_point3f_t *in,
                                bh_point3f_t *result);


float bh_point3f_dot(const bh_point3f_t *a,
                     const bh_point3f_t *b);


bh_point3f_t *bh_point3f_cross(const bh_point3f_t *a,
                               const bh_point3f_t *b,
                               bh_point3f_t *result);


float bh_point3f_length(const bh_point3f_t *in);


bh_point3f_t *bh_point3f_normal(const bh_point3f_t *in,
                                bh_point3f_t *result);


bh_point3f_t *bh_point3f_min(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


bh_point3f_t *bh_point3f_max(const bh_point3f_t *a,
                             const bh_point3f_t *b,
                             bh_point3f_t *result);


bh_point3f_t *bh_point3f_lerp(const bh_point3f_t *a,
                              const bh_point3f_t *b,
                              float t,
                              bh_point3f_t *result);


bh_point3f_t *bh_point3f_slerp(const bh_point3f_t *a,
                               const bh_point3f_t *b,
                               float t,
                               bh_point3f_t *result);


bh_point2f_t *bh_point2f_add(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


bh_point2f_t *bh_point2f_sub(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


bh_point2f_t *bh_point2f_mul(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


bh_point2f_t *bh_point2f_scale(const bh_point2f_t *a,
                               float b,
                               bh_point2f_t *result);


bh_point2f_t *bh_point2f_madd(const bh_point2f_t *a,
                              const bh_point2f_t *b,
                              const bh_point2f_t *c,
                              bh_point2f_t *result);


bh_point2f_t *bh_point2f_negate(const bh_point2f_t *in,
                                bh_point2f_t *result);


float bh_point2f_dot(const bh_point2f_t *a,
                     const bh_point2f_t *b);


float bh_point2f_cross(const bh_point2f_t *a,
                       const bh_point2f_t *b);


float bh_point2f_length(const bh_point2f_t *in);


bh_point2f_t *bh_point2f_normal(const bh_point2f_t *in,
                                bh_point2f_t *result);


bh_point2f_t *bh_point2f_min(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


bh_point2f_t *bh_point2f_max(const bh_point2f_t *a,
                             const bh_point2f_t *b,
                             bh_point2f_t *result);


bh_point2f_t *bh_point2f_lerp(const bh_point2f_t *a,
                              const bh_point2f_t *b,
                              float t,
                              bh_point2f_t *result);


bh_point2f_t *bh_point2f_slerp(const bh_point2f_t *a,
                               const bh_point2f_t *b,
                               float t,
                               bh_point2f_t *result);


bh_point4i_t *bh_point4i_add(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


bh_point4i_t *bh_point4i_sub(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


bh_point4i_t *bh_point4i_mul(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


bh_point4i_t *bh_point4i_scale(const bh_point4i_t *a,
                               int b,
                               bh_point4i_t *result);


bh_point4i_t *bh_point4i_madd(const bh_point4i_t *a,
                              const bh_point4i_t *b,
                              const bh_point4i_t *c,
                              bh_point4i_t *result);


bh_point4i_t *bh_point4i_negate(const bh_point4i_t *in,
                                bh_point4i_t *result);


bh_point4i_t *bh_point4i_min(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


bh_point4i_t *bh_point4i_max(const bh_point4i_t *a,
                             const bh_point4i_t *b,
                             bh_point4i_t *result);


bh_point4i_t *bh_point4i_lerp(const bh_point4i_t *a,
                              const bh_point4i_t *b,
                              float t,
                              bh_point4i_t *result);


bh_point3i_t *bh_point3i_add(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


bh_point3i_t *bh_point3i_sub(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


bh_point3i_t *bh_point3i_mul(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


bh_point3i_t *bh_point3i_scale(const bh_point3i_t *a,
                               int b,
                               bh_point3i_t *result);


bh_point3i_t *bh_point3i_madd(const bh_point3i_t *a,
                              const bh_point3i_t *b,
                              const bh_point3i_t *c,
                              bh_point3i_t *result);


bh_point3i_t *bh_point3i_negate(const bh_point3i_t *in,
                                bh_point3i_t *result);


bh_point3i_t *bh_point3i_min(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


bh_point3i_t *bh_point3i_max(const bh_point3i_t *a,
                             const bh_point3i_t *b,
                             bh_point3i_t *result);


bh_point3i_t *bh_point3i_lerp(const bh_point3i_t *a,
                              const bh_point3i_t *b,
                              float t,
                              bh_point3i_t *result);


bh_point2i_t *bh_point2i_add(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


bh_point2i_t *bh_point2i_sub(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


bh_point2i_t *bh_point2i_mul(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


bh_point2i_t *bh_point2i_scale(const bh_point2i_t *a,
                               int b,
                               bh_point2i_t *result);


bh_point2i_t *bh_point2i_madd(const bh_point2i_t *a,
                              const bh_point2i_t *b,
                              const bh_point2i_t *c,
                              bh_point2i_t *result);


bh_point2i_t *bh_point2i_negate(const bh_point2i_t *in,
                                bh_point2i_t *result);


bh_point2i_t *bh_point2i_min(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


bh_point2i_t *bh_point2i_max(const bh_point2i_t *a,
                             const bh_point2i_t *b,
                             bh_point2i_t *result);


bh_point2i_t *bh_point2i_lerp(const bh_point2i_t *a,
                              const bh_point2i_t *b,
                              float t,
                              bh_point2i_t *result);


#define bh_quat_add     bh_point4f_add


#define bh_quat_sub     bh_point4f_sub


#define bh_quat_scale   bh_point4f_scale


#define bh_quat_negate  bh_point4f_negate


#define bh_quat_length  bh_point4f_length


#define bh_quat_normal  bh_point4f_normal


#define bh_quat_dot     bh_point4f_dot


#define bh_quat_lerp    bh_point4f_lerp


#define bh_quat_slerp   bh_point4f_slerp


bh_quat_t *bh_quat_identity(bh_quat_t *result);


bh_quat_t *bh_quat_conjugate(const bh_quat_t *in,
                             bh_quat_t *result);


bh_quat_t *bh_quat_inverse(const bh_quat_t *in,
                           bh_quat_t *result);


bh_quat_t *bh_quat_mul(const bh_quat_t *a,
                       const bh_quat_t *b,
                       bh_quat_t *result);


bh_quat_t *bh_quat_set_euler(float roll,
                             float pitch,
                             float yaw,
                             bh_quat_t *result);


bh_quat_t *bh_quat_set_rotation(const bh_point3f_t *axis,
                                float angle,
                                bh_quat_t *result);


void bh_quat_euler(const bh_quat_t *in,
                   float *roll,
                   float *pitch,
                   float *yaw);


void bh_quat_rotation(const bh_quat_t *in,
                      bh_point3f_t *axis,
                      float *angle);


bh_matrix4f_t *bh_quat_matrix(const bh_quat_t *in,
                              bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_identity(bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_add(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_sub(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_mul(const bh_matrix4f_t *a,
                               const bh_matrix4f_t *b,
                               bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_scale(const bh_matrix4f_t *a,
                                 float b,
                                 bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_transpose(const bh_matrix4f_t *in,
                                     bh_matrix4f_t *result);


float bh_matrix4f_trace(const bh_matrix4f_t *in);


float bh_matrix4f_determinant(const bh_matrix4f_t *in);


bh_matrix4f_t *bh_matrix4f_inverse(const bh_matrix4f_t *in,
                                   bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_scaling(float x,
                                   float y,
                                   float z,
                                   bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_translation(float x,
                                       float y,
                                       float z,
                                       bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation_x(float angle,
                                      bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation_y(float angle,
                                      bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation_z(float angle,
                                      bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation(const bh_point3f_t *axis,
                                    float angle,
                                    bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation_euler(float roll,
                                          float pitch,
                                          float yaw,
                                          bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_rotation_quat(bh_quat_t *rotation,
                                         bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_ortho(float x_min,
                                 float x_max,
                                 float y_min,
                                 float y_max,
                                 float z_min,
                                 float z_max,
                                 bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_perspective(float fov,
                                       float aspect,
                                       float z_min,
                                       float z_max,
                                       bh_matrix4f_t *result);


bh_matrix4f_t *bh_matrix4f_lookat(const bh_point3f_t *camera,
                                  const bh_point3f_t *at,
                                  const bh_point3f_t *up,
                                  bh_matrix4f_t *result);


bh_point3f_t *bh_matrix4f_transform_point3f(const bh_matrix4f_t *a,
                                            const bh_point3f_t *b,
                                            bh_point3f_t *result);


bh_point4f_t *bh_matrix4f_transform_point4f(const bh_matrix4f_t *a,
                                            const bh_point4f_t *b,
                                            bh_point4f_t *result);


bh_matrix3f_t *bh_matrix3f_identity(bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_add(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_sub(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_mul(const bh_matrix3f_t *a,
                               const bh_matrix3f_t *b,
                               bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_scale(const bh_matrix3f_t *a,
                                 float b,
                                 bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_transpose(const bh_matrix3f_t *in,
                                     bh_matrix3f_t *result);


float bh_matrix3f_trace(const bh_matrix3f_t *in);


float bh_matrix3f_determinant(const bh_matrix3f_t *in);


bh_matrix3f_t *bh_matrix3f_inverse(const bh_matrix3f_t *in,
                                   bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_scaling(float x,
                                   float y,
                                   bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_translation(float x,
                                       float y,
                                       bh_matrix3f_t *result);


bh_matrix3f_t *bh_matrix3f_rotation(float angle,
                                    bh_matrix3f_t *result);


bh_point2f_t *bh_matrix3f_transform_point2f(const bh_matrix3f_t *a,
                                            const bh_point2f_t *b,
                                            bh_point2f_t *result);


bh_point3f_t *bh_matrix3f_transform_point3f(const bh_matrix3f_t *a,
                                            const bh_point3f_t *b,
                                            bh_point3f_t *result);


#endif /* BH_MATH_H */
