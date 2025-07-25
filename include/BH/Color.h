#ifndef BH_COLOR_H
#define BH_COLOR_H


#include "Common.h"


#define BH_COLOR_TYPE_RGBA 0x0000
#define BH_COLOR_TYPE_HSVA 0x0001
#define BH_COLOR_TYPE_HSLA 0x0002


#define BH_COLOR_MODE_NORMAL        0x0000
#define BH_COLOR_MODE_MULTIPLY      0x0001
#define BH_COLOR_MODE_SCREEN        0x0002
#define BH_COLOR_MODE_OVERLAY       0x0003
#define BH_COLOR_MODE_DARKEN        0x0004
#define BH_COLOR_MODE_LIGHTEN       0x0005
#define BH_COLOR_MODE_COLOR_DODGE   0x0006
#define BH_COLOR_MODE_COLOR_BURN    0x0007
#define BH_COLOR_MODE_LINEAR_DODGE  0x0008
#define BH_COLOR_MODE_LINEAR_BURN   0x0009
#define BH_COLOR_MODE_HARD_LIGHT    0x000A
#define BH_COLOR_MODE_SOFT_LIGHT    0x000B
#define BH_COLOR_MODE_DIFFERENCE    0x000C
#define BH_COLOR_MODE_EXCLUSION     0x000D
#define BH_COLOR_MODE_HUE           0x000E
#define BH_COLOR_MODE_SATURATION    0x000F
#define BH_COLOR_MODE_COLOR         0x0010
#define BH_COLOR_MODE_LUMINOSITY    0x0011


typedef struct BH_Color
{
    int type;
    union
    {
        struct
        {
            uint16_t r;
            uint16_t g;
            uint16_t b;
            uint16_t a;
        } rgba;
        struct
        {
            uint16_t h;
            uint16_t s;
            uint16_t v;
            uint16_t a;
        } hsva;
        struct
        {
            uint16_t h;
            uint16_t s;
            uint16_t l;
            uint16_t a;
        } hsla;
    } data;
} BH_Color;


void BH_ColorRGBA8(const BH_Color *color,
                   uint8_t *r,
                   uint8_t *g,
                   uint8_t *b,
                   uint8_t *a);


void BH_ColorRGBA16(const BH_Color *color,
                    uint16_t *r,
                    uint16_t *g,
                    uint16_t *b,
                    uint16_t *a);


void BH_ColorRGBAf(const BH_Color *color,
                   float *r,
                   float *g,
                   float *b,
                   float *a);


void BH_ColorSetRGBA8(BH_Color *color,
                      uint8_t r,
                      uint8_t g,
                      uint8_t b,
                      uint8_t a);


void BH_ColorSetRGBA16(BH_Color *color,
                       uint16_t r,
                       uint16_t g,
                       uint16_t b,
                       uint16_t a);


void BH_ColorSetRGBAf(BH_Color *color,
                      float r,
                      float g,
                      float b,
                      float a);


void BH_ColorHSVAf(const BH_Color *color,
                   float *h,
                   float *s,
                   float *v,
                   float *a);


void BH_ColorSetHSVAf(BH_Color *color,
                      float h,
                      float s,
                      float v,
                      float a);


void BH_ColorHSLAf(const BH_Color *color,
                   float *h,
                   float *s,
                   float *l,
                   float *a);


void BH_ColorSetHSLAf(BH_Color *color,
                      float h,
                      float s,
                      float l,
                      float a);


void BH_ColorToRGBA(const BH_Color *color,
                    BH_Color *out);


void BH_ColorToHSVA(const BH_Color *color,
                    BH_Color *out);


void BH_ColorToHSLA(const BH_Color *color,
                    BH_Color *out);


void BH_ColorBlend(const BH_Color *foreground,
                   const BH_Color *background,
                   int mode,
                   BH_Color *dest);


#endif /* BH_COLOR_H */
