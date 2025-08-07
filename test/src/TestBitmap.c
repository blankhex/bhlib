#include <BH/Bitmap.h>
#include <BH/Color.h>
#include <BH/IO.h>
#include <BH/Unit.h>


BH_UNIT_TEST(RoundTrip)
{
    size_t i, flag, format;

    uint16_t data[][4] =
    {
        {0,     0,     0,     65535},
        {0,     0,     65535, 65535},
        {0,     65535, 0,     65535},
        {65535, 0,     0,     65535},
        {0,     65535, 65535, 65535},
        {65535, 0,     65535, 65535},
        {65535, 65535, 0,     65535},
        {65535, 65535, 65535, 65535},
        {0,     0,     0,     0},
        {0,     0,     65535, 0},
        {0,     65535, 0,     0},
        {65535, 0,     0,     0},
        {0,     65535, 65535, 0},
        {65535, 0,     65535, 0},
        {65535, 65535, 0,     0},
        {65535, 65535, 65535, 0},
    };

    uint16_t formats[] =
    {
        BH_BITMAP_RGBA32,
        BH_BITMAP_RGBA64,
        BH_BITMAP_RGB888,
        BH_BITMAP_RGBA8888,
        BH_BITMAP_RGB161616,
        BH_BITMAP_RGBA16161616,
        BH_BITMAP_RGB565,
        BH_BITMAP_RGBA1010102,
        BH_BITMAP_RGBA8888 | BH_BITMAP_NOALPHA,
        BH_BITMAP_RGBA16161616 | BH_BITMAP_NOALPHA,
        BH_BITMAP_RGBA1010102 | BH_BITMAP_NOALPHA,
    };

    for (format = 0; format < sizeof(formats) / sizeof(uint16_t); ++format)
    {
        for (i = 0; i < 16; ++i)
        {
            BH_Color source, destination;
            uint64_t temp;

            temp = 0;
            BH_ColorSetRGBA16(&source, data[i][0], data[i][1], data[i][2],
                                        data[i][3]);
            BH_BitmapConvertRow(&source.data, BH_BITMAP_RGBA16161616, NULL,
                                &temp, formats[format], NULL, 1);
            BH_BitmapConvertRow(&temp, formats[format], NULL, &destination.data, 
                                BH_BITMAP_RGBA16161616, NULL, 1);

            BH_VERIFY(source.data.rgba.r == destination.data.rgba.r);
            BH_VERIFY(source.data.rgba.g == destination.data.rgba.g);
            BH_VERIFY(source.data.rgba.b == destination.data.rgba.b);

            if (formats[format] == BH_BITMAP_RGB888 ||
                formats[format] == BH_BITMAP_RGB161616 ||
                formats[format] == BH_BITMAP_RGB565 ||
                formats[format] & BH_BITMAP_NOALPHA)
                BH_VERIFY(destination.data.rgba.a == 65535);
            else
                BH_VERIFY(source.data.rgba.a == destination.data.rgba.a);
        }
    }

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(RoundTrip);

    return BH_UnitRun();
}
