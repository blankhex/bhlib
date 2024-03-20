/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */

#ifndef BHLIB_H
#define BHLIB_H

#include <stddef.h>

typedef int (*bh_compare_cb_t)(const void *, const void *);
typedef size_t (*bh_hash_cb_t)(const void *);

#endif /* BHLIB_H */
