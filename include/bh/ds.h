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
 * Example:
 * ```c
 * bh_array_t array;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * bh_array_destroy(&array);
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(HANDLE));
 *
 * do_stuff();
 *
 * for (iter = bh_array_next(&array, NULL); iter; iter = bh_array_next(&array, iter))
 *     CloseHandle(*(HANDLE*)bh_array_value(&array, iter));
 *
 * bh_array_destroy(&array);
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(HANDLE));
 *
 * do_stuff();
 *
 * for (iter = bh_array_next(&array, NULL); iter; iter = bh_array_next(&array, iter))
 *     CloseHandle(*(HANDLE*)bh_array_value(&array, iter));
 *
 * bh_array_clear(&array);
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * bh_array_init(&array, sizeof(int));
 *
 * if (bh_array_reserve(&array, 1024))
 * {
 *     fprintf(stderr, "Can't reserve space for the array!\n");
 *     return -1;
 * }
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * bh_array_init(&array, sizeof(int));
 *
 * if (bh_array_resize(&array, 1024))
 * {
 *     fprintf(stderr, "Can't resize an array!");
 *     return -1;
 * }
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * size_t i;
 * bh_array_init(&array, sizeof(int));
 *
 * for (i = 0; i < 8; i++)
 * {
 *     iter = bh_array_insert(&array, 0);
 *     if (!iter)
 *         return -1;
 *     *(int *)bh_array_value(&array, iter) = i;
 *
 *     iter = bh_array_insert(&array, -1);
 *     if (!iter)
 *         return -1;
 *     *(int *)bh_array_value(&array, iter) = i;
 * }
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * iter = bh_array_at(&array, 0);
 * if (iter)
 *     printf("Value at index 0: %d\n", *(int *)bh_array_value(&array, iter));
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * for (iter = bh_array_next(&array, NULL); iter;)
 * {
 *     if (*(int *)bh_array_value(&array, iter) % 2)
 *         iter = bh_array_remove(&array, iter);
 *     else
 *         iter = bh_array_next(&array, iter);
 * }
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * for (iter = bh_array_next(&array, NULL); iter; iter = bh_array_next(&array, iter))
 *     printf("Element %d\n", *(int *)bh_array_value(&array, iter));
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * void *iter;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * for (iter = bh_array_next(&array, NULL); iter; iter = bh_array_next(&array, iter))
 *     printf("Element %d\n", *(int *)bh_array_value(&array, iter));
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * printf("Array size: %d", (int)bh_array_size(&array));
 * ```
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
 * Example:
 * ```c
 * bh_array_t array;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * printf("Array capacity: %d", (int)bh_array_size(&array));
 * ```
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
 *
 * Example:
 * ```c
 * bh_array_t array;
 * int *int_array;
 * bh_array_init(&array, sizeof(int));
 *
 * do_stuff();
 *
 * int_array = (int *)bh_array_data(&array);
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * bh_map_init(&map, sizeof(int), sizeof(char *), int_compare, int_hash);
 *
 * do_stuff();
 *
 * bh_map_destroy(&map);
 * ```
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
 *
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(HANDLE), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter; iter = bh_map_next(&map, iter))
 *     CloseHandle(*(HANDLE*)bh_map_value(&map, iter));
 *
 * bh_map_destroy(&map);
 * ```
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
 *
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(HANDLE), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter; iter = bh_map_next(&map, iter))
 *     CloseHandle(*(HANDLE*)bh_map_value(&map, iter));
 *
 * bh_map_clear(&map);
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * bh_map_init(&map, sizeof(int), sizeof(char *), int_compare, int_hash);
 *
 * if (bh_map_reserve(&map, 1024))
 * {
 *     fprintf(stderr, "Can't reserve space for the map!\n");
 *     return -1;
 * }
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * size_t i;
 * bh_map_init(&map, sizeof(size_t), sizeof(int), size_compare, size_hash);
 *
 * for (i = 0; i < 8; i++)
 * {
 *     iter = bh_map_insert(&map, &i);
 *     if (!iter)
 *         return -1;
 *
 *     *(size_t *)bh_map_key(&map, iter) = i;
 *     *(int *)bh_map_value(&map, iter) = i;
 * }
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * int key;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * key = 0;
 * iter = bh_map_at(&map, &key);
 *
 * if (iter)
 *     printf("Value at key %d: %d\n", key, *(int *)bh_map_value(&map, iter));
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter;)
 * {
 *     if (*(int *)bh_map_key(&map, iter) % 2)
 *         iter = bh_map_remove(&map, iter);
 *     else
 *         iter = bh_map_next(&map, iter);
 * }
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter; iter = bh_map_next(&map, iter))
 *     printf("Element value %d\n", *(int *)bh_map_value(&map, iter));
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter; iter = bh_map_next(&map, iter))
 *     printf("Element key %d\n", *(int *)bh_map_key(&map, iter));
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * void *iter;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * for (iter = bh_map_next(&map, NULL); iter; iter = bh_map_next(&map, iter))
 *     printf("Element value %d\n", *(int *)bh_map_value(&map, iter));
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * printf("Map size: %d", (int)bh_map_size(&map));
 * ```
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
 * Example:
 * ```c
 * bh_map_t map;
 * bh_map_init(&map, sizeof(int), sizeof(int), int_compare, int_hash);
 *
 * do_stuff();
 *
 * printf("Map capacity: %d", (int)bh_map_capacity(&map));
 * ```
 *
 * @sa bh_map_size
 */
#define bh_map_capacity(map) \
    (map)->capacity

#endif /* BHLIB_DS_H */
