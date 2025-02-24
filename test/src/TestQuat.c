#include <BH/Math.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(Identity)
{
    float r[4];

    BH_Quat4fIdentity(r);
    BH_VERIFY_DELTA(r[0], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 1.000f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(Conjugate)
{
    float a[4], r[4];

    a[0] = -0.9018f; a[1] = -0.0010f; a[2] = -0.4099f; a[3] = 0.1370f;

    BH_Quat4fConjugate(a, r);
    BH_VERIFY_DELTA(r[0], 0.9018f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 0.0010f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 0.4099f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 0.1370f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(ToEuler)
{
    float a[4];
    float roll, pitch, yaw;

    a[0] = -0.9018f; a[1] = -0.0010f; a[2] = -0.4099f; a[3] = 0.1370f;

    BH_Quat4fToEuler(a, &roll, &pitch, &yaw);
    BH_VERIFY_DELTA(roll,  -2.7671f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(pitch, -0.8324f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(yaw,   -0.1649f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(FromEuler)
{
    float r[4];

    BH_Quat4fFromEuler(-2.7671f, -0.8324f, -0.1649f, r);
    BH_VERIFY_DELTA(r[0], -0.9018f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -0.0010f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -0.4099f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.1370f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(ToAxis)
{
    float a[4], r[3];
    float angle;

    a[0] = -0.9018f; a[1] = -0.0010f; a[2] = -0.4099f; a[3] = 0.1370f;

    BH_Quat4fToAxis(a, r, &angle);
    BH_VERIFY_DELTA(r[0], -0.9104f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -0.0010f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -0.4138f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(angle, 2.8668f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(FromAxis)
{
    float a[3], r[4];
    a[0] = -0.9104f; a[1] = -0.0010f; a[2] = -0.4138f;

    BH_Quat4fFromAxis(a, 2.8668f, r);
    BH_VERIFY_DELTA(r[0], -0.9018f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], -0.0010f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], -0.4099f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3],  0.1370f, ACCEPTABLE_DELTA);

    return 0;
}


BH_UNIT_TEST(InverseMultiply)
{
    float a[4], r[4];

    a[0] = -0.9018f; a[1] = -0.0010f; a[2] = -0.4099f; a[3] = 0.1370f;

    BH_Quat4fInverse(a, r);
    BH_Quat4fMul(a, r, r);
    BH_VERIFY_DELTA(r[0], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[1], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[2], 0.000f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(r[3], 1.000f, ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Identity);
    BH_UNIT_ADD(Conjugate);
    BH_UNIT_ADD(ToEuler);
    BH_UNIT_ADD(FromEuler);
    BH_UNIT_ADD(ToAxis);
    BH_UNIT_ADD(FromAxis);
    BH_UNIT_ADD(InverseMultiply);

    return BH_UnitRun();
}
