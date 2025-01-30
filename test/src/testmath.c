#include <bh/math.h>
#include <bh/unit.h>


#define ACCEPTABLE_DELTA 0.0001f


static int checkVec4f(void)
{
    float a[4], b[4], c[4], r[4];
    float value;

    a[0] = 1.0f; a[1] = 2.0f; a[2] = 3.0f; a[3] = 4.0f;
    b[0] = 5.0f; b[1] = 6.0f; b[2] = 7.0f; b[3] = 8.0f;
    c[0] = 1.5f; c[1] = 2.5f; c[2] = 3.5f; c[3] = 4.5f;

    BH_Vec4fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 12.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fSub(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], -4.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fMul(a, b, r);
    BH_VERIFY_DELTA(r[0],  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 12.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 21.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 32.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fScale(a, 10.0f, r);
    BH_VERIFY_DELTA(r[0], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 40.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fMulAdd(a, b, c, r);
    BH_VERIFY_DELTA(r[0],  6.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 14.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 24.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 36.5000f, ACCEPTABLE_DELTA);

    BH_Vec4fNegate(a, r);
    BH_VERIFY_DELTA(r[0], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], -4.0000f, ACCEPTABLE_DELTA);

    value = BH_Vec4fDot(a, b);
    BH_VERIFY_DELTA(value, 70.0000f, ACCEPTABLE_DELTA);

    value = BH_Vec4fLength(a);
    BH_VERIFY_DELTA(value, sqrt(30.0f), ACCEPTABLE_DELTA);

    BH_Vec4fNormal(a, r);
    BH_VERIFY_DELTA(r[0], 1.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0f / sqrt(30.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 4.0f / sqrt(30.0f), ACCEPTABLE_DELTA);

    BH_Vec4fMin(a, b, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 4.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fMax(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 8.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fLerp(a, b, 0.0f, r);
    BH_VERIFY_DELTA(r[0], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 4.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fLerp(a, b, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 6.0000f, ACCEPTABLE_DELTA);

    BH_Vec4fLerp(a, b, 1.0f, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 8.0000f, ACCEPTABLE_DELTA);

    return 0;
}


static int checkVec3f(void)
{
    float a[3], b[3], c[3], r[3];
    float value;

    a[0] = 1.0f; a[1] = 2.0f; a[2] = 3.0f;
    b[0] = 5.0f; b[1] = 6.0f; b[2] = 7.0f;
    c[0] = 1.5f; c[1] = 2.5f; c[2] = 3.5f;

    BH_Vec3fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 8.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0f, ACCEPTABLE_DELTA);

    BH_Vec3fSub(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -4.0f, ACCEPTABLE_DELTA);

    BH_Vec3fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 12.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 21.0f, ACCEPTABLE_DELTA);

    BH_Vec3fScale(a, 10.0f, r);
    BH_VERIFY_DELTA(r[0], 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 20.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 30.0f, ACCEPTABLE_DELTA);

    BH_Vec3fMulAdd(a, b, c, r);
    BH_VERIFY_DELTA(r[0], 6.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 14.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 24.5f, ACCEPTABLE_DELTA);

    BH_Vec3fNegate(a, r);
    BH_VERIFY_DELTA(r[0], -1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0f, ACCEPTABLE_DELTA);

    value = BH_Vec3fDot(a, b);
    BH_VERIFY_DELTA(value, 38.0f, ACCEPTABLE_DELTA);

    BH_Vec3fCross(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 8.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -4.0f, ACCEPTABLE_DELTA);

    value = BH_Vec3fLength(a);
    BH_VERIFY_DELTA(value, sqrt(14.0f), ACCEPTABLE_DELTA);

    BH_Vec3fNormal(a, r);
    BH_VERIFY_DELTA(r[0], 1.0f / sqrt(14.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f / sqrt(14.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0f / sqrt(14.0f), ACCEPTABLE_DELTA);

    BH_Vec3fMin(a, b, r);
    BH_VERIFY_DELTA(r[0], 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0f, ACCEPTABLE_DELTA);

    BH_Vec3fMax(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(a, b, 0.0f, r);
    BH_VERIFY_DELTA(r[0], 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 3.0f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(a, b, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 3.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.0f, ACCEPTABLE_DELTA);

    BH_Vec3fLerp(a, b, 1.0f, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 7.0f, ACCEPTABLE_DELTA);

    return 0;
}


static int checkVec2f(void)
{
    float a[2], b[2], c[2], r[2];
    float value;

    a[0] = 1.0f; a[1] = 2.0f;
    b[0] = 5.0f; b[1] = 6.0f;
    c[0] = 1.5f; c[1] = 2.5f;

    BH_Vec2fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 6.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 8.0f, ACCEPTABLE_DELTA);

    BH_Vec2fSub(a, b, r);
    BH_VERIFY_DELTA(r[0], -4.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -4.0f, ACCEPTABLE_DELTA);

    BH_Vec2fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 12.0f, ACCEPTABLE_DELTA);

    BH_Vec2fScale(a, 10.0f, r);
    BH_VERIFY_DELTA(r[0], 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 20.0f, ACCEPTABLE_DELTA);

    BH_Vec2fMulAdd(a, b, c, r);
    BH_VERIFY_DELTA(r[0], 6.5f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 14.5f, ACCEPTABLE_DELTA);

    BH_Vec2fNegate(a, r);
    BH_VERIFY_DELTA(r[0], -1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0f, ACCEPTABLE_DELTA);

    value = BH_Vec2fDot(a, b);
    BH_VERIFY_DELTA(value, 17.0f, ACCEPTABLE_DELTA);

    value = BH_Vec2fCross(a, b);
    BH_VERIFY_DELTA(value, -4.0f, ACCEPTABLE_DELTA);

    value = BH_Vec2fLength(a);
    BH_VERIFY_DELTA(value, sqrt(5.0f), ACCEPTABLE_DELTA);

    BH_Vec2fNormal(a, r);
    BH_VERIFY_DELTA(r[0], 1.0f / sqrt(5.0f), ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f / sqrt(5.0f), ACCEPTABLE_DELTA);

    BH_Vec2fMin(a, b, r);
    BH_VERIFY_DELTA(r[0], 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f, ACCEPTABLE_DELTA);

    BH_Vec2fMax(a, b, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0f, ACCEPTABLE_DELTA);

    BH_Vec2fLerp(a, b, 0.0f, r);
    BH_VERIFY_DELTA(r[0], 1.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 2.0f, ACCEPTABLE_DELTA);

    BH_Vec2fLerp(a, b, 0.5f, r);
    BH_VERIFY_DELTA(r[0], 3.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 4.0f, ACCEPTABLE_DELTA);

    BH_Vec2fLerp(a, b, 1.0f, r);
    BH_VERIFY_DELTA(r[0], 5.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0f, ACCEPTABLE_DELTA);

    return 0;
}


static int checkVec4i(void)
{
    int a[4], b[4], c[4], r[4];

    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    b[0] = 5; b[1] = 6; b[2] = 7; b[3] = 8;
    c[0] = 4; c[1] = 3; c[2] = 2; c[3] = 1;

    BH_Vec4iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);
    BH_VERIFY(r[2] == 10);
    BH_VERIFY(r[3] == 12);

    BH_Vec4iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);
    BH_VERIFY(r[2] == -4);
    BH_VERIFY(r[3] == -4);

    BH_Vec4iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);
    BH_VERIFY(r[2] == 21);
    BH_VERIFY(r[3] == 32);

    BH_Vec4iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);
    BH_VERIFY(r[2] == 30);
    BH_VERIFY(r[3] == 40);

    BH_Vec4iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);
    BH_VERIFY(r[2] == 23);
    BH_VERIFY(r[3] == 33);

    BH_Vec4iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);
    BH_VERIFY(r[2] == -3);
    BH_VERIFY(r[3] == -4);

    BH_Vec4iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);
    BH_VERIFY(r[3] == 4);

    BH_Vec4iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);
    BH_VERIFY(r[3] == 8);

    return 0;
}


