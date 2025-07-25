#include "BH/Common.h"
#include <BH/Color.h>
#include <math.h>


#define MIN(a,b)        (((a)<(b))?(a):(b))
#define MAX(a,b)        (((a)>(b))?(a):(b))


/* Conversion between RGB <-> HSL/HSV has error of around ~ 0.009% */
#define DEGREE_MULT     1.8204444e02f


void BH_ColorRGBA8(const BH_Color *color,
                   uint8_t *r,
                   uint8_t *g,
                   uint8_t *b,
                   uint8_t *a)
{
    BH_Color tmp;

    BH_ColorToRGBA(color, &tmp);
    *r = tmp.data.rgba.r >> 8;
    *g = tmp.data.rgba.g >> 8;
    *b = tmp.data.rgba.b >> 8;
    *a = tmp.data.rgba.a >> 8;
}

void BH_ColorRGBA16(const BH_Color *color,
                    uint16_t *r,
                    uint16_t *g,
                    uint16_t *b,
                    uint16_t *a)
{
    BH_Color tmp;

    BH_ColorToRGBA(color, &tmp);
    *r = tmp.data.rgba.r;
    *g = tmp.data.rgba.g;
    *b = tmp.data.rgba.b;
    *a = tmp.data.rgba.a;
}


void BH_ColorRGBAf(const BH_Color *color,
                   float *r,
                   float *g,
                   float *b,
                   float *a)
{
    BH_Color tmp;

    BH_ColorToRGBA(color, &tmp);
    *r = tmp.data.rgba.r / 65535.0f;
    *g = tmp.data.rgba.g / 65535.0f;
    *b = tmp.data.rgba.b / 65535.0f;
    *a = tmp.data.rgba.a / 65535.0f;
}


void BH_ColorSetRGBA8(BH_Color *color,
                      uint8_t r,
                      uint8_t g,
                      uint8_t b,
                      uint8_t a)
{
    color->type = BH_COLOR_TYPE_RGBA;
    color->data.rgba.r = (uint16_t)r * 0x0101;
    color->data.rgba.g = (uint16_t)g * 0x0101;
    color->data.rgba.b = (uint16_t)b * 0x0101;
    color->data.rgba.a = (uint16_t)a * 0x0101;
}


void BH_ColorSetRGBA16(BH_Color *color,
                       uint16_t r,
                       uint16_t g,
                       uint16_t b,
                       uint16_t a)
{
    color->type = BH_COLOR_TYPE_RGBA;
    color->data.rgba.r = r;
    color->data.rgba.g = g;
    color->data.rgba.b = b;
    color->data.rgba.a = a;
}


void BH_ColorSetRGBAf(BH_Color *color,
                      float r,
                      float g,
                      float b,
                      float a)
{
    r = MAX(MIN(1.0f, r), 0.0f);
    g = MAX(MIN(1.0f, g), 0.0f);
    b = MAX(MIN(1.0f, b), 0.0f);
    a = MAX(MIN(1.0f, a), 0.0f);

    color->type = BH_COLOR_TYPE_RGBA;
    color->data.rgba.r = r * 65535.0f;
    color->data.rgba.g = g * 65535.0f;
    color->data.rgba.b = b * 65535.0f;
    color->data.rgba.a = a * 65535.0f;
}


void BH_ColorHSVAf(const BH_Color *color,
                   float *h,
                   float *s,
                   float *v,
                   float *a)
{
    BH_Color tmp;

    BH_ColorToHSVA(color, &tmp);
    *h = tmp.data.hsva.h / DEGREE_MULT;
    *s = tmp.data.hsva.s / 65535.0f;
    *v = tmp.data.hsva.v / 65535.0f;
    *a = tmp.data.hsva.a / 65535.0f;
}


void BH_ColorSetHSVAf(BH_Color *color,
                      float h,
                      float s,
                      float v,
                      float a)
{
    while (h >= 360.0f)
        h -= 360.0f;
    while (h < 0.0f)
        h += 360.0f;

    s = MAX(MIN(1.0f, s), 0.0f);
    v = MAX(MIN(1.0f, v), 0.0f);

    color->type = BH_COLOR_TYPE_HSVA;
    color->data.hsva.h = h * DEGREE_MULT;
    color->data.hsva.s = s * 65535.0f;
    color->data.hsva.v = v * 65535.0f;
    color->data.hsva.a = a * 65535.0f;
}


void BH_ColorHSLAf(const BH_Color *color,
                   float *h,
                   float *s,
                   float *l,
                   float *a)
{
    BH_Color tmp;

    BH_ColorToHSLA(color, &tmp);
    *h = tmp.data.hsla.h / DEGREE_MULT;
    *s = tmp.data.hsla.s / 65535.0f;
    *l = tmp.data.hsla.l / 65535.0f;
    *a = tmp.data.hsla.a / 65535.0f;
}


