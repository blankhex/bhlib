#include "BH/Common.h"
#include <BH/Bitmap.h>
#include <stdlib.h>
#include <string.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


#define TYPE_PACKED     0x0000
#define TYPE_INDEX      0x0100
#define TYPE_ARRAY      0x0200


#define TYPE_PACKED8    (0x00 | TYPE_PACKED)
#define TYPE_PACKED16   (0x01 | TYPE_PACKED)
#define TYPE_PACKED32   (0x02 | TYPE_PACKED)
#define TYPE_PACKED64   (0x03 | TYPE_PACKED)
#define TYPE_INDEX1     (0x00 | TYPE_INDEX)
#define TYPE_INDEX2     (0x01 | TYPE_INDEX)
#define TYPE_INDEX4     (0x02 | TYPE_INDEX)
#define TYPE_INDEX8     (0x03 | TYPE_INDEX)
#define TYPE_ARRAY8     (0x00 | TYPE_ARRAY)
#define TYPE_ARRAY16    (0x01 | TYPE_ARRAY)


typedef struct FormatInfo
{
    int type;
    size_t channels;
    uint16_t masks[4];
    uint8_t shifts[8];
    size_t size;
} FormatInfo;

struct BH_Bitmap
{
    uint32_t width;
    uint32_t height;
    int format;
    const FormatInfo *formatInfo;
    int flags;
    size_t stride;
    uint8_t *data;
    BH_Color *palette;
};


const static struct FormatInfo formats[] =
{
    /* BH_BITMAP_INDEX1 */
    {TYPE_INDEX1, 7, {0x0001}, {7, 6, 5, 4, 3, 2, 1, 0}, 0},
    /* BH_BITMAP_INDEX1_LSB */
    {TYPE_INDEX1, 7, {0x0001}, {0, 1, 2, 3, 4, 5, 6, 7}, 0},
    /* BH_BITMAP_INDEX2 */
    {TYPE_INDEX2, 3, {0x0003}, {3, 2, 1, 0}, 0},
    /* BH_BITMAP_INDEX2_LSB */
    {TYPE_INDEX2, 3, {0x0003}, {0, 1, 2, 3}, 0},
    /* BH_BITMAP_INDEX4 */
    {TYPE_INDEX4, 1, {0x000F}, {1, 0}, 0},
    /* BH_BITMAP_INDEX4_LSB */
    {TYPE_INDEX4, 1, {0x000F}, {0, 1}, 0},
    /* BH_BITMAP_INDEX8 */
    {TYPE_INDEX8, 0, {0x00FF}, {0}, 1},
    /* BH_BITMAP_GRAY8 */
    {TYPE_PACKED8, 1, {0x00FF}, {0}, 1},
    /* BH_BITMAP_GRAY16 */
    {TYPE_PACKED16, 1, {0xFFFF}, {0}, 2},
    /* BH_BITMAP_RGBA32 */
    {TYPE_PACKED32, 4, {0x00FF, 0x00FF, 0x00FF, 0x00FF}, {16, 8, 0, 24}, 4},
    /* BH_BITMAP_RGBA64 */
    {TYPE_PACKED64, 4, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, {32, 16, 0, 48}, 8},
    /* BH_BITMAP_RGB565 */
    {TYPE_PACKED16, 3, {0x001F, 0x003F, 0x001F}, {11, 5, 0}, 2},
    /* BH_BITMAP_BGR565 */
    {TYPE_PACKED16, 3, {0x001F, 0x003F, 0x001F}, {0, 5, 11}, 2},
    /* BH_BITMAP_RGBA5551 */
    {TYPE_PACKED16, 4, {0x001F, 0x001F, 0x001F, 0x0001}, {11, 6, 1, 0}, 2},
    /* BH_BITMAP_BGRA5551 */
    {TYPE_PACKED16, 4, {0x001F, 0x001F, 0x001F, 0x0001}, {1, 6, 11, 0}, 2},
    /* BH_BITMAP_ARGB1555 */
    {TYPE_PACKED16, 4, {0x001F, 0x001F, 0x001F, 0x0001}, {10, 5, 0, 15}, 2},
    /* BH_BITMAP_ABGR1555 */
    {TYPE_PACKED16, 4, {0x001F, 0x001F, 0x001F, 0x0001}, {0, 5, 10, 15}, 2},
    /* BH_BITMAP_RGB888 */
    {TYPE_ARRAY8, 3, {0x00FF, 0x00FF, 0x00FF}, {0, 1, 2}, 3},
    /* BH_BITMAP_BGR888 */
    {TYPE_ARRAY8, 3, {0x00FF, 0x00FF, 0x00FF}, {2, 1, 0}, 3},
    /* BH_BITMAP_RGBA8888 */
    {TYPE_ARRAY8, 4, {0x00FF, 0x00FF, 0x00FF, 0x00FF}, {0, 1, 2, 3}, 4},
    /* BH_BITMAP_BGRA8888 */
    {TYPE_ARRAY8, 4, {0x00FF, 0x00FF, 0x00FF, 0x00FF}, {2, 1, 0, 3}, 4},
    /* BH_BITMAP_ARGB8888 */
    {TYPE_ARRAY8, 4, {0x00FF, 0x00FF, 0x00FF, 0x00FF}, {1, 2, 3, 0}, 4},
    /* BH_BITMAP_ABGR8888 */
    {TYPE_ARRAY8, 4, {0x00FF, 0x00FF, 0x00FF, 0x00FF}, {3, 2, 1, 0}, 4},
    /* BH_BITMAP_RGB161616 */
    {TYPE_ARRAY16, 3, {0xFFFF, 0xFFFF, 0xFFFF}, {0, 1, 2}, 6},
    /* BH_BITMAP_BGR161616 */
    {TYPE_ARRAY16, 3, {0xFFFF, 0xFFFF, 0xFFFF}, {2, 1, 0}, 6},
    /* BH_BITMAP_RGBA16161616 */
    {TYPE_ARRAY16, 4, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, {0, 1, 2, 3}, 8},
    /* BH_BITMAP_BGRA16161616 */
    {TYPE_ARRAY16, 4, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, {2, 1, 0, 3}, 8},
    /* BH_BITMAP_ARGB16161616 */
    {TYPE_ARRAY16, 4, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, {1, 2, 3, 0}, 8},
    /* BH_BITMAP_ABGR16161616 */
    {TYPE_ARRAY16, 4, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, {3, 2, 1, 0}, 8},
    /* BH_BITMAP_RGBA1010102 */
    {TYPE_PACKED32, 4, {0x03FF, 0x03FF, 0x03FF, 0x0003}, {22, 12, 2, 0}, 4},
    /* BH_BITMAP_BGRA1010102 */
    {TYPE_PACKED32, 4, {0x03FF, 0x03FF, 0x03FF, 0x0003}, {2, 12, 22, 0}, 4},
    /* BH_BITMAP_ARGB2101010 */
    {TYPE_PACKED32, 4, {0x03FF, 0x03FF, 0x03FF, 0x0003}, {20, 10, 0, 30}, 4},
    /* BH_BITMAP_ABGR2101010 */
    {TYPE_PACKED32, 4, {0x03FF, 0x03FF, 0x03FF, 0x0003}, {0, 10, 20, 30}, 4},
};


