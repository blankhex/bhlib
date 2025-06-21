#include <BH/Unicode.h>
#include <BH/Util.h>

#include "Inline/Unicode.h"


uint32_t decodeUtf8(uint32_t *unit,
                    unsigned char *state,
                    unsigned char byte)
{
    unsigned char type, bits;

    type = lookupUtf8Type[(size_t)byte];
    bits = lookupUtf8Bits[(size_t)type];
    *unit = (*unit << bits) | ((0xFF >> (8 - bits)) & byte);

    return *state = lookupUtf8State[(size_t)type + *state];
}


uint32_t BH_UnicodeLower(uint32_t unit)
{
    size_t i;

    /* In convertable range */
    if (unit >= 0xFFFF)
        return unit;

    /* Fasttrack and search lookup table */
    i = lookupLowerIndex[unit >> 8];
    while (i < sizeof(lookupLower) / sizeof(struct CaseMap))
    {
        if (lookupLower[i].from > unit)
            return unit;
        if (lookupLower[i].from == unit)
            return lookupLower[i].to;
        i++;
    }

    return unit;
}


uint32_t BH_UnicodeUpper(uint32_t unit)
{
    size_t i;

    /* In convertable range */
    if (unit >= 0xFFFF)
        return unit;

    /* Fasttrack and search lookup table */
    i = lookupUpperIndex[unit >> 8];
    while (i < sizeof(lookupUpper) / sizeof(struct CaseMap))
    {
        if (lookupUpper[i].from > unit)
            return unit;
        if (lookupUpper[i].from == unit)
            return lookupUpper[i].to;
        i++;
    }

    return unit;
}


size_t BH_UnicodeDecodeUtf8(const char *string,
                            size_t size,
                            uint32_t *unit)
{
    unsigned char state;
    size_t i;

    state = 0;
    *unit = 0;
    for (i = 0; i < size; i++)
    {
        switch (decodeUtf8(unit, &state, string[i]))
        {
        case UTF8_OK: return i + 1;
        case UTF8_ERROR: *unit = 0xFFFFFFFF; return (i > 0 ? i : i + 1);
        default: break;
        }
    }

    return 0;
}


size_t BH_UnicodeEncodeUtf8(uint32_t unit,
                            char *string)
{
    size_t result;

    if (unit > 0xD7FF && unit < 0xE000)
        return 0;

    result = 0;
    if (unit < 0x80ul)
    {
        string[0] = unit & 0x7F;
        result = 1;
    }
    else if (unit < 0x800ul)
    {
        string[0] = 0xC0 | (unit >> 6);
        string[1] = 0x80 | (unit & 0x3F);
        result = 2;
    }
    else if (unit < 0x10000ul)
    {
        string[0] = 0xE0 | (unit >> 12);
        string[1] = 0x80 | ((unit >> 6) & 0x3F);
        string[2] = 0x80 | (unit & 0x3F);
        result = 3;
    }
    else if (unit < 0x200000ul)
    {
        string[0] = 0xF0 | (unit >> 18);
        string[1] = 0x80 | ((unit >> 12) & 0x3F);
        string[2] = 0x80 | ((unit >> 6) & 0x3F);
        string[3] = 0x80 | (unit & 0x3F);
        result = 4;
    }

    return result;
}


static int classifyUtf16(uint16_t value)
{
    if (value > 0xD7FF && value < 0xDC00)
        return UTF16_LOWSUR;
    else if (value > 0xDBFF && value < 0xE000)
        return UTF16_HIGHSUR;
    return UTF16_NORMAL;
}


size_t BH_UnicodeDecodeUtf16LE(const char *string,
                               size_t size,
                               uint32_t *unit)
{
    uint16_t lower, upper;

    if (size < 2)
        return 0;

    upper = BH_Read16LEu(string);
    *unit = 0xFFFFFFFF;

    if (classifyUtf16(upper) == UTF16_NORMAL)
        *unit = upper;
    else if (classifyUtf16(upper) == UTF16_LOWSUR)
    {
        if (size < 4)
            return 0;

        lower = BH_Read16LEu(string + 2);
        if (classifyUtf16(lower) == UTF16_HIGHSUR)
        {
            *unit = (((upper & 0x3FF) << 10) | (lower & 0x3FF)) + 0x10000;
            return 4;
        }
    }

    return 2;
}


size_t BH_UnicodeDecodeUtf16BE(const char *string,
                               size_t size,
                               uint32_t *unit)
{
    uint16_t lower, upper;

    if (size < 2)
        return 0;

    upper = BH_Read16BEu(string);
    *unit = 0xFFFFFFFF;

    if (classifyUtf16(upper) == UTF16_NORMAL)
        *unit = upper;
    else if (classifyUtf16(upper) == UTF16_LOWSUR)
    {
        if (size < 4)
            return 0;

        lower = BH_Read16BEu(string + 2);
        if (classifyUtf16(lower) == UTF16_HIGHSUR)
        {
            *unit = (((upper & 0x3FF) << 10) | (lower & 0x3FF)) + 0x10000;
            return 4;
        }
    }

    return 2;
}


size_t BH_UnicodeEncodeUtf16LE(uint32_t unit,
                               char *string)
{
    if (unit > 0xD7FF && unit < 0xE000)
        return 0;

    if (unit < 0x10000)
    {
        BH_Write16LEu(string, unit);
        return 2;
    }
    else if (unit < 0x200000)
    {
        unit -= 0x10000;
        BH_Write16LEu(string, 0xD800 | (unit >> 10));
        BH_Write16LEu(string + 2, 0xDC00 | (unit & 0x3FF));
        return 4;
    }
    return 0;
}


size_t BH_UnicodeEncodeUtf16BE(uint32_t unit,
                               char *string)
{
    if (unit > 0xD7FF && unit < 0xE000)
        return 0;

    if (unit < 0x10000)
    {
        BH_Write16BEu(string, unit);
        return 2;
    }
    else if (unit < 0x200000)
    {
        unit -= 0x10000;
        BH_Write16BEu(string, 0xD800 | (unit >> 10));
        BH_Write16BEu(string + 2, 0xDC00 | (unit & 0x3FF));
        return 4;
    }
    return 0;
}


size_t BH_UnicodeDecodeUtf32LE(const char *string,
                               size_t size,
                               uint32_t *unit)
{
    if (size < 4)
        return 0;

    *unit = BH_Read32LEu(string);
    return 4;
}


size_t BH_UnicodeDecodeUtf32BE(const char *string,
                               size_t size,
                               uint32_t *unit)
{
    if (size < 4)
        return 0;

    *unit = BH_Read32BEu(string);
    return 4;
}


size_t BH_UnicodeEncodeUtf32LE(uint32_t unit,
                               char *string)
{
    if (unit > 0x1FFFFF || (unit > 0xD7FF && unit < 0xE000))
        return 0;

    BH_Write32LEu(string, unit);
    return 4;
}


size_t BH_UnicodeEncodeUtf32BE(uint32_t unit,
                               char *string)
{
    if (unit > 0x1FFFFF || (unit > 0xD7FF && unit < 0xE000))
        return 0;

    BH_Write32BEu(string, unit);
    return 4;
}
