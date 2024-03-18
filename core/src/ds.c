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
#include <bh/ds.h>
#include <bh/algo.h>
#include <string.h>
#include <stdlib.h>

void bh_array_init(struct bh_array *array, size_t element)
{
    memset(array, 0, sizeof(*array));
    array->element = element;
}

void bh_array_destroy(struct bh_array *array)
{
    if (array->data)
        free(array->data);
}

void bh_array_clear(struct bh_array *array)
{
    array->size = 0;
}

int bh_array_reserve(struct bh_array *array, size_t size)
{
    void *data;
    size_t capacity;

    /* Requested capacity should be in range [array->size; max_capacity] */
    capacity = size;
    if (capacity < array->size)
        capacity = array->size;

    if (capacity > ((size_t)-1) / array->element)
        return -1;

    /* Prevent same size reallocation */
    if (capacity == array->capacity)
        return 0;

    /* Allocate and copy data */
    data = NULL;
    if (capacity)
    {
        data = malloc(array->element * capacity);
        if (!data)
            return -1;
        if (array->data)
            memmove(data, array->data, array->size * array->element);
    }

    /* Update array fields */
    if (array->data)
        free(array->data);
    array->data = data;
    array->capacity = capacity;
    return 0;
}

void *bh_array_insert(struct bh_array *array, size_t index)
{
    size_t move_size;
    char *from, *to;

    /* Check array capacity */
    if (array->capacity < array->size + 1)
    {
        size_t capacity;

        /* Check potential size overflow and reserve capacity */
        capacity = (array->size) ? (array->size * 2) : (16);
        if (capacity < array->size || bh_array_reserve(array, capacity))
            return NULL;
    }

    /* Index should be in valid range */
    index = (index > array->size) ? (array->size) : (index);

    /* Shift data to the right */
    move_size = (array->size - index) * array->element;
    from = (char *)array->data + index * array->element;
    to = from + array->element;
    memmove(to, from, move_size);

    /* Update array fields and return iterator */
    array->size++;
    return from;
}

void *bh_array_at(struct bh_array *array, size_t index)
{
    return (char *)array->data + index * array->element;
}

void *bh_array_remove(struct bh_array *array, void *iter)
{
    size_t move_size, index;
    char *from, *to;

    /* Iterator should be valid */
    index = ((char *)iter - (char *)array->data) / array->element;
    if (index >= array->size)
        return NULL;

    /* Shift data to the left */
    move_size = (array->size - index - 1) * array->element;
    to = (char *)array->data + index * array->element;
    from = to + array->element;
    memmove(to, from, move_size);

    /* Update array fields and return iterator */
    array->size--;
    if (index >= array->size)
        return NULL;

    return iter;
}

void *bh_array_next(struct bh_array *array, void *iter)
{
    char *item = (char *)iter;

    /* Advance or set iterator */
    if (item)
        item += array->element;
    else
        item = array->data;

    /* Check iterator for validity */
    if (item >= (char *)array->data + array->size * array->element)
        return NULL;

    return item;
}

void *bh_array_value(struct bh_array *array, void *iter)
{
    (void)array;
    return iter;
}

void bh_map_init(struct bh_map *map, size_t key, size_t value, int (*compare)(void *, void *), size_t (*hash)(void *))
{
    memset(map, 0, sizeof(*map));
    map->element.key = key;
    map->element.value = value;
    map->compare = compare;
    map->hash = hash;
}

void bh_map_destroy(struct bh_map *map)
{
    if (map->capacity)
    {
        free(map->data.key);
        free(map->data.value);
        free(map->data.psl);
    }
}

void bh_map_clear(struct bh_map *map)
{
    /* Reset probe sequence lengths and map size */
    if (map->capacity)
        memset(map->data.psl, 0, sizeof(size_t) * map->capacity);
    map->size = 0;
}

