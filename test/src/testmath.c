#include <bh/math.h>
#include <bh/unit.h>


#define ACCEPTABLE_DELTA 0.0001f


static int check_point4f(void)
{
    bh_point4f_t a, b, c, r;
    float value;

    a.x = 1.0f; a.y = 2.0f; a.z = 3.0f; a.w = 4.0f;
    b.x = 5.0f; b.y = 6.0f; b.z = 7.0f; b.w = 8.0f;
    c.x = 1.5f; c.y = 2.5f; c.z = 3.5f; c.w = 4.5f;

    bh_point4f_add(&a, &b, &r);
    BH_VERIFY_DELTA(r.x,  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y,  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 12.0000f, ACCEPTABLE_DELTA);

    bh_point4f_sub(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, -4.0000f, ACCEPTABLE_DELTA);

    bh_point4f_mul(&a, &b, &r);
    BH_VERIFY_DELTA(r.x,  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 12.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 21.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 32.0000f, ACCEPTABLE_DELTA);

    bh_point4f_scale(&a, 10.0f, &r);
    BH_VERIFY_DELTA(r.x, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 40.0000f, ACCEPTABLE_DELTA);

    bh_point4f_madd(&a, &b, &c, &r);
    BH_VERIFY_DELTA(r.x,  6.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 14.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 24.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 36.5000f, ACCEPTABLE_DELTA);

    bh_point4f_negate(&a, &r);
    BH_VERIFY_DELTA(r.x, -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, -4.0000f, ACCEPTABLE_DELTA);

    value = bh_point4f_dot(&a, &b);
    BH_VERIFY_DELTA(value, 70.0000f, ACCEPTABLE_DELTA);

    value = bh_point4f_dot3(&a, &b);
    BH_VERIFY_DELTA(value, 38.0000f, ACCEPTABLE_DELTA);

    bh_point4f_cross(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y,  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -4.0000f, ACCEPTABLE_DELTA);

    value = bh_point4f_length(&a);
    BH_VERIFY_DELTA(value, sqrt(30.0f), ACCEPTABLE_DELTA);

    bh_point4f_normal(&a, &r);
    BH_VERIFY_DELTA(r.x, 1.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 4.0f / sqrt(30.0f), ACCEPTABLE_DELTA);

    bh_point4f_min(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 4.0000f, ACCEPTABLE_DELTA);

    bh_point4f_max(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 8.0000f, ACCEPTABLE_DELTA);

    bh_point4f_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 4.0000f, ACCEPTABLE_DELTA);

    bh_point4f_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 6.0000f, ACCEPTABLE_DELTA);

    bh_point4f_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 8.0000f, ACCEPTABLE_DELTA);

    bh_point4f_slerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 4.0000f, ACCEPTABLE_DELTA);

    bh_point4f_slerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 0.50350f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 0.67135f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 0.83918f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 1.00702f, ACCEPTABLE_DELTA);

    bh_point4f_slerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w, 8.0000f, ACCEPTABLE_DELTA);

    return 0;
}


