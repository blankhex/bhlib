#include <BH/Bitmap.h>
#include <stdlib.h>
#include <string.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


struct BH_Bitmap
{
    int width;
    int height;
    int format;
    int flags;
    size_t step;
    size_t stride;
    uint8_t *data;
    uint32_t *palette;
};


/* Bit and unit order arrays for working with RGB/BGR and MSB/LSB */
static const size_t bitOrder1[][8] =
{
    {7, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 7},
};


static const size_t bitMask1[][8] =
{
    {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
};


static const size_t bitOrder2[][4] =
{
    {6, 4, 2, 0},
    {0, 2, 4, 6},
};


static const size_t bitMask2[][4] =
{
    {0xC0, 0x30, 0x0C, 0x03},
    {0x03, 0x0C, 0x30, 0xC0},
};


static const size_t bitOrder4[][2] =
{
    {4, 0},
    {0, 4},
};


static const size_t bitMask4[][2] =
{
    {0xF0, 0x0F},
    {0x0F, 0xF0},
};


static const size_t bitOrder565[][3] =
{
    {11, 5, 0},
    {0, 5, 11},
};


static const size_t bitOrder1010102[][4] =
{
    {0, 10, 20, 30},
    {20, 10, 0, 30},
};


static const size_t unitOrderRGB[][3] =
{
    {0, 1, 2},
    {2, 1, 0},
};


static const size_t unitOrderRGBA[][4] =
{
    {0, 1, 2, 3},
    {2, 1, 0, 3},
};


/* Private functions */
static size_t calculateStep(int format)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
    case BH_BITMAP_INDEX2:
    case BH_BITMAP_INDEX4:
        return 0;

    case BH_BITMAP_INDEX8:
    case BH_BITMAP_GRAY8:
        return 1;

    case BH_BITMAP_GRAY16:
    case BH_BITMAP_RGB565:
        return 2;

    case BH_BITMAP_RGB888:
        return 3;

    case BH_BITMAP_RGBA32:
    case BH_BITMAP_RGBA8888:
    case BH_BITMAP_RGBA1010102:
        return 4;

    case BH_BITMAP_RGB161616:
        return 6;

    case BH_BITMAP_RGBA64:
    case BH_BITMAP_RGBA16161616:
        return 8;
    }

    return 0;
}


static uint8_t bitmapIndex(void *data,
                           int format,
                           int x)
{
    int isLSB;
    uint8_t octet;

    isLSB = (format & BH_BITMAP_LSB) > 0;
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
        octet = (*(uint8_t *)data) & bitMask1[isLSB][x & 7];
        return octet >> bitOrder1[isLSB][x & 7];

    case BH_BITMAP_INDEX2:
        octet = (*(uint8_t *)data) & bitMask2[isLSB][x & 3];
        return octet >> bitOrder2[isLSB][x & 3];

    case BH_BITMAP_INDEX4:
        octet = (*(uint8_t *)data) & bitMask4[isLSB][x & 1];
        return octet >> bitOrder4[isLSB][x & 1];

    case BH_BITMAP_INDEX8:
        return *(uint8_t *)data;
    }

    return 0;
}


static void setBitmapIndex(void *data,
                           int format,
                           int x,
                           uint8_t index)
{
    int isLSB;
    uint8_t octet;

    isLSB = (format & BH_BITMAP_LSB) > 0;
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
        octet = (*(uint8_t *)data) & ~bitMask1[isLSB][x & 7];
        octet |= (index & 0x1) << bitOrder1[isLSB][x & 7];
        *(uint8_t *)data = octet;
        break;

    case BH_BITMAP_INDEX2:
        octet = (*(uint8_t *)data) & ~bitMask2[isLSB][x & 3];
        octet |= (index & 0x3) << bitOrder2[isLSB][x & 3];
        *(uint8_t *)data = octet;
        break;

    case BH_BITMAP_INDEX4:
        octet = (*(uint8_t *)data) & ~bitMask4[isLSB][x & 1];
        octet |= (index & 0xF) << bitOrder4[isLSB][x & 1];
        *(uint8_t *)data = octet;
        break;

    case BH_BITMAP_INDEX8:
        *(uint8_t *)data = index;
        break;
    }
}