int bh_map_reserve(struct bh_map *map, size_t size)
{
    struct bh_map other;
    size_t capacity, max_capacity, max_element;

    capacity = map->capacity;

    /* Calculate max capacity (with 2 additional elements) */
    max_element = sizeof(size_t) + map->element.key + map->element.value;
    max_capacity = (((size_t)-1) / max_element) - 1;

    /* Requested capacity can't be lower than current map size */
    if (size < map->size)
        size = map->size;

    /* Find best capacity for the given size */
    if (!size)
        capacity = 0;
    else if (size > capacity / 8 * 7)
    {
        /* Find larger capacity to fit elements with load factor 87.5% */
        while (size > capacity / 8 * 7)
        {
            capacity = (capacity) ? (capacity * 2) : (16);

            /* Capacity can't be bigger than max capacity and overflow */
            if (capacity > max_capacity || capacity < 16)
                return -1;
        }
    }
    else
    {
        /* Find smaller capacity to fit elements with load factor 87.5% */
        while (size <= capacity / 16 * 7 && capacity > 16)
            capacity /= 2;
    }

    /* Prevent same size reallocation */
    if (capacity == map->capacity)
        return 0;

    bh_map_init(&other, map->element.key, map->element.value, map->compare, map->hash);
    if (capacity)
    {
        void *iter;

        /* Prepare new map */
        other.data.key = malloc(other.element.key * (capacity + 1));
        other.data.value = malloc(other.element.value * (capacity + 1));
        other.data.psl = malloc(sizeof(size_t) * (capacity + 1));
        other.capacity = capacity;

        if (!other.data.key || !other.data.value || !other.data.psl)
        {
            if (other.data.key)
                free(other.data.key);
            if (other.data.value)
                free(other.data.value);
            if (other.data.psl)
                free(other.data.psl);
            return -1;
        }

        /* Reset probe sequence lengths */
        memset(other.data.psl, 0, sizeof(size_t) * other.capacity);

        /* Iterate over map */
        for (iter = bh_map_next(map, NULL); iter; iter = bh_map_next(map, iter))
        {
            void *item;

            /* Insert and copy data */
            item = bh_map_insert(&other, bh_map_key(map, iter));
            memmove(bh_map_key(&other, item), bh_map_key(map, iter), other.element.key);
            memmove(bh_map_value(&other, item), bh_map_value(map, iter), other.element.value);
        }
    }

    /* Destroy previous map, update map fields */
    bh_map_destroy(map);
    memmove(map, &other, sizeof(other));
    return 0;
}

void *bh_map_insert(struct bh_map *map, void *key)
{
    size_t bucket, *item_psl, *bucket_psl;
    void *item_key, *item_value, *bucket_key, *bucket_value, *result;

    /* Capcity should try to keep 87.5% load factor */
    if (map->size + 1 > map->capacity / 8 * 7)
        if (bh_map_reserve(map, map->size + 1) && map->size >= map->capacity)
            return NULL;

    /* Prepare pointer for inserted and temporary item */
    item_psl = map->data.psl + map->capacity;
    item_key = (char *)map->data.key + map->capacity * map->element.key;
    item_value = (char *)map->data.value + map->capacity * map->element.value;

    /* Calculate prefered bucket index and set PSL to 1 */
    bucket = map->hash(key) & (map->capacity - 1);
    *item_psl = 1;
    result = NULL;

    /* Find empty bucket */
    while (map->data.psl[bucket])
    {
        /* Current bucket is richer then us - swap elements */
        if (*item_psl > map->data.psl[bucket])
        {
            bucket_psl = map->data.psl + bucket;
            bucket_key = (char *)map->data.key + bucket * map->element.key;
            bucket_value = (char *)map->data.value + bucket * map->element.value;

            bh_swap(bucket_psl, item_psl, sizeof(size_t));
            bh_swap(bucket_key, item_key, map->element.key);
            bh_swap(bucket_value, item_value, map->element.key);

            /* If this is first swap - store current bucket address */
            if (!result)
                result = bucket_psl;
        }

        bucket = (bucket + 1) & (map->capacity - 1);
        (*item_psl)++;
    }

    /* Found empty bucket - place element here */
    bucket_psl = map->data.psl + bucket;
    bucket_key = (char *)map->data.key + bucket * map->element.key;
    bucket_value = (char *)map->data.value + bucket * map->element.value;

    memmove(bucket_psl, item_psl, sizeof(size_t));
    memmove(bucket_key, item_key, map->element.key);
    memmove(bucket_value, item_value, map->element.value);
    map->size++;

    /* If this is first swap - store current bucket address */
    if (!result)
        result = bucket_psl;
    return result;
}