static int check_point3f(void)
{
    bh_point3f_t a, b, c, r;
    float value;

    a.x = 1.0f; a.y = 2.0f; a.z = 3.0f;
    b.x = 5.0f; b.y = 6.0f; b.z = 7.0f;
    c.x = 1.5f; c.y = 2.5f; c.z = 3.5f;

    bh_point3f_add(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 8.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 10.0f, ACCEPTABLE_DELTA);

    bh_point3f_sub(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -4.0f, ACCEPTABLE_DELTA);

    bh_point3f_mul(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 12.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 21.0f, ACCEPTABLE_DELTA);

    bh_point3f_scale(&a, 10.0f, &r);
    BH_VERIFY_DELTA(r.x, 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 20.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 30.0f, ACCEPTABLE_DELTA);

    bh_point3f_madd(&a, &b, &c, &r);
    BH_VERIFY_DELTA(r.x, 6.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 14.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 24.5f, ACCEPTABLE_DELTA);

    bh_point3f_negate(&a, &r);
    BH_VERIFY_DELTA(r.x, -1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -3.0f, ACCEPTABLE_DELTA);

    value = bh_point3f_dot(&a, &b);
    BH_VERIFY_DELTA(value, 38.0f, ACCEPTABLE_DELTA);

    bh_point3f_cross(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 8.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, -4.0f, ACCEPTABLE_DELTA);

    value = bh_point3f_length(&a);
    BH_VERIFY_DELTA(value, sqrt(14.0f), ACCEPTABLE_DELTA);

    bh_point3f_normal(&a, &r);
    BH_VERIFY_DELTA(r.x, 1.0f / sqrt(14.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f / sqrt(14.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0f / sqrt(14.0f), ACCEPTABLE_DELTA);

    bh_point3f_min(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0f, ACCEPTABLE_DELTA);

    bh_point3f_max(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0f, ACCEPTABLE_DELTA);

    bh_point3f_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0f, ACCEPTABLE_DELTA);

    bh_point3f_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 3.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 5.0f, ACCEPTABLE_DELTA);

    bh_point3f_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0f, ACCEPTABLE_DELTA);

    bh_point3f_slerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 3.0f, ACCEPTABLE_DELTA);

    bh_point3f_slerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 0.67937f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 0.90582f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 1.13228f, ACCEPTABLE_DELTA);

    bh_point3f_slerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z, 7.0f, ACCEPTABLE_DELTA);

    return 0;
}


static int check_point2f(void)
{
    bh_point2f_t a, b, c, r;
    float value;

    a.x = 1.0f; a.y = 2.0f;
    b.x = 5.0f; b.y = 6.0f;
    c.x = 1.5f; c.y = 2.5f;

    bh_point2f_add(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 8.0f, ACCEPTABLE_DELTA);

    bh_point2f_sub(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -4.0f, ACCEPTABLE_DELTA);

    bh_point2f_mul(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 12.0f, ACCEPTABLE_DELTA);

    bh_point2f_scale(&a, 10.0f, &r);
    BH_VERIFY_DELTA(r.x, 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 20.0f, ACCEPTABLE_DELTA);

    bh_point2f_madd(&a, &b, &c, &r);
    BH_VERIFY_DELTA(r.x, 6.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 14.5f, ACCEPTABLE_DELTA);

    bh_point2f_negate(&a, &r);
    BH_VERIFY_DELTA(r.x, -1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, -2.0f, ACCEPTABLE_DELTA);

    value = bh_point2f_dot(&a, &b);
    BH_VERIFY_DELTA(value, 17.0f, ACCEPTABLE_DELTA);

    value = bh_point2f_cross(&a, &b);
    BH_VERIFY_DELTA(value, -4.0f, ACCEPTABLE_DELTA);

    value = bh_point2f_length(&a);
    BH_VERIFY_DELTA(value, sqrt(5.0f), ACCEPTABLE_DELTA);

    bh_point2f_normal(&a, &r);
    BH_VERIFY_DELTA(r.x, 1.0f / sqrt(5.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f / sqrt(5.0f), ACCEPTABLE_DELTA);

    bh_point2f_min(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);

    bh_point2f_max(&a, &b, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);

    bh_point2f_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);

    bh_point2f_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 3.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 4.0f, ACCEPTABLE_DELTA);

    bh_point2f_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);

    bh_point2f_slerp(&a, &b, 0.0f, &r);
    BH_VERIFY_DELTA(r.x, 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 2.0f, ACCEPTABLE_DELTA);

    bh_point2f_slerp(&a, &b, 0.5f, &r);
    BH_VERIFY_DELTA(r.x, 1.00000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 1.33333f, ACCEPTABLE_DELTA);

    bh_point2f_slerp(&a, &b, 1.0f, &r);
    BH_VERIFY_DELTA(r.x, 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y, 6.0f, ACCEPTABLE_DELTA);

    return 0;
}


