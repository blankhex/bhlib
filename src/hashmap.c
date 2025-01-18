#include <bh/hashmap.h>
#include <stdlib.h>
#include <string.h>


typedef struct bh_hashmap_node_s
{
    void *key;
    void *value;
} bh_hashmap_node_t;


struct bh_hashmap_s
{
    bh_hashmap_node_t *data;
    size_t *psls;
    size_t size;
    size_t capacity;
    size_t threshold;
    bh_equal_cb_t equal;
    bh_hash_cb_t hash;
    float factor;
};


static void bh_hashmap_init(bh_hashmap_t *hashmap,
                            bh_equal_cb_t equal,
                            bh_hash_cb_t hash)
{
    memset(hashmap, 0, sizeof(*hashmap));
    hashmap->factor = 0.75f;
    hashmap->equal = equal;
    hashmap->hash = hash;
}


static void bh_hashmap_destroy(bh_hashmap_t *hashmap)
{
    if (hashmap->capacity)
    {
        free(hashmap->data);
        free(hashmap->psls);
    }
}


static int calc_capacity(size_t size,
                         float factor,
                         size_t *capacity,
                         size_t *threshold)
{
    /* Check if we need any capacity at all */
    if (!size)
    {
        *capacity = 0;
        *threshold = 0;
        return BH_OK;
    }

    /* Calculate nearest power of 2 capacity */
    *capacity = 16;
    *threshold = *capacity * factor;
    while (size > *threshold)
    {
        *capacity *= 2;
        *threshold = *capacity * factor;

        /* Catch capacity overflow  */
        if (*capacity < 16)
            return BH_OOM;
    }

    /* Catch malloc overflow */
    if (*capacity >= ((size_t)-1) / sizeof(bh_hashmap_node_t))
        return BH_OOM;

    return BH_OK;
}


static void copy_hashmap(bh_hashmap_t *dest,
                         bh_hashmap_t *src)
{
    void *iter;

    /* Iterate and insert data into hashmap */
    iter = bh_hashmap_iter_next(src, NULL);
    while (iter)
    {
        void *key, *value;

        key = bh_hashmap_iter_key(iter);
        value = bh_hashmap_iter_value(iter);
        bh_hashmap_insert(dest, key, value);

        iter = bh_hashmap_iter_next(src, iter);
    }
}


bh_hashmap_t *bh_hashmap_new(bh_equal_cb_t equal,
                             bh_hash_cb_t hash)
{
    bh_hashmap_t *result;

    result = malloc(sizeof(*result));
    if (result)
        bh_hashmap_init(result, equal, hash);

    return result;
}


void bh_hashmap_free(bh_hashmap_t *hashmap)
{
    bh_hashmap_destroy(hashmap);
    free(hashmap);
}


void bh_hashmap_clear(bh_hashmap_t *hashmap)
{
    if (hashmap->capacity)
        memset(hashmap->psls, 0, hashmap->capacity * sizeof(size_t));
    hashmap->size = 0;
}


int bh_hashmap_reserve(bh_hashmap_t *hashmap,
                       size_t size)
{
    bh_hashmap_t other;
    size_t capacity, threshold;

    /* New capacity can't be smaller then current hashmap size */
    if (size < hashmap->size)
        size = hashmap->size;

    /* Calculate new capacity */
    if (calc_capacity(size, hashmap->factor, &capacity, &threshold))
        return BH_OOM;

    /* Prevent same size reallocation */
    if (capacity == hashmap->capacity)
        return BH_OK;

    /* Initialize new hashmap */
    bh_hashmap_init(&other, hashmap->equal, hashmap->hash);
    other.factor = hashmap->factor;

    if (capacity)
    {
        /* Allocate new memory for the hashmap */
        other.data = malloc(sizeof(*other.data) * capacity);
        other.psls = malloc(sizeof(size_t) * capacity);
        other.threshold = threshold;
        other.capacity = capacity;

        /* Check for allocations failure */
        if (!other.data || !other.psls)
        {
            if (other.data)
                free(other.data);
            if (other.psls)
                free(other.psls);
            return BH_OOM;
        }

        /* Reset probe sequence lengths */
        memset(other.psls, 0, sizeof(size_t) * other.capacity);

        /* Copy data from old hashmap to the new hashmap */
        copy_hashmap(&other, hashmap);
    }

    /* Swap hashmaps */
    bh_hashmap_destroy(hashmap);
    *hashmap = other;
    return BH_OK;
}


