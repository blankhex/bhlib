#include <bh/hashmap.h>
#include <bh/unit.h>


static size_t direct_hash(const void *ptr)
{
    return BH_PTR2INT(ptr);
}


static int direct_equal(const void *lhs, const void *rhs)
{
    return BH_PTR2INT(lhs) - BH_PTR2INT(rhs);
}


static int new_free(void)
{
    bh_hashmap_t *hashmap;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);

    BH_VERIFY(bh_hashmap_empty(hashmap) != 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 0);
    BH_VERIFY(bh_hashmap_capacity(hashmap) == 0);
    BH_VERIFY(bh_hashmap_factor(hashmap) >= 0.15f);
    BH_VERIFY(bh_hashmap_factor(hashmap) <= 1.0f);

    bh_hashmap_free(hashmap);
    return 0;
}

static int grow_shrink(void)
{
    bh_hashmap_t *hashmap;
    void *iter;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);

    /* Allocate space for 1024 entries and insert 1 element */
    BH_VERIFY(bh_hashmap_reserve(hashmap, 1024) == 0);
    BH_VERIFY(bh_hashmap_insert(hashmap, BH_INT2PTR(1337), BH_INT2PTR(80085)) == 0);

    /* Check hashmap contents */
    iter = bh_hashmap_iter_next(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_key(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_value(iter)) == 80085);
    BH_VERIFY(bh_hashmap_iter_next(hashmap, iter) == NULL);
    BH_VERIFY(bh_hashmap_empty(hashmap) == 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 1);
    BH_VERIFY(bh_hashmap_capacity(hashmap) >= 1024);

    /* Change factor and grow */
    bh_hashmap_set_factor(hashmap, 0.35f);

    /* Check hashmap contents */
    iter = bh_hashmap_iter_next(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_key(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_value(iter)) == 80085);
    BH_VERIFY(bh_hashmap_iter_next(hashmap, iter) == NULL);
    BH_VERIFY(bh_hashmap_reserve(hashmap, 8192) == 0);
    BH_VERIFY(bh_hashmap_empty(hashmap) == 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 1);
    BH_VERIFY(bh_hashmap_capacity(hashmap) >= 8192);
    BH_VERIFY(bh_hashmap_factor(hashmap) == 0.35f);

    /* Shrink */
    BH_VERIFY(bh_hashmap_reserve(hashmap, 0) == 0);

    /* Check hashmap contents */
    iter = bh_hashmap_iter_next(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_key(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(bh_hashmap_iter_value(iter)) == 80085);
    BH_VERIFY(bh_hashmap_iter_next(hashmap, iter) == NULL);
    BH_VERIFY(bh_hashmap_empty(hashmap) == 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 1);
    BH_VERIFY(bh_hashmap_capacity(hashmap) >= 1);
    BH_VERIFY(bh_hashmap_capacity(hashmap) < 8192);
    BH_VERIFY(bh_hashmap_factor(hashmap) == 0.35f);

    /* Shrink to 0 (deallocate) */
    bh_hashmap_clear(hashmap);
    BH_VERIFY(bh_hashmap_empty(hashmap) != 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 0);
    BH_VERIFY(bh_hashmap_capacity(hashmap) > 0);

    BH_VERIFY(bh_hashmap_reserve(hashmap, 0) == 0);
    BH_VERIFY(bh_hashmap_empty(hashmap) != 0);
    BH_VERIFY(bh_hashmap_size(hashmap) == 0);
    BH_VERIFY(bh_hashmap_capacity(hashmap) == 0);

    /* Check hashmap contents */
    iter = bh_hashmap_iter_next(hashmap, NULL);
    BH_VERIFY(iter == NULL);

    bh_hashmap_free(hashmap);
    return 0;
}

static int insert_remove(void)
{
    bh_hashmap_t *hashmap;
    size_t i, added, removed;
    void *iter;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);
    bh_hashmap_set_factor(hashmap, 1.0f);

    /* Insert elements into hashmap */
    added = 0;
    for (i = 1024; i > 0; i--)
    {
        added += (i - 1) / 4;
        BH_VERIFY(bh_hashmap_insert(hashmap, BH_INT2PTR((i - 1) / 4), BH_INT2PTR(i)) == 0);
    }

    /* Remove elements */
    iter = bh_hashmap_iter_next(hashmap, NULL);
    removed = 0;
    while (iter)
    {
        removed += BH_PTR2INT(bh_hashmap_iter_key(iter));
        bh_hashmap_iter_remove(hashmap, iter);

        iter = bh_hashmap_iter_next(hashmap, NULL);
    }

    /* Check inserted elements are equal to removed */
    BH_VERIFY(added == removed);

    bh_hashmap_free(hashmap);
    return 0;
}

static int lookup(void)
{
    bh_hashmap_t *hashmap;
    size_t i;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);

    /* Insert elements into hashmap */
    for (i = 0; i < 256; i++)
        BH_VERIFY(bh_hashmap_insert(hashmap, BH_INT2PTR(i * 4), BH_INT2PTR(i)) == 0);

    /* Lookup inserted elements */
    for (i = 0; i < 256; i++)
    {
        void *value;

        BH_VERIFY(bh_hashmap_at(hashmap, BH_INT2PTR(i * 4), NULL) == BH_OK);
        BH_VERIFY(bh_hashmap_at(hashmap, BH_INT2PTR(i * 4), &value) == BH_OK);
        BH_VERIFY(BH_PTR2INT(value) == i);
    }

    /* Lookup non-existing elements */
    for (i = 256; i < 512; i++)
    {
        void *value;

        BH_VERIFY(bh_hashmap_at(hashmap, BH_INT2PTR(i * 4), NULL) != BH_OK);
        BH_VERIFY(bh_hashmap_at(hashmap, BH_INT2PTR(i * 4), &value) != BH_OK);
    }

    bh_hashmap_free(hashmap);
    return 0;
}

static int clear(void)
{
    bh_hashmap_t *hashmap;
    size_t i;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);

    /* Insert elements into hashmap */
    for (i = 0; i < 128; i++)
        BH_VERIFY(bh_hashmap_insert(hashmap, BH_INT2PTR(i), 0) == 0);

    bh_hashmap_clear(hashmap);

    /* Remove non-existing elements */
    for (i = 0; i < 128; i++)
        bh_hashmap_remove(hashmap, BH_INT2PTR(i));

    bh_hashmap_free(hashmap);
    return 0;
}

static int fields(void)
{
    bh_hashmap_t *hashmap;
    size_t i;

    hashmap = bh_hashmap_new(direct_equal, direct_hash);
    BH_VERIFY(hashmap != NULL);
    BH_VERIFY(bh_hashmap_empty(hashmap) == 1);

    /* Insert elements into hashmap */
    for (i = 0; i < 14; i++)
        BH_VERIFY(bh_hashmap_insert(hashmap, BH_INT2PTR(i), NULL) == 0);

    /* Check hashmap fields correspond to getter functions */
    BH_VERIFY(bh_hashmap_size(hashmap) == 14);
    BH_VERIFY(bh_hashmap_capacity(hashmap) >= 14);
    BH_VERIFY(bh_hashmap_empty(hashmap) == 0);

    bh_hashmap_free(hashmap);
    return 0;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* Add unit tests */
    bh_unit_add("new_free", new_free);
    bh_unit_add("grow_shrink", grow_shrink);
    bh_unit_add("insert_remove", insert_remove);
    bh_unit_add("lookup", lookup);
    bh_unit_add("clear", clear);
    bh_unit_add("fields", fields);

    return bh_unit_run();
}
