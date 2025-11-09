#include <BH/String.h>
#include <ctype.h>
#include <limits.h>
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


int BH_StringFromInt8s(char *string,
                       size_t size,
                       int8_t value,
                       int base,
                       size_t *actual)
{
    #include "Inline/Signed.h"
}


int BH_StringFromInt16s(char *string,
                        size_t size,
                        int16_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Signed.h"
}


int BH_StringFromInt32s(char *string,
                        size_t size,
                        int32_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Signed.h"
}


int BH_StringFromInt64s(char *string,
                        size_t size,
                        int64_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Signed.h"
}


int BH_StringFromInt8u(char *string,
                       size_t size,
                       uint8_t value,
                       int base,
                       size_t *actual)
{
    #include "Inline/Unsigned.h"
}


int BH_StringFromInt16u(char *string,
                        size_t size,
                        uint16_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Unsigned.h"
}


int BH_StringFromInt32u(char *string,
                        size_t size,
                        uint32_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Unsigned.h"
}


int BH_StringFromInt64u(char *string,
                        size_t size,
                        uint64_t value,
                        int base,
                        size_t *actual)
{
    #include "Inline/Unsigned.h"
}


int8_t BH_StringToInt8s(const char *string,
                        int base,
                        size_t *actual)
{
    int8_t result;
    #include "Inline/Int.h"
}


int16_t BH_StringToInt16s(const char *string,
                          int base,
                          size_t *actual)
{
    int16_t result;
    #include "Inline/Int.h"
}


int32_t BH_StringToInt32s(const char *string,
                          int base,
                          size_t *actual)
{
    int32_t result;
    #include "Inline/Int.h"
}


int64_t BH_StringToInt64s(const char *string,
                          int base,
                          size_t *actual)
{
    int64_t result;
    #include "Inline/Int.h"
}


uint8_t BH_StringToInt8u(const char *string,
                         int base,
                         size_t *actual)
{
    uint8_t result;
    #include "Inline/Int.h"
}


uint16_t BH_StringToInt16u(const char *string,
                           int base,
                           size_t *actual)
{
    uint16_t result;
    #include "Inline/Int.h"
}


uint32_t BH_StringToInt32u(const char *string,
                           int base,
                           size_t *actual)
{
    uint32_t result;
    #include "Inline/Int.h"
}


uint64_t BH_StringToInt64u(const char *string,
                           int base,
                           size_t *actual)
{
    uint64_t result;
    #include "Inline/Int.h"
}