static int check_point4i(void)
{
    bh_point4i_t a, b, c, r;

    a.x = 1; a.y = 2; a.z = 3; a.w = 4;
    b.x = 5; b.y = 6; b.z = 7; b.w = 8;
    c.x = 4; c.y = 3; c.z = 2; c.w = 1;

    bh_point4i_add(&a, &b, &r);
    BH_VERIFY(r.x == 6);
    BH_VERIFY(r.y == 8);
    BH_VERIFY(r.z == 10);
    BH_VERIFY(r.w == 12);

    bh_point4i_sub(&a, &b, &r);
    BH_VERIFY(r.x == -4);
    BH_VERIFY(r.y == -4);
    BH_VERIFY(r.z == -4);
    BH_VERIFY(r.w == -4);

    bh_point4i_mul(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 12);
    BH_VERIFY(r.z == 21);
    BH_VERIFY(r.w == 32);

    bh_point4i_scale(&a, 10, &r);
    BH_VERIFY(r.x == 10);
    BH_VERIFY(r.y == 20);
    BH_VERIFY(r.z == 30);
    BH_VERIFY(r.w == 40);

    bh_point4i_madd(&a, &b, &c, &r);
    BH_VERIFY(r.x == 9);
    BH_VERIFY(r.y == 15);
    BH_VERIFY(r.z == 23);
    BH_VERIFY(r.w == 33);

    bh_point4i_negate(&a, &r);
    BH_VERIFY(r.x == -1);
    BH_VERIFY(r.y == -2);
    BH_VERIFY(r.z == -3);
    BH_VERIFY(r.w == -4);

    bh_point4i_min(&a, &b, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);
    BH_VERIFY(r.z == 3);
    BH_VERIFY(r.w == 4);

    bh_point4i_max(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);
    BH_VERIFY(r.z == 7);
    BH_VERIFY(r.w == 8);

    bh_point4i_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);
    BH_VERIFY(r.z == 3);
    BH_VERIFY(r.w == 4);

    bh_point4i_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY(r.x == 3);
    BH_VERIFY(r.y == 4);
    BH_VERIFY(r.z == 5);
    BH_VERIFY(r.w == 6);

    bh_point4i_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);
    BH_VERIFY(r.z == 7);
    BH_VERIFY(r.w == 8);

    return 0;
}


static int check_point3i(void)
{
    bh_point3i_t a, b, c, r;

    a.x = 1; a.y = 2; a.z = 3;
    b.x = 5; b.y = 6; b.z = 7;
    c.x = 4; c.y = 3; c.z = 2;

    bh_point3i_add(&a, &b, &r);
    BH_VERIFY(r.x == 6);
    BH_VERIFY(r.y == 8);
    BH_VERIFY(r.z == 10);

    bh_point3i_sub(&a, &b, &r);
    BH_VERIFY(r.x == -4);
    BH_VERIFY(r.y == -4);
    BH_VERIFY(r.z == -4);

    bh_point3i_mul(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 12);
    BH_VERIFY(r.z == 21);

    bh_point3i_scale(&a, 10, &r);
    BH_VERIFY(r.x == 10);
    BH_VERIFY(r.y == 20);
    BH_VERIFY(r.z == 30);

    bh_point3i_madd(&a, &b, &c, &r);
    BH_VERIFY(r.x == 9);
    BH_VERIFY(r.y == 15);
    BH_VERIFY(r.z == 23);

    bh_point3i_negate(&a, &r);
    BH_VERIFY(r.x == -1);
    BH_VERIFY(r.y == -2);
    BH_VERIFY(r.z == -3);

    bh_point3i_min(&a, &b, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);
    BH_VERIFY(r.z == 3);

    bh_point3i_max(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);
    BH_VERIFY(r.z == 7);

    bh_point3i_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);
    BH_VERIFY(r.z == 3);

    bh_point3i_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY(r.x == 3);
    BH_VERIFY(r.y == 4);
    BH_VERIFY(r.z == 5);

    bh_point3i_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);
    BH_VERIFY(r.z == 7);

    return 0;
}


