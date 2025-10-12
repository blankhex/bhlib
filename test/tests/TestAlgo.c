#include <BH/Algo.h>
#include <BH/Unit.h>
#include <string.h>
#include <stdlib.h>


static int DBG_IntEqual(const void *lhs,
                        const void *rhs)
{
    return *(const int*)lhs - *(const int*)rhs;
}


static int DBG_VerifyPartition(size_t index,
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


static int DBG_VerifyHeap(int *array,
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


static int DBG_ReferenceRand(void)
{
    static uint32_t next = 2025;
    next = next * 1103515245 + 12345;
    return (next / 65536) % 32768;
}


static void DBG_ReferenceSort(int *array,
                              size_t size)
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


static void DBG_FillArrays(int *array,
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
        array[i] = DBG_ReferenceRand();

        if (mask > 1)
            array[i] = array[i] % mask;

        if (negate)
            array[i] = -array[i];

        if (reference)
            reference[i] = array[i];
    }
}


static int CheckSort(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int reference[317], data[317];

    /* Test empty array and one element arrays */
    data[0] = 1; data[1] = 2; data[2] = 3;
    BH_Sort(data, 0, sizeof(int), DBG_IntEqual);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    BH_Sort(data, 1, sizeof(int), DBG_IntEqual);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 0);
        DBG_ReferenceSort(reference, *size);
        BH_Sort(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    /* Test against negative values */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, -1);
        DBG_ReferenceSort(reference, *size);
        BH_Sort(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 4);
        DBG_ReferenceSort(reference, *size);
        BH_Sort(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(memcmp(reference, data, *size * sizeof(int)) == 0);
    }

    return 0;
}


static int CheckPartition(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int reference[317], data[317], value, *pivot;

    /* Test empty array and one element array */
    data[0] = 1; data[1] = 2; data[2] = 3;
    value = 0;
    pivot = BH_Partition(&value, data, 0, sizeof(int), DBG_IntEqual);
    BH_VERIFY(pivot != NULL);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    pivot = BH_Partition(&value, data, 1, sizeof(int), DBG_IntEqual);
    BH_VERIFY(pivot == data);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 0);
        value = 16384;
        pivot = BH_Partition(&value, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against negative values */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, -1);
        value = -16384;
        pivot = BH_Partition(&value, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 4);
        value = 2;
        pivot = BH_Partition(&value, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against small pivots */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 0);
        value = -100;
        pivot = BH_Partition(&value, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against large pivots */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 0);
        value = 65536;
        pivot = BH_Partition(&value, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test array against different sizes (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 0);
        value = data[0];
        pivot = BH_Partition(data, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against negative values (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, -1);
        value = data[0];
        pivot = BH_Partition(data, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Test against duplicates (pivot inside the array) */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, reference, *size, 4);
        value = data[0];
        pivot = BH_Partition(data, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    /* Same data test */
    for (size = sizes; *size; ++size)
    {
        memset(data, 0, sizeof(int) * *size);
        memset(reference, 0, sizeof(int) * *size);
        value = data[*size - 1];
        pivot = BH_Partition(data + *size - 1, data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyPartition(pivot - data, value, data, *size) == 0);

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size * sizeof(int)) == 0);
    }

    return 0;
}


static int CheckHeapMake(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317];

    /* Test empty array */
    data[0] = 1; data[1] = 2; data[2] = 3;
    BH_HeapMake(data, 0, sizeof(int), DBG_IntEqual);
    BH_VERIFY(data[0] == 1);
    BH_VERIFY(data[1] == 2);
    BH_VERIFY(data[2] == 3);

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, NULL, *size, 0);
        BH_HeapMake(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyHeap(data, *size) == 0);
    }

    /* Test array against negative values */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, NULL, *size, -1);
        BH_HeapMake(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyHeap(data, *size) == 0);
    }

    /* Test against duplicates */
    for (size = sizes; *size; ++size)
    {
        DBG_FillArrays(data, NULL, *size, 4);
        BH_HeapMake(data, *size, sizeof(int), DBG_IntEqual);
        BH_VERIFY(DBG_VerifyHeap(data, *size) == 0);
    }

    return 0;
}


static int CheckHeapInsert(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317], reference[317];

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        size_t i;
        DBG_FillArrays(data, reference, *size, 0);
        for (i = 0; i < *size; ++i)
        {
            int value;

            value = data[i];
            BH_HeapInsert(&value, data, i, sizeof(int), DBG_IntEqual);
            BH_VERIFY(DBG_VerifyHeap(data, i + 1) == 0);
        }

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    /* Test array against different sizes (inplace)*/
    for (size = sizes; *size; ++size)
    {
        size_t i;
        DBG_FillArrays(data, reference, *size, 0);
        for (i = 0; i < *size; ++i)
        {
            BH_HeapInsert(NULL, data, i, sizeof(int), DBG_IntEqual);
            BH_VERIFY(DBG_VerifyHeap(data, i + 1) == 0);
        }

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    return 0;
}


