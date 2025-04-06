#include <BH/Unit.h>
#include <BH/String.h>
#include <BH/IO.h>
#include <stdlib.h>


struct TestCase
{
    char *input;
    size_t size;
    size_t read;
    uint32_t result;
};


BH_UNIT_TEST(Case)
{
    size_t i, j;

    for (i = 0; i < 0x110000; i++)
    {
        j = BH_UnicodeLower(i);
        if (j == i)
        {
            j = BH_UnicodeUpper(i);
            j = BH_UnicodeLower(j);
        }
        else
            j = BH_UnicodeUpper(j);

        /* Some exceptions */
        if (i == 0x130 && j == 0x49)
            continue;
        else if (i == 0x131 && j == 0x69)
            continue;
        else if (i == 0x1C5 && j == 0x1C4)
            continue;
        else if (i == 0x1C8 && j == 0x1C7)
            continue;
        else if (i == 0x1CB && j == 0x1CA)
            continue;

        BH_VERIFY(i == j);
    }

    return 0;
}


BH_UNIT_TEST(Utf8)
{
    const struct TestCase *current;
    const struct TestCase cases[] =
    {
        /* Normal cases */
        {"\x00", 1, 1, 0},
        {"\xC2\x80", 2, 2, 0x80},
        {"\xE0\xA0\x80", 3, 3, 0x800},
        {"\xF0\x90\x80\x80", 4, 4, 0x10000},
        {"\x7F", 1, 1, 0x7F},
        {"\xDF\xBF", 2, 2, 0x7FF},
        {"\xEF\xBF\xBF", 3, 3, 0xFFFF},
        {"\xED\x9F\xBF", 3, 3, 0xD7FF},
        {"\xEE\x80\x80", 3, 3, 0xE000},
        {"\xEF\xBF\xBD", 3, 3, 0xFFFD},
        {"H", 1, 1, 'H'},
        {"\xCE\xBA", 2, 2, 0x3BA},

        /* Lonely start characters */
        {"\xC0 ", 2, 1, -1},
        {"\xC1 ", 2, 1, -1},
        {"\xC2 ", 2, 1, -1},
        {"\xC3 ", 2, 1, -1},
        {"\xC4 ", 2, 1, -1},

        /* Malformed sequences */
        {"\x80", 1, -1, -1},
        {"\xBF", 1, -1, -1},
        {"\xFE", 1, -1, -1},
        {"\xFF", 1, -1, -1},

        /* Overlong sequences */
        {"\xC0\xAF", 2, 1, -1},

        /* UTF-16 surrogate pairs */
        {"\xED\xA0\x80", 3, -1, -1},
        {"\xED\xAE\x80", 3, -1, -1},
        {"\xED\xB0\x80", 3, -1, -1},
        {"\xED\xBF\xBF", 3, -1, -1},

        {NULL, 0, 0, 0}
    };
    char buffer[8];
    uint32_t unit;
    size_t i, outSize, inSize;

    /* Encode and decode all character in a valid UTF-8 range */
    for (i = 0; i < 0x110000; i++)
    {
        inSize = BH_UnicodeEncodeUtf8(i, buffer);

        /* Check for surrogate pairs */
        if (i > 0xD7FF && i < 0xE000)
        {
            BH_VERIFY(inSize == 0);
            continue;
        }

        BH_VERIFY(inSize > 0);
        outSize = BH_UnicodeDecodeUtf8(buffer, inSize, &unit);
        BH_VERIFY(inSize == outSize);
        BH_VERIFY(unit == i);
    }

    /* Test special cases */
    for (current = cases; current->input; current++)
    {
        i = BH_UnicodeDecodeUtf8(current->input, current->size, &unit);
        if (current->read == (size_t)-1 && i)
            i = -1;

        if (i != current->read || unit != current->result)
        {
            printf("\tcase %d\n", (int)(current - cases));
            BH_VERIFY(i == current->read);
            BH_VERIFY(unit == current->result);
        }
    }

    return 0;
}


BH_UNIT_TEST(Utf16)
{
    char buffer[8];
    uint32_t unit;
    size_t i, outSize, inSize;

    /* Encode and decode all character in a valid UTF-8 range */
    for (i = 0; i < 0x110000; i++)
    {
        /* Check for little endian */
        inSize = BH_UnicodeEncodeUtf16LE(i, buffer);
        if (i > 0xD7FF && i < 0xE000)
        {
            BH_VERIFY(inSize == 0);
            continue;
        }
        BH_VERIFY(inSize > 0);

        outSize = BH_UnicodeDecodeUtf16LE(buffer, inSize, &unit);
        BH_VERIFY(inSize == outSize);
        BH_VERIFY(unit == i);

        /* Check for big endian */
        inSize = BH_UnicodeEncodeUtf16BE(i, buffer);
        if (i > 0xD7FF && i < 0xE000)
        {
            BH_VERIFY(inSize == 0);
            continue;
        }
        BH_VERIFY(inSize > 0);

        outSize = BH_UnicodeDecodeUtf16BE(buffer, inSize, &unit);
        BH_VERIFY(inSize == outSize);
        BH_VERIFY(unit == i);
    }

    return 0;
}


BH_UNIT_TEST(Utf32)
{
    char buffer[8];
    uint32_t unit;
    size_t i, outSize, inSize;

    /* Encode and decode all character in a valid UTF-8 range */
    for (i = 0; i < 0x110000; i++)
    {
        /* Check for little endian */
        inSize = BH_UnicodeEncodeUtf32LE(i, buffer);
        if (i > 0xD7FF && i < 0xE000)
        {
            BH_VERIFY(inSize == 0);
            continue;
        }
        BH_VERIFY(inSize > 0);

        outSize = BH_UnicodeDecodeUtf32LE(buffer, inSize, &unit);
        BH_VERIFY(inSize == outSize);
        BH_VERIFY(unit == i);

        /* Check for big endian */
        inSize = BH_UnicodeEncodeUtf32BE(i, buffer);
        if (i > 0xD7FF && i < 0xE000)
        {
            BH_VERIFY(inSize == 0);
            continue;
        }
        BH_VERIFY(inSize > 0);

        outSize = BH_UnicodeDecodeUtf32BE(buffer, inSize, &unit);
        BH_VERIFY(inSize == outSize);
        BH_VERIFY(unit == i);
    }

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(Case);
    BH_UNIT_ADD(Utf8);
    BH_UNIT_ADD(Utf16);
    BH_UNIT_ADD(Utf32);

    return BH_UnitRun();
}