static int checkVec3i(void)
{
    int a[3], b[3], c[3], r[3];

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;
    c[0] = 4; c[1] = 3; c[2] = 2;

    BH_Vec3iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);
    BH_VERIFY(r[2] == 10);

    BH_Vec3iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);
    BH_VERIFY(r[2] == -4);

    BH_Vec3iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);
    BH_VERIFY(r[2] == 21);

    BH_Vec3iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);
    BH_VERIFY(r[2] == 30);

    BH_Vec3iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);
    BH_VERIFY(r[2] == 23);

    BH_Vec3iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);
    BH_VERIFY(r[2] == -3);

    BH_Vec3iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);
    BH_VERIFY(r[2] == 3);

    BH_Vec3iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);
    BH_VERIFY(r[2] == 7);

    return 0;
}


static int checkVec2i(void)
{
    int a[2], b[2], c[2], r[2];

    a[0] = 1; a[1] = 2;
    b[0] = 5; b[1] = 6;
    c[0] = 4; c[1] = 3;

    BH_Vec2iAdd(a, b, r);
    BH_VERIFY(r[0] == 6);
    BH_VERIFY(r[1] == 8);

    BH_Vec2iSub(a, b, r);
    BH_VERIFY(r[0] == -4);
    BH_VERIFY(r[1] == -4);

    BH_Vec2iMul(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 12);

    BH_Vec2iScale(a, 10, r);
    BH_VERIFY(r[0] == 10);
    BH_VERIFY(r[1] == 20);

    BH_Vec2iMulAdd(a, b, c, r);
    BH_VERIFY(r[0] == 9);
    BH_VERIFY(r[1] == 15);

    BH_Vec2iNegate(a, r);
    BH_VERIFY(r[0] == -1);
    BH_VERIFY(r[1] == -2);

    BH_Vec2iMin(a, b, r);
    BH_VERIFY(r[0] == 1);
    BH_VERIFY(r[1] == 2);

    BH_Vec2iMax(a, b, r);
    BH_VERIFY(r[0] == 5);
    BH_VERIFY(r[1] == 6);

    return 0;
}


