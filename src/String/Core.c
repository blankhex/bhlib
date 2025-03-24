#include <BH/String.h>
#include <stdlib.h>
#include <string.h>


void BH_StringFree(char *string)
{
    free(string);
}


char *BH_StringCopy(const char *string)
{
    char *result;

    result = malloc(strlen(string) + 1);
    if (result)
        strcpy(result, string);

    return result;
}
