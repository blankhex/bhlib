/*
 * BHLib
 *
 * Copyright (c) 2024 Mikhail Romanko
 */

/**
 * @file bh/ds.h
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

/**
 * Initialize the array with the specified element size.
 *
 * Initialized array will be empty both in terms of capacity or size.
 *
 * @param array    Pointer to the array
 * @param element  Element size
 *
 * @sa bh_array_destroy
 */
void bh_array_init(bh_array_t *array,
                   size_t element);

/**
 * Destroy array.
 *
 * Memory allocated by an array will be freed.
 *
 * @param array  Pointer to the array
 *
 * @warning If array's elements require custom destruction (by calling their
 *          respective destroy function) - then user should iterate over an
 *          array to manually destroy elements.
 *
 * @sa bh_array_clear, bh_array_remove
 */
void bh_array_destroy(bh_array_t *array);

/**
 * Reset array size counter to zero.
 *
 * @param array  Pointer to the array
 *
 * @warning If array's elements require custom destruction (by calling their
 *          respective destroy function) - then user should iterate over an
 *          array to manually destroy elements.
 *
 * @sa bh_array_destroy, bh_array_remove
 */
void bh_array_clear(bh_array_t *array);

/**
 * Reserve memory for the array to store required elements.
 *
 * @param array  Pointer to the array
 * @param size   Anticipated array size
 *
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_array_capacity, bh_array_resize
 */
int bh_array_reserve(bh_array_t *array,
                     size_t size);

/**
 * Changes array's size.
 *
 * In case where new size is bigger then array's capacity - bh_array_reserve
 * will be called implicitly.
 *
 * @param array  Pointer to the array
 * @param size   New size of the array
 *
 * @return 0 on success, non-zero otherwise
 *
 * @warning In case of array growing - inserted items are not initialized.
 * @warning In case of array shrinking - removed items are not destroyed.
 *
 * @sa bh_array_reserve, bh_array_size
 */
int bh_array_resize(bh_array_t *array,
                    size_t size);

/**
 * Prepare space in array for the new element at specified index.
 *
 * @param array  Pointer to the array
 * @param index  Index
 * @return Non-null iterator on success, null otherwise
 *
 * @warning If index value greater-or-equal to array size - element
 *          will be inserted at the back of an array.
 *
 * @warning Inserted element are not initialized.
 *
 * @sa bh_array_remove, bh_array_next, bh_array_value
 */
void *bh_array_insert(bh_array_t *array,
                      size_t index);

/**
 * Return iterator to the specified index.
 *
 * @param array  Pointer to the array
 * @param index  Index
 * @return Non-null iterator on success, null otherwise
 *
 * @sa bh_array_next, bh_array_value, bh_array_remove
 */
void *bh_array_at(bh_array_t *array,
                  size_t index);

/**
 * Remove element by iterator.
 *
 * All elements to the right of the element pointed by iterator
 * will be shifted left.
 *
 * @param array  Pointer to the array
 * @param iter   Iterator
 * @return Iterator to the next element or null if reached the end
 *
 * @warning Removed element are not destroyed.
 *
 * @sa bh_array_at, bh_array_insert, bh_array_next, bh_array_value
 */
void *bh_array_remove(bh_array_t *array,
                      void *iter);

/**
 * Return iterator to the next element.
 *
 * If passed NULL-iterator, then iterator for the first element will
 * be returned.
 *
 * @param array  Pointer to the array
 * @param iter   Iterator
 * @return Iterator to the next element or null if reached the end
 * 
 * @sa bh_array_value, bh_array_remove
 */
void *bh_array_next(bh_array_t *array,
                    void *iter);

/**
 * Return pointer to the array value.
 *
 * @param array  Pointer to the array
 * @param iter   Iterator
 * @return Pointer to the array value
 *
 * @sa bh_array_next, bh_array_remove
 */
void *bh_array_value(bh_array_t *array,
                     void *iter);

/**
 * Return array size
 *
 * @param array  Pointer to the array
 * @return Array size
 *
 * @sa bh_array_capacity
 */
#define bh_array_size(array) \
    (array)->size

/**
 * Return array capacity.
 *
 * @param array  Pointer to the array
 * @return Array capacity
 *
 * @sa bh_array_size
 */