static uint16_t normilize(uint16_t mask,
                          uint16_t value)
{
    return ((uint32_t)(value & mask) * 65535) / mask;
}


static uint16_t denormilize(uint16_t mask,
                            uint16_t value)
{
    return (((uint32_t)(value * mask)) / 65535) & mask;
}


static size_t bestPaletteIndex(BH_Color *color,
                               const BH_Color *palette,
                               const FormatInfo *formatInfo)
{
    uint32_t bestError = -1;
    size_t i, bestIndex = 0, paletteSize;

    switch (formatInfo->type)
    {
    case TYPE_INDEX1: paletteSize = 2; break;
    case TYPE_INDEX2: paletteSize = 4; break;
    case TYPE_INDEX4: paletteSize = 16; break;
    case TYPE_INDEX8: paletteSize = 256; break;
    }

    for (i = 0; i < paletteSize; ++i) {
        int32_t delta[4];
        uint32_t currentError;

        switch (palette[i].type)
        {
        case BH_COLOR_TYPE_HSLA: BH_ColorToHSLA(color, color); break;
        case BH_COLOR_TYPE_HSVA: BH_ColorToHSVA(color, color); break;
        case BH_COLOR_TYPE_RGBA: BH_ColorToRGBA(color, color); break;
        }

        delta[0] = (int32_t)color->data.channel[0] - palette[i].data.channel[0];
        delta[1] = (int32_t)color->data.channel[1] - palette[i].data.channel[1];
        delta[2] = (int32_t)color->data.channel[2] - palette[i].data.channel[2];
        delta[3] = (int32_t)color->data.channel[3] - palette[i].data.channel[3];

        currentError = delta[0] * delta[0] + delta[1] * delta[1] +
                       delta[2] * delta[2] + delta[3] * delta[3];

        if (currentError < bestError)
        {
            bestError = currentError;
            bestIndex = i;
        }
    }

    return bestIndex;
}