static void bitmapColor(void *data,
                        void *palette,
                        int format,
                        BH_Color *value,
                        int x)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
        {
            uint32_t color;
            color = ((uint32_t *)palette)[bitmapIndex(data, format, x)];

            BH_ColorSetRGBA8(value, color >> 16 & 0xFF, color >> 8 & 0xFF,
                                    color & 0xFF, color >> 24 & 0xFF);
        }
        break;

    case BH_BITMAP_INDEX2:
        {
            uint32_t color;
            color = ((uint32_t *)palette)[bitmapIndex(data, format, x)];

            BH_ColorSetRGBA8(value, color >> 16 & 0xFF, color >> 8 & 0xFF,
                                    color & 0xFF, color >> 24 & 0xFF);
        }
        break;

    case BH_BITMAP_INDEX4:
        {
            uint32_t color;
            color = ((uint32_t *)palette)[bitmapIndex(data, format, x)];

            BH_ColorSetRGBA8(value, color >> 16 & 0xFF, color >> 8 & 0xFF,
                                    color & 0xFF, color >> 24 & 0xFF);
        }
        break;

    case BH_BITMAP_INDEX8:
        {
            uint32_t color;
            color = ((uint32_t *)palette)[bitmapIndex(data, format, x)];

            BH_ColorSetRGBA8(value, color >> 16 & 0xFF, color >> 8 & 0xFF,
                                    color & 0xFF, color >> 24 & 0xFF);
        }
        break;

    case BH_BITMAP_GRAY8:
        {
            uint8_t color;

            color = *(uint8_t *)data;
            BH_ColorSetRGBA8(value, color, color, color, 0xFF);
        }
        break;

    case BH_BITMAP_GRAY16:
        {
            uint16_t color;

            color = *(uint16_t *)data;
            BH_ColorSetRGBA16(value, color, color, color, 0xFFFF);
        }
        break;

    case BH_BITMAP_RGBA32:
        {
            uint32_t color;

            color = *(uint32_t *)data;
            BH_ColorSetRGBA8(value, color >> 16 & 0xFF, color >> 8 & 0xFF,
                                    color & 0xFF, color >> 24 & 0xFF);
        }
        break;

    case BH_BITMAP_RGBA64:
        {
            uint64_t color;

            color = *(uint64_t *)data;
            BH_ColorSetRGBA16(value, color >> 32 & 0xFFFF, color >> 16 & 0xFFFF,
                                     color & 0xFFFF, color >> 48 & 0xFFFF);
        }
        break;

    case BH_BITMAP_RGB565:
        {
            uint8_t r, g, b;
            uint16_t color;
            int isBGR;

            color = *(uint16_t *)data;
            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = color >> bitOrder565[isBGR][0] & 0x1F;
            g = color >> bitOrder565[isBGR][1] & 0x3F;
            b = color >> bitOrder565[isBGR][2] & 0x1F;
            r = r << 3 | r >> 2;
            g = g << 2 | g >> 4;
            b = b << 3 | b >> 2;

            BH_ColorSetRGBA8(value, r, g, b, 0xFF);
        }
        break;

    case BH_BITMAP_RGB888:
        {
            uint8_t r, g, b;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = ((uint8_t *)data)[unitOrderRGB[isBGR][0]];
            g = ((uint8_t *)data)[unitOrderRGB[isBGR][1]];
            b = ((uint8_t *)data)[unitOrderRGB[isBGR][2]];

            BH_ColorSetRGBA8(value, r, g, b, 0xFF);
        }
        break;

    case BH_BITMAP_RGBA8888:
        {
            uint8_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = ((uint8_t *)data)[unitOrderRGBA[isBGR][0]];
            g = ((uint8_t *)data)[unitOrderRGBA[isBGR][1]];
            b = ((uint8_t *)data)[unitOrderRGBA[isBGR][2]];
            a = ((uint8_t *)data)[unitOrderRGBA[isBGR][3]];

            BH_ColorSetRGBA8(value, r, g, b, a);
        }
        break;

    case BH_BITMAP_RGB161616:
        {
            uint16_t r, g, b;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = ((uint16_t *)data)[unitOrderRGB[isBGR][0]];
            g = ((uint16_t *)data)[unitOrderRGB[isBGR][1]];
            b = ((uint16_t *)data)[unitOrderRGB[isBGR][2]];

            BH_ColorSetRGBA16(value, r, g, b, 0xFFFF);
        }
        break;

    case BH_BITMAP_RGBA16161616:
        {
            uint16_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = ((uint16_t *)data)[unitOrderRGBA[isBGR][0]];
            g = ((uint16_t *)data)[unitOrderRGBA[isBGR][1]];
            b = ((uint16_t *)data)[unitOrderRGBA[isBGR][2]];
            a = ((uint16_t *)data)[unitOrderRGBA[isBGR][3]];

            BH_ColorSetRGBA16(value, r, g, b, a);
        }
        break;

    case BH_BITMAP_RGBA1010102:
        {
            uint16_t r, g, b, a;
            uint32_t color;
            int isBGR;

            color = *(uint32_t *)data;
            isBGR = (format & BH_BITMAP_BGR) > 0;
            r = color >> bitOrder1010102[isBGR][0] & 0x3FF;
            g = color >> bitOrder1010102[isBGR][1] & 0x3FF;
            b = color >> bitOrder1010102[isBGR][2] & 0x3FF;
            a = color >> bitOrder1010102[isBGR][3] & 0x3;
            r = r << 6 | r >> 4;
            g = g << 6 | g >> 4;
            b = b << 6 | b >> 4;
            a = a << 2 | a;
            a = a << 4 | a;
            a = a << 8 | a;

            BH_ColorSetRGBA16(value, r, g, b, a);
        }
        break;
    }

    /* Fix alpha, if format doesn't support alpha channel */
    if (format & BH_BITMAP_NOALPHA)
        value->data.rgba.a = 0xFFFF;
}


