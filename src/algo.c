#include <bh/algo.h>
#include <string.h>


void bh_swap(void *dest,
             void *src,
             size_t size)
{
    int tmp;

    /* Swap bytes in int-sized chunks */
    while (size >= sizeof(tmp))
    {
        memmove(&tmp, dest, sizeof(tmp));
        memmove(dest, src, sizeof(tmp));
        memmove(src, &tmp, sizeof(tmp));

        dest = (char *)dest + sizeof(tmp);
        src = (char *)src + sizeof(tmp);
        size -= sizeof(tmp);
    }

    /* Swap the remaining size */
    if (size)
    {
        memmove(&tmp, dest, size);
        memmove(dest, src, size);
        memmove(src, &tmp, size);
    }
}


void *bh_partition(void *pivot,
                   void *array,
                   size_t size,
                   size_t element,
                   bh_equal_cb_t equal)
{
    char *start, *end, *i, *j;

    /* Calculate start, end and item pointers */
    start = (char *)array;
    end = start + size * element;
    i = start;
    j = start + (size - 1) * element;

    /* Iterate over array */
    while (1)
    {
        /* Find first element from the left that are bigger then pivot */
        while (i < end && equal(i, pivot) < 0)
            i += element;

        /* Find first element from the right that are less then pivot*/
        while (j >= start && equal(j, pivot) >= 0)
            j -= element;

        /* If item elemetns passed each other - we are done */
        if (i >= j)
            break;

        /* Special case when pivot is actually part of the array */
        if (pivot == i)
            pivot = j;
        else if (pivot == j)
            pivot = i;

        /* Swap elements and continue */
        bh_swap(i, j, element);
        i += element;
        j -= element;
    }

    /* Return pointer to the middle of the partition */
    return j + element;
}


#if 0
static void bh_sort_insert(void *array,
                           size_t size,
                           size_t element,
                           bh_equal_cb_t equal)
{
    size_t i, j;

    /* Standard insert sort */
    for (i = 1; i < size; i++)
    {
        for (j = i; j >= 1; j -= 1)
        {
            char *lhs, *rhs;

            lhs = (char *)array + j * element;
            rhs = (char *)array + (j - 1) * element;

            if (equal(lhs, rhs) < 0)
                bh_swap(lhs, rhs, element);
            else
                break;
        }
    }

}
#endif


static void bh_sort_shell(void *array,
                          size_t size,
                          size_t element,
                          bh_equal_cb_t equal)
{
    static const size_t gaps[10] = {1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};
    const size_t *gap;
    size_t i, j;

    /* Shell sort with A102549 sequence */
    for (gap = gaps; *gap; ++gap)
    {
        for (i = *gap; i < size; i++)
        {
            for (j = i; j >= *gap; j -= *gap)
            {
                char *lhs, *rhs;

                lhs = (char *)array + j * element;
                rhs = (char *)array + (j - *gap) * element;

                if (equal(lhs, rhs) < 0)
                    bh_swap(lhs, rhs, element);
                else
                    break;
            }
        }
    }
}


static void bh_sort_heap(void *array,
                         size_t size,
                         size_t element,
                         bh_equal_cb_t equal)
{
    size_t i;

    bh_heap_make(array, size, element, equal);
    for (i = size; i > 0; i--)
        bh_heap_remove(array, i, element, equal);
}


static void bh_sort_intro_r(void *array,
                            size_t size,
                            size_t element,
                            bh_equal_cb_t equal,
                            size_t depth)
{
    /* Introsort (with manual tail call optimization) */
    while (1)
    {
        char *start, *middle, *end, *pivot;

        if (size < 16)
        {
            /* There are less then 16 elements left - use Shell/Insert sort */
            bh_sort_shell(array, size, element, equal);
            return;
        }
        else if (!depth)
        {
            /* Max depth reached - use heap sort */
            bh_sort_heap(array, size, element, equal);
            return;
        }

        /* Calculate start, middle and end pointers */
        start = (char *)array;
        middle = start + (size / 2) * element;
        end = start + (size - 1) * element;

        /* Select middle element */
        if (equal(start, middle) > 0)
        {
            if (equal(middle, end) > 0)
                pivot = middle;
            else if (equal(start, end) > 0)
                pivot = end;
            else
                pivot = start;
        }
        else
        {
            if (equal(start, end) > 0)
                pivot = start;
            else if (equal(middle, end) > 0)
                pivot = end;
            else
                pivot = middle;
        }

        /* Partition the array */
        middle = bh_partition(pivot, array, size, element, equal);

        /* Recursive call into first half */
        bh_sort_intro_r(array, (middle - start) / element, element, equal, depth - 1);

        /* Setup array and size for the second half */
        array = middle;
        size = size - (middle - start) / element;
        depth--;
    }
}


void bh_sort(void *array,
             size_t size,
             size_t element,
             bh_equal_cb_t equal)
{
    size_t depth, depth_log;

    /* Calculate max depth */
    depth = 0;
    depth_log = 1;
    while (depth_log < size)
    {
        depth++;
        depth_log <<= 1;
    }

    /* Call main sorting function */
    bh_sort_intro_r(array, size, element, equal, depth);
}


void bh_heap_make(void *array,
                  size_t size,
                  size_t element,
                  bh_equal_cb_t equal)
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
            if (right < end && equal(left, right) < 0)
                biggest = right;

            /* Compare biggest child with current */
            if (equal(current, biggest) < 0)
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


void bh_heap_remove(void *array,
                    size_t size,
                    size_t element,
                    bh_equal_cb_t equal)
{
    char *start, *end, *current, *left, *right;

    if (size <= 1)
        return;

    /* Calculate start, end and children pointers */
    start = (char *)array;
    end = start + (size - 1) * element;
    current = start;
    left = start + (current - start) * 2 + element;
    right = left + element;

    /* Swap first and last element */
    bh_swap(current, end, element);

    /* Iterate until we reach the end */
    while (left < end)
    {
        char *biggest;

        /* Determine biggest child */
        biggest = left;
        if (right < end && equal(left, right) < 0)
            biggest = right;

        /* Compare biggest child with current */
        if (equal(current, biggest) < 0)
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


void bh_heap_insert(void *value,
                    void *array,
                    size_t size,
                    size_t element,
                    bh_equal_cb_t equal)
{
    char *start, *end, *current;

    /* Calculate begin and end pointers */
    start = (char *)array;
    end = start + size * element;
    current = end;

    /* Copy value into array */
    if (value)
        memmove(current, value, element);

    while (current > start)
    {
        char *parent;

        /* Calculate parent pointer */
        parent = start + (((current - start) / element - 1) / 2) * element;

        /* Compare current and parent */
        if (equal(parent, current) < 0)
        {
            /* Swap current and parent */
            bh_swap(parent, current, element);
            current = parent;
        }
        else
            break;
    }
}


void bh_heap_replace(void *value,
                     void *array,
                     size_t size,
                     size_t element,
                     bh_equal_cb_t equal)
{
    char *start, *end, *current, *left, *right;

    if (size < 1)
        return;

    /* Calculate start, end and children pointers */
    start = (char *)array;
    end = start + size * element;
    current = start;
    left = start + (current - start) * 2 + element;
    right = left + element;

    /* Copy supplied element to the first (top) position */
    if (value)
        memmove(current, value, element);
    else
        memmove(current, start + size * element, element);

    /* Iterate until we reach the end */
    while (left < end)
    {
        char *biggest;

        /* Determine biggest child */
        biggest = left;
        if (right < end && equal(left, right) < 0)
            biggest = right;

        /* Compare biggest child with current */
        if (equal(current, biggest) < 0)
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
