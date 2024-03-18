/**
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */
#include <bh/algo.h>
#include <string.h>
#include <stdio.h>

void bh_swap(void *a, void *b, size_t size)
{
    int tmp;

    /* Swap values in int sized chunks */
    while (size >= sizeof(tmp))
    {
        memmove(&tmp, a, sizeof(tmp));
        memmove(a, b, sizeof(tmp));
        memmove(b, &tmp, sizeof(tmp));

        a = (char *)a + sizeof(tmp);
        b = (char *)b + sizeof(tmp);
        size -= sizeof(tmp);
    }

    /* Swap the rest */
    if (size)
    {
        memmove(&tmp, a, size);
        memmove(a, b, size);
        memmove(b, &tmp, size);
    }
}

void bh_sort(void *array, size_t element, size_t size, bh_compare_cb_t compare)
{
    bh_heap_make(array, element, size, compare);
    while (size)
        bh_heap_pop(array, element, size--, compare);    
}

void bh_heap_make(void *array, size_t element, size_t size, bh_compare_cb_t compare)
{
    char *start, *end;
    size_t i;

    /* Calculate start and end pointers of the array */
    start = (char *)array;
    end = start + size * element;

    /* Bottom up heapify algorithm */
    for (i = size / 2 + 1; i; --i)
    {
        char *current, *left, *right;

        /* Calculate current and children pointers */
        current = start + (i - 1) * element;
        left = start + (current - start) * 2 + element;
        right = left + element;

        while (left < end)
        {
            char *biggest;

            /* Determine biggest child */
            biggest = left;
            if (right < end && compare(left, right) < 0)
                biggest = right;

            /* Compare biggest child with current */
            if (compare(current, biggest) < 0)
            {
                /* Swap content and recalculate children pointers */
                bh_swap(current, biggest, element);
                current = biggest;
                left = start + (current - start) * 2 + element;
                right = left + element;
            }
            else
                break;
        }
    }
}

void bh_heap_pop(void *array, size_t element, size_t size, bh_compare_cb_t compare)
{
    char *start, *end, *current, *left, *right;
    
    if (size <= 1)
        return;

    start = (char *)array;
    end = start + (size - 1) * element;
    current = start;
    left = start + (current - start) * 2 + element;
    right = left + element;

    bh_swap(current, end, element);

    while (left < end)
    {
        char *biggest;

        biggest = left;
        if (right < end && compare(left, right) < 0)
            biggest = right;

        if (compare(current, biggest) < 0)
        {
            bh_swap(current, biggest, element);
            current = biggest;
            left = start + (current - start) * 2 + element;
            right = left + element;
        }
        else
            break;
    }
}

void bh_heap_push(const void *item, void *array, size_t element, size_t size, bh_compare_cb_t compare)
{
    char *start, *end, *current;

    start = (char *)array;
    end = start + size * element;
    current = end;
    
    memmove(current, item, element);
    while (current > start)
    {
        char *parent;

        parent = start + (((current - start) / element - 1) / 2) * element;
        if (compare(parent, current) < 0)
        {
            bh_swap(parent, current, element);
            current = parent;
        }
        else
            break;
    }
}

