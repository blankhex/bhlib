/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */

#ifndef BHLIB_ALGO_H
#define BHLIB_ALGO_H

#include "bh.h"

/**
 * Swap two elements.
 *
 * @param a     Left element
 * @param b     Right element
 * @param size  Element size
 *
 * Example:
 * ```c
 * int a = 1, b = 2;
 *
 * bh_swap(&a, &b, sizeof(int));
 * ```
 */
void bh_swap(void *a,
             void *b,
             size_t size);

/**
 * Sort array of elements.
 *
 * @param array    Pointer to the array
 * @param element  Element size
 * @param size     Array size
 * @param compare  Compare function
 *
 * ```c
 * int array[8] = {4, 3, 2, 1, 5, 6, 7, 8};
 *
 * bh_sort(array, sizeof(int), 8, int_compare);
 * ```
 */
void bh_sort(void *array,
             size_t element,
             size_t size,
             bh_compare_cb_t compare);

/**
 * Make heap from the array.
 *
 * @param array    Pointer to the array
 * @param element  Element size
 * @param size     Array size
 * @param compare  Compare function
 *
 * Example:
 * ```c
 * int array[8] = {4, 3, 2, 1, 5, 6, 7, 8};
 *
 * bh_heap_make(array, sizeof(int), 8, int_compare);
 * ```
 *
 * @sa bh_heap_push, bh_heap_pop
 */
void bh_heap_make(void *array,
                  size_t element,
                  size_t size,
                  bh_compare_cb_t compare);

/**
 * Removes element from the heap.
 *
 * Removed element is placed at the end of the array.
 *
 * @param array    Pointer to the array
 * @param element  Element size
 * @param size     Array size
 * @param compare  Compare function
 *
 * @warning Removed element is not destoyed.
 *
 * Example:
 * ```c
 * int array[8] = {4, 3, 2, 1, 5, 6, 7, 8};
 * bh_heap_make(array, sizeof(int), 8, int_compare);
 *
 * do_stuff();
 *
 * bh_heap_pop(array, sizeof(int), 8, int_compare);
 * ```
 *
 * @sa bh_heap_make, bh_heap_push
 */
void bh_heap_pop(void *array,
                 size_t element,
                 size_t size,
                 bh_compare_cb_t compare);

/**
 * Insert element into the heap.
 *
 * @param item     Pointer to the item
 * @param array    Pointer to the array
 * @param element  Element size
 * @param size     Array size
 * @param compare  Compare function
 *
 * Example:
 * ```c
 * int array[8];
 *
 * bh_heap_push(array, sizeof(int), 0, int_compare);
 * ```
 *
 * @sa bh_heap_make, bh_heap_pop
 */
void bh_heap_push(const void *item,
                  void *array,
                  size_t element,
                  size_t size,
                  bh_compare_cb_t compare);

#endif /* BHLIB_ALGO_H */