static size_t bestPaletteIndex(uint8_t r,
                               uint8_t g,
                               uint8_t b,
                               uint8_t a,
                               const uint32_t *palette,
                               size_t paletteSize)
{
    uint32_t bestError = -1;
    size_t i, bestIndex = 0;

    for (i = 0; i < paletteSize; ++i) {
        int32_t dr, dg, db, da;
        uint32_t currentError;

        dr = (int32_t)r - (palette[i] >> 16 & 0xFF);
        dg = (int32_t)g - (palette[i] >> 8 & 0xFF);
        db = (int32_t)b - (palette[i] & 0xFF);
        da = (int32_t)a - (palette[i] >> 24 & 0xFF);

        currentError = dr * dr + dg * dg + db * db + da * da;
        if (currentError < bestError)
        {
            bestError = currentError;
            bestIndex = i;
        }
    }

    return bestIndex;
}


static void setBitmapColor(void *data,
                           void *palette,
                           int format,
                           const BH_Color *value,
                           int x)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            setBitmapIndex(data, format, x, bestPaletteIndex(r, g, b, a, palette, 1));
        }
        break;

    case BH_BITMAP_INDEX2:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            setBitmapIndex(data, format, x, bestPaletteIndex(r, g, b, a, palette, 4));
        }
        break;

    case BH_BITMAP_INDEX4:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            setBitmapIndex(data, format, x, bestPaletteIndex(r, g, b, a, palette, 16));
        }
        break;

    case BH_BITMAP_INDEX8:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            setBitmapIndex(data, format, x, bestPaletteIndex(r, g, b, a, palette, 256));
        }
        break;

    case BH_BITMAP_GRAY8:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            *(uint8_t *)data = r;
        }
        break;

    case BH_BITMAP_GRAY16:
        {
            uint16_t r, g, b, a;

            BH_ColorRGBA16(value, &r, &g, &b, &a);
            *(uint16_t *)data = r;
        }
        break;

    case BH_BITMAP_RGBA32:
        {
            uint8_t r, g, b, a;

            BH_ColorRGBA8(value, &r, &g, &b, &a);
            if (format & BH_BITMAP_NOALPHA)
                a = 0xFF;

            *(uint32_t *)data = (uint32_t)r << 16 | (uint32_t)g << 8 |
                                (uint32_t)b | (uint32_t)a << 24;
        }
        break;

    case BH_BITMAP_RGBA64:
        {
            uint16_t r, g, b, a;

            BH_ColorRGBA16(value, &r, &g, &b, &a);
            if (format & BH_BITMAP_NOALPHA)
                a = 0xFFFF;

            *(uint64_t *)data = (uint64_t)r << 32 | (uint64_t)g << 16 |
                                (uint64_t)b | (uint64_t)a << 48;
        }
        break;

    case BH_BITMAP_RGB565:
        {
            uint8_t r, g, b, a;
            uint16_t color;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA8(value, &r, &g, &b, &a);
            color = 0;
            color |= (r >> 3) << bitOrder565[isBGR][0];
            color |= (g >> 2) << bitOrder565[isBGR][1];
            color |= (b >> 3) << bitOrder565[isBGR][2];

            *(uint16_t *)(data) = color;
        }
        break;

    case BH_BITMAP_RGB888:
        {
            uint8_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA8(value, &r, &g, &b, &a);
            ((uint8_t *)data)[unitOrderRGB[isBGR][0]] = r;
            ((uint8_t *)data)[unitOrderRGB[isBGR][1]] = g;
            ((uint8_t *)data)[unitOrderRGB[isBGR][2]] = b;
        }
        break;

    case BH_BITMAP_RGBA8888:
        {
            uint8_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA8(value, &r, &g, &b, &a);
            if (format & BH_BITMAP_NOALPHA)
                a = 0xFF;

            ((uint8_t *)data)[unitOrderRGBA[isBGR][0]] = r;
            ((uint8_t *)data)[unitOrderRGBA[isBGR][1]] = g;
            ((uint8_t *)data)[unitOrderRGBA[isBGR][2]] = b;
            ((uint8_t *)data)[unitOrderRGBA[isBGR][3]] = a;
        }
        break;

    case BH_BITMAP_RGB161616:
        {
            uint16_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA16(value, &r, &g, &b, &a);
            ((uint16_t *)data)[unitOrderRGB[isBGR][0]] = r;
            ((uint16_t *)data)[unitOrderRGB[isBGR][1]] = g;
            ((uint16_t *)data)[unitOrderRGB[isBGR][2]] = b;
        }
        break;

    case BH_BITMAP_RGBA16161616:
        {
            uint16_t r, g, b, a;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA16(value, &r, &g, &b, &a);
            if (format & BH_BITMAP_NOALPHA)
                a = 0xFFFF;

            ((uint16_t *)data)[unitOrderRGBA[isBGR][0]] = r;
            ((uint16_t *)data)[unitOrderRGBA[isBGR][1]] = g;
            ((uint16_t *)data)[unitOrderRGBA[isBGR][2]] = b;
            ((uint16_t *)data)[unitOrderRGBA[isBGR][3]] = a;
        }
        break;

    case BH_BITMAP_RGBA1010102:
        {
            uint16_t r, g, b, a;
            uint32_t color;
            int isBGR;

            isBGR = (format & BH_BITMAP_BGR) > 0;
            BH_ColorRGBA16(value, &r, &g, &b, &a);
            if (format & BH_BITMAP_NOALPHA)
                a = 0xFFFF;

            color = 0;
            color |= (r >> 6) << bitOrder1010102[isBGR][0];
            color |= (g >> 6) << bitOrder1010102[isBGR][1];
            color |= (b >> 6) << bitOrder1010102[isBGR][2];
            color |= (a >> 10) << bitOrder1010102[isBGR][3];

            *(uint32_t *)data = color;
        }
        break;
    }
}


