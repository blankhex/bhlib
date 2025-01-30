#ifndef BH_ALGO_H
#define BH_ALGO_H


#include "common.h"


/**
 * Exchanges the values of two elements.
 *
 * \param dest	Pointer to the element
 * \param src	Pointer to the element
 * \param size	Element size in bytes
 */
void BH_Swap(void *dest,
             void *src,
             size_t size);


/**
 * Partitions the array relative to the specified pivot element.
 *
 * The pivot element can be part of the partitioned array.
 *
 * \param pivot     Pointer to the pivot element
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparision function
 *
 * \return Pointer to the first element of the second partition.
 */
void *BH_Partition(void *pivot,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Sorts the array.
 *
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparision function
 */
void BH_Sort(void *array,
             size_t size,
             size_t element,
             BH_EqualCallback equal);


/**
 * Makes heap in an array from the array.
 *
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparision function
 */
void BH_HeapMake(void *array,
                 size_t size,
                 size_t element,
                 BH_EqualCallback equal);


/**
 * Removes top/first element from a heap in an array.
 *
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparasion function
 */
void BH_HeapRemove(void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Inserts new element into heap in an array.
 *
 * If the pointer to value is NULL, this function assumes that the new value
 * is at the end of the array.
 *
 * \param value     Pointer to the value
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparasion function
 */
void BH_HeapInsert(void *value,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


/**
 * Removes top/first element and inserts new element into heap in an array.
 *
 * If the pointer to value is NULL, this function assumes that the new value
 * is at the end of the array.
 *
 * This function is roughly equivalent to the following code:
 * \code
 * BH_HeapRemove(array, size, element, equal);
 * BH_HeapInsert(value, array, size - 1, element, equal);
 * \endcode
 *
 * \param value     Pointer to the value
 * \param array     Pointer to the array
 * \param size      Array size
 * \param element   Element size in bytes
 * \param equal     Comparasion function
 */
void BH_HeapReplace(void *value,
                    void *array,
                    size_t size,
                    size_t element,
                    BH_EqualCallback equal);


#endif /* BH_ALGO_H */
