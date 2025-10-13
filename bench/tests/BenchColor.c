#include <BH/Bench.h>
#include <BH/Color.h>


static BH_Color color, other, result;
static BH_Color foreground, background;
static uint8_t  r8, g8, b8, a8;
static uint16_t r16, g16, b16, a16;
static float    rf, gf, bf, af;
static float    hf, sf, vf, lf, af_hsv, af_hsl;
static int blendMode = BH_COLOR_MODE_NORMAL;


BH_BENCH_TEST(SetRGBA8GetRGBA8)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBA8(&color, 100, 200, 150, 255);
        BH_ColorRGBA8(&color, &r8, &g8, &b8, &a8);

        BH_BenchDoNotOptimize(r8);
        BH_BenchDoNotOptimize(g8);
        BH_BenchDoNotOptimize(b8);
        BH_BenchDoNotOptimize(a8);
    }
}


BH_BENCH_TEST(SetRGBA16GetRGBA16)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBA16(&color, 32768, 40000, 50000, 65535);
        BH_ColorRGBA16(&color, &r16, &g16, &b16, &a16);

        BH_BenchDoNotOptimize(r16);
        BH_BenchDoNotOptimize(g16);
        BH_BenchDoNotOptimize(b16);
        BH_BenchDoNotOptimize(a16);
    }
}


BH_BENCH_TEST(SetRGBAfGetRGBAf)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&color, 0.392f, 0.784f, 0.588f, 1.0f);
        BH_ColorRGBAf(&color, &rf, &gf, &bf, &af);

        BH_BenchDoNotOptimize(rf);
        BH_BenchDoNotOptimize(gf);
        BH_BenchDoNotOptimize(bf);
        BH_BenchDoNotOptimize(af);
    }
}


BH_BENCH_TEST(SetHSVAfGetHSVAf)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetHSVAf(&color, 0.333f, 0.6f, 0.8f, 1.0f);
        BH_ColorHSVAf(&color, &hf, &sf, &vf, &af_hsv);

        BH_BenchDoNotOptimize(hf);
        BH_BenchDoNotOptimize(sf);
        BH_BenchDoNotOptimize(vf);
        BH_BenchDoNotOptimize(af_hsv);
    }
}


BH_BENCH_TEST(SetHSLAfGetHSLAf)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetHSLAf(&color, 0.333f, 0.6f, 0.5f, 1.0f);
        BH_ColorHSLAf(&color, &hf, &sf, &lf, &af_hsl);

        BH_BenchDoNotOptimize(hf);
        BH_BenchDoNotOptimize(sf);
        BH_BenchDoNotOptimize(lf);
        BH_BenchDoNotOptimize(af_hsl);
    }
}


BH_BENCH_TEST(ToRGBAFromHSVA)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetHSVAf(&color, 0.4f, 0.7f, 0.9f, 1.0f);
        BH_ColorToRGBA(&color, &result);

        BH_BenchDoNotOptimize(result.data.rgba.r);
        BH_BenchDoNotOptimize(result.data.rgba.g);
        BH_BenchDoNotOptimize(result.data.rgba.b);
        BH_BenchDoNotOptimize(result.data.rgba.a);
    }
}


BH_BENCH_TEST(ToHSVAFromRGBA)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&color, 0.2f, 0.6f, 0.4f, 1.0f);
        BH_ColorToHSVA(&color, &result);

        BH_BenchDoNotOptimize(result.data.hsva.h);
        BH_BenchDoNotOptimize(result.data.hsva.s);
        BH_BenchDoNotOptimize(result.data.hsva.v);
        BH_BenchDoNotOptimize(result.data.hsva.a);
    }
}


BH_BENCH_TEST(ToHSLAFromRGBA)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&color, 0.2f, 0.6f, 0.4f, 1.0f);
        BH_ColorToHSLA(&color, &result);

        BH_BenchDoNotOptimize(result.data.hsla.h);
        BH_BenchDoNotOptimize(result.data.hsla.s);
        BH_BenchDoNotOptimize(result.data.hsla.l);
        BH_BenchDoNotOptimize(result.data.hsla.a);
    }
}