static void *rowAt(void *data,
                   int format,
                   int step,
                   int x)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1:
        return (uint8_t *)data + x / 8;

    case BH_BITMAP_INDEX2:
        return (uint8_t *)data + x / 4;

    case BH_BITMAP_INDEX4:
        return (uint8_t *)data + x / 2;

    default:
        return (uint8_t *)data + step * x;
    }
}


static size_t calculateStride(int format,
                              int width)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1: return (width + 7) / 8;
    case BH_BITMAP_INDEX2: return (width + 3) / 4;
    case BH_BITMAP_INDEX4: return (width + 1) / 2;
    case BH_BITMAP_INDEX8: return width * calculateStep(format);
    }
    return width * calculateStep(format);
}


static int isPaletteNeeded(int format)
{
    switch (format)
    {
    case BH_BITMAP_INDEX1:
    case BH_BITMAP_INDEX2:
    case BH_BITMAP_INDEX4:
    case BH_BITMAP_INDEX8:
        return 1;
    }

    return 0;
}


static size_t calculateTrailer(int format)
{
    switch (format & 0x0FFF)
    {
    case BH_BITMAP_INDEX1: return sizeof(uint32_t) * 2;
    case BH_BITMAP_INDEX2: return sizeof(uint32_t) * 4;
    case BH_BITMAP_INDEX4: return sizeof(uint32_t) * 16;
    case BH_BITMAP_INDEX8: return sizeof(uint32_t) * 256;
    }
    return 0;
}