void BH_ColorSetHSLAf(BH_Color *color,
                      float h,
                      float s,
                      float l,
                      float a)
{
    while (h >= 360.0f)
        h -= 360.0f;
    while (h < 0.0f)
        h += 360.0f;

    s = MAX(MIN(1.0f, s), 0.0f);
    l = MAX(MIN(1.0f, l), 0.0f);

    color->type = BH_COLOR_TYPE_HSLA;
    color->data.hsla.h = h * DEGREE_MULT;
    color->data.hsla.s = s * 65535;
    color->data.hsla.l = l * 65535;
    color->data.hsla.a = a * 65535;
}


/*
 * Transformations between color models are based on:
 * Computer Graphics and Geometric Modeling by Max K. Agoston
 */
static void rgbToHsv(const BH_Color *color,
                     BH_Color *out)
{
    float min, max, d, r, g, b, a, h, s, v;

    BH_ColorRGBAf(color, &r, &g, &b, &a);
    max = MAX(MAX(r, g), b);
    min = MIN(MIN(r, g), b);

    v = max;
    s = 0.0f;
    h = 0.0f;
    d = max - min;

    if (max)
        s = d / max;

    if (s)
    {
        if (r == max)
            h = (g - b) / d;
        else if (g == max)
            h = 2 + (b - r) / d;
        else
            h = 4 + (r - g) / d;
    }

    BH_ColorSetHSVAf(out, h * 60.0f, s, v, a);
}


static void hsvToRgb(const BH_Color *color,
                     BH_Color *out)
{
    float h, s, v, a, r, g, b, fract, p, q, t;
    int sextant;
    BH_ColorHSVAf(color, &h, &s, &v, &a);

    r = v;
    g = v;
    b = v;

    if (s)
    {
        h /= 60.0f;
        sextant = (int)h;
        fract = h - sextant;

        p = v * (1 - s);
        q = v * (1 - (s * fract));
        t = v * (1 - (s * (1 - fract)));

        switch (sextant)
        {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        }
    }

    BH_ColorSetRGBAf(out, r, g, b, a);
}


static void rgbToHsl(const BH_Color *color,
                     BH_Color *out)
{
    float min, max, d, r, g, b, a, h, s, l;

    BH_ColorRGBAf(color, &r, &g, &b, &a);
    max = MAX(MAX(r, g), b);
    min = MIN(MIN(r, g), b);

    l = (max + min) / 2.0;
    s = 0.0f;
    h = 0.0f;
    d =  max - min;

    if (max != min)
    {
        if (l <= 0.5f)
            s = d / (max + min);
        else
            s = d / (2.0f - max - min);

        if (r == max)
            h = (g - b) / d;
        else if (g == max)
            h = 2 + (b - r) / d;
        else
            h = 4 + (r - g) / d;
    }

    BH_ColorSetHSLAf(out, h * 60.0f, s, l, a);
}


static void hslToHsv(const BH_Color *color,
                     BH_Color *out)
{
    float h, s, l, v, a;

    BH_ColorHSLAf(color, &h, &s, &l, &a);
    v = s * MIN(l, 1.0f - l) + l;
    s = (v) ? (2.0f - 2.0f * l / v) : (0.0f);

    BH_ColorSetHSVAf(out, h, s, v, a);
}


static void hsvToHsl(const BH_Color *color,
                     BH_Color *out)
{
    float h, s, v, l, a, m;

    BH_ColorHSVAf(color, &h, &s, &v, &a);
    l = v - v * s / 2.0f;
    m = MIN(l, 1.0f - l);
    s = (m) ? ((v - l) / m) : (0);
    BH_ColorSetHSLAf(out, h, s, l, a);
}


void BH_ColorToRGBA(const BH_Color *color,
                    BH_Color *out)
{
    switch (color->type)
    {
    case BH_COLOR_TYPE_RGBA:
        *out = *color;
        break;

    case BH_COLOR_TYPE_HSVA:
        hsvToRgb(color, out);
        break;

    case BH_COLOR_TYPE_HSLA:
        hslToHsv(color, out);
        hsvToRgb(out, out);
        break;
    }
}


void BH_ColorToHSVA(const BH_Color *color,
                    BH_Color *out)
{
    switch (color->type)
    {
    case BH_COLOR_TYPE_RGBA:
        rgbToHsv(color, out);
        break;

    case BH_COLOR_TYPE_HSVA:
        *out = *color;
        break;

    case BH_COLOR_TYPE_HSLA:
        hslToHsv(color, out);
        break;
    }
}


void BH_ColorToHSLA(const BH_Color *color,
                    BH_Color *out)
{
    switch (color->type)
    {
    case BH_COLOR_TYPE_RGBA:
        rgbToHsl(color, out);
        break;

    case BH_COLOR_TYPE_HSVA:
        hsvToHsl(color, out);
        break;

    case BH_COLOR_TYPE_HSLA:
        *out = *color;
        break;
    }
}


static float blendNormal(float foreground,
                         float background)
{
    BH_UNUSED(background);
    return foreground;
}


static float blendMultiply(float foreground,
                           float background)
{
    return foreground * background;
}


static float blendScreen(float foreground,
                         float background)
{
    return foreground + background - (foreground * background);
}


