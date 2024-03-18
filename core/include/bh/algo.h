/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */

#ifndef BHLIB_ALGO_H
#define BHLIB_ALGO_H

#include "bh.h"

void bh_swap(void *a, void *b, size_t size);
void bh_sort(void *array, size_t element, size_t size, bh_compare_cb_t compare);
void bh_heap_make(void *array, size_t element, size_t size, bh_compare_cb_t compare);
void bh_heap_pop(void *array, size_t element, size_t size, bh_compare_cb_t compare);
void bh_heap_push(const void *item, void *array, size_t element, size_t size, bh_compare_cb_t compare);

#endif /* BHLIB_ALGO_H */