/* Public functions */
BH_Bitmap *BH_BitmapNew(int width,
                        int height,
                        int format,
                        int flags,
                        void *data,
                        void *palette)
{
    BH_Bitmap *result;
    int needPalette;
    size_t header, body, trailer, stride, step;

    /* Unset internal flags */
    flags &= ~BH_BITMAP_FLAG_EXT_DATA;
    flags &= ~BH_BITMAP_FLAG_EXT_PALETTE;

    /* Calculate size of the bitmap with headers */
    step = calculateStep(format);
    stride = calculateStride(format, width);
    needPalette = isPaletteNeeded(format);

    if (flags & BH_BITMAP_FLAG_ALIGN32)
        stride = (stride + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);

    header = sizeof(*result);
    header = (header + (sizeof(uint64_t) - 1)) & ~(sizeof(uint64_t) - 1);
    body = (stride * height + (sizeof(uint32_t) - 1)) & ~(sizeof(uint32_t) - 1);
    trailer = calculateTrailer(format);

    /* Adjust body and trailer size if ext data or palette is provided */
    if (palette)
    {
        flags |= BH_BITMAP_FLAG_EXT_PALETTE;
        trailer = 0;
    }

    if (data)
    {
        flags |= BH_BITMAP_FLAG_EXT_DATA;
        body = 0;
    }

    /* Allocate and setup bitmap data */
    result = malloc(header + body + trailer);
    if (!result)
        return NULL;

    if (!data)
        data = (uint8_t *)result + header;

    if (!palette && needPalette)
        palette = (uint8_t *)result + header + body;

    result->width = width;
    result->height = height;
    result->format = format;
    result->flags = flags;
    result->step = step;
    result->stride = stride;
    result->data = data;
    result->palette = palette;

    return result;
}


void BH_BitmapFree(BH_Bitmap *bitmap)
{
    free(bitmap);
}


void BH_BitmapColor(const BH_Bitmap *bitmap,
                    int x,
                    int y,
                    BH_Color *value)
{
    bitmapColor(BH_BitmapAt(bitmap, x, y), bitmap->palette, bitmap->format, value, x);
}

void BH_BitmapSetColor(BH_Bitmap *bitmap,
                       int x,
                       int y,
                       const BH_Color *value)
{
    setBitmapColor(BH_BitmapAt(bitmap, x, y), bitmap->palette, bitmap->format, value, x);
}


