#ifndef BH_ALGO_H
#define BH_ALGO_H


#include "Common.h"


/**
 * Exchanges values between \a src and \a dest elements of sizze \a size.
 *
 * \param dest	Destination element pointer
 * \param src	Source element pointer
 * \param size	Element size in bytes
 */
void BH_Swap(void *dest,
             void *src,
             size_t size);


/**
 * Partitions the \a array (with specified \a size and \a element size)
 * relative to specified \a pivot element.
 *
 * The \a pivot element can be part of the partitioned \a array.
 *
 * \param pivot    Pivot element pointer
 * \param array    Array pointer
 * \param size     Array size
 * \param element  Array element size
 * \param equal    Comparision function
 *
 * \return Pointer to the first element of the second partition.
 */
void *BH_Partition(void *pivot,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Sorts the \a array (with specified \a size and \a element size).
 *
 * The sorting algorithm is implementation defined and may change between
 * revisions.
 *
 * \param array    Array pointer
 * \param size     Array size
 * \param element  Array element size
 * \param equal    Comparision function
 */
void BH_Sort(void *array,
             size_t size,
             size_t element,
             BH_EqualCallback equal);


/**
 * Heapifies an \a array (with specified \a size and \a element size).
 *
 * \param array    Array pointer
 * \param size     Array size
 * \param element  Array element size
 * \param equal    Comparision function
 */
void BH_HeapMake(void *array,
                 size_t size,
                 size_t element,
                 BH_EqualCallback equal);


/**
 * Removes top value from the heapified \a array (with specified \a size
 * and \a element size).
 *
 * \param array     Array pointer
 * \param size      Array size
 * \param element   Array element size
 * \param equal     Comparasion function
 */
void BH_HeapRemove(void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Inserts new \a value into heapified \a array in an array (with specified
 * \a size and \a element size)
 *
 * If \a value pointer is NULL, it is assumed that new value is placed at the
 * end of the array.
 *
 * \param value    Value pointer
 * \param array    Array pointer
 * \param size     Array size
 * \param element  Array element size
 * \param equal    Comparasion function
 */
void BH_HeapInsert(void *value,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Removes top value from heapified \a array (with specified \a size and
 * \a element size) and inserts new \a value.
 *
 * If value pointer is NULL, it is assumed that new value is placed at the
 * end of the array.
 *
 * \param value    Value pointer
 * \param array    Array pointer
 * \param size     Array size
 * \param element  Array element size
 * \param equal    Comparasion function
 */
void BH_HeapReplace(void *value,
                    void *array,
                    size_t size,
                    size_t element,
                    BH_EqualCallback equal);


#endif /* BH_ALGO_H */