static int check_point2i(void)
{
    bh_point2i_t a, b, c, r;

    a.x = 1; a.y = 2;
    b.x = 5; b.y = 6;
    c.x = 4; c.y = 3;

    bh_point2i_add(&a, &b, &r);
    BH_VERIFY(r.x == 6);
    BH_VERIFY(r.y == 8);

    bh_point2i_sub(&a, &b, &r);
    BH_VERIFY(r.x == -4);
    BH_VERIFY(r.y == -4);

    bh_point2i_mul(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 12);

    bh_point2i_scale(&a, 10, &r);
    BH_VERIFY(r.x == 10);
    BH_VERIFY(r.y == 20);

    bh_point2i_madd(&a, &b, &c, &r);
    BH_VERIFY(r.x == 9);
    BH_VERIFY(r.y == 15);

    bh_point2i_negate(&a, &r);
    BH_VERIFY(r.x == -1);
    BH_VERIFY(r.y == -2);

    bh_point2i_min(&a, &b, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);

    bh_point2i_max(&a, &b, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);

    bh_point2i_lerp(&a, &b, 0.0f, &r);
    BH_VERIFY(r.x == 1);
    BH_VERIFY(r.y == 2);

    bh_point2i_lerp(&a, &b, 0.5f, &r);
    BH_VERIFY(r.x == 3);
    BH_VERIFY(r.y == 4);

    bh_point2i_lerp(&a, &b, 1.0f, &r);
    BH_VERIFY(r.x == 5);
    BH_VERIFY(r.y == 6);

    return 0;
}


static int check_quat(void)
{
    return 0;
}