static int checkQuat(void)
{
    return 0;
}


static int checkMat4f(void)
{
    float a[16], b[16], r[16];
    float value;

    a[0] = 5.0f; a[4] = 1.0f; a[8] = 2.0f; a[12] = 7.0f;
    a[1] = 3.0f; a[5] = 0.0f; a[9] = 0.0f; a[13] = 2.0f;
    a[2] = 1.0f; a[6] = 3.0f; a[10] = 4.0f; a[14] = 5.0f;
    a[3] = 2.0f; a[7] = 0.0f; a[11] = 0.0f; a[15] = 3.0f;

    b[0] = 5.0f; b[4] = 1.0f; b[8] = 2.0f; b[12] = 7.0f;
    b[1] = 3.0f; b[5] = 1.0f; b[9] = 0.0f; b[13] = 2.0f;
    b[2] = 4.0f; b[6] = 2.0f; b[10] = 4.0f; b[14] = 5.0f;
    b[3] = 6.0f; b[7] = 2.0f; b[11] = 0.0f; b[15] = 4.0f;

    BH_Mat4fIdentity(r);
    BH_VERIFY(r[0] == 1.0f);
    BH_VERIFY(r[1] == 0.0f);
    BH_VERIFY(r[2] == 0.0f);
    BH_VERIFY(r[3] == 0.0f);

    BH_VERIFY(r[4] == 0.0f);
    BH_VERIFY(r[5] == 1.0f);
    BH_VERIFY(r[6] == 0.0f);
    BH_VERIFY(r[7] == 0.0f);

    BH_VERIFY(r[8] == 0.0f);
    BH_VERIFY(r[9] == 0.0f);
    BH_VERIFY(r[10] == 1.0f);
    BH_VERIFY(r[11] == 0.0f);

    BH_VERIFY(r[12] == 0.0f);
    BH_VERIFY(r[13] == 0.0f);
    BH_VERIFY(r[14] == 0.0f);
    BH_VERIFY(r[15] == 1.0f);

    BH_Mat4fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 10.0f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 8.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 14.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  7.0000f, ACCEPTABLE_DELTA);

    BH_Mat4fSub(a, b, r);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], -4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], -2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], -1.0000f, ACCEPTABLE_DELTA);

    BH_Mat4fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 78.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 27.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 60.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 28.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 24.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 22.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  8.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  4.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 75.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 29.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 53.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 26.0000f, ACCEPTABLE_DELTA);

    BH_Mat4fScale(a, 10, r);
    BH_VERIFY_DELTA(r[0], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 20.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 40.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 70.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 30.0000f, ACCEPTABLE_DELTA);

    BH_Mat4fTranspose(a, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 7.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15], 3.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat4fTrace(a);
    BH_VERIFY_DELTA(value, 12.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat4fDet(a);
    BH_VERIFY_DELTA(value, 10.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat4fDet(b);
    BH_VERIFY_DELTA(value, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat4fInverse(a, r) == BH_OK);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  1.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[4],  0.6000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[6], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], -0.4000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[8],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[9],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[10], -0.5000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[11],  0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[12], -0.4000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[13],  1.8000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[14], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[15],  0.6000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat4fInverse(b, r) != BH_OK);

    return 0;
}