static void readPacked(const FormatInfo *formatInfo,
                       void *data,
                       BH_Color *value)
{
    uint64_t raw;

    switch (formatInfo->type)
    {
    case TYPE_PACKED8: raw = *(uint8_t *)data; break;
    case TYPE_PACKED16: raw = *(uint16_t *)data; break;
    case TYPE_PACKED32: raw = *(uint32_t *)data; break;
    case TYPE_PACKED64: raw = *(uint64_t *)data; break;
    }

    switch (formatInfo->channels)
    {
    case 4: value->data.channel[3] = normilize(formatInfo->masks[3], raw >> formatInfo->shifts[3]);
    case 3: value->data.channel[2] = normilize(formatInfo->masks[2], raw >> formatInfo->shifts[2]);
    case 2: value->data.channel[1] = normilize(formatInfo->masks[1], raw >> formatInfo->shifts[1]);
    case 1: value->data.channel[0] = normilize(formatInfo->masks[0], raw >> formatInfo->shifts[0]);
    }
}


static void writePacked(const FormatInfo *formatInfo,
                        void *data,
                        BH_Color *value)
{
    uint64_t raw;

    raw = 0;
    switch (formatInfo->channels)
    {
    case 4: raw |= (uint64_t)denormilize(formatInfo->masks[3], value->data.channel[3]) << formatInfo->shifts[3];
    case 3: raw |= (uint64_t)denormilize(formatInfo->masks[2], value->data.channel[2]) << formatInfo->shifts[2];
    case 2: raw |= (uint64_t)denormilize(formatInfo->masks[1], value->data.channel[1]) << formatInfo->shifts[1];
    case 1: raw |= (uint64_t)denormilize(formatInfo->masks[0], value->data.channel[0]) << formatInfo->shifts[0];
    }

    switch (formatInfo->type)
    {
    case TYPE_PACKED8: *(uint8_t *)data = raw; break;
    case TYPE_PACKED16: *(uint16_t *)data = raw; break;
    case TYPE_PACKED32: *(uint32_t *)data = raw; break;
    case TYPE_PACKED64: *(uint64_t *)data = raw; break;
    }
}


static void readArray8(const FormatInfo *formatInfo,
                       void *data,
                       BH_Color *value)
{
    switch (formatInfo->channels)
    {
    case 4: value->data.channel[3] = normilize(formatInfo->masks[3], ((uint8_t *)data)[formatInfo->shifts[3]]);
    case 3: value->data.channel[2] = normilize(formatInfo->masks[2], ((uint8_t *)data)[formatInfo->shifts[2]]);
    case 2: value->data.channel[1] = normilize(formatInfo->masks[1], ((uint8_t *)data)[formatInfo->shifts[1]]);
    case 1: value->data.channel[0] = normilize(formatInfo->masks[0], ((uint8_t *)data)[formatInfo->shifts[0]]);
    }
}


static void writeArray8(const FormatInfo *formatInfo,
                        void *data,
                        BH_Color *value)
{
    switch (formatInfo->channels)
    {
    case 4: ((uint8_t *)data)[formatInfo->shifts[3]] = denormilize(formatInfo->masks[3], value->data.channel[3]);
    case 3: ((uint8_t *)data)[formatInfo->shifts[2]] = denormilize(formatInfo->masks[2], value->data.channel[2]);
    case 2: ((uint8_t *)data)[formatInfo->shifts[1]] = denormilize(formatInfo->masks[1], value->data.channel[1]);
    case 1: ((uint8_t *)data)[formatInfo->shifts[0]] = denormilize(formatInfo->masks[0], value->data.channel[0]);
    }
}


static void readArray16(const FormatInfo *formatInfo,
                        void *data,
                        BH_Color *value)
{
    value->type = BH_COLOR_TYPE_RGBA;
    switch (formatInfo->channels)
    {
    case 4: value->data.channel[3] = normilize(formatInfo->masks[3], ((uint16_t *)data)[formatInfo->shifts[3]]);
    case 3: value->data.channel[2] = normilize(formatInfo->masks[2], ((uint16_t *)data)[formatInfo->shifts[2]]);
    case 2: value->data.channel[1] = normilize(formatInfo->masks[1], ((uint16_t *)data)[formatInfo->shifts[1]]);
    case 1: value->data.channel[0] = normilize(formatInfo->masks[0], ((uint16_t *)data)[formatInfo->shifts[0]]);
    }
}