static int check_matrix4f(void)
{
    bh_matrix4f_t a, b, r;
    float value;

    a.x.x = 5.0f; a.y.x = 1.0f; a.z.x = 2.0f; a.w.x = 7.0f;
    a.x.y = 3.0f; a.y.y = 0.0f; a.z.y = 0.0f; a.w.y = 2.0f;
    a.x.z = 1.0f; a.y.z = 3.0f; a.z.z = 4.0f; a.w.z = 5.0f;
    a.x.w = 2.0f; a.y.w = 0.0f; a.z.w = 0.0f; a.w.w = 3.0f;

    b.x.x = 5.0f; b.y.x = 1.0f; b.z.x = 2.0f; b.w.x = 7.0f;
    b.x.y = 3.0f; b.y.y = 1.0f; b.z.y = 0.0f; b.w.y = 2.0f;
    b.x.z = 4.0f; b.y.z = 2.0f; b.z.z = 4.0f; b.w.z = 5.0f;
    b.x.w = 6.0f; b.y.w = 2.0f; b.z.w = 0.0f; b.w.w = 4.0f;

    bh_matrix4f_identity(&r);
    BH_VERIFY(r.x.x == 1.0f);
    BH_VERIFY(r.x.y == 0.0f);
    BH_VERIFY(r.x.z == 0.0f);
    BH_VERIFY(r.x.w == 0.0f);

    BH_VERIFY(r.y.x == 0.0f);
    BH_VERIFY(r.y.y == 1.0f);
    BH_VERIFY(r.y.z == 0.0f);
    BH_VERIFY(r.y.w == 0.0f);

    BH_VERIFY(r.z.x == 0.0f);
    BH_VERIFY(r.z.y == 0.0f);
    BH_VERIFY(r.z.z == 1.0f);
    BH_VERIFY(r.z.w == 0.0f);

    BH_VERIFY(r.w.x == 0.0f);
    BH_VERIFY(r.w.y == 0.0f);
    BH_VERIFY(r.w.z == 0.0f);
    BH_VERIFY(r.w.w == 1.0f);

    bh_matrix4f_add(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x, 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y,  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z,  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w,  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w, 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x, 14.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y,  4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w,  7.0000f, ACCEPTABLE_DELTA);

    bh_matrix4f_sub(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, -3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w, -4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z,  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w, -2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w, -1.0000f, ACCEPTABLE_DELTA);

    bh_matrix4f_mul(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x, 78.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 27.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 60.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w, 28.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 24.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 22.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w,  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w,  4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x, 75.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y, 29.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z, 53.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w, 26.0000f, ACCEPTABLE_DELTA);

    bh_matrix4f_scale(&a, 10, &r);
    BH_VERIFY_DELTA(r.x.x, 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w, 20.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w,  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 40.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w,  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x, 70.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y, 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z, 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w, 30.0000f, ACCEPTABLE_DELTA);

    bh_matrix4f_transpose(&a, &r);
    BH_VERIFY_DELTA(r.x.x, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w, 7.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w, 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w, 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w, 3.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix4f_trace(&a);
    BH_VERIFY_DELTA(value, 12.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix4f_determinant(&a);
    BH_VERIFY_DELTA(value, 10.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix4f_determinant(&b);
    BH_VERIFY_DELTA(value, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY(bh_matrix4f_inverse(&a, &r) == BH_OK);
    BH_VERIFY_DELTA(r.x.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z,  1.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.w,  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x,  0.6000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.w, -0.4000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, -0.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.w,  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.w.x, -0.4000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.y,  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.z, -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.w.w,  0.6000f, ACCEPTABLE_DELTA);

    BH_VERIFY(bh_matrix4f_inverse(&b, &r) != BH_OK);

    return 0;
}


static int check_matrix3f(void)
{
    bh_matrix3f_t a, b, r;
    float value;

    a.x.x = 5.0f; a.y.x = 1.0f; a.z.x = 2.0f;
    a.x.y = 3.0f; a.y.y = 0.0f; a.z.y = 0.0f;
    a.x.z = 1.0f; a.y.z = 3.0f; a.z.z = 4.0f;

    b.x.x = 2.0f; b.y.x = 1.0f; b.z.x = 2.0f;
    b.x.y = 3.0f; b.y.y = 1.0f; b.z.y = 0.0f;
    b.x.z = 4.0f; b.y.z = 2.0f; b.z.z = 4.0f;

    bh_matrix3f_identity(&r);
    BH_VERIFY(r.x.x == 1.0f);
    BH_VERIFY(r.x.y == 0.0f);
    BH_VERIFY(r.x.z == 0.0f);

    BH_VERIFY(r.y.x == 0.0f);
    BH_VERIFY(r.y.y == 1.0f);
    BH_VERIFY(r.y.z == 0.0f);

    BH_VERIFY(r.z.x == 0.0f);
    BH_VERIFY(r.z.y == 0.0f);
    BH_VERIFY(r.z.z == 1.0f);

    bh_matrix3f_add(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x, 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 8.0000f, ACCEPTABLE_DELTA);

    bh_matrix3f_sub(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x,  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, -3.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z,  1.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 0.0000f, ACCEPTABLE_DELTA);

    bh_matrix3f_mul(&a, &b, &r);
    BH_VERIFY_DELTA(r.x.x, 21.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y,  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 27.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 12.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 18.0000f, ACCEPTABLE_DELTA);

    bh_matrix3f_scale(&a, 10, &r);
    BH_VERIFY_DELTA(r.x.x, 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 10.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 30.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 40.0000f, ACCEPTABLE_DELTA);

    bh_matrix3f_transpose(&a, &r);
    BH_VERIFY_DELTA(r.x.x, 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z, 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y, 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x, 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y, 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, 4.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix3f_trace(&a);
    BH_VERIFY_DELTA(value, 9.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix3f_determinant(&a);
    BH_VERIFY_DELTA(value, 6.0000f, ACCEPTABLE_DELTA);

    value = bh_matrix3f_determinant(&b);
    BH_VERIFY_DELTA(value, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY(bh_matrix3f_inverse(&a, &r) == BH_OK);
    BH_VERIFY_DELTA(r.x.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.y, -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.x.z,  1.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.y.x,  0.3333f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.y,  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.y.z, -2.3333f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r.z.x,  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.y,  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r.z.z, -0.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY(bh_matrix3f_inverse(&b, &r) != BH_OK);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    bh_unit_add("point4f", check_point4f);
    bh_unit_add("point3f", check_point3f);
    bh_unit_add("point2f", check_point2f);
    bh_unit_add("point4i", check_point4i);
    bh_unit_add("point3i", check_point3i);
    bh_unit_add("point2i", check_point2i);
    bh_unit_add("quat", check_quat);
    bh_unit_add("matrix4f", check_matrix4f);
    bh_unit_add("matrix3f", check_matrix3f);

    return bh_unit_run();
}