static float blendDarken(float foreground,
                         float background)
{
    return MIN(foreground, background);
}


static float blendLighten(float foreground,
                          float background)
{
    return MAX(foreground, background);
}


static float blendColorDodge(float foreground,
                             float background)
{
    if (foreground != 1.0f)
        return MIN(1.0f, background / (1.0f - foreground));
    return foreground;
}


static float blendColorBurn(float foreground,
                            float background)
{
    if (foreground != 0.0f)
        return 1.0f - MIN(1.0f, (1.0f - background) / foreground);
    return foreground;
}


static float blendLinearDodge(float foreground,
                              float background)
{
    return foreground + background;
}


static float blendLinearBurn(float foreground,
                             float background)
{
    return foreground + background - 1.0f;
}


static float blendDifference(float foreground,
                             float background)
{
    return fabsf(background - foreground);
}


static float blendExclusion(float foreground,
                            float background)
{
    return foreground + background - (2.0f * foreground * background);
}


static float blendHardLight(float foreground,
                            float background)
{
    if (foreground <= 0.5f)
        return blendMultiply(2.0f * foreground, background);
    else
        return blendScreen(2.0f * foreground - 1.0f, background);
}


static float blendSoftLight(float foreground,
                            float background)
{
    return (1.0f - 2.0f * foreground) * background * background + 2.0f * foreground * background;
}


static float blendOverlay(float foreground,
                          float background)
{
    return blendHardLight(background, foreground);
}


void BH_ColorBlend(const BH_Color *foreground,
                   const BH_Color *background,
                   int mode,
                   BH_Color *dest)
{
    float br, bg, bb, ba;
    float fr, fg, fb, fa;

    if (mode == BH_COLOR_MODE_HUE || mode == BH_COLOR_MODE_SATURATION ||
        mode == BH_COLOR_MODE_COLOR || mode == BH_COLOR_MODE_LUMINOSITY)
    {
        BH_ColorHSLAf(foreground, &fr, &fg, &fb, &fa);
        BH_ColorHSLAf(background, &br, &bg, &bb, &ba);
    }
    else
    {
        BH_ColorRGBAf(foreground, &fr, &fg, &fb, &fa);
        BH_ColorRGBAf(background, &br, &bg, &bb, &ba);
    }

    switch (mode)
    {
    default:
    case BH_COLOR_MODE_NORMAL:
        fr = blendNormal(fr, br);
        fg = blendNormal(fg, bg);
        fb = blendNormal(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_MULTIPLY:
        fr = blendMultiply(fr, br);
        fg = blendMultiply(fg, bg);
        fb = blendMultiply(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_SCREEN:
        fr = blendScreen(fr, br);
        fg = blendScreen(fg, bg);
        fb = blendScreen(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_OVERLAY:
        fr = blendOverlay(fr, br);
        fg = blendOverlay(fg, bg);
        fb = blendOverlay(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_DARKEN:
        fr = blendDarken(fr, br);
        fg = blendDarken(fg, bg);
        fb = blendDarken(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_LIGHTEN:
        fr = blendLighten(fr, br);
        fg = blendLighten(fg, bg);
        fb = blendLighten(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_COLOR_DODGE:
        fr = blendColorDodge(fr, br);
        fg = blendColorDodge(fg, bg);
        fb = blendColorDodge(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_COLOR_BURN:
        fr = blendColorBurn(fr, br);
        fg = blendColorBurn(fg, bg);
        fb = blendColorBurn(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_LINEAR_DODGE:
        fr = blendLinearDodge(fr, br);
        fg = blendLinearDodge(fg, bg);
        fb = blendLinearDodge(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_LINEAR_BURN:
        fr = blendLinearBurn(fr, br);
        fg = blendLinearBurn(fg, bg);
        fb = blendLinearBurn(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_HARD_LIGHT:
        fr = blendHardLight(fr, br);
        fg = blendHardLight(fg, bg);
        fb = blendHardLight(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_SOFT_LIGHT:
        fr = blendSoftLight(fr, br);
        fg = blendSoftLight(fg, bg);
        fb = blendSoftLight(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_DIFFERENCE:
        fr = blendDifference(fr, br);
        fg = blendDifference(fg, bg);
        fb = blendDifference(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_EXCLUSION:
        fr = blendExclusion(fr, br);
        fg = blendExclusion(fg, bg);
        fb = blendExclusion(fb, bb);
        BH_ColorSetRGBAf(dest, fr, fg, fb, fa);
        break;

    case BH_COLOR_MODE_HUE:
        BH_ColorSetHSLAf(dest, fr, bg, bb, fa);
        break;

    case BH_COLOR_MODE_SATURATION:
        BH_ColorSetHSLAf(dest, br, fg, bb, fa);
        break;

    case BH_COLOR_MODE_COLOR:
        BH_ColorSetHSLAf(dest, fr, fg, bb, fa);
        break;

    case BH_COLOR_MODE_LUMINOSITY:
        BH_ColorSetHSLAf(dest, br, bg, fb, fa);
        break;
    }
}