static void writeArray16(const FormatInfo *formatInfo,
                         void *data,
                         BH_Color *value)
{
    switch (formatInfo->channels)
    {
    case 4: ((uint16_t *)data)[formatInfo->shifts[3]] = denormilize(formatInfo->masks[3], value->data.channel[3]);
    case 3: ((uint16_t *)data)[formatInfo->shifts[2]] = denormilize(formatInfo->masks[2], value->data.channel[2]);
    case 2: ((uint16_t *)data)[formatInfo->shifts[1]] = denormilize(formatInfo->masks[1], value->data.channel[1]);
    case 1: ((uint16_t *)data)[formatInfo->shifts[0]] = denormilize(formatInfo->masks[0], value->data.channel[0]);
    }
}


static void readArray(const FormatInfo *formatInfo,
                      void *data,
                      BH_Color *value)
{
    switch (formatInfo->type)
    {
    case TYPE_ARRAY8: readArray8(formatInfo, data, value); break;
    case TYPE_ARRAY16: readArray16(formatInfo, data, value); break;
    }
}


static void writeArray(const FormatInfo *formatInfo,
                      void *data,
                      BH_Color *value)
{
    switch (formatInfo->type)
    {
    case TYPE_ARRAY8: writeArray8(formatInfo, data, value); break;
    case TYPE_ARRAY16: writeArray16(formatInfo, data, value); break;
    }
}


static uint8_t readIndex(const FormatInfo *formatInfo,
                         void *data,
                         int x)
{
    uint8_t value = *(uint8_t *)data;
    return (value >> formatInfo->shifts[x & formatInfo->channels]) & formatInfo->masks[0];
}


static void writeIndex(const FormatInfo *formatInfo,
                       void *data,
                       int x,
                       uint8_t index)
{
    uint8_t mask = ~(formatInfo->masks[0] << formatInfo->shifts[x & formatInfo->channels]);
    uint8_t value = (index & formatInfo->masks[0]) << formatInfo->shifts[x & formatInfo->channels];
    *(uint8_t *)data = (*(uint8_t *)data & mask) | value;
}


static void readData(const FormatInfo *formatInfo,
                     void *data,
                     int x,
                     BH_Color *value,
                     const BH_Color *palette)
{
    switch (formatInfo->type & 0x0F00)
    {
    case TYPE_PACKED:
        readPacked(formatInfo, data, value);
        value->type = BH_COLOR_TYPE_RGBA;
        break;

    case TYPE_INDEX:
        *value = palette[readIndex(formatInfo, data, x)];
        break;

    case TYPE_ARRAY:
        readArray(formatInfo, data, value);
        value->type = BH_COLOR_TYPE_RGBA;
        break;
    }
}


static void writeData(const FormatInfo *formatInfo,
                      void *data,
                      int x,
                      BH_Color *value,
                      const BH_Color *palette)
{
    switch (formatInfo->type & 0x0F00)
    {
    case TYPE_PACKED:
        BH_ColorToRGBA(value, value);
        writePacked(formatInfo, data, value);
        break;

    case TYPE_INDEX:
        writeIndex(formatInfo, data, x, bestPaletteIndex(value, palette, formatInfo));
        break;

    case TYPE_ARRAY:
        BH_ColorToRGBA(value, value);
        writeArray(formatInfo, data, value);
        break;
    }
}


static void *rowAt(const FormatInfo *formatInfo,
                   void *data,
                   uint32_t x)
{
    switch (formatInfo->type)
    {
    case TYPE_INDEX1: return (uint8_t *)data + x / 8;
    case TYPE_INDEX2: return (uint8_t *)data + x / 4;
    case TYPE_INDEX4: return (uint8_t *)data + x / 2;
    default: return (uint8_t *)data + formatInfo->size * x;
    }
}


static size_t calculateStride(const FormatInfo *formatInfo,
                              uint32_t width)
{
    switch (formatInfo->type)
    {
    case TYPE_INDEX1: return (width + 7) / 8;
    case TYPE_INDEX2: return (width + 3) / 4;
    case TYPE_INDEX4: return (width + 1) / 2;
    }

    if (BH_CHECK_UMUL_WRAP(formatInfo->size, width, size_t))
        return 0;

    return formatInfo->size * width;
}