static int CheckHeapRemove(void)
{
    size_t sizes[] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0}, *size;
    int data[317], reference[317];

    /* Test array against different sizes */
    for (size = sizes; *size; ++size)
    {
        size_t i;
        DBG_FillArrays(data, reference, *size, 0);
        BH_HeapMake(data, *size, sizeof(int), DBG_IntEqual);

        for (i = *size; i > 0; i--)
        {
            BH_VERIFY(DBG_VerifyHeap(data, i) == 0);
            BH_HeapRemove(data, i, sizeof(int), DBG_IntEqual);
        }

        DBG_ReferenceSort(data, *size);
        DBG_ReferenceSort(reference, *size);
        BH_VERIFY(memcmp(data, reference, *size) == 0);
    }

    return 0;
}


static int CheckHeapReplace(void)
{
    int data[11] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0};
    int reference[11] = {1, 2, 3, 5, 11, 23, 41, 79, 163, 317, 0};
    int value;

    /* Prepare test arrays */
    BH_HeapMake(data, 10, sizeof(int), DBG_IntEqual);
    BH_HeapMake(reference, 10, sizeof(int), DBG_IntEqual);
    BH_VERIFY(DBG_VerifyHeap(data, 10) == 0);
    BH_VERIFY(DBG_VerifyHeap(reference, 10) == 0);

    /* Verfify heap replace */
    value = 20;
    BH_HeapReplace(&value, data, 10, sizeof(int), DBG_IntEqual);
    BH_HeapRemove(reference, 10, sizeof(int), DBG_IntEqual);
    BH_HeapInsert(&value, reference, 9, sizeof(int), DBG_IntEqual);

    BH_VERIFY(DBG_VerifyHeap(data, 10) == 0);
    BH_VERIFY(DBG_VerifyHeap(reference, 10) == 0);
    BH_Sort(data, 10, sizeof(int), DBG_IntEqual);
    BH_Sort(reference, 10, sizeof(int), DBG_IntEqual);
    BH_VERIFY(memcmp(data, reference, 10 * sizeof(int)) == 0);

    /* Verify heap replace on single element array */
    value = 400;
    BH_HeapReplace(&value, data, 1, sizeof(int), DBG_IntEqual);
    BH_HeapRemove(reference, 1, sizeof(int), DBG_IntEqual);
    BH_HeapInsert(&value, reference, 0, sizeof(int), DBG_IntEqual);

    BH_VERIFY(DBG_VerifyHeap(data, 1) == 0);
    BH_VERIFY(DBG_VerifyHeap(reference, 1) == 0);
    BH_VERIFY(memcmp(data, reference, 1 * sizeof(int)) == 0);

    /* Prepare test arrays */
    BH_Sort(data, 10, sizeof(int), DBG_IntEqual);
    BH_Sort(reference, 10, sizeof(int), DBG_IntEqual);
    BH_HeapMake(data, 10, sizeof(int), DBG_IntEqual);
    BH_HeapMake(reference, 10, sizeof(int), DBG_IntEqual);
    BH_VERIFY(DBG_VerifyHeap(data, 10) == 0);
    BH_VERIFY(DBG_VerifyHeap(reference, 10) == 0);

    data[10] = 1000;
    value = 1000;
    BH_HeapReplace(NULL, data, 10, sizeof(int), DBG_IntEqual);
    BH_HeapRemove(reference, 10, sizeof(int), DBG_IntEqual);
    BH_HeapInsert(&value, reference, 9, sizeof(int), DBG_IntEqual);
    BH_VERIFY(DBG_VerifyHeap(data, 10) == 0);
    BH_VERIFY(DBG_VerifyHeap(reference, 10) == 0);
    BH_Sort(data, 10, sizeof(int), DBG_IntEqual);
    BH_Sort(reference, 10, sizeof(int), DBG_IntEqual);
    BH_VERIFY(memcmp(data, reference, 10 * sizeof(int)) == 0);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UnitAdd("Sort", CheckSort);
    BH_UnitAdd("Partition", CheckPartition);
    BH_UnitAdd("HeapMake", CheckHeapMake);
    BH_UnitAdd("HeapInsert", CheckHeapInsert);
    BH_UnitAdd("HeapRemove", CheckHeapRemove);
    BH_UnitAdd("HeapReplace", CheckHeapReplace);

    return BH_UnitRun();
}
