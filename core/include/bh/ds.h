/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef BHLIB_DS_H
#define BHLIB_DS_H

#include <stddef.h>

struct bh_array
{
    void *data;
    size_t size;
    size_t capacity;
    size_t element;
};

/**
 *
 */
void bh_array_init(struct bh_array *array, size_t element);

/**
 *
 */
void bh_array_destroy(struct bh_array *array);

/**
 *
 */
void bh_array_clear(struct bh_array *array);

/**
 *
 */
int bh_array_reserve(struct bh_array *array, size_t size);

/**
 *
 */
void *bh_array_insert(struct bh_array *array, size_t index);

/**
 *
 */
void *bh_array_at(struct bh_array *array, size_t index);

/**
 *
 */
void *bh_array_remove(struct bh_array *array, void *iter);

/**
 *
 */
void *bh_array_next(struct bh_array *array, void *iter);

/**
 *
 */
void *bh_array_value(struct bh_array *array, void *iter);

struct bh_map
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

    int (*compare)(void *left, void *right);
    size_t (*hash)(void *key);
};

/**
 *
 */
void bh_map_init(struct bh_map *map, size_t key, size_t value, int (*compare)(void *, void *), size_t (*hash)(void *));

/**
 *
 */
void bh_map_destroy(struct bh_map *map);

/**
 *
 */
void bh_map_clear(struct bh_map *map);

/**
 *
 */
int bh_map_reserve(struct bh_map *map, size_t size);

/**
 *
 */
void *bh_map_insert(struct bh_map *map, void *key);

/**
 *
 */
void *bh_map_at(struct bh_map *map, void *key);

/**
 *
 */
void *bh_map_remove(struct bh_map *map, void *iter);

/**
 *
 */
void *bh_map_next(struct bh_map *map, void *iter);

/**
 *
 */
void *bh_map_key(struct bh_map *map, void *iter);

/**
 *
 */
void *bh_map_value(struct bh_map *map, void *iter);

#endif /* BHLIB_DS_H */
