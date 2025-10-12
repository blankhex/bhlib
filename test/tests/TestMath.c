#include <BH/Math/Quat.h>
#include <BH/Math/Mat4f.h>
#include <BH/Unit.h>


#define ACCEPTABLE_DELTA 0.0001f


BH_UNIT_TEST(QuatMat4fParity)
{
    float a[16], b[16], c[4];

    BH_Mat4fFromEuler(-2.7671f, -0.8324f, -0.1649f, a);

    BH_Quat4fFromEuler(-2.7671f, -0.8324f, -0.1649f, c);
    BH_VERIFY_DELTA(c[0], -0.9018f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(c[1], -0.0010f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(c[2], -0.4099f, ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(c[3],  0.1370f, ACCEPTABLE_DELTA);
    BH_Quat4fToMat4f(c, b);

    BH_VERIFY_DELTA(a[0], b[0], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[1], b[1], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[2], b[2], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[3], b[3], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[4], b[4], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[5], b[5], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[6], b[6], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[7], b[7], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[8], b[8], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[9], b[9], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[10], b[10], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[11], b[11], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[12], b[12], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[13], b[13], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[14], b[14], ACCEPTABLE_DELTA);
    BH_VERIFY_DELTA(a[15], b[15], ACCEPTABLE_DELTA);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(QuatMat4fParity);

    return BH_UnitRun();
}