void *bh_map_at(struct bh_map *map, void *key)
{
    size_t bucket, psl;
    void *bucket_key;

    /* Nothing can be in empty map */
    if (!map->size)
        return NULL;

    /* Calculate prefered bucket index and set PSL to 1 */
    bucket = map->hash(key) & (map->capacity - 1);
    bucket_key = (char *)map->data.key + map->element.key * bucket;
    psl = 1;

    /* Iterate map until we find element or find richer bucket */
    while (map->data.psl[bucket] >= psl && map->compare(bucket_key, key))
    {
        bucket = (bucket + 1) & (map->capacity - 1);
        bucket_key = (char *)map->data.key + map->element.key * bucket;
        psl++;
    }

    /* If bucket is poorer or equal to us - we found our element */
    if (map->data.psl[bucket] >= psl)
        return map->data.psl + bucket;

    return NULL;
}

void *bh_map_remove(struct bh_map *map, void *iter)
{
    size_t bucket, next_bucket, *current_psl, *next_psl;
    void *current_key, *next_key, *current_value, *next_value;

    if (!iter || !map->size)
        return NULL;

    map->size--;
    bucket = (size_t *)iter - map->data.psl;
    next_bucket = (bucket + 1) & (map->capacity - 1);

    current_psl = map->data.psl + bucket;
    current_key = (char *)map->data.key + bucket * map->element.key;
    current_value = (char *)map->data.value + bucket * map->element.value;
    next_psl = map->data.psl + next_bucket;
    next_key = (char *)map->data.key + next_bucket * map->element.key;
    next_value = (char *)map->data.value + next_bucket * map->element.value;

    while (map->data.psl[next_bucket] > 1)
    {
        /* Copy item and adjust PSL */
        memmove(current_psl, next_psl, sizeof(size_t));
        memmove(current_key, next_key, map->element.key);
        memmove(current_value, next_value, map->element.value);
        (*current_psl)--;

        /* Calculate next bucket index */
        bucket = next_bucket;
        current_psl = next_psl;
        current_key = next_key;
        current_value = next_value;

        next_bucket = (bucket + 1) & (map->capacity - 1);
        next_psl = map->data.psl + next_bucket;
        next_key = (char *)map->data.key + next_bucket * map->element.key;
        next_value = (char *)map->data.value + next_bucket * map->element.value;
    }

    /* Mark bucket as empty */
    *current_psl = 0;

    /* If current iterator is still valid - return it */
    if (*((size_t *)iter))
        return iter;

    /* Otherwise advance iterator */
    return bh_map_next(map, iter);
}

void *bh_map_next(struct bh_map *map, void *iter)
{
    size_t *item;

    /* Iterate over map */
    item = (size_t *)iter;
    while (1)
    {
        /* Set iterator to the first element or advance to the next position */
        if (item == NULL)
            item = map->data.psl;
        else
            item++;

        /* Check iterator for validity */
        if (item >= map->data.psl + map->capacity)
            return NULL;

        /* If iterator points to non-empty bucket - we are done */
        if (*item)
            return item;
    }
}

void *bh_map_key(struct bh_map *map, void *iter)
{
    size_t index;

    index = (size_t *)iter - map->data.psl;
    return (char *)map->data.key + index * map->element.key;
}

void *bh_map_value(struct bh_map *map, void *iter)
{
    size_t index;

    index = (size_t *)iter - map->data.psl;
    return (char *)map->data.value + index * map->element.value;
}