static int isPaletteNeeded(const FormatInfo *formatInfo)
{
    switch (formatInfo->type)
    {
    case TYPE_INDEX1:
    case TYPE_INDEX2:
    case TYPE_INDEX4:
    case TYPE_INDEX8:
        return 1;
    }

    return 0;
}


static size_t calculateTrailer(const FormatInfo *formatInfo)
{
    switch (formatInfo->type)
    {
    case TYPE_INDEX1: return sizeof(BH_Color) * 2;
    case TYPE_INDEX2: return sizeof(BH_Color) * 4;
    case TYPE_INDEX4: return sizeof(BH_Color) * 16;
    case TYPE_INDEX8: return sizeof(BH_Color) * 256;
    }
    return 0;
}


BH_Bitmap *BH_BitmapNew(uint32_t width,
                        uint32_t height,
                        int format,
                        int flags,
                        void *data,
                        BH_Color *palette,
                        int *result)
{
    const FormatInfo *formatInfo;
    size_t header, body, allocSize, stride;
    int needPalette, code;
    BH_Bitmap *bitmap;

    bitmap = NULL;
    code = BH_OK;
    formatInfo = formats + (format & 0x0FFF);

    /* Basic checks and format validation  */
    if (width == 0 || width >= 0x7FFFFFFF ||
        height == 0 || height >= 0x7FFFFFFF ||
        (format & 0x0FFF) > sizeof(formats) / sizeof(FormatInfo))
    {
        code = BH_INVALID;
        goto done;
    }

    /* Unset internal flags */
    flags &= ~BH_BITMAP_FLAG_EXT_DATA;
    flags &= ~BH_BITMAP_FLAG_EXT_PALETTE;

    /* Calculate size of the bitmap with headers */
    stride = calculateStride(formatInfo, width);
    needPalette = isPaletteNeeded(formatInfo);

    /* Check stride overflow */
    if (!stride)
    {
        code = BH_ERROR;
        goto done;
    }

    if (flags & BH_BITMAP_FLAG_ALIGN32)
    {
        if (BH_CHECK_UADD_WRAP(stride, sizeof(uint32_t) - 1, size_t))
        {
            code = BH_ERROR;
            goto done;
        }

        stride = (stride + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);
    }

    header = sizeof(*bitmap);
    header = (header + (sizeof(uint64_t) - 1)) & ~(sizeof(uint64_t) - 1);
    allocSize = calculateTrailer(formatInfo);

    body = stride * height;
    if (BH_CHECK_UMUL_WRAP(stride, height, size_t) ||
        BH_CHECK_UADD_WRAP(body, sizeof(uint32_t) - 1, size_t))
    {
        code = BH_ERROR;
        goto done;
    }
    body = (body + (sizeof(uint32_t) - 1)) & ~(sizeof(uint32_t) - 1);

    /* Adjust body and trailer size if ext data or palette is provided */
    if (palette)
    {
        flags |= BH_BITMAP_FLAG_EXT_PALETTE;
        allocSize = 0;
    }

    if (data)
    {
        flags |= BH_BITMAP_FLAG_EXT_DATA;
        body = 0;
    }

    if (BH_CHECK_UADD_WRAP(allocSize, header, size_t) ||
        BH_CHECK_UADD_WRAP(allocSize + header, body, size_t))
    {
        code = BH_ERROR;
        goto done;
    }
    allocSize += header + body;

    /* Allocate and setup bitmap data */
    bitmap = malloc(allocSize);
    if (!bitmap)
    {
        code = BH_OOM;
        goto done;
    }

    if (!data)
        data = (uint8_t *)bitmap + header;

    if (!palette && needPalette)
        palette = (BH_Color *)((uint8_t *)bitmap + header + body);

    bitmap->width = width;
    bitmap->height = height;
    bitmap->format = format;
    bitmap->formatInfo = formatInfo;
    bitmap->flags = flags;
    bitmap->stride = stride;
    bitmap->data = data;
    bitmap->palette = palette;

done:
    if (result)
        *result = code;

    return bitmap;
}


void BH_BitmapFree(BH_Bitmap *bitmap)
{
    free(bitmap);
}