static int checkMat3f(void)
{
    float a[9], b[9], r[9];
    float value;

    a[0] = 5.0f; a[3] = 1.0f; a[6] = 2.0f;
    a[1] = 3.0f; a[4] = 0.0f; a[7] = 0.0f;
    a[2] = 1.0f; a[5] = 3.0f; a[8] = 4.0f;

    b[0] = 2.0f; b[3] = 1.0f; b[6] = 2.0f;
    b[1] = 3.0f; b[4] = 1.0f; b[7] = 0.0f;
    b[2] = 4.0f; b[5] = 2.0f; b[8] = 4.0f;

    BH_Mat3fIdentity(r);
    BH_VERIFY(r[0] == 1.0f);
    BH_VERIFY(r[1] == 0.0f);
    BH_VERIFY(r[2] == 0.0f);

    BH_VERIFY(r[3] == 0.0f);
    BH_VERIFY(r[4] == 1.0f);
    BH_VERIFY(r[5] == 0.0f);

    BH_VERIFY(r[6] == 0.0f);
    BH_VERIFY(r[7] == 0.0f);
    BH_VERIFY(r[8] == 1.0f);

    BH_Mat3fAdd(a, b, r);
    BH_VERIFY_DELTA(r[0], 7.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 5.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 4.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 8.0000f, ACCEPTABLE_DELTA);

    BH_Mat3fSub(a, b, r);
    BH_VERIFY_DELTA(r[0],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -3.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], -1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5],  1.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 0.0000f, ACCEPTABLE_DELTA);

    BH_Mat3fMul(a, b, r);
    BH_VERIFY_DELTA(r[0], 21.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 27.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 12.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 18.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  6.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 18.0000f, ACCEPTABLE_DELTA);

    BH_Mat3fScale(a, 10, r);
    BH_VERIFY_DELTA(r[0], 50.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 30.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 10.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 10.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 30.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 20.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 40.0000f, ACCEPTABLE_DELTA);

    BH_Mat3fTranspose(a, r);
    BH_VERIFY_DELTA(r[0], 5.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 2.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4], 0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6], 1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7], 3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], 4.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat3fTrace(a);
    BH_VERIFY_DELTA(value, 9.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat3fDet(a);
    BH_VERIFY_DELTA(value, 6.0000f, ACCEPTABLE_DELTA);

    value = BH_Mat3fDet(b);
    BH_VERIFY_DELTA(value, 0.0000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat3fInverse(a, r) == BH_OK);
    BH_VERIFY_DELTA(r[0],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -2.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2],  1.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[3],  0.3333f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[4],  3.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[5], -2.3333f, ACCEPTABLE_DELTA);

    BH_VERIFY_DELTA(r[6],  0.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[7],  1.0000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[8], -0.5000f, ACCEPTABLE_DELTA);

    BH_VERIFY(BH_Mat3fInverse(b, r) != BH_OK);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UnitAdd("Vec4f", checkVec4f);
    BH_UnitAdd("Vec3f", checkVec3f);
    BH_UnitAdd("Vec2f", checkVec2f);
    BH_UnitAdd("Vec4i", checkVec4i);
    BH_UnitAdd("Vec3i", checkVec3i);
    BH_UnitAdd("Vec2i", checkVec2i);
    BH_UnitAdd("Quat", checkQuat);
    BH_UnitAdd("Mat4f", checkMat4f);
    BH_UnitAdd("Mat3f", checkMat3f);

    return BH_UnitRun();
}
