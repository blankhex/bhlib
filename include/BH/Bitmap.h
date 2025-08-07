#ifndef BH_BITMAP_H
#define BH_BITMAP_H


#include "Common.h"
#include "Color.h"


typedef struct BH_Bitmap BH_Bitmap;


#define BH_BITMAP_PREMULT           0x1000
#define BH_BITMAP_NOALPHA           0x2000

#define BH_BITMAP_INDEX1            0x0000
#define BH_BITMAP_INDEX1_LSB        0x0001
#define BH_BITMAP_INDEX2            0x0002
#define BH_BITMAP_INDEX2_LSB        0x0003
#define BH_BITMAP_INDEX4            0x0004
#define BH_BITMAP_INDEX4_LSB        0x0005
#define BH_BITMAP_INDEX8            0x0006
#define BH_BITMAP_GRAY8             0x0007
#define BH_BITMAP_GRAY16            0x0008
#define BH_BITMAP_RGBA32            0x0009
#define BH_BITMAP_RGBA64            0x000A
#define BH_BITMAP_RGB565            0x000B
#define BH_BITMAP_BGR565            0x000C
#define BH_BITMAP_RGB888            0x000D
#define BH_BITMAP_BGR888            0x000E
#define BH_BITMAP_RGBA8888          0x000F
#define BH_BITMAP_BGRA8888          0x0010
#define BH_BITMAP_ARGB8888          0x0011
#define BH_BITMAP_ABGR8888          0x0012
#define BH_BITMAP_RGB161616         0x0013
#define BH_BITMAP_BGR161616         0x0014
#define BH_BITMAP_RGBA16161616      0x0015
#define BH_BITMAP_BGRA16161616      0x0016
#define BH_BITMAP_ARGB16161616      0x0017
#define BH_BITMAP_ABGR16161616      0x0018
#define BH_BITMAP_RGBA1010102       0x0019
#define BH_BITMAP_BGRA1010102       0x001A
#define BH_BITMAP_ARGB2101010       0x001B
#define BH_BITMAP_ABGR2101010       0x001C

#define BH_BITMAP_FLAG_ALIGN32      0x0001
#define BH_BITMAP_FLAG_EXT_DATA     0x0002
#define BH_BITMAP_FLAG_EXT_PALETTE  0x0004


BH_Bitmap *BH_BitmapNew(uint32_t width,
                        uint32_t height,
                        int format,
                        int flags,
                        void *data,
                        BH_Color *palette);


void BH_BitmapFree(BH_Bitmap *bitmap);


void BH_BitmapColor(const BH_Bitmap *bitmap,
                    uint32_t x,
                    uint32_t y,
                    BH_Color *value);


void BH_BitmapSetColor(BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y,
                       const BH_Color *value);


uint8_t BH_BitmapIndex(const BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y);


void BH_BitmapSetIndex(BH_Bitmap *bitmap,
                       uint32_t x,
                       uint32_t y,
                       uint8_t index);


BH_Bitmap *BH_BitmapCopy(BH_Bitmap *bitmap,
                         uint32_t x,
                         uint32_t y,
                         uint32_t width,
                         uint32_t height,
                         int shallow);


void *BH_BitmapScanline(const BH_Bitmap *bitmap,
                        uint32_t y);


void *BH_BitmapAt(const BH_Bitmap *bitmap,
                  uint32_t x,
                  uint32_t y);


uint32_t BH_BitmapWidth(BH_Bitmap *bitmap);


uint32_t BH_BitmapHeight(BH_Bitmap *bitmap);


int BH_BitmapFormat(BH_Bitmap *bitmap);


size_t BH_BitmapStride(BH_Bitmap *bitmap);


void *BH_BitmapData(BH_Bitmap *bitmap);


void *BH_BitmapPalette(BH_Bitmap *bitmap);


int BH_BitmapFlags(BH_Bitmap *bitmap);


void BH_BitmapConvertRow(void *src,
                         int srcFormat,
                         const BH_Color *srcPalette,
                         void *dest,
                         int destFormat,
                         const BH_Color *destPalette,
                         size_t count);


#endif /* BH_BITMAP_H */
