#include <BH/String.h>
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