BH_BENCH_TEST(BlendNormal)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.8f, 0.3f, 0.2f, 0.7f);
        BH_ColorSetRGBAf(&background, 0.1f, 0.5f, 0.9f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_NORMAL, &result);

        BH_BenchDoNotOptimize(result.data.rgba.r);
        BH_BenchDoNotOptimize(result.data.rgba.g);
        BH_BenchDoNotOptimize(result.data.rgba.b);
        BH_BenchDoNotOptimize(result.data.rgba.a);
    }
}


BH_BENCH_TEST(BlendMultiply)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.6f, 0.4f, 0.3f, 0.8f);
        BH_ColorSetRGBAf(&background, 0.5f, 0.7f, 0.9f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_MULTIPLY, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendScreen)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.7f, 0.2f, 0.1f, 0.6f);
        BH_ColorSetRGBAf(&background, 0.3f, 0.8f, 0.6f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_SCREEN, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendOverlay)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.5f, 0.5f, 0.5f, 0.9f);
        BH_ColorSetRGBAf(&background, 0.4f, 0.6f, 0.3f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_OVERLAY, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendHardLight)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.8f, 0.1f, 0.1f, 0.7f);
        BH_ColorSetRGBAf(&background, 0.5f, 0.5f, 0.5f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_HARD_LIGHT, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendDifference)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.9f, 0.2f, 0.1f, 0.8f);
        BH_ColorSetRGBAf(&background, 0.1f, 0.8f, 0.9f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_DIFFERENCE, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendHue)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.8f, 0.3f, 0.2f, 1.0f);
        BH_ColorSetRGBAf(&background, 0.2f, 0.7f, 0.6f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_HUE, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendSaturation)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.3f, 0.9f, 0.4f, 1.0f);
        BH_ColorSetRGBAf(&background, 0.6f, 0.2f, 0.7f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_SATURATION, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendColor)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.1f, 0.8f, 0.3f, 1.0f);
        BH_ColorSetRGBAf(&background, 0.7f, 0.2f, 0.6f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_COLOR, &result);

        BH_BenchDoNotOptimize(result);
    }
}


BH_BENCH_TEST(BlendLuminosity)
{
    while (BH_BenchIter(state))
    {
        BH_ColorSetRGBAf(&foreground, 0.2f, 0.8f, 0.4f, 1.0f);
        BH_ColorSetRGBAf(&background, 0.6f, 0.3f, 0.7f, 1.0f);
        BH_ColorBlend(&foreground, &background, BH_COLOR_MODE_LUMINOSITY, &result);

        BH_BenchDoNotOptimize(result);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(SetRGBA8GetRGBA8);
    BH_BENCH_ADD(SetRGBA16GetRGBA16);
    BH_BENCH_ADD(SetRGBAfGetRGBAf);
    BH_BENCH_ADD(SetHSVAfGetHSVAf);
    BH_BENCH_ADD(SetHSLAfGetHSLAf);
    BH_BENCH_ADD(ToRGBAFromHSVA);
    BH_BENCH_ADD(ToHSVAFromRGBA);
    BH_BENCH_ADD(ToHSLAFromRGBA);
    BH_BENCH_ADD(BlendNormal);
    BH_BENCH_ADD(BlendMultiply);
    BH_BENCH_ADD(BlendScreen);
    BH_BENCH_ADD(BlendOverlay);
    BH_BENCH_ADD(BlendHardLight);
    BH_BENCH_ADD(BlendDifference);
    BH_BENCH_ADD(BlendHue);
    BH_BENCH_ADD(BlendSaturation);
    BH_BENCH_ADD(BlendColor);
    BH_BENCH_ADD(BlendLuminosity);

    return BH_BenchRun();
}
