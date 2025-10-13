#include <BH/Bench.h>
#include <BH/String.h>


#define BUF_SIZE 64
static char buffer[BUF_SIZE];
static size_t actual;
static double testDouble = 1234.5678;
static int8_t testInt8s  = -128;
static int16_t testInt16s = -32768;
static int32_t testInt32s = -2147483647;
static int64_t testInt64s = -9223372036854775807LL;
static uint8_t testInt8u  = 255;
static uint16_t testInt16u = 65535;
static uint32_t testInt32u = 4294967295U;
static uint64_t testInt64u = 18446744073709551615ULL;
static const char *strDouble = "1234.5678";
static const char *strInt8s  = "-128";
static const char *strInt16s = "-32768";
static const char *strInt32s = "-2147483647";
static const char *strInt64s = "-9223372036854775807";
static const char *strInt8u  = "255";
static const char *strInt16u = "65535";
static const char *strInt32u = "4294967295";
static const char *strInt64u = "18446744073709551615";
static size_t parsedSize;


BH_BENCH_TEST(StringFromDouble)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromDouble(buffer, BUF_SIZE, testDouble, 'f', 6, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt8s)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt8s(buffer, BUF_SIZE, testInt8s, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt16s)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt16s(buffer, BUF_SIZE, testInt16s, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt32s)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt32s(buffer, BUF_SIZE, testInt32s, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt64s)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt64s(buffer, BUF_SIZE, testInt64s, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt8u)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt8u(buffer, BUF_SIZE, testInt8u, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt16u)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt16u(buffer, BUF_SIZE, testInt16u, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt32u)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt32u(buffer, BUF_SIZE, testInt32u, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringFromInt64u)
{
    while (BH_BenchIter(state))
    {
        int result;
        result = BH_StringFromInt64u(buffer, BUF_SIZE, testInt64u, 10, &actual);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(buffer);
        BH_BenchDoNotOptimize(actual);
    }
}


BH_BENCH_TEST(StringToDouble)
{
    while (BH_BenchIter(state))
    {
        double result;
        parsedSize = 0;
        result = BH_StringToDouble(strDouble, &parsedSize);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt8s)
{
    while (BH_BenchIter(state))
    {
        int8_t result;
        parsedSize = 0;
        result = BH_StringToInt8s(strInt8s, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt16s)
{
    while (BH_BenchIter(state))
    {
        int16_t result;
        parsedSize = 0;
        result = BH_StringToInt16s(strInt16s, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt32s)
{
    while (BH_BenchIter(state))
    {
        int32_t result;
        parsedSize = 0;
        result = BH_StringToInt32s(strInt32s, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt64s)
{
    while (BH_BenchIter(state))
    {
        int64_t result;
        parsedSize = 0;
        result = BH_StringToInt64s(strInt64s, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt8u)
{
    while (BH_BenchIter(state))
    {
        uint8_t result;
        parsedSize = 0;
        result = BH_StringToInt8u(strInt8u, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt16u)
{
    while (BH_BenchIter(state))
    {
        uint16_t result;
        parsedSize = 0;
        result = BH_StringToInt16u(strInt16u, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt32u)
{
    while (BH_BenchIter(state))
    {
        uint32_t result;
        parsedSize = 0;
        result = BH_StringToInt32u(strInt32u, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


BH_BENCH_TEST(StringToInt64u)
{
    while (BH_BenchIter(state))
    {
        uint64_t result;
        parsedSize = 0;
        result = BH_StringToInt64u(strInt64u, &parsedSize, 10);
        BH_BenchDoNotOptimize(result);
        BH_BenchDoNotOptimize(parsedSize);
    }
}


int main(void)
{
    BH_BENCH_ADD(StringFromDouble);
    BH_BENCH_ADD(StringFromInt8s);
    BH_BENCH_ADD(StringFromInt16s);
    BH_BENCH_ADD(StringFromInt32s);
    BH_BENCH_ADD(StringFromInt64s);
    BH_BENCH_ADD(StringFromInt8u);
    BH_BENCH_ADD(StringFromInt16u);
    BH_BENCH_ADD(StringFromInt32u);
    BH_BENCH_ADD(StringFromInt64u);

    BH_BENCH_ADD(StringToDouble);
    BH_BENCH_ADD(StringToInt8s);
    BH_BENCH_ADD(StringToInt16s);
    BH_BENCH_ADD(StringToInt32s);
    BH_BENCH_ADD(StringToInt64s);
    BH_BENCH_ADD(StringToInt8u);
    BH_BENCH_ADD(StringToInt16u);
    BH_BENCH_ADD(StringToInt32u);
    BH_BENCH_ADD(StringToInt64u);

    return BH_BenchRun();
}