int bh_hashmap_insert(bh_hashmap_t *hashmap,
                      void *key,
                      void *value)
{
    size_t bucket, psl, tmp_psl;
    bh_hashmap_node_t item, tmp;

    /* Try to stay below hashmap threshold */
    if (hashmap->size + 1 > hashmap->threshold)
        if (bh_hashmap_reserve(hashmap, hashmap->size + 1))
            if (hashmap->size >= hashmap->capacity)
                return BH_OOM;

    /* Prepare inserted data and set PSL to 1 */
    item.key = key;
    item.value = value;
    psl = 1;

    /* Calculate prefered bucket index */
    bucket = hashmap->hash(key) & (hashmap->capacity - 1);

    /* Find empty bucket */
    while (hashmap->psls[bucket])
    {
        /* Current bucket is richer then us - swap elements */
        if (psl > hashmap->psls[bucket])
        {
            tmp = hashmap->data[bucket];
            tmp_psl = hashmap->psls[bucket];
            hashmap->data[bucket] = item;
            hashmap->psls[bucket] = psl;
            item = tmp;
            psl = tmp_psl;
        }

        bucket = (bucket + 1) & (hashmap->capacity - 1);
        psl++;
    }

    /* Found empty bucket - place item here */
    hashmap->data[bucket] = item;
    hashmap->psls[bucket] = psl;
    hashmap->size++;

    return BH_OK;
}


void bh_hashmap_remove(bh_hashmap_t *hashmap,
                       void *key)
{
    void *iter;

    iter = bh_hashmap_iter_at(hashmap, key);
    if (iter)
        bh_hashmap_iter_remove(hashmap, iter);
}


int bh_hashmap_at(bh_hashmap_t *hashmap,
                  void *key,
                  void **value)
{
    void *iter;
    iter = bh_hashmap_iter_at(hashmap, key);

    if (!iter)
        return BH_NOTFOUND;

    if (value)
        *value = bh_hashmap_iter_value(iter);

    return BH_OK;
}


int bh_hashmap_empty(bh_hashmap_t *hashmap)
{
    return !hashmap->size;
}


size_t bh_hashmap_size(bh_hashmap_t *hashmap)
{
    return hashmap->size;
}


size_t bh_hashmap_capacity(bh_hashmap_t *hashmap)
{
    return hashmap->capacity;
}


float bh_hashmap_factor(bh_hashmap_t *hashmap)
{
    return hashmap->factor;
}


void bh_hashmap_set_factor(bh_hashmap_t *hashmap,
                           float factor)
{
    /* Limit the factor value to [0.15, 1.0] */
    factor = (factor > 1.0f) ? (1.0f) : (factor);
    factor = (factor < 0.15f) ? (0.15f) : (factor);

    /* Calculate new threshold value */
    hashmap->factor = factor;
    hashmap->threshold = hashmap->capacity * factor;
}


void *bh_hashmap_iter_at(bh_hashmap_t *hashmap,
                         void *key)
{
    size_t bucket, psl;

    /* Nothing can be in empty map */
    if (!hashmap->size)
        return NULL;

    /* Calculate prefered bucket index and set PSL to 1 */
    bucket = hashmap->hash(key) & (hashmap->capacity - 1);
    psl = 1;

    /* Iterate hashmap until we find element or find richer bucket */
    while (hashmap->psls[bucket] >= psl && hashmap->equal(hashmap->data[bucket].key, key))
    {
        bucket = (bucket + 1) & (hashmap->capacity - 1);
        psl++;
    }

    /* If bucket is poorer or equal to us - we found our element */
    if (hashmap->psls[bucket] >= psl)
        return hashmap->data + bucket;

    return NULL;
}


void *bh_hashmap_iter_next(bh_hashmap_t *hashmap,
                           void *iter)
{
    bh_hashmap_node_t *item;

    item = (bh_hashmap_node_t *)iter;
    while (1)
    {
        /* Advance or set iterator to the first element */
        if (item)
            item++;
        else
            item = hashmap->data;

        /* Check iterator for validity */
        if (item >= hashmap->data + hashmap->capacity)
            return NULL;

        /* Check iterator's item PSL */
        if (hashmap->psls[item - hashmap->data])
            return item;
    }
}


void bh_hashmap_iter_remove(bh_hashmap_t *hashmap,
                            void *iter)
{
    size_t bucket, next_bucket;

    /* Check if hashmap is empty or we are given NULL iterator */
    if (!iter || !hashmap->size)
        return;

    /* Adjust hashmap size, calculate current and next bucket index */
    hashmap->size--;
    bucket = (bh_hashmap_node_t *)iter - hashmap->data;
    next_bucket = (bucket + 1) & (hashmap->capacity - 1);

    /* Shift all elements toward their preffered place */
    while (hashmap->psls[next_bucket] > 1)
    {
        /* Copy item and adjust PSL */
        hashmap->data[bucket] = hashmap->data[next_bucket];
        hashmap->psls[bucket] = hashmap->psls[next_bucket] - 1;

        /* Calculate next bucket index */
        bucket = next_bucket;
        next_bucket = (bucket + 1) & (hashmap->capacity - 1);
    }

    /* Reset bucket's PSL (mark empty) */
    hashmap->psls[bucket] = 0;
}


void *bh_hashmap_iter_key(void *iter)
{
    return ((bh_hashmap_node_t *)iter)->key;
}


void *bh_hashmap_iter_value(void *iter)
{
    return ((bh_hashmap_node_t *)iter)->value;
}

