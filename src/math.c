#include <bh/math.h>
#include <math.h>


void bh_point4f_add(const bh_point4f_t *a,
                    const bh_point4f_t *b,
                    bh_point4f_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
    result->w = a->w + b->w;
}


void bh_point4f_sub(const bh_point4f_t *a,
                    const bh_point4f_t *b,
                    bh_point4f_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    result->w = a->w - b->w;
}


void bh_point4f_mul(const bh_point4f_t *a,
                    const bh_point4f_t *b,
                    bh_point4f_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
    result->w = a->w * b->w;
}


void bh_point4f_scale(const bh_point4f_t *a,
                      float b,
                      bh_point4f_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
    result->z = a->z * b;
    result->w = a->w * b;
}


void bh_point4f_madd(const bh_point4f_t *a,
                     const bh_point4f_t *b,
                     const bh_point4f_t *c,
                     bh_point4f_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
    result->z = a->z * b->z + c->z;
    result->w = a->w * b->w + c->w;
}


void bh_point4f_negate(const bh_point4f_t *in,
                       bh_point4f_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
    result->z = -in->z;
    result->w = -in->w;
}


float bh_point4f_dot(const bh_point4f_t *a,
                     const bh_point4f_t *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}


float bh_point4f_dot3(const bh_point4f_t *a,
                      const bh_point4f_t *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


void bh_point4f_cross(const bh_point4f_t *a,
                      const bh_point4f_t *b,
                      bh_point4f_t *result)
{
    bh_point4f_t tmp;

    tmp.x = a->y * b->z - a->z * b->y;
    tmp.y = a->z * b->x - a->x * b->z;
    tmp.z = a->x * b->y - a->y * b->x;
    tmp.w = 0.0f;

    *result = tmp;
}


float bh_point4f_length(const bh_point4f_t *in)
{
    return sqrtf(bh_point4f_dot(in, in));
}


void bh_point4f_normal(const bh_point4f_t *in,
                       bh_point4f_t *result)
{
    float length;

    length = 1.0f / bh_point4f_length(in);
    bh_point4f_scale(in, length, result);
}


void bh_point4f_min(const bh_point4f_t *a,
                    const bh_point4f_t *b,
                    bh_point4f_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
    if (a->z < b->z) result->z = a->z; else result->z = b->z;
    if (a->w < b->w) result->w = a->w; else result->w = b->w;
}


void bh_point4f_max(const bh_point4f_t *a,
                    const bh_point4f_t *b,
                    bh_point4f_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
    if (a->z > b->z) result->z = a->z; else result->z = b->z;
    if (a->w > b->w) result->w = a->w; else result->w = b->w;
}


void bh_point4f_lerp(const bh_point4f_t *a,
                     const bh_point4f_t *b,
                     float t,
                     bh_point4f_t *result)
{
    bh_point4f_t tmp;

    bh_point4f_sub(b, a, &tmp);
    bh_point4f_scale(&tmp, t, &tmp);
    bh_point4f_add(a, &tmp, result);
}


void bh_point4f_slerp(const bh_point4f_t *a,
                      const bh_point4f_t *b,
                      float t,
                      bh_point4f_t *result)
{
    float angle, denom;
    bh_point4f_t from, to;

    angle = acosf(bh_point4f_dot(a, b));

    /* Special case - reducing to linear interpolation */
    if (angle == 0.0f)
    {
        bh_point4f_lerp(a, b, t, result);
    }
    else
    {
        denom = 1.0f / sinf(angle);
        bh_point4f_scale(a, sinf((1 - t) * angle) * denom, &from);
        bh_point4f_scale(b, sinf(t * angle) * denom, &to);
        bh_point4f_add(&from, &to, result);
    }
}


void bh_point3f_add(const bh_point3f_t *a,
                    const bh_point3f_t *b,
                    bh_point3f_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}


void bh_point3f_sub(const bh_point3f_t *a,
                    const bh_point3f_t *b,
                    bh_point3f_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}


void bh_point3f_mul(const bh_point3f_t *a,
                    const bh_point3f_t *b,
                    bh_point3f_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
}


void bh_point3f_scale(const bh_point3f_t *a,
                      float b,
                      bh_point3f_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
    result->z = a->z * b;
}


void bh_point3f_madd(const bh_point3f_t *a,
                     const bh_point3f_t *b,
                     const bh_point3f_t *c,
                     bh_point3f_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
    result->z = a->z * b->z + c->z;
}


void bh_point3f_negate(const bh_point3f_t *in,
                       bh_point3f_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
    result->z = -in->z;
}


float bh_point3f_dot(const bh_point3f_t *a,
                     const bh_point3f_t *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


void bh_point3f_cross(const bh_point3f_t *a,
                      const bh_point3f_t *b,
                      bh_point3f_t *result)
{
    bh_point3f_t tmp;

    tmp.x = a->y * b->z - a->z * b->y;
    tmp.y = a->z * b->x - a->x * b->z;
    tmp.z = a->x * b->y - a->y * b->x;

    *result = tmp;
}


float bh_point3f_length(const bh_point3f_t *in)
{
    return sqrtf(bh_point3f_dot(in, in));
}


void bh_point3f_normal(const bh_point3f_t *in,
                       bh_point3f_t *result)
{
    float length;

    length = 1.0f / bh_point3f_length(in);
    bh_point3f_scale(in, length, result);
}


void bh_point3f_min(const bh_point3f_t *a,
                    const bh_point3f_t *b,
                    bh_point3f_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
    if (a->z < b->z) result->z = a->z; else result->z = b->z;
}


void bh_point3f_max(const bh_point3f_t *a,
                    const bh_point3f_t *b,
                    bh_point3f_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
    if (a->z > b->z) result->z = a->z; else result->z = b->z;
}


void bh_point3f_lerp(const bh_point3f_t *a,
                     const bh_point3f_t *b,
                     float t,
                     bh_point3f_t *result)
{
    bh_point3f_t tmp;

    bh_point3f_sub(b, a, &tmp);
    bh_point3f_scale(&tmp, t, &tmp);
    bh_point3f_add(a, &tmp, result);
}


void bh_point3f_slerp(const bh_point3f_t *a,
                      const bh_point3f_t *b,
                      float t,
                      bh_point3f_t *result)
{
    float angle, denom;
    bh_point3f_t from, to;

    angle = acosf(bh_point3f_dot(a, b));

    /* Special case - reducing to linear interpolation */
    if (angle == 0.0f)
    {
        bh_point3f_lerp(a, b, t, result);
    }
    else
    {
        denom = 1.0f / sinf(angle);
        bh_point3f_scale(a, sinf((1 - t) * angle) * denom, &from);
        bh_point3f_scale(b, sinf(t * angle) * denom, &to);
        bh_point3f_add(&from, &to, result);
    }
}


void bh_point2f_add(const bh_point2f_t *a,
                    const bh_point2f_t *b,
                    bh_point2f_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
}


void bh_point2f_sub(const bh_point2f_t *a,
                    const bh_point2f_t *b,
                    bh_point2f_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
}


void bh_point2f_mul(const bh_point2f_t *a,
                    const bh_point2f_t *b,
                    bh_point2f_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
}


void bh_point2f_scale(const bh_point2f_t *a,
                      float b,
                      bh_point2f_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
}


void bh_point2f_madd(const bh_point2f_t *a,
                     const bh_point2f_t *b,
                     const bh_point2f_t *c,
                     bh_point2f_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
}


void bh_point2f_negate(const bh_point2f_t *in,
                       bh_point2f_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
}


float bh_point2f_dot(const bh_point2f_t *a,
                     const bh_point2f_t *b)
{
    return a->x * b->x + a->y * b->y;
}


float bh_point2f_cross(const bh_point2f_t *a,
                       const bh_point2f_t *b)
{
    return a->x * b->y - a->y * b->x;
}


float bh_point2f_length(const bh_point2f_t *in)
{
    return sqrtf(bh_point2f_dot(in, in));
}


void bh_point2f_normal(const bh_point2f_t *in,
                       bh_point2f_t *result)
{
    float length;

    length = 1.0f / bh_point2f_length(in);
    bh_point2f_scale(in, length, result);
}


void bh_point2f_min(const bh_point2f_t *a,
                    const bh_point2f_t *b,
                    bh_point2f_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
}


void bh_point2f_max(const bh_point2f_t *a,
                    const bh_point2f_t *b,
                    bh_point2f_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
}


void bh_point2f_lerp(const bh_point2f_t *a,
                     const bh_point2f_t *b,
                     float t,
                     bh_point2f_t *result)
{
    bh_point2f_t tmp;

    bh_point2f_sub(b, a, &tmp);
    bh_point2f_scale(&tmp, t, &tmp);
    bh_point2f_add(a, &tmp, result);
}


void bh_point2f_slerp(const bh_point2f_t *a,
                      const bh_point2f_t *b,
                      float t,
                      bh_point2f_t *result)
{
    float angle, denom;
    bh_point2f_t from, to;

    angle = acosf(bh_point2f_dot(a, b));

    /* Special case - reducing to linear interpolation */
    if (angle == 0.0f)
    {
        bh_point2f_lerp(a, b, t, result);
    }
    else {
        denom = 1.0f / sinf(angle);
        bh_point2f_scale(a, sinf((1 - t) * angle) * denom, &from);
        bh_point2f_scale(b, sinf(t * angle) * denom, &to);
        bh_point2f_add(&from, &to, result);
    }
}


void bh_point4i_add(const bh_point4i_t *a,
                    const bh_point4i_t *b,
                    bh_point4i_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
    result->w = a->w + b->w;
}


void bh_point4i_sub(const bh_point4i_t *a,
                    const bh_point4i_t *b,
                    bh_point4i_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    result->w = a->w - b->w;
}


void bh_point4i_mul(const bh_point4i_t *a,
                    const bh_point4i_t *b,
                    bh_point4i_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
    result->w = a->w * b->w;
}


void bh_point4i_scale(const bh_point4i_t *a,
                      int b,
                      bh_point4i_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
    result->z = a->z * b;
    result->w = a->w * b;
}


void bh_point4i_madd(const bh_point4i_t *a,
                     const bh_point4i_t *b,
                     const bh_point4i_t *c,
                     bh_point4i_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
    result->z = a->z * b->z + c->z;
    result->w = a->w * b->w + c->w;
}


void bh_point4i_negate(const bh_point4i_t *in,
                       bh_point4i_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
    result->z = -in->z;
    result->w = -in->w;
}


void bh_point4i_min(const bh_point4i_t *a,
                    const bh_point4i_t *b,
                    bh_point4i_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
    if (a->z < b->z) result->z = a->z; else result->z = b->z;
    if (a->w < b->w) result->w = a->w; else result->w = b->w;
}


void bh_point4i_max(const bh_point4i_t *a,
                    const bh_point4i_t *b,
                    bh_point4i_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
    if (a->z > b->z) result->z = a->z; else result->z = b->z;
    if (a->w > b->w) result->w = a->w; else result->w = b->w;
}


void bh_point4i_lerp(const bh_point4i_t *a,
                     const bh_point4i_t *b,
                     float t,
                     bh_point4i_t *result)
{
    bh_point4i_t tmp;

    tmp.x = (b->x - a->x) * t;
    tmp.y = (b->y - a->y) * t;
    tmp.z = (b->z - a->z) * t;
    tmp.w = (b->w - a->w) * t;

    bh_point4i_add(a, &tmp, result);
}


void bh_point3i_add(const bh_point3i_t *a,
                    const bh_point3i_t *b,
                    bh_point3i_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}


void bh_point3i_sub(const bh_point3i_t *a,
                    const bh_point3i_t *b,
                    bh_point3i_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}


void bh_point3i_mul(const bh_point3i_t *a,
                    const bh_point3i_t *b,
                    bh_point3i_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
}


void bh_point3i_scale(const bh_point3i_t *a,
                      int b,
                      bh_point3i_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
    result->z = a->z * b;
}


void bh_point3i_madd(const bh_point3i_t *a,
                     const bh_point3i_t *b,
                     const bh_point3i_t *c,
                     bh_point3i_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
    result->z = a->z * b->z + c->z;
}


void bh_point3i_negate(const bh_point3i_t *in,
                       bh_point3i_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
    result->z = -in->z;
}


void bh_point3i_min(const bh_point3i_t *a,
                    const bh_point3i_t *b,
                    bh_point3i_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
    if (a->z < b->z) result->z = a->z; else result->z = b->z;
}


void bh_point3i_max(const bh_point3i_t *a,
                    const bh_point3i_t *b,
                    bh_point3i_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
    if (a->z > b->z) result->z = a->z; else result->z = b->z;
}


void bh_point3i_lerp(const bh_point3i_t *a,
                     const bh_point3i_t *b,
                     float t,
                     bh_point3i_t *result)
{
    bh_point3i_t tmp;

    tmp.x = (b->x - a->x) * t;
    tmp.y = (b->y - a->y) * t;
    tmp.z = (b->z - a->z) * t;

    bh_point3i_add(a, &tmp, result);
}


void bh_point2i_add(const bh_point2i_t *a,
                    const bh_point2i_t *b,
                    bh_point2i_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
}


void bh_point2i_sub(const bh_point2i_t *a,
                    const bh_point2i_t *b,
                    bh_point2i_t *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
}


void bh_point2i_mul(const bh_point2i_t *a,
                    const bh_point2i_t *b,
                    bh_point2i_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
}


void bh_point2i_scale(const bh_point2i_t *a,
                      int b,
                      bh_point2i_t *result)
{
    result->x = a->x * b;
    result->y = a->y * b;
}


void bh_point2i_madd(const bh_point2i_t *a,
                     const bh_point2i_t *b,
                     const bh_point2i_t *c,
                     bh_point2i_t *result)
{
    result->x = a->x * b->x + c->x;
    result->y = a->y * b->y + c->y;
}


void bh_point2i_negate(const bh_point2i_t *in,
                       bh_point2i_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
}


void bh_point2i_min(const bh_point2i_t *a,
                    const bh_point2i_t *b,
                    bh_point2i_t *result)
{
    if (a->x < b->x) result->x = a->x; else result->x = b->x;
    if (a->y < b->y) result->y = a->y; else result->y = b->y;
}


void bh_point2i_max(const bh_point2i_t *a,
                    const bh_point2i_t *b,
                    bh_point2i_t *result)
{
    if (a->x > b->x) result->x = a->x; else result->x = b->x;
    if (a->y > b->y) result->y = a->y; else result->y = b->y;
}


void bh_point2i_lerp(const bh_point2i_t *a,
                     const bh_point2i_t *b,
                     float t,
                     bh_point2i_t *result)
{
    bh_point2i_t tmp;

    tmp.x = (b->x - a->x) * t;
    tmp.y = (b->y - a->y) * t;

    bh_point2i_add(a, &tmp, result);
}


void bh_quat_identity(bh_quat_t *result)
{
    static const bh_quat_t ident = {0.0f, 0.0f, 0.0f, 1.0f};

    *result = ident;
}


void bh_quat_conjugate(const bh_quat_t *in,
                       bh_quat_t *result)
{
    result->x = -in->x;
    result->y = -in->y;
    result->z = -in->z;
    result->w = in->w;
}


void bh_quat_inverse(const bh_quat_t *in,
                     bh_quat_t *result)
{
    float length;

    length = bh_quat_dot(in, in);
    bh_quat_conjugate(in, result);
    bh_quat_scale(result, 1.0f / length, result);
}


void bh_quat_mul(const bh_quat_t *a,
                 const bh_quat_t *b,
                 bh_quat_t *result)
{
    bh_quat_t tmp1, tmp2, tmp3;
    float w;

    w = a->w * b->w - bh_point4f_dot3(a, b);

    bh_point4f_scale(a, b->w, &tmp1);
    bh_point4f_scale(b, a->w, &tmp2);
    bh_point4f_cross(a, b, &tmp3);
    bh_point4f_add(&tmp1, &tmp2, result);
    bh_point4f_add(&tmp3, result, result);
    result->w = w;
}


void bh_quat_set_euler(float roll,
                       float pitch,
                       float yaw,
                       bh_quat_t *result)
{
    float cr, cp, cy, sr, sp, sy;

    cr = cosf(roll / 2.0f);
    cp = cosf(pitch / 2.0f);
    cy = cosf(yaw / 2.0f);
    sr = sinf(roll / 2.0f);
    sp = sinf(pitch / 2.0f);
    sy = sinf(yaw / 2.0f);

    result->x = sr * cp * cy - cr * sp * sy;
    result->y = cr * sp * cy + sr * cp * sy;
    result->z = cr * cp * sy - sr * sp * cy;
    result->w = cr * cp * cy + sr * sp * sy;
}


void bh_quat_set_rotation(const bh_point3f_t *axis,
                          float angle,
                          bh_quat_t *result)
{
    float c, s;

    c = cosf(angle / 2.0f);
    s = sinf(angle / 2.0f);

    result->x = axis->x * s;
    result->y = axis->y * s;
    result->z = axis->z * s;
    result->w = c;
}


void bh_quat_euler(const bh_quat_t *in,
                   float *roll,
                   float *pitch,
                   float *yaw)
{
    float ww, xw, yw, zw, xx, xy, xz, yy, yz, zz, angle;

    xx = in->x * in->x;
    xy = in->x * in->y;
    xz = in->x * in->z;
    xw = in->x * in->w;
    yy = in->y * in->y;
    yz = in->y * in->z;
    yw = in->y * in->w;
    zz = in->z * in->z;
    zw = in->z * in->w;
    ww = in->w * in->w;

    angle = 2.0f * (yw - xz);
    if (angle > 1.0f)
        angle = 1.0f;
    if (angle < -1.0f)
        angle = -1.0f;

    *pitch = asinf(angle);

    if (*pitch == (M_PI / 2.0f))
    {
        *roll = 0.0f;
        *yaw = -2.0f * atan2f(in->x, in->w);
    }
    else if (*pitch == (M_PI / -2.0f))
    {
        *roll = 0.0f;
        *yaw = 2.0f * atan2f(in->x, in->w);
    }
    else
    {
        *roll = atan2f(2.0f * (xw + yz), ww - xx - yy + zz);
        *yaw = atan2f(2.0f * (zw + xy), ww + xx - yy - zz);
    }
}


void bh_quat_rotation(const bh_quat_t *in,
                      bh_point3f_t *axis,
                      float *angle)
{
    float tmp;

    *angle = 2.0f * acosf(in->w);
    tmp = sqrtf(1.0f - in->w * in->w);

    if (*angle == 0.0f)
    {
        axis->x = 1.0f;
        axis->y = 0.0f;
        axis->z = 0.0f;
    }
    else
    {
        axis->x = in->x / tmp;
        axis->y = in->y / tmp;
        axis->z = in->z / tmp;
    }
}


void bh_quat_matrix(const bh_quat_t *in,
                    bh_matrix4f_t *result)
{
    float xx, xy, xz, xw, yy, yz, yw, zz, zw;

    xx = in->x * in->x;
    xy = in->x * in->y;
    xz = in->x * in->z;
    xw = in->x * in->w;
    yy = in->y * in->y;
    yz = in->y * in->z;
    yw = in->y * in->w;
    zz = in->z * in->z;
    zw = in->z * in->w;

    bh_matrix4f_identity(result);
    result->x.x = 1.0f - 2.0f * (yy + zz);
    result->x.y = 2.0f * (xy + zw);
    result->x.z = 2.0f * (xz - yw);
    result->y.x = 2.0f * (xy - zw);
    result->y.y = 1.0f - 2.0f * (xx + zz);
    result->y.z = 2.0f * (yz + xw);
    result->z.x = 2.0f * (xz + yw);
    result->z.y = 2.0f * (yz - xw);
    result->z.z = 1.0f - 2.0f * (xx + yy);
}


void bh_matrix4f_identity(bh_matrix4f_t *result)
{
    static const bh_matrix4f_t ident = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    *result = ident;
}


void bh_matrix4f_add(const bh_matrix4f_t *a,
                     const bh_matrix4f_t *b,
                     bh_matrix4f_t *result)
{
    bh_point4f_add(&a->x, &b->x, &result->x);
    bh_point4f_add(&a->y, &b->y, &result->y);
    bh_point4f_add(&a->z, &b->z, &result->z);
    bh_point4f_add(&a->w, &b->w, &result->w);
}


void bh_matrix4f_sub(const bh_matrix4f_t *a,
                     const bh_matrix4f_t *b,
                     bh_matrix4f_t *result)
{
    bh_point4f_sub(&a->x, &b->x, &result->x);
    bh_point4f_sub(&a->y, &b->y, &result->y);
    bh_point4f_sub(&a->z, &b->z, &result->z);
    bh_point4f_sub(&a->w, &b->w, &result->w);
}


void bh_matrix4f_mul(const bh_matrix4f_t *a,
                     const bh_matrix4f_t *b,
                     bh_matrix4f_t *result)
{
    bh_matrix4f_t tmp;
    bh_point4f_t row;

    row.x = row.y = row.z = row.w = b->x.x; bh_point4f_mul(&a->x, &row, &tmp.x);
    row.x = row.y = row.z = row.w = b->x.y; bh_point4f_madd(&a->y, &row, &tmp.x, &tmp.x);
    row.x = row.y = row.z = row.w = b->x.z; bh_point4f_madd(&a->z, &row, &tmp.x, &tmp.x);
    row.x = row.y = row.z = row.w = b->x.w; bh_point4f_madd(&a->w, &row, &tmp.x, &tmp.x);

    row.x = row.y = row.z = row.w = b->y.x; bh_point4f_mul(&a->x, &row, &tmp.y);
    row.x = row.y = row.z = row.w = b->y.y; bh_point4f_madd(&a->y, &row, &tmp.y, &tmp.y);
    row.x = row.y = row.z = row.w = b->y.z; bh_point4f_madd(&a->z, &row, &tmp.y, &tmp.y);
    row.x = row.y = row.z = row.w = b->y.w; bh_point4f_madd(&a->w, &row, &tmp.y, &tmp.y);

    row.x = row.y = row.z = row.w = b->z.x; bh_point4f_mul(&a->x, &row, &tmp.z);
    row.x = row.y = row.z = row.w = b->z.y; bh_point4f_madd(&a->y, &row, &tmp.z, &tmp.z);
    row.x = row.y = row.z = row.w = b->z.z; bh_point4f_madd(&a->z, &row, &tmp.z, &tmp.z);
    row.x = row.y = row.z = row.w = b->z.w; bh_point4f_madd(&a->w, &row, &tmp.z, &tmp.z);

    row.x = row.y = row.z = row.w = b->w.x; bh_point4f_mul(&a->x, &row, &tmp.w);
    row.x = row.y = row.z = row.w = b->w.y; bh_point4f_madd(&a->y, &row, &tmp.w, &tmp.w);
    row.x = row.y = row.z = row.w = b->w.z; bh_point4f_madd(&a->z, &row, &tmp.w, &tmp.w);
    row.x = row.y = row.z = row.w = b->w.w; bh_point4f_madd(&a->w, &row, &tmp.w, &tmp.w);

    *result = tmp;
}


void bh_matrix4f_scale(const bh_matrix4f_t *a,
                       float b,
                       bh_matrix4f_t *result)
{
    bh_point4f_scale(&a->x, b, &result->x);
    bh_point4f_scale(&a->y, b, &result->y);
    bh_point4f_scale(&a->z, b, &result->z);
    bh_point4f_scale(&a->w, b, &result->w);
}


void bh_matrix4f_transpose(const bh_matrix4f_t *in,
                           bh_matrix4f_t *result)
{
    bh_matrix4f_t tmp;

    tmp.x.x = in->x.x;
    tmp.x.y = in->y.x;
    tmp.x.z = in->z.x;
    tmp.x.w = in->w.x;

    tmp.y.x = in->x.y;
    tmp.y.y = in->y.y;
    tmp.y.z = in->z.y;
    tmp.y.w = in->w.y;

    tmp.z.x = in->x.z;
    tmp.z.y = in->y.z;
    tmp.z.z = in->z.z;
    tmp.z.w = in->w.z;

    tmp.w.x = in->x.w;
    tmp.w.y = in->y.w;
    tmp.w.z = in->z.w;
    tmp.w.w = in->w.w;

    *result = tmp;
}


float bh_matrix4f_trace(const bh_matrix4f_t *in)
{
    return in->x.x + in->y.y + in->z.z + in->w.w;
}


float bh_matrix4f_determinant(const bh_matrix4f_t *in)
{
    float a, b, c, d, e, f, result;

    a = in->x.z * in->y.w - in->x.w * in->y.z;
    b = in->x.z * in->z.w - in->x.w * in->z.z;
    c = in->x.z * in->w.w - in->x.w * in->w.z;
    d = in->y.z * in->z.w - in->y.w * in->z.z;
    e = in->y.z * in->w.w - in->y.w * in->w.z;
    f = in->z.z * in->w.w - in->z.w * in->w.z;

    result = 0.0f;
    result += in->x.x * (in->y.y * f - in->z.y * e + in->w.y * d);
    result -= in->y.x * (in->x.y * f - in->z.y * c + in->w.y * b);
    result += in->z.x * (in->x.y * e - in->y.y * c + in->w.y * a);
    result -= in->w.x * (in->x.y * d - in->y.y * b + in->z.y * a);

    return result;
}


int bh_matrix4f_inverse(const bh_matrix4f_t *in,
                        bh_matrix4f_t *result)
{
    float a, b, c, d, e, f, det;
    bh_matrix4f_t tmp;

    a = in->x.z * in->y.w - in->x.w * in->y.z;
    b = in->x.z * in->z.w - in->x.w * in->z.z;
    c = in->x.z * in->w.w - in->x.w * in->w.z;
    d = in->y.z * in->z.w - in->y.w * in->z.z;
    e = in->y.z * in->w.w - in->y.w * in->w.z;
    f = in->z.z * in->w.w - in->z.w * in->w.z;

    tmp.x.x =  (in->y.y * f - in->z.y * e + in->w.y * d);
    tmp.x.y = -(in->x.y * f - in->z.y * c + in->w.y * b);
    tmp.x.z =  (in->x.y * e - in->y.y * c + in->w.y * a);
    tmp.x.w = -(in->x.y * d - in->y.y * b + in->z.y * a);

    det = 0.0f;
    det += in->x.x * tmp.x.x;
    det += in->y.x * tmp.x.y;
    det += in->z.x * tmp.x.z;
    det += in->w.x * tmp.x.w;

    if (det == 0.0f)
        return BH_ERROR;

    tmp.y.x = -(in->y.x * f - in->z.x * e + in->w.x * d);
    tmp.y.y =  (in->x.x * f - in->z.x * c + in->w.x * b);
    tmp.y.z = -(in->x.x * e - in->y.x * c + in->w.x * a);
    tmp.y.w =  (in->x.x * d - in->y.x * b + in->z.x * a);

    a = in->x.y * in->y.w - in->x.w * in->y.y;
    b = in->x.y * in->z.w - in->x.w * in->z.y;
    c = in->x.y * in->w.w - in->x.w * in->w.y;
    d = in->y.y * in->z.w - in->y.w * in->z.y;
    e = in->y.y * in->w.w - in->y.w * in->w.y;
    f = in->z.y * in->w.w - in->z.w * in->w.y;

    tmp.z.x =  (in->y.x * f - in->z.x * e + in->w.x * d);
    tmp.z.y = -(in->x.x * f - in->z.x * c + in->w.x * b);
    tmp.z.z =  (in->x.x * e - in->y.x * c + in->w.x * a);
    tmp.z.w = -(in->x.x * d - in->y.x * b + in->z.x * a);

    a = in->x.y * in->y.z - in->x.z * in->y.y;
    b = in->x.y * in->z.z - in->x.z * in->z.y;
    c = in->x.y * in->w.z - in->x.z * in->w.y;
    d = in->y.y * in->z.z - in->y.z * in->z.y;
    e = in->y.y * in->w.z - in->y.z * in->w.y;
    f = in->z.y * in->w.z - in->z.z * in->w.y;

    tmp.w.x = -(in->y.x * f - in->z.x * e + in->w.x * d);
    tmp.w.y =  (in->x.x * f - in->z.x * c + in->w.x * b);
    tmp.w.z = -(in->x.x * e - in->y.x * c + in->w.x * a);
    tmp.w.w =  (in->x.x * d - in->y.x * b + in->z.x * a);

    bh_matrix4f_scale(&tmp, 1.0f / det, result);
    return BH_OK;
}


void bh_matrix4f_scaling(float x,
                         float y,
                         float z,
                         bh_matrix4f_t *result)
{
    bh_matrix4f_identity(result);
    result->x.x = x;
    result->y.y = y;
    result->z.z = z;
}


void bh_matrix4f_translation(float x,
                             float y,
                             float z,
                             bh_matrix4f_t *result)
{
    bh_matrix4f_identity(result);
    result->w.x = x;
    result->w.y = y;
    result->w.z = z;
}


void bh_matrix4f_rotation_x(float angle,
                            bh_matrix4f_t *result)
{
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    bh_matrix4f_identity(result);
    result->y.y = c;
    result->z.z = c;
    result->z.y = -s;
    result->y.z = s;
}


void bh_matrix4f_rotation_y(float angle,
                            bh_matrix4f_t *result)
{
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    bh_matrix4f_identity(result);
    result->x.x = c;
    result->z.z = c;
    result->z.x = s;
    result->x.z = -s;
}


void bh_matrix4f_rotation_z(float angle,
                            bh_matrix4f_t *result)
{
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    bh_matrix4f_identity(result);
    result->x.x = c;
    result->y.y = c;
    result->y.x = -s;
    result->x.y = s;
}


void bh_matrix4f_rotation(const bh_point3f_t *axis,
                          float angle,
                          bh_matrix4f_t *result)
{
    float x, y, z, length;
    float c, s, moc, xx, xy, xz, yy, yz, zz;

    length = bh_point3f_length(axis);

    if (length == 0.0f)
    {
        bh_matrix4f_identity(result);
        return;
    }

    x = axis->x / length;
    y = axis->y / length;
    z = axis->z / length;

    /* Handle simple axis aligned rotations */
    if (x == 0.0f)
    {
        if (y == 0.0f)
        {
            if (z != 0.0f)
            {
                if (z < 0.0f)
                    bh_matrix4f_rotation_z(-angle, result);
                else
                    bh_matrix4f_rotation_z(angle, result);

                return;
            }
        }
        else if (z == 0.0f)
        {
            if (y < 0.0f)
                bh_matrix4f_rotation_y(-angle, result);
            else
                bh_matrix4f_rotation_y(angle, result);

            return;
        }
    }
    else if (y == 0.0f && z == 0.0f)
    {
        if (x < 0.0f)
            bh_matrix4f_rotation_x(-angle, result);
        else
            bh_matrix4f_rotation_x(angle, result);

        return;
    }

    /* Rotate around arbitrary axis */
    bh_matrix4f_identity(result);

    c = cosf(angle);
    s = sinf(angle);
    moc = 1.0f - c;

    xx = x * x;
    xy = x * y;
    xz = x * z;
    yy = y * y;
    yz = y * z;
    zz = z * z;

    result->x.x = c + xx * moc;
    result->y.x = xy * moc - z * s;
    result->z.x = xz * moc + y * s;

    result->x.y = xy * moc + z * s;
    result->y.y = c + yy * moc;
    result->z.y = yz * moc - x * s;

    result->x.z = xz * moc - y * s;
    result->y.z = yz * moc + x * s;
    result->z.z = c + zz * moc;
}


void bh_matrix4f_rotation_euler(float roll,
                                float pitch,
                                float yaw,
                                bh_matrix4f_t *result)
{
    float rs, rc, ys, yc, ps, pc;

    rs = sinf(roll);
    rc = cosf(roll);
    ps = sinf(pitch);
    pc = cosf(pitch);
    ys = sinf(yaw);
    yc = cosf(yaw);

    bh_matrix4f_identity(result);
    result->x.x = pc * yc;
    result->x.y = pc * ys;
    result->x.z = -ps;
    result->y.x = ps * rs * yc - rc * ys;
    result->y.y = ps * rs * ys + rc * yc;
    result->y.z = pc * rs;
    result->z.x = rs * ys + ps * rc * yc;
    result->z.y = ps * rc * ys - rs * yc;
    result->z.z = pc * rc;
}


void bh_matrix4f_rotation_quat(bh_quat_t *rotation,
                               bh_matrix4f_t *result)
{
    bh_quat_matrix(rotation, result);
}


void bh_matrix4f_ortho(float x_min,
                       float x_max,
                       float y_min,
                       float y_max,
                       float z_min,
                       float z_max,
                       bh_matrix4f_t *result)
{
    float dx, dy, dz;

    dx = x_max - x_min;
    dy = y_max - y_min;
    dz = z_max - z_min;

    bh_matrix4f_identity(result);

    result->x.x = 2.0f / dx;
    result->y.y = 2.0f / dy;
    result->z.z = -2.0f / dz;
    result->w.x = -(x_max + x_min) / dx;
    result->w.y = -(y_max + y_min) / dy;
    result->w.z = -(z_max + z_min) / dz;
}


void bh_matrix4f_perspective(float fov,
                             float aspect,
                             float z_min,
                             float z_max,
                             bh_matrix4f_t *result)
{
    float t, dz;

    dz = z_max - z_min;
    t = tanf(fov / 2.0f);

    bh_matrix4f_identity(result);

    result->x.x = 1.0f / (aspect * t);
    result->y.y = 1.0f / t;
    result->z.z = -(z_max + z_min) / dz;
    result->z.w = -1.0f;
    result->w.z = -(2.0f * z_max * z_min) / dz;
    result->w.w = 0.0f;
}


void bh_matrix4f_lookat(const bh_point3f_t *camera,
                        const bh_point3f_t *at,
                        const bh_point3f_t *up,
                        bh_matrix4f_t *result)
{
    bh_point3f_t cdir, cright, cup;

    bh_point3f_sub(camera, at, &cdir); bh_point3f_normal(&cdir, &cdir);
    bh_point3f_cross(up, &cdir, &cright); bh_point3f_normal(&cright, &cright);
    bh_point3f_cross(&cdir, &cright, &cup);

    result->x.x = cright.x;
    result->x.y = cup.x;
    result->x.z = cdir.x;
    result->x.w = 0.0f;

    result->y.x = cright.y;
    result->y.y = cup.y;
    result->y.z = cdir.y;
    result->y.w = 0.0f;

    result->z.x = cright.z;
    result->z.y = cup.z;
    result->z.z = cdir.z;
    result->z.w = 0.0f;

    result->w.x = -bh_point3f_dot(&cright, camera);
    result->w.y = -bh_point3f_dot(&cup, camera);
    result->w.z = -bh_point3f_dot(&cdir, camera);
    result->w.w = 1.0f;
}


void bh_matrix4f_transform_point3f(const bh_matrix4f_t *a,
                                   const bh_point3f_t *b,
                                   bh_point3f_t *result)
{
    bh_point4f_t tmp, row;

    row.x = row.y = row.z = row.w = b->x; bh_point4f_mul(&a->x, &row, &tmp);
    row.x = row.y = row.z = row.w = b->y; bh_point4f_madd(&a->y, &row, &tmp, &tmp);
    row.x = row.y = row.z = row.w = b->z; bh_point4f_madd(&a->z, &row, &tmp, &tmp);
    row.x = row.y = row.z = row.w = 1.0f; bh_point4f_madd(&a->w, &row, &tmp, &tmp);

    result->x = tmp.x;
    result->y = tmp.y;
    result->z = tmp.z;
}


void bh_matrix4f_transform_point4f(const bh_matrix4f_t *a,
                                   const bh_point4f_t *b,
                                   bh_point4f_t *result)
{
    bh_point4f_t tmp, row;

    row.x = row.y = row.z = row.w = b->x; bh_point4f_mul(&a->x, &row, &tmp);
    row.x = row.y = row.z = row.w = b->y; bh_point4f_madd(&a->y, &row, &tmp, &tmp);
    row.x = row.y = row.z = row.w = b->z; bh_point4f_madd(&a->z, &row, &tmp, &tmp);
    row.x = row.y = row.z = row.w = b->w; bh_point4f_madd(&a->w, &row, &tmp, &tmp);

    *result = tmp;
}


void bh_matrix3f_identity(bh_matrix3f_t *result)
{
    static const bh_matrix3f_t ident = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    *result = ident;
}


void bh_matrix3f_add(const bh_matrix3f_t *a,
                     const bh_matrix3f_t *b,
                     bh_matrix3f_t *result)
{
    bh_point3f_add(&a->x, &b->x, &result->x);
    bh_point3f_add(&a->y, &b->y, &result->y);
    bh_point3f_add(&a->z, &b->z, &result->z);
}


void bh_matrix3f_sub(const bh_matrix3f_t *a,
                     const bh_matrix3f_t *b,
                     bh_matrix3f_t *result)
{
    bh_point3f_sub(&a->x, &b->x, &result->x);
    bh_point3f_sub(&a->y, &b->y, &result->y);
    bh_point3f_sub(&a->z, &b->z, &result->z);
}


void bh_matrix3f_mul(const bh_matrix3f_t *a,
                     const bh_matrix3f_t *b,
                     bh_matrix3f_t *result)
{
    bh_matrix3f_t tmp;
    bh_point3f_t row;

    row.x = row.y = row.z = b->x.x; bh_point3f_mul(&a->x, &row, &tmp.x);
    row.x = row.y = row.z = b->x.y; bh_point3f_madd(&a->y, &row, &tmp.x, &tmp.x);
    row.x = row.y = row.z = b->x.z; bh_point3f_madd(&a->z, &row, &tmp.x, &tmp.x);

    row.x = row.y = row.z = b->y.x; bh_point3f_mul(&a->x, &row, &tmp.y);
    row.x = row.y = row.z = b->y.y; bh_point3f_madd(&a->y, &row, &tmp.y, &tmp.y);
    row.x = row.y = row.z = b->y.z; bh_point3f_madd(&a->z, &row, &tmp.y, &tmp.y);

    row.x = row.y = row.z = b->z.x; bh_point3f_mul(&a->x, &row, &tmp.z);
    row.x = row.y = row.z = b->z.y; bh_point3f_madd(&a->y, &row, &tmp.z, &tmp.z);
    row.x = row.y = row.z = b->z.z; bh_point3f_madd(&a->z, &row, &tmp.z, &tmp.z);

    *result = tmp;
}


void bh_matrix3f_scale(const bh_matrix3f_t *a,
                       float b,
                       bh_matrix3f_t *result)
{
    bh_point3f_scale(&a->x, b, &result->x);
    bh_point3f_scale(&a->y, b, &result->y);
    bh_point3f_scale(&a->z, b, &result->z);
}


void bh_matrix3f_transpose(const bh_matrix3f_t *in,
                           bh_matrix3f_t *result)
{
    bh_matrix3f_t tmp;

    tmp.x.x = in->x.x;
    tmp.x.y = in->y.x;
    tmp.x.z = in->z.x;

    tmp.y.x = in->x.y;
    tmp.y.y = in->y.y;
    tmp.y.z = in->z.y;

    tmp.z.x = in->x.z;
    tmp.z.y = in->y.z;
    tmp.z.z = in->z.z;

    *result = tmp;
}


float bh_matrix3f_trace(const bh_matrix3f_t *in)
{
    return in->x.x + in->y.y + in->z.z;
}


float bh_matrix3f_determinant(const bh_matrix3f_t *in)
{
    float a, b, c, result;

    a = in->y.y * in->z.z - in->z.y * in->y.z;
    b = in->x.y * in->z.z - in->z.y * in->x.z;
    c = in->x.y * in->y.z - in->y.y * in->x.z;

    result = 0.0f;
    result += in->x.x * a;
    result -= in->y.x * b;
    result += in->z.x * c;

    return result;
}


int bh_matrix3f_inverse(const bh_matrix3f_t *in,
                        bh_matrix3f_t *result)
{
    float a, b, c, det;
    bh_matrix3f_t tmp;

    a = in->y.y * in->z.z - in->z.y * in->y.z;
    b = in->x.y * in->z.z - in->z.y * in->x.z;
    c = in->x.y * in->y.z - in->y.y * in->x.z;

    tmp.x.x = a;
    tmp.x.y = -b;
    tmp.x.z = c;

    det = 0.0f;
    det += in->x.x * tmp.x.x;
    det += in->y.x * tmp.x.y;
    det += in->z.x * tmp.x.z;

    if (det == 0.0f)
        return BH_ERROR;

    a = in->y.x * in->z.z - in->z.x * in->y.z;
    b = in->x.x * in->z.z - in->z.x * in->x.z;
    c = in->x.x * in->y.z - in->y.x * in->x.z;

    tmp.y.x = -a;
    tmp.y.y = b;
    tmp.y.z = -c;

    a = in->y.x * in->z.y - in->z.x * in->y.y;
    b = in->x.x * in->z.y - in->z.x * in->x.y;
    c = in->x.x * in->y.y - in->y.x * in->x.y;

    tmp.z.x = a;
    tmp.z.y = -b;
    tmp.z.z = c;

    bh_matrix3f_scale(&tmp, 1.0f / det, result);
    return BH_OK;
}


void bh_matrix3f_scaling(float x,
                         float y,
                         bh_matrix3f_t *result)
{
    bh_matrix3f_identity(result);

    result->x.x = x;
    result->y.y = y;
}


void bh_matrix3f_translation(float x,
                             float y,
                             bh_matrix3f_t *result)
{
    bh_matrix3f_identity(result);

    result->z.x = x;
    result->z.y = y;
}


void bh_matrix3f_rotation(float angle,
                          bh_matrix3f_t *result)
{
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    bh_matrix3f_identity(result);
    result->x.x = c;
    result->y.y = c;
    result->y.x = -s;
    result->x.y = s;
}


void bh_matrix3f_transform_point2f(const bh_matrix3f_t *a,
                                   const bh_point2f_t *b,
                                   bh_point2f_t *result)
{
    bh_point3f_t tmp, row;

    row.x = row.y = row.z = b->x; bh_point3f_mul(&a->x, &row, &tmp);
    row.x = row.y = row.z = b->y; bh_point3f_madd(&a->y, &row, &tmp, &tmp);
    row.x = row.y = row.z = 1.0f; bh_point3f_madd(&a->z, &row, &tmp, &tmp);

    result->x = tmp.x;
    result->y = tmp.y;
}


void bh_matrix3f_transform_point3f(const bh_matrix3f_t *a,
                                   const bh_point3f_t *b,
                                   bh_point3f_t *result)
{
    bh_point3f_t tmp, row;

    row.x = row.y = row.z = b->x; bh_point3f_mul(&a->x, &row, &tmp);
    row.x = row.y = row.z = b->y; bh_point3f_madd(&a->y, &row, &tmp, &tmp);
    row.x = row.y = row.z = b->z; bh_point3f_madd(&a->z, &row, &tmp, &tmp);

    result->x = tmp.x;
    result->y = tmp.y;
    result->z = tmp.z;
}
