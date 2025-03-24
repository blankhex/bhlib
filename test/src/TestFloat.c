#include <BH/String.h>
#include <BH/Util.h>
#include <BH/Unit.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


static int compareString(double value,
                         int format,
                         int precision,
                         const char *ref)
{
    int result;
    char *str;

    str = BH_StringFromDouble(value, format, precision);
    result = strcmp(str, ref);
    if (result)
        printf("Value: %.17g\tReference: %s\tGot: %s\n", value, ref, str);

    BH_StringFree(str);

    return result;
}


static int roundtripString(double value,
                           int format)
{
    double result;
    char *str;

    str = BH_StringFromDouble(value, format, -1);
    result = BH_StringToDouble(str, NULL);
    if (result != value)
        printf("Value: %.17g\tGot: %.17g\tStr: %s\n", value, result, str);

    BH_StringFree(str);

    return result != value;
}


BH_UNIT_TEST(FixedFormat)
{
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 0, "30") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 1, "30.0") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 2, "30.02") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 3, "30.016") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 4, "30.0159") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'f', 5, "30.01593") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 0, "-30") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 1, "-30.0") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 2, "-30.02") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 3, "-30.016") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 4, "-30.0159") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'f', 5, "-30.01593") == 0);

    BH_VERIFY(compareString(0.0, 'f', 0, "0") == 0);
    BH_VERIFY(compareString(0.0, 'f', 1, "0.0") == 0);
    BH_VERIFY(compareString(-0.0, 'f', 0, "-0") == 0);
    BH_VERIFY(compareString(-0.0, 'f', 1, "-0.0") == 0);

    BH_VERIFY(compareString(0.00015425, 'f', 0, "0") == 0);
    BH_VERIFY(compareString(0.00015425, 'f', 1, "0.0") == 0);
    BH_VERIFY(compareString(0.00015425, 'f', 2, "0.00") == 0);
    BH_VERIFY(compareString(0.00015425, 'f', 3, "0.000") == 0);
    BH_VERIFY(compareString(0.00015425, 'f', 4, "0.0002") == 0);
    BH_VERIFY(compareString(0.00015425, 'f', 5, "0.00015") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 0, "-0") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 1, "-0.0") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 2, "-0.00") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 3, "-0.000") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 4, "-0.0002") == 0);
    BH_VERIFY(compareString(-0.00015425, 'f', 5, "-0.00015") == 0);

    BH_VERIFY(compareString(1234567.1234, 'f', 0, "1234567") == 0);
    BH_VERIFY(compareString(-1234567.1234, 'f', 0, "-1234567") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'f', 0, "1230000000") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'f', 1, "1230000000.0") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'f', 2, "1230000000.00") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'f', 3, "1230000000.001") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'f', 0, "-1230000000") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'f', 1, "-1230000000.0") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'f', 2, "-1230000000.00") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'f', 3, "-1230000000.001") == 0);

    return 0;
}


BH_UNIT_TEST(FixedRoundTrip)
{
    BH_VERIFY(roundtripString(1.0, 'f') == 0);
    BH_VERIFY(roundtripString(-1.0, 'f') == 0);
    BH_VERIFY(roundtripString(0.0, 'f') == 0);
    BH_VERIFY(roundtripString(-0.0, 'f') == 0);
    BH_VERIFY(roundtripString(3.14159, 'f') == 0);
    BH_VERIFY(roundtripString(-3.14159, 'f') == 0);
    BH_VERIFY(roundtripString(123000000.0, 'f') == 0);
    BH_VERIFY(roundtripString(-123000000.0, 'f') == 0);
    BH_VERIFY(roundtripString(0.81, 'f') == 0);
    BH_VERIFY(roundtripString(-0.81, 'f') == 0);
    BH_VERIFY(roundtripString(0.81, 'f') == 0);
    BH_VERIFY(roundtripString(-0.81, 'f') == 0);
    BH_VERIFY(roundtripString(144115188075855877.0, 'f') == 0);
    BH_VERIFY(roundtripString(-144115188075855877.0, 'f') == 0);
    BH_VERIFY(roundtripString(DBL_MIN, 'f') == 0);
    BH_VERIFY(roundtripString(-DBL_MIN, 'f') == 0);
    BH_VERIFY(roundtripString(DBL_MAX, 'f') == 0);
    BH_VERIFY(roundtripString(-DBL_MAX, 'f') == 0);

    return 0;
}


BH_UNIT_TEST(ScientificFormat)
{
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 0, "3e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 1, "3.0e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 2, "3.00e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 3, "3.002e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 4, "3.0016e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'e', 5, "3.00159e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 0, "-3e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 1, "-3.0e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 2, "-3.00e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 3, "-3.002e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 4, "-3.0016e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'e', 5, "-3.00159e+01") == 0);

    BH_VERIFY(compareString(0.0, 'e', 0, "0e+00") == 0);
    BH_VERIFY(compareString(0.0, 'e', 1, "0.0e+00") == 0);
    BH_VERIFY(compareString(-0.0, 'e', 0, "-0e+00") == 0);
    BH_VERIFY(compareString(-0.0, 'e', 1, "-0.0e+00") == 0);

    BH_VERIFY(compareString(0.00015425, 'e', 0, "2e-04") == 0);
    BH_VERIFY(compareString(0.00015425, 'e', 1, "1.5e-04") == 0);
    BH_VERIFY(compareString(0.00015425, 'e', 2, "1.54e-04") == 0);
    BH_VERIFY(compareString(0.00015425, 'e', 3, "1.543e-04") == 0);
    BH_VERIFY(compareString(0.00015425, 'e', 4, "1.5425e-04") == 0);
    BH_VERIFY(compareString(0.00015425, 'e', 5, "1.54250e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 0, "-2e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 1, "-1.5e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 2, "-1.54e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 3, "-1.543e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 4, "-1.5425e-04") == 0);
    BH_VERIFY(compareString(-0.00015425, 'e', 5, "-1.54250e-04") == 0);

    BH_VERIFY(compareString(1234567.1234, 'e', 0, "1e+06") == 0);
    BH_VERIFY(compareString(-1234567.1234, 'e', 0, "-1e+06") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'e', 0, "1e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'e', 1, "1.2e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'e', 2, "1.23e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'e', 3, "1.230e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'e', 0, "-1e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'e', 1, "-1.2e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'e', 2, "-1.23e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'e', 3, "-1.230e+09") == 0);

    return 0;
}


BH_UNIT_TEST(ShortestFormat)
{
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 0, "3e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 1, "3e+01") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 2, "30") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 3, "30") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 4, "30.02") == 0);
    BH_VERIFY(compareString(30.0159265358979323846, 'g', 5, "30.016") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 0, "-3e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 1, "-3e+01") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 2, "-30") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 3, "-30") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 4, "-30.02") == 0);
    BH_VERIFY(compareString(-30.0159265358979323846, 'g', 5, "-30.016") == 0);

    BH_VERIFY(compareString(0.0, 'g', 0, "0") == 0);
    BH_VERIFY(compareString(0.0, 'g', 1, "0") == 0);
    BH_VERIFY(compareString(-0.0, 'g', 0, "-0") == 0);
    BH_VERIFY(compareString(-0.0, 'g', 1, "-0") == 0);

    BH_VERIFY(compareString(0.00015425, 'g', 0, "0.0002") == 0);
    BH_VERIFY(compareString(0.00015425, 'g', 1, "0.0002") == 0);
    BH_VERIFY(compareString(0.00015425, 'g', 2, "0.00015") == 0);
    BH_VERIFY(compareString(0.00015425, 'g', 3, "0.000154") == 0);
    BH_VERIFY(compareString(0.00015425, 'g', 4, "0.0001543") == 0);
    BH_VERIFY(compareString(0.00015425, 'g', 5, "0.00015425") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 0, "-0.0002") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 1, "-0.0002") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 2, "-0.00015") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 3, "-0.000154") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 4, "-0.0001543") == 0);
    BH_VERIFY(compareString(-0.00015425, 'g', 5, "-0.00015425") == 0);

    BH_VERIFY(compareString(1234567.1234, 'g', 0, "1e+06") == 0);
    BH_VERIFY(compareString(-1234567.1234, 'g', 0, "-1e+06") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'g', 0, "1e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'g', 1, "1e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'g', 2, "1.2e+09") == 0);
    BH_VERIFY(compareString(1230000000.00123, 'g', 3, "1.23e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'g', 0, "-1e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'g', 1, "-1e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'g', 2, "-1.2e+09") == 0);
    BH_VERIFY(compareString(-1230000000.00123, 'g', 3, "-1.23e+09") == 0);
    BH_VERIFY(compareString(144115188075855877.0, 'g', 17, "1.4411518807585587e+17") == 0);
    BH_VERIFY(compareString(-144115188075855877.0, 'g', 17, "-1.4411518807585587e+17") == 0);

    return 0;
}


BH_UNIT_TEST(ScientificRoundTrip)
{
    BH_VERIFY(roundtripString(1.0, 'e') == 0);
    BH_VERIFY(roundtripString(-1.0, 'e') == 0);
    BH_VERIFY(roundtripString(0.0, 'e') == 0);
    BH_VERIFY(roundtripString(-0.0, 'e') == 0);
    BH_VERIFY(roundtripString(3.14159, 'e') == 0);
    BH_VERIFY(roundtripString(-3.14159, 'e') == 0);
    BH_VERIFY(roundtripString(123000000.0, 'e') == 0);
    BH_VERIFY(roundtripString(-123000000.0, 'e') == 0);
    BH_VERIFY(roundtripString(0.81, 'e') == 0);
    BH_VERIFY(roundtripString(-0.81, 'e') == 0);
    BH_VERIFY(roundtripString(0.81, 'e') == 0);
    BH_VERIFY(roundtripString(-0.81, 'e') == 0);
    BH_VERIFY(roundtripString(144115188075855877.0, 'e') == 0);
    BH_VERIFY(roundtripString(-144115188075855877.0, 'e') == 0);
    BH_VERIFY(roundtripString(DBL_MIN, 'e') == 0);
    BH_VERIFY(roundtripString(-DBL_MIN, 'e') == 0);
    BH_VERIFY(roundtripString(DBL_MAX, 'e') == 0);
    BH_VERIFY(roundtripString(-DBL_MAX, 'e') == 0);

    return 0;
}


BH_UNIT_TEST(ShortestRoundTrip)
{
    BH_VERIFY(roundtripString(1.0, 'g') == 0);
    BH_VERIFY(roundtripString(-1.0, 'g') == 0);
    BH_VERIFY(roundtripString(0.0, 'g') == 0);
    BH_VERIFY(roundtripString(-0.0, 'g') == 0);
    BH_VERIFY(roundtripString(3.14159, 'g') == 0);
    BH_VERIFY(roundtripString(-3.14159, 'g') == 0);
    BH_VERIFY(roundtripString(123000000.0, 'g') == 0);
    BH_VERIFY(roundtripString(-123000000.0, 'g') == 0);
    BH_VERIFY(roundtripString(0.81, 'g') == 0);
    BH_VERIFY(roundtripString(-0.81, 'g') == 0);
    BH_VERIFY(roundtripString(0.81, 'g') == 0);
    BH_VERIFY(roundtripString(-0.81, 'g') == 0);
    BH_VERIFY(roundtripString(144115188075855877.0, 'g') == 0);
    BH_VERIFY(roundtripString(-144115188075855877.0, 'g') == 0);
    BH_VERIFY(roundtripString(DBL_MIN, 'g') == 0);
    BH_VERIFY(roundtripString(-DBL_MIN, 'g') == 0);
    BH_VERIFY(roundtripString(DBL_MAX, 'g') == 0);
    BH_VERIFY(roundtripString(-DBL_MAX, 'g') == 0);

    return 0;
}


BH_UNIT_TEST(Parity)
{
    char buffer[16], output[2000];
    uint64_t frac;
    double value;
    int i, j, k;

    for (i = 0; i < 100; i++)
    {
        frac = (rand() & 0x7FFF);
        frac = (frac << 15) | (rand() & 0x7FFF);
        frac = (frac << 15) | (rand() & 0x7FFF);
        frac = (frac << 15) | (rand() & 0x7FFF);

        for (j = 0; j < 100; j++)
        {
            value = frac * pow(2, (rand() % 2046) - 1024);

            for (k = 0; k < 18; k++)
            {
                char *str;

                sprintf(buffer, "%%.%dg", k);
                str = BH_StringFromDouble(value, 'g', k);
                sprintf(output, buffer, value);

                if (strcmp(str, output))
                {
                    printf("(%.17g) (%d) %s vs %s\n", value, k, str, output);
                    BH_FAIL("Strings aren't equal");
                }
                BH_StringFree(str);
            }
        }
    }

    return 0;
}


BH_UNIT_TEST(ToDouble)
{
    size_t size;

    BH_VERIFY(BH_ClassifyDouble(BH_StringToDouble("  INFa  ", &size)) == BH_FP_INFINITE);
    BH_VERIFY(size == 5);
    BH_VERIFY(BH_ClassifyDouble(BH_StringToDouble("  INFINITYc  ", &size)) == BH_FP_INFINITE);
    BH_VERIFY(size == 10);

    BH_VERIFY(BH_ClassifyDouble(BH_StringToDouble("  -INFb  ", &size)) == (BH_FP_INFINITE | BH_FP_NEGATIVE));
    BH_VERIFY(size == 6);
    BH_VERIFY(BH_ClassifyDouble(BH_StringToDouble("  -INFINITYd  ", &size)) == (BH_FP_INFINITE | BH_FP_NEGATIVE));
    BH_VERIFY(size == 11);

    BH_VERIFY(BH_ClassifyDouble(BH_StringToDouble("  NANe  ", &size)) == BH_FP_NAN);
    BH_VERIFY(size == 5);

    BH_VERIFY_DELTA(BH_StringToDouble("  1234.0312f  ", &size), 1234.0312, 0.00001);
    BH_VERIFY(size == 11);

    BH_VERIFY_DELTA(BH_StringToDouble("  3.14159g  ", &size), 3.14159, 0.00001);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringToDouble("  h  ", &size) == 0.0);
    BH_VERIFY(size == 0);

    BH_VERIFY(BH_StringToDouble("  0  ", &size) == 0.0);
    BH_VERIFY(size == 3);

    BH_VERIFY(BH_StringToDouble("  0.0  ", &size) == 0.0);
    BH_VERIFY(size == 5);

    BH_VERIFY(BH_StringToDouble("  0.  ", &size) == 0.0);
    BH_VERIFY(size == 4);

    BH_VERIFY(BH_StringToDouble("  .0  ", &size) == 0.0);
    BH_VERIFY(size == 4);

    BH_VERIFY(BH_StringToDouble("  .Hello  ", &size) == 0.0);
    BH_VERIFY(size == 0);

    BH_VERIFY(BH_StringToDouble("  .E12  ", &size) == 0.0);
    BH_VERIFY(size == 0);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(FixedFormat);
    BH_UNIT_ADD(FixedRoundTrip);
    BH_UNIT_ADD(ScientificFormat);
    BH_UNIT_ADD(ScientificRoundTrip);
    BH_UNIT_ADD(ShortestFormat);
    BH_UNIT_ADD(ShortestRoundTrip);
    BH_UNIT_ADD(Parity);
    BH_UNIT_ADD(ToDouble);

    return BH_UnitRun();
}
