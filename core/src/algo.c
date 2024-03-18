#include <bh/algo.h>
#include <string.h>

void bh_swap(void *a, void *b, size_t size)
{
    int tmp;

    while (size >= sizeof(tmp))
    {
        memmove(&tmp, a, sizeof(tmp));
        memmove(a, b, sizeof(tmp));
        memmove(b, &tmp, sizeof(tmp));

        a = (char *)a + sizeof(tmp);
        b = (char *)b + sizeof(tmp);
        size -= sizeof(tmp);
    }

    if (size)
    {
        memmove(&tmp, a, size);
        memmove(a, b, size);
        memmove(b, &tmp, size);
    }
}