void BH_BitmapColor(const BH_Bitmap *bitmap,
                    uint32_t x,
                    uint32_t y,
                    BH_Color *value)
{
    readData(bitmap->formatInfo, BH_BitmapAt(bitmap, x, y), x, value, bitmap->palette);
    if (bitmap->format & BH_BITMAP_NOALPHA || bitmap->formatInfo->channels < 4)
        value->data.rgba.a = 65535;
}

void BH_BitmapSetColor(BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y,
                       const BH_Color *value)
{
    BH_Color tmp;
    tmp = *value;

    if (bitmap->format & BH_BITMAP_NOALPHA || bitmap->formatInfo->channels < 4)
        tmp.data.rgba.a = 65535;
    writeData(bitmap->formatInfo, BH_BitmapAt(bitmap, x, y), x, &tmp, bitmap->palette);
}


BH_Bitmap *BH_BitmapCopy(BH_Bitmap *bitmap,
                         uint32_t x,
                         uint32_t y,
                         uint32_t width,
                         uint32_t height,
                         int shallow,
                         int *result)
{
    BH_Bitmap *resultBitmap;
    uint32_t i, j;

    /* Sanity checks */
    if (!width || !height || x >= bitmap->width || y >= bitmap->height)
        return NULL;

    if (width < bitmap->width - x || height < bitmap->height - y)
        return NULL;

    /* Shallow copy can't go out of bounds of the source bitmap */
    if (shallow)
    {
        resultBitmap = BH_BitmapNew(width, height, bitmap->format, bitmap->flags,
                                    BH_BitmapAt(bitmap, x, y), bitmap->palette,
                                    result);
        resultBitmap->stride = bitmap->stride;
        return resultBitmap;
    }

    /* Deep copy of the bitmap */
    resultBitmap = BH_BitmapNew(width, height, bitmap->format, bitmap->flags,
                                NULL, NULL, result);
    if (!resultBitmap)
        return NULL;

    /* Copy the palette if neccesery */
    if (resultBitmap->palette)
        memcpy(resultBitmap->palette, bitmap->palette, sizeof(uint32_t) * 256);

    for (j = 0; j < height; ++j)
    {
        for (i = 0; i < width; ++i)
        {
            BH_Color color;
            BH_BitmapColor(bitmap, i + x, j + y, &color);
            BH_BitmapSetColor(resultBitmap, i, j, &color);
        }
    }

    return resultBitmap;
}


uint8_t BH_BitmapIndex(const BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y)
{
    return readIndex(bitmap->formatInfo, BH_BitmapAt(bitmap, x, y), x);
}


void BH_BitmapSetIndex(BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y,
                       uint8_t index)
{
    writeIndex(bitmap->formatInfo, BH_BitmapAt(bitmap, x, y), x, index);
}


void *BH_BitmapScanline(const BH_Bitmap *bitmap,
                        uint32_t y)
{
    return bitmap->data + y * bitmap->stride;
}


void *BH_BitmapAt(const BH_Bitmap *bitmap,
                  uint32_t x,
                  uint32_t y)
{
    return rowAt(bitmap->formatInfo, BH_BitmapScanline(bitmap, y), x);
}


uint32_t BH_BitmapWidth(BH_Bitmap *bitmap)
{
    return bitmap->width;
}


uint32_t BH_BitmapHeight(BH_Bitmap *bitmap)
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
                         const BH_Color *srcPalette,
                         void *dest,
                         int destFormat,
                         const BH_Color *destPalette,
                         size_t count)
{
    size_t x;
    const FormatInfo *srcInfo, *destInfo;

    srcInfo = formats + (srcFormat & 0x0FFF);
    destInfo = formats + (destFormat & 0x0FFF);

    if ((srcFormat & 0x0FFF) > sizeof(formats) / sizeof(FormatInfo))
        return;

    if ((destFormat & 0x0FFF) > sizeof(formats) / sizeof(FormatInfo))
        return;

    for (x = 0; count; --count, ++x)
    {
        void *srcAt, *destAt;
        BH_Color data;

        srcAt = rowAt(srcInfo, src, x);
        destAt = rowAt(destInfo, dest, x);
        readData(srcInfo, srcAt, x, &data, srcPalette);
        if (srcFormat & BH_BITMAP_NOALPHA || destFormat & BH_BITMAP_NOALPHA ||
            srcInfo->channels < 4 || destInfo->channels < 4)
            data.data.rgba.a = 65535;
        writeData(destInfo, destAt, x, &data, destPalette);
    }
}
