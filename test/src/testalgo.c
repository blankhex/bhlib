#include <bh/algo.h>
#include <bh/unit.h>
#include <string.h>
#include <stdlib.h>


static int int_equal(const void *lhs,
                     const void *rhs)
{
    return *(const int*)lhs - *(const int*)rhs;
}


static int verify_partition(size_t index,
                            int pivot,
                            int *array,
                            size_t size)
{
    size_t i;

    for (i = 0; i < index; i++)
        if (array[i] >= pivot)
            return -1;

    for (i = index; i < size; i++)
        if (array[i] < pivot)
            return -1;

    return 0;
}


static int verify_heap(int *array,
                       size_t size)
{
    size_t i, left, right;

    for (i = 0; i < size; i++)
    {
        left = i * 2 + 1;
        right = i * 2 + 2;

        if (left < size && array[i] < array[left])
            return -1;
        if (right < size && array[i] < array[right])
            return -1;
    }

    return 0;
}


static int reference_rand(void)
{
    static uint32_t next = 2025;
    next = next * 1103515245 + 12345;
    return (next / 65536) % 32768;
}


static void reference_sort(int *array, size_t size)
{
    size_t i, j;
    int tmp;

    /* Reference sort is... buble sort! */
    for (i = 0; i < size; i++)
    {
        for (j = 1; j < size; j++)
        {
            if (array[j - 1] > array[j])
            {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }
}


static void fill_arrays(int *array,
                        int *reference,
                        size_t size,
                        int mask)
{
    size_t i;
    int negate;

    /* Check if mask needs to be negated */
    negate = mask < 0;
    if (negate)
        mask = -mask;

    /* Fill the array */
    for (i = 0; i < size; ++i)
    {
        array[i] = reference_rand();

        if (mask > 1)
            array[i] = array[i] % mask;

        if (negate)
            array[i] = -array[i];

        if (reference)
            reference[i] = array[i];
    }
}


static int check_sort(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int reference[317], data[317];

    /* Test empty array and one element arrays */
    data[0] = 1; data[1] = 2; data[2] = 3;
    bh_sort(data, 0, sizeof(int), int_equal);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    bh_sort(data, 1, sizeof(int), int_equal);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 0);
        reference_sort(reference, *size);
        bh_sort(data, *size, sizeof(int), int_equal);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    /* Test against negative values */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, -1);
        reference_sort(reference, *size);
        bh_sort(data, *size, sizeof(int), int_equal);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 4);
        reference_sort(reference, *size);
        bh_sort(data, *size, sizeof(int), int_equal);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    return 0;
}


static int check_partition(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int reference[317], data[317], value, *pivot;

    /* Test empty array and one element array */
    data[0] = 1; data[1] = 2; data[2] = 3;
    value = 0;
    pivot = bh_partition(&value, data, 0, sizeof(int), int_equal);
    BH_VERIFY(pivot != NULL);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    pivot = bh_partition(&value, data, 1, sizeof(int), int_equal);
    BH_VERIFY(pivot == data);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 0);
        value = 16384;
        pivot = bh_partition(&value, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against negative values */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, -1);
        value = -16384;
        pivot = bh_partition(&value, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 4);
        value = 2;
        pivot = bh_partition(&value, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against small pivots */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 0);
        value = -100;
        pivot = bh_partition(&value, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against large pivots */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 0);
        value = 65536;
        pivot = bh_partition(&value, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against different sizes (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 0);
        value = data[0];
        pivot = bh_partition(data, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against negative values (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, -1);
        value = data[0];
        pivot = bh_partition(data, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, reference, *size, 4);
        value = data[0];
        pivot = bh_partition(data, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Same data test */
    for (size = sizes; *size; ++size)
    {
        memset(data, 0, sizeof(int) * *size);
        memset(reference, 0, sizeof(int) * *size);
        value = data[*size - 1];
        pivot = bh_partition(data + *size - 1, data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_partition(pivot - data, value, data, *size) == 0);

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    return 0;
}


static int check_heap_make(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317];

    /* Test empty array */
    data[0] = 1; data[1] = 2; data[2] = 3;
    bh_heap_make(data, 0, sizeof(int), int_equal);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, NULL, *size, 0);
        bh_heap_make(data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_heap(data, *size) == 0);
    }

    /* Test array against negative values */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, NULL, *size, -1);
        bh_heap_make(data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_heap(data, *size) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        fill_arrays(data, NULL, *size, 4);
        bh_heap_make(data, *size, sizeof(int), int_equal);
        BH_VERIFY(verify_heap(data, *size) == 0);
    }

    return 0;
}


