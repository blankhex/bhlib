#include <BH/Color.h>
#include <BH/Unit.h>


BH_UNIT_TEST(RoundTrip)
{
    BH_Color src, dest;
    uint8_t r, g, b, a;

    BH_ColorSetRGBA8(&src, 123, 210, 34, 50);

    BH_ColorToHSLA(&src, &dest);
    BH_ColorRGBA8(&dest, &r, &g, &b, &a);
    BH_VERIFY(r == 123);
    BH_VERIFY(g == 210);
    BH_VERIFY(b == 34);
    BH_VERIFY(a == 50);

    BH_ColorToHSVA(&dest, &dest);
    BH_ColorRGBA8(&dest, &r, &g, &b, &a);
    BH_VERIFY(r == 123);
    BH_VERIFY(g == 210);
    BH_VERIFY(b == 34);
    BH_VERIFY(a == 50);

    BH_ColorToRGBA(&dest, &dest);
    BH_ColorRGBA8(&dest, &r, &g, &b, &a);
    BH_VERIFY(r == 123);
    BH_VERIFY(g == 210);
    BH_VERIFY(b == 34);
    BH_VERIFY(a == 50);

    BH_ColorToHSVA(&dest, &dest);
    BH_ColorRGBA8(&dest, &r, &g, &b, &a);
    BH_VERIFY(r == 123);
    BH_VERIFY(g == 210);
    BH_VERIFY(b == 34);
    BH_VERIFY(a == 50);

    BH_ColorToHSLA(&src, &dest);
    BH_ColorRGBA8(&dest, &r, &g, &b, &a);
    BH_VERIFY(r == 123);
    BH_VERIFY(g == 210);
    BH_VERIFY(b == 34);
    BH_VERIFY(a == 50);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(RoundTrip);

    return 0;
}
