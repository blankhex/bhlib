#include <BH/String.h>
#include <BH/Unicode.h>
#include <string.h>
#include <stdlib.h>


char *BH_StringDup(const char *string)
{
    size_t length;
    char *result;

    if (!string)
        return NULL;

    length = strlen(string) + 1;
    result = malloc(length);
    if (result)
        memcpy(result, string, length);
    return result;
}


int BH_StringCompare(const char *s1,
                     const char *s2)
{
    return strcmp(s1, s2);
}


int BH_StringCompareCaseless(const char *s1,
                             const char *s2)
{
    uint32_t c1, c2;

    while (*s1 && *s2)
    {
        s1 += BH_UnicodeDecodeUtf8(s1, 4, &c1);
        s2 += BH_UnicodeDecodeUtf8(s2, 4, &c2);

        c1 = BH_UnicodeLower(c1);
        c2 = BH_UnicodeLower(c2);

        if (c1 != c2)
            return (c1 < c2) ? -1 : 1;
    }

    return (!*s1) ? (!*s2 ? 0 : -1) : 1;
}
