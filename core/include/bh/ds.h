/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */

#ifndef BHLIB_DS_H
#define BHLIB_DS_H

#include "bh.h"
#include <stddef.h>

typedef struct
{
    void *data;
    size_t size;
    size_t capacity;
    size_t element;
} bh_array_t;

typedef struct
{
    struct
    {
        void *key;
        void *value;
        size_t *psl;
    } data;
    struct
    {
        size_t key;
        size_t value;
    } element;

    size_t size;
    size_t capacity;

    bh_compare_cb_t compare;
    bh_hash_cb_t hash;
} bh_map_t;

void bh_array_init(bh_array_t *array,
                   size_t element);

void bh_array_destroy(bh_array_t *array);

void bh_array_clear(bh_array_t *array);

int bh_array_reserve(bh_array_t *array,
                     size_t size);

int bh_array_resize(bh_array_t *array,
                    size_t size);

void *bh_array_insert(bh_array_t *array,
                      size_t index);

void *bh_array_at(bh_array_t *array,
                  size_t index);

void *bh_array_remove(bh_array_t *array,
                      void *iter);

void *bh_array_next(bh_array_t *array,
                    void *iter);

void *bh_array_value(bh_array_t *array,
                     void *iter);

#define bh_array_size(array) \
    (array)->size

#define bh_array_capacity(array) \
    (array)->capacity

#define bh_array_data(array) \
    (array)->data

void bh_map_init(bh_map_t *map,
                 size_t key,
                 size_t value,
                 bh_compare_cb_t compare,
                 bh_hash_cb_t hash);

void bh_map_destroy(bh_map_t *map);

void bh_map_clear(bh_map_t *map);

int bh_map_reserve(bh_map_t *map,
                   size_t size);

void *bh_map_insert(bh_map_t *map,
                    void *key);

void *bh_map_at(bh_map_t *map,
                void *key);

void *bh_map_remove(bh_map_t *map,
                void *iter);

void *bh_map_next(bh_map_t *map,
                  void *iter);

void *bh_map_key(bh_map_t *map,
                 void *iter);

void *bh_map_value(bh_map_t *map,
                   void *iter);

#define bh_map_size(map) \
    (map)->size

#define bh_map_capacity(map) \
    (map)->capacity

#endif /* BHLIB_DS_H */