#define bh_array_capacity(array) \
    (array)->capacity

/**
 * Return pointer to the beginning of the data.
 *
 * @param array  Pointer to the array
 * @return Pointer to the data or null (if array doesn't have capacity)
 */
#define bh_array_data(array) \
    (array)->data

/**
 * Initialize map with specified key and value size, comparasion and hash
 * functions.
 *
 * Initialized map will be empty in both size and capacity terms.
 *
 * @param map      Pointer to the map
 * @param key      Key size
 * @param value    Value size
 * @param compare  Compare function
 * @param hash     Hash fucntion
 *
 * @sa bh_map_destroy
 */
void bh_map_init(bh_map_t *map,
                 size_t key,
                 size_t value,
                 bh_compare_cb_t compare,
                 bh_hash_cb_t hash);

/**
 * Destroy map.
 *
 * Memory allocated by the map will be freed.
 *
 * @param map  Pointer to the map
 *
 * @warning If map's elements require custom destruction (by calling their
 *          respective destroy function) - then user should iterate over a
 *          map to manually destroy elements.
 */
void bh_map_destroy(bh_map_t *map);

/**
 * Reset map size to zero.
 *
 * @param map  Pointer to the map
 *
 * @warning If map's elements require custom destruction (by calling their
 *          respective destroy function) - then user should iterate over a
 *          map to manually destroy elements.
 */
void bh_map_clear(bh_map_t *map);

/**
 * Reserve memory for the map to store required elements.
 *
 * @param map   Pointer to the map
 * @param size  Anticipated map size
 *
 * @return 0 on success, non-zero otherwise
 *
 * @sa bh_map_capacity
 */
int bh_map_reserve(bh_map_t *map,
                   size_t size);

/**
 * Prepare space in map for the new element at specified key.
 *
 * @param map  Pointer to the map
 * @param key  Pointer to the key value
 * @return Non-null iterator on success, null otherwise
 *
 * @warning Inserted element (key and value) are not initialized.
 *
 * @sa bh_map_remove, bh_map_next, bh_map_key, bh_map_value
 */
void *bh_map_insert(bh_map_t *map,
                    void *key);

/**
 * Return iterator to the specified key.
 *
 * @param map  Pointer to the map
 * @param key  Pointer to the key
 * @return Non-null iterator on success, null otherwise
 *
 * @sa bh_map_next, bh_map_key, bh_map_value, bh_map_remove
 */
void *bh_map_at(bh_map_t *map,
                void *key);

/**
 * Remove element by iterator.
 *
 * @param map   Pointer to the map
 * @param iter  Iterator
 * @return Iterator to the next element or null if reached the end
 *
 * @warning Removed element are not destroyed.
 *
 * @sa bh_map_at, bh_map_insert, bh_map_next, bh_map_key, bh_map_value
 */
void *bh_map_remove(bh_map_t *map,
                void *iter);

/**
 * Return iterator to the next element.
 *
 * If passed NULL-iterator, then iterator for the first element will
 * be returned.
 *
 * @param map   Pointer to the map
 * @param iter  Iterator
 * @return Iterator to the next element or null if reached the end
 *
 * @sa bh_map_key, bh_map_value, bh_map_remove
 */
void *bh_map_next(bh_map_t *map,
                  void *iter);

/**
 * Return pointer to the map key.
 *
 * @param map   Pointer to the map
 * @param iter  Iterator
 * @return Pointer to the map key
 *
 * @sa bh_map_value, bh_map_next, bh_map_remove
 */
void *bh_map_key(bh_map_t *map,
                 void *iter);

/**
 * Return pointer to the map value.
 *
 * @param map   Pointer to the map
 * @param iter  Iterator
 * @return Pointer to the map value
 *
 * @sa bh_map_value, bh_map_next, bh_map_remove
 */
void *bh_map_value(bh_map_t *map,
                   void *iter);

/**
 * Return map size.
 *
 * @param map  Pointer to the map
 * @return Map size
 *
 * @sa bh_map_capacity
 */
#define bh_map_size(map) \
    (map)->size

/**
 * Return map capacity.
 *
 * @param map  Pointer to the map
 * @return Map capacity
 *
 * @sa bh_map_size
 */
#define bh_map_capacity(map) \
    (map)->capacity

#endif /* BHLIB_DS_H */