BH_Bitmap *BH_BitmapCopy(BH_Bitmap *bitmap,
                         int x,
                         int y,
                         int width,
                         int height,
                         int shallow)
{
    BH_Bitmap *result;
    int i, j;

    /* Check for bogus width and height */
    if (width < 0 || height < 0)
        return NULL;

    /* Shallow copy can't go out of bounds of the source bitmap */
    if (shallow)
    {
        if (x < 0 || x > bitmap->width || y < 0 || y > bitmap->height)
            return NULL;

        if (width < 0 || width > bitmap->width - x ||
            height < 0 || height > bitmap->height - y)
            return NULL;

        result = BH_BitmapNew(width, height, bitmap->format, bitmap->flags,
                              BH_BitmapAt(bitmap, x, y), bitmap->palette);
        result->stride = bitmap->stride;

        return result;
    }

    /* Deep copy of the bitmap */
    result = BH_BitmapNew(width, height, bitmap->format, bitmap->flags, NULL, NULL);
    if (!result)
        return NULL;

    /* Copy the palette if neccesery */
    if (result->palette)
        memcpy(result->palette, bitmap->palette, sizeof(uint32_t) * 256);

    for (j = 0; j < height; ++j)
    {
        for (i = 0; i < width; ++i)
        {
            BH_Color color;
            memset(&color, 0, sizeof(color));


            if (i + x >= 0 && i + x < bitmap->width &&
                j + y >= 0 && j + y < bitmap->height)
                BH_BitmapColor(bitmap, i + x, j + y, &color);

            BH_BitmapSetColor(result, i, j, &color);
        }
    }

    return result;
}


uint8_t BH_BitmapIndex(const BH_Bitmap *bitmap,
                       int x,
                       int y)
{
    return bitmapIndex(BH_BitmapAt(bitmap, x, y), bitmap->format, x);
}


void BH_BitmapSetIndex(BH_Bitmap *bitmap,
                       int x,
                       int y,
                       uint8_t index)
{
    setBitmapIndex(BH_BitmapAt(bitmap, x, y), bitmap->format, x, index);
}


void *BH_BitmapScanline(const BH_Bitmap *bitmap,
                        int y)
{
    return bitmap->data + y * bitmap->stride;
}


void *BH_BitmapAt(const BH_Bitmap *bitmap,
                  int x,
                  int y)
{
    return rowAt(BH_BitmapScanline(bitmap, y), bitmap->format, bitmap->step, x);
}


int BH_BitmapWidth(BH_Bitmap *bitmap)
{
    return bitmap->width;
}


int BH_BitmapHeight(BH_Bitmap *bitmap)
{
    return bitmap->height;
}


int BH_BitmapFormat(BH_Bitmap *bitmap)
{
    return bitmap->format;
}


size_t BH_BitmapStride(BH_Bitmap *bitmap)
{
    return bitmap->stride;
}


void *BH_BitmapData(BH_Bitmap *bitmap)
{
    return bitmap->data;
}


void *BH_BitmapPalette(BH_Bitmap *bitmap)
{
    return bitmap->palette;
}


int BH_BitmapFlags(BH_Bitmap *bitmap)
{
    return bitmap->flags;
}


void BH_BitmapConvertRow(void *src,
                         int srcFormat,
                         void *srcPalette,
                         void *dest,
                         int destFormat,
                         void *destPalette,
                         size_t count)
{
    size_t srcStep, destStep, x;
    srcStep = calculateStep(srcFormat);
    destStep = calculateStep(destFormat);

    for (x = 0; count; --count, ++x)
    {
        void *srcAt, *destAt;
        BH_Color data;

        srcAt = rowAt(src, srcFormat, srcStep, x);
        destAt = rowAt(dest, destFormat, destStep, x);
        bitmapColor(srcAt, srcPalette, srcFormat, &data, x);
        setBitmapColor(destAt, destPalette, destFormat, &data, x);
    }
}
