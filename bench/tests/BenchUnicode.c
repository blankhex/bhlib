#include <BH/Bench.h>
#include <BH/Unicode.h>


#define BUF_SIZE 8


static char buffer[BUF_SIZE];
static size_t result;
static uint32_t testUnitLower = 'a';
static uint32_t testUnitUpper = 'A';
static uint32_t testUnitLatin1 = 0x00E9;
static uint32_t testUnitBMP = 0x2603;
static uint32_t testUnitSMP = 0x1F600;

static const char utf8_a[]     = { 'a' };
static const char utf8_e_acute[] = { 0xC3, 0xA9 };
static const char utf8_snowman[] = { 0xE2, 0x98, 0x83 };
static const char utf8_grin[]    = { 0xF0, 0x9F, 0x98, 0x80 };
static const char utf16_a_le[]     = { 'a', 0x00 };
static const char utf16_e_acute_le[] = { 0xE9, 0x00 };
static const char utf16_snowman_le[] = { 0x03, 0x26 };
static const char utf16_grin_le[]    = { 0xD8, 0x3D, 0xDE, 0x00 };
static const char utf16_a_be[]     = { 0x00, 'a' };
static const char utf16_e_acute_be[] = { 0x00, 0xE9 };
static const char utf16_snowman_be[] = { 0x26, 0x03 };
static const char utf16_grin_be[]    = { 0x3D, 0xD8, 0x00, 0xDE };
static const char utf32_a_le[]     = { 'a', 0x00, 0x00, 0x00 };
static const char utf32_e_acute_le[] = { 0xE9, 0x00, 0x00, 0x00 };
static const char utf32_snowman_le[] = { 0x03, 0x26, 0x00, 0x00 };
static const char utf32_grin_le[]    = { 0x00, 0xF0, 0x01, 0x00 };
static const char utf32_a_be[]     = { 0x00, 0x00, 0x00, 'a' };
static const char utf32_e_acute_be[] = { 0x00, 0x00, 0x00, 0xE9 };
static const char utf32_snowman_be[] = { 0x00, 0x00, 0x26, 0x03 };
static const char utf32_grin_be[]    = { 0x00, 0x01, 0xF0, 0x00 };


BH_BENCH_TEST(Lower)
{
    while (BH_BenchIter(state))
    {
        uint32_t lower;
        lower = BH_UnicodeLower(testUnitUpper);
        BH_BenchDoNotOptimize(lower);
    }
}


BH_BENCH_TEST(Upper)
{
    while (BH_BenchIter(state))
    {
        uint32_t upper;
        upper = BH_UnicodeUpper(testUnitLower);
        BH_BenchDoNotOptimize(upper);
    }
}


BH_BENCH_TEST(DecodeUtf8Ascii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf8(utf8_a, 1, &testUnitLower);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLower);
    }
}


BH_BENCH_TEST(DecodeUtf8Latin1)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf8(utf8_e_acute, 2, &testUnitLatin1);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLatin1);
    }
}


BH_BENCH_TEST(DecodeUtf8BMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf8(utf8_snowman, 3, &testUnitBMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitBMP);
    }
}


BH_BENCH_TEST(DecodeUtf8SMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf8(utf8_grin, 4, &testUnitSMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitSMP);
    }
}


BH_BENCH_TEST(EncodeUtf8Ascii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf8(testUnitLower, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf8Latin1)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf8(testUnitLatin1, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf8BMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf8(testUnitBMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf8SMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf8(testUnitSMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(DecodeUtf16LEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16LE(utf16_a_le, 2, &testUnitLower);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLower);
    }
}


BH_BENCH_TEST(DecodeUtf16LELatin1)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16LE(utf16_e_acute_le, 2, &testUnitLatin1);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLatin1);
    }
}


BH_BENCH_TEST(DecodeUtf16LEBMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16LE(utf16_snowman_le, 2, &testUnitBMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitBMP);
    }
}


BH_BENCH_TEST(DecodeUtf16LESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16LE(utf16_grin_le, 4, &testUnitSMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitSMP);
    }
}


BH_BENCH_TEST(DecodeUtf16BEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16BE(utf16_a_be, 2, &testUnitLower);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLower);
    }
}


BH_BENCH_TEST(DecodeUtf16BESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf16BE(utf16_grin_be, 4, &testUnitSMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitSMP);
    }
}


BH_BENCH_TEST(EncodeUtf16LEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf16LE(testUnitLower, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf16LESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf16LE(testUnitSMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf16BEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf16BE(testUnitLower, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf16BESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf16BE(testUnitSMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(DecodeUtf32LEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf32LE(utf32_a_le, 4, &testUnitLower);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLower);
    }
}


BH_BENCH_TEST(DecodeUtf32LESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf32LE(utf32_grin_le, 4, &testUnitSMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitSMP);
    }
}


BH_BENCH_TEST(DecodeUtf32BEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf32BE(utf32_a_be, 4, &testUnitLower);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitLower);
    }
}


BH_BENCH_TEST(DecodeUtf32BESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeDecodeUtf32BE(utf32_grin_be, 4, &testUnitSMP);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(testUnitSMP);
    }
}


BH_BENCH_TEST(EncodeUtf32LEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf32LE(testUnitLower, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf32LESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf32LE(testUnitSMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf32BEAscii)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf32BE(testUnitLower, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


BH_BENCH_TEST(EncodeUtf32BESMP)
{
    while (BH_BenchIter(state))
    {
        result = BH_UnicodeEncodeUtf32BE(testUnitSMP, buffer);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Lower);
    BH_BENCH_ADD(Upper);
    BH_BENCH_ADD(DecodeUtf8Ascii);
    BH_BENCH_ADD(DecodeUtf8Latin1);
    BH_BENCH_ADD(DecodeUtf8BMP);
    BH_BENCH_ADD(DecodeUtf8SMP);
    BH_BENCH_ADD(EncodeUtf8Ascii);
    BH_BENCH_ADD(EncodeUtf8Latin1);
    BH_BENCH_ADD(EncodeUtf8BMP);
    BH_BENCH_ADD(EncodeUtf8SMP);
    BH_BENCH_ADD(DecodeUtf16LEAscii);
    BH_BENCH_ADD(DecodeUtf16LELatin1);
    BH_BENCH_ADD(DecodeUtf16LEBMP);
    BH_BENCH_ADD(DecodeUtf16LESMP);
    BH_BENCH_ADD(DecodeUtf16BEAscii);
    BH_BENCH_ADD(DecodeUtf16BESMP);
    BH_BENCH_ADD(EncodeUtf16LEAscii);
    BH_BENCH_ADD(EncodeUtf16LESMP);
    BH_BENCH_ADD(EncodeUtf16BEAscii);
    BH_BENCH_ADD(EncodeUtf16BESMP);
    BH_BENCH_ADD(DecodeUtf32LEAscii);
    BH_BENCH_ADD(DecodeUtf32LESMP);
    BH_BENCH_ADD(DecodeUtf32BEAscii);
    BH_BENCH_ADD(DecodeUtf32BESMP);
    BH_BENCH_ADD(EncodeUtf32LEAscii);
    BH_BENCH_ADD(EncodeUtf32LESMP);
    BH_BENCH_ADD(EncodeUtf32BEAscii);
    BH_BENCH_ADD(EncodeUtf32BESMP);

    return BH_BenchRun();
}
