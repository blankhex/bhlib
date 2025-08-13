#include <BH/Hashmap.h>
#include <stdlib.h>
#include <string.h>


typedef struct BH_HashmapNode
{
    void *key;
    void *value;
} BH_HashmapNode;


struct BH_Hashmap
{
    BH_HashmapNode *data;
    size_t *psls;
    size_t size;
    size_t capacity;
    size_t threshold;
    BH_EqualCallback equal;
    BH_HashCallback hash;
    float factor;
};


static void BH_HashmapInit(BH_Hashmap *hashmap,
                           BH_EqualCallback equal,
                           BH_HashCallback hash)
{
    memset(hashmap, 0, sizeof(*hashmap));
    hashmap->factor = 0.75f;
    hashmap->equal = equal;
    hashmap->hash = hash;
}


static void BH_HashmapDestroy(BH_Hashmap *hashmap)
{
    if (hashmap->capacity)
    {
        free(hashmap->data);
        free(hashmap->psls);
    }
}


static int BH_CalcCapacity(size_t size,
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
        /* Catch capacity overflow  */
        if (BH_CHECK_UMUL_WRAP(*capacity, 2, size_t))
            return BH_OOM;

        *capacity *= 2;
        *threshold = *capacity * factor;
    }

    /* Catch malloc overflow */
    if (BH_CHECK_UMUL_WRAP(*capacity, sizeof(BH_HashmapNode), size_t))
        return BH_OOM;

    return BH_OK;
}


static void BH_CopyHashmap(BH_Hashmap *dest,
                           BH_Hashmap *src)
{
    void *iter;

    /* Iterate and insert data into hashmap */
    iter = BH_HashmapIterNext(src, NULL);
    while (iter)
    {
        void *key, *value;

        key = BH_HashmapIterKey(iter);
        value = BH_HashmapIterValue(iter);
        BH_HashmapInsert(dest, key, value);

        iter = BH_HashmapIterNext(src, iter);
    }
}


BH_Hashmap *BH_HashmapNew(BH_EqualCallback equal,
                          BH_HashCallback hash)
{
    BH_Hashmap *result;

    result = malloc(sizeof(*result));
    if (result)
        BH_HashmapInit(result, equal, hash);

    return result;
}


void BH_HashmapFree(BH_Hashmap *hashmap)
{
    BH_HashmapDestroy(hashmap);
    free(hashmap);
}


void BH_HashmapClear(BH_Hashmap *hashmap)
{
    if (hashmap->capacity)
        memset(hashmap->psls, 0, hashmap->capacity * sizeof(size_t));
    hashmap->size = 0;
}


int BH_HashmapReserve(BH_Hashmap *hashmap,
                      size_t size)
{
    BH_Hashmap other;
    size_t capacity, threshold;

    /* New capacity can't be smaller then current hashmap size */
    if (size < hashmap->size)
        size = hashmap->size;

    /* Calculate new capacity */
    if (BH_CalcCapacity(size, hashmap->factor, &capacity, &threshold))
        return BH_OOM;

    /* Prevent same size reallocation */
    if (capacity == hashmap->capacity)
        return BH_OK;

    /* Initialize new hashmap */
    BH_HashmapInit(&other, hashmap->equal, hashmap->hash);
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
        BH_CopyHashmap(&other, hashmap);
    }

    /* Swap hashmaps */
    BH_HashmapDestroy(hashmap);
    *hashmap = other;
    return BH_OK;
}


int BH_HashmapInsert(BH_Hashmap *hashmap,
                     void *key,
                     void *value)
{
    size_t bucket, psl, tmp_psl;
    BH_HashmapNode item, tmp;

    /* Try to stay below hashmap threshold */
    if (hashmap->size + 1 > hashmap->threshold)
        if (BH_HashmapReserve(hashmap, hashmap->size + 1))
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


void BH_HashmapRemove(BH_Hashmap *hashmap,
                      void *key)
{
    void *iter;

    iter = BH_HashmapIterAt(hashmap, key);
    if (iter)
        BH_HashmapIterRemove(hashmap, iter);
}


int BH_HashmapAt(BH_Hashmap *hashmap,
                 void *key,
                 void **value)
{
    void *iter;
    iter = BH_HashmapIterAt(hashmap, key);

    if (!iter)
        return BH_NOTFOUND;

    if (value)
        *value = BH_HashmapIterValue(iter);

    return BH_OK;
}


int BH_HashmapEmpty(BH_Hashmap *hashmap)
{
    return !hashmap->size;
}


size_t BH_HashmapSize(BH_Hashmap *hashmap)
{
    return hashmap->size;
}


size_t BH_HashmapCapacity(BH_Hashmap *hashmap)
{
    return hashmap->capacity;
}


float BH_HashmapFactor(BH_Hashmap *hashmap)
{
    return hashmap->factor;
}


void BH_HashmapSetFactor(BH_Hashmap *hashmap,
                         float factor)
{
    /* Limit the factor value to [0.15, 1.0] */
    factor = (factor > 1.0f) ? (1.0f) : (factor);
    factor = (factor < 0.15f) ? (0.15f) : (factor);

    /* Calculate new threshold value */
    hashmap->factor = factor;
    hashmap->threshold = hashmap->capacity * factor;
}


void *BH_HashmapIterAt(BH_Hashmap *hashmap,
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


void *BH_HashmapIterNext(BH_Hashmap *hashmap,
                         void *iter)
{
    BH_HashmapNode *item;

    item = (BH_HashmapNode *)iter;
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


void BH_HashmapIterRemove(BH_Hashmap *hashmap,
                          void *iter)
{
    size_t bucket, next_bucket;

    /* Check if hashmap is empty or we are given NULL iterator */
    if (!iter || !hashmap->size)
        return;

    /* Adjust hashmap size, calculate current and next bucket index */
    hashmap->size--;
    bucket = (BH_HashmapNode *)iter - hashmap->data;
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


void *BH_HashmapIterKey(void *iter)
{
    return ((BH_HashmapNode *)iter)->key;
}


void *BH_HashmapIterValue(void *iter)
{
    return ((BH_HashmapNode *)iter)->value;
}
