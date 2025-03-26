#include <BH/String.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static const signed char lookup[] =
{
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
};


static void skipSpace(const char **string,
                      size_t *size)
{
    while (isspace(**string))
    {
        (*string)++;
        if (size) (*size)++;
    }
}


static void handleSign(const char **string,
                       size_t *size,
                       int *sign)
{
    *sign = 1;
    if (**string == '-')
    {
        *sign = -1; (*string)++;
        if (size) (*size)++;
    }
}


static void guessBase(const char **string,
                      size_t *size,
                      int *base)
{
    if (*base != 0 && *base != 2 && *base != 8 && *base != 16)
        return;

    if (**string != '0')
    {
        if (*base == 0)
            *base = 10;
        return;
    }

    (*string)++;
    if (size)
        (*size)++;

    if ((**string == 'x' || **string == 'X') && (*base == 0 || *base == 16))
    {
        *base = 16;
        (*string)++;
        if (size)
            (*size)++;
    }
    else if ((**string == 'b' || **string == 'B') && (*base == 0 || *base == 2))
    {
        *base = 2;
        (*string)++;
        if (size)
            (*size)++;
    }
    else if ((*base == 0 || *base == 8))
        *base = 8;
}


#define TEMPLATE_IMPL \
    char tmp[sizeof(value) * CHAR_BIT + 1]; char *current, *end, *result; \
    int sign; end = tmp + sizeof(tmp); current = end; sign = 0; \
    if (value < 0) { sign = 1; value = -value; } while (value) { \
    *(--current) = digits[value % base]; value /= base; } \
    if (sign) { *(--current) = '-'; } result = malloc(end - current + 1); \
    if (!result) { return NULL; } memcpy(result, current, end - current); \
    result[end - current] = 0; return result;


char *BH_StringFromInt8s(int8_t value,
                         int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt16s(int16_t value,
                          int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt32s(int32_t value,
                          int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt64s(int64_t value,
                          int base)
{
    TEMPLATE_IMPL
}


#undef TEMPLATE_IMPL
#define TEMPLATE_IMPL \
    char tmp[sizeof(value) * CHAR_BIT]; char *current, *end, *result; \
    end = tmp + sizeof(tmp); current = end; while (value) { \
    *(--current) = digits[value % base]; value /= base; } \
    result = malloc(end - current + 1); if (!result) { return NULL; } \
    memcpy(result, current, end - current); result[end - current] = 0; \
    return result;


char *BH_StringFromInt8u(uint8_t value,
                         int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt16u(uint16_t value,
                          int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt32u(uint32_t value,
                          int base)
{
    TEMPLATE_IMPL
}


char *BH_StringFromInt64u(uint64_t value,
                          int base)
{
    TEMPLATE_IMPL
}


#undef TEMPLATE_IMPL
#define TEMPLATE_IMPL(type) \
    type result = 0; int sign, flag = 0; signed char sym; if (size) *size = 0; \
    if (base != 0 && (base < 2 || base > 36)) { return 0; } \
    skipSpace(&string, size); handleSign(&string, size, &sign); \
    guessBase(&string, size, &base); while(*string) { sym = *(string++); \
    sym = lookup[(unsigned int)sym]; if (sym >= base || sym == -1) { break; } \
    if (size) { (*size)++; } result = result * base + sym; flag = 1; } \
    if (!result && !flag && size) { *size = 0; } return result * sign;


int8_t BH_StringToInt8s(const char *string,
                        size_t *size,
                        int base)
{
    TEMPLATE_IMPL(int8_t)
}


int16_t BH_StringToInt16s(const char *string,
                          size_t *size,
                          int base)
{
    TEMPLATE_IMPL(int16_t)
}


int32_t BH_StringToInt32s(const char *string,
                          size_t *size,
                          int base)
{
    TEMPLATE_IMPL(int32_t)
}


int64_t BH_StringToInt64s(const char *string,
                          size_t *size,
                          int base)
{
    TEMPLATE_IMPL(int64_t)
}


uint8_t BH_StringToInt8u(const char *string,
                         size_t *size,
                         int base)
{
    TEMPLATE_IMPL(uint8_t)
}


uint16_t BH_StringToInt16u(const char *string,
                           size_t *size,
                           int base)
{
    TEMPLATE_IMPL(uint16_t)
}


uint32_t BH_StringToInt32u(const char *string,
                           size_t *size,
                           int base)
{
    TEMPLATE_IMPL(uint32_t)
}


uint64_t BH_StringToInt64u(const char *string,
                           size_t *size,
                           int base)
{
    TEMPLATE_IMPL(uint64_t)
}


#undef TEMPLATE_IMPL