static int check_heap_insert(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317], reference[317];

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        size_t i;
        fill_arrays(data, reference, *size, 0);
        for (i = 0; i < *size; ++i)
        {
            int value;

            value = data[i];
            bh_heap_insert(&value, data, i, sizeof(int), int_equal);
            BH_VERIFY(verify_heap(data, i + 1) == 0);
        }

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    /* Test array against different sizes (inplace)*/
    for (size = sizes; *size; ++size)
    {
        size_t i;
        fill_arrays(data, reference, *size, 0);
        for (i = 0; i < *size; ++i)
        {
            bh_heap_insert(NULL, data, i, sizeof(int), int_equal);
            BH_VERIFY(verify_heap(data, i + 1) == 0);
        }

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    return 0;
}


static int check_heap_remove(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317], reference[317];

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        size_t i;
        fill_arrays(data, reference, *size, 0);
        bh_heap_make(data, *size, sizeof(int), int_equal);

        for (i = *size; i > 0; i--)
        {
            BH_VERIFY(verify_heap(data, i) == 0);
            bh_heap_remove(data, i, sizeof(int), int_equal);
        }

        reference_sort(data, *size);
        reference_sort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    return 0;
}


static int check_heap_replace(void)
{
    int data[11] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0};
    int reference[11] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0};
    int value;

    /* Prepare test arrays */
    bh_heap_make(data, 10, sizeof(int), int_equal);
    bh_heap_make(reference, 10, sizeof(int), int_equal);
    BH_VERIFY(verify_heap(data, 10) == 0);
    BH_VERIFY(verify_heap(reference, 10) == 0);

    /* Verfify heap replace */
    value = 20;
    bh_heap_replace(&value, data, 10, sizeof(int), int_equal);
    bh_heap_remove(reference, 10, sizeof(int), int_equal);
    bh_heap_insert(&value, reference, 9, sizeof(int), int_equal);

    BH_VERIFY(verify_heap(data, 10) == 0);
    BH_VERIFY(verify_heap(reference, 10) == 0);
    bh_sort(data, 10, sizeof(int), int_equal);
    bh_sort(reference, 10, sizeof(int), int_equal);
    BH_VERIFY(memcmp(data, reference, 10 * sizeof(int)) == 0);

    /* Verify heap replace on single element array */
    value = 400;
    bh_heap_replace(&value, data, 1, sizeof(int), int_equal);
    bh_heap_remove(reference, 1, sizeof(int), int_equal);
    bh_heap_insert(&value, reference, 0, sizeof(int), int_equal);

    BH_VERIFY(verify_heap(data, 1) == 0);
    BH_VERIFY(verify_heap(reference, 1) == 0);
    BH_VERIFY(memcmp(data, reference, 1 * sizeof(int)) == 0);

    /* Prepare test arrays */
    bh_sort(data, 10, sizeof(int), int_equal);
    bh_sort(reference, 10, sizeof(int), int_equal);
    bh_heap_make(data, 10, sizeof(int), int_equal);
    bh_heap_make(reference, 10, sizeof(int), int_equal);
    BH_VERIFY(verify_heap(data, 10) == 0);
    BH_VERIFY(verify_heap(reference, 10) == 0);

    data[10] = 1000;
    value = 1000;
    bh_heap_replace(NULL, data, 10, sizeof(int), int_equal);
    bh_heap_remove(reference, 10, sizeof(int), int_equal);
    bh_heap_insert(&value, reference, 9, sizeof(int), int_equal);
    BH_VERIFY(verify_heap(data, 10) == 0);
    BH_VERIFY(verify_heap(reference, 10) == 0);
    bh_sort(data, 10, sizeof(int), int_equal);
    bh_sort(reference, 10, sizeof(int), int_equal);
    BH_VERIFY(memcmp(data, reference, 10 * sizeof(int)) == 0);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    bh_unit_add("sort", check_sort);
    bh_unit_add("partition", check_partition);
    bh_unit_add("heap_make", check_heap_make);
    bh_unit_add("heap_insert", check_heap_insert);
    bh_unit_add("heap_remove", check_heap_remove);
    bh_unit_add("heap_replace", check_heap_replace);

    return bh_unit_run();
}