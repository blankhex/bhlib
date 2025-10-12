#include <BH/Hashmap.h>
#include <BH/Unit.h>


static size_t DBG_PtrIntHash(const void *ptr)
{
    return BH_PTR2INT(ptr);
}


static int DBG_PtrIntEqual(const void *lhs, const void *rhs)
{
    return BH_PTR2INT(lhs) - BH_PTR2INT(rhs);
}


static int NewFree(void)
{
    BH_Hashmap *hashmap;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);

    BH_VERIFY(BH_HashmapEmpty(hashmap) != 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 0);
    BH_VERIFY(BH_HashmapCapacity(hashmap) == 0);
    BH_VERIFY(BH_HashmapFactor(hashmap) >= 0.15f);
    BH_VERIFY(BH_HashmapFactor(hashmap) <= 1.0f);

    BH_HashmapFree(hashmap);
    return 0;
}


static int GrowShrink(void)
{
    BH_Hashmap *hashmap;
    void *iter;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);

    /* Allocate space for 1024 entries and insert 1 element */
    BH_VERIFY(BH_HashmapReserve(hashmap, 1024) == 0);
    BH_VERIFY(BH_HashmapInsert(hashmap, BH_INT2PTR(1337), BH_INT2PTR(80085)) == 0);

    /* Check hashmap contents */
    iter = BH_HashmapIterNext(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterKey(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterValue(iter)) == 80085);
    BH_VERIFY(BH_HashmapIterNext(hashmap, iter) == NULL);
    BH_VERIFY(BH_HashmapEmpty(hashmap) == 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 1);
    BH_VERIFY(BH_HashmapCapacity(hashmap) >= 1024);

    /* Change factor and grow */
    BH_HashmapSetFactor(hashmap, 0.35f);

    /* Check hashmap contents */
    iter = BH_HashmapIterNext(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterKey(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterValue(iter)) == 80085);
    BH_VERIFY(BH_HashmapIterNext(hashmap, iter) == NULL);
    BH_VERIFY(BH_HashmapReserve(hashmap, 8192) == 0);
    BH_VERIFY(BH_HashmapEmpty(hashmap) == 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 1);
    BH_VERIFY(BH_HashmapCapacity(hashmap) >= 8192);
    BH_VERIFY_DELTA(BH_HashmapFactor(hashmap), 0.35f, 0.001f);

    /* Shrink */
    BH_VERIFY(BH_HashmapReserve(hashmap, 0) == 0);

    /* Check hashmap contents */
    iter = BH_HashmapIterNext(hashmap, NULL);
    BH_VERIFY(iter != NULL);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterKey(iter)) == 1337);
    BH_VERIFY(BH_PTR2INT(BH_HashmapIterValue(iter)) == 80085);
    BH_VERIFY(BH_HashmapIterNext(hashmap, iter) == NULL);
    BH_VERIFY(BH_HashmapEmpty(hashmap) == 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 1);
    BH_VERIFY(BH_HashmapCapacity(hashmap) >= 1);
    BH_VERIFY(BH_HashmapCapacity(hashmap) < 8192);
    BH_VERIFY_DELTA(BH_HashmapFactor(hashmap), 0.35f, 0.001f);

    /* Shrink to 0 (deallocate) */
    BH_HashmapClear(hashmap);
    BH_VERIFY(BH_HashmapEmpty(hashmap) != 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 0);
    BH_VERIFY(BH_HashmapCapacity(hashmap) > 0);

    BH_VERIFY(BH_HashmapReserve(hashmap, 0) == 0);
    BH_VERIFY(BH_HashmapEmpty(hashmap) != 0);
    BH_VERIFY(BH_HashmapSize(hashmap) == 0);
    BH_VERIFY(BH_HashmapCapacity(hashmap) == 0);

    /* Check hashmap contents */
    iter = BH_HashmapIterNext(hashmap, NULL);
    BH_VERIFY(iter == NULL);

    BH_HashmapFree(hashmap);
    return 0;
}


static int InsertRemove(void)
{
    BH_Hashmap *hashmap;
    size_t i, added, removed;
    void *iter;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);
    BH_HashmapSetFactor(hashmap, 1.0f);

    /* Insert elements into hashmap */
    added = 0;
    for (i = 1024; i > 0; i--)
    {
        added += (i - 1) / 4;
        BH_VERIFY(BH_HashmapInsert(hashmap, BH_INT2PTR((i - 1) / 4), BH_INT2PTR(i)) == 0);
    }

    /* Remove elements */
    iter = BH_HashmapIterNext(hashmap, NULL);
    removed = 0;
    while (iter)
    {
        removed += BH_PTR2INT(BH_HashmapIterKey(iter));
        BH_HashmapIterRemove(hashmap, iter);

        iter = BH_HashmapIterNext(hashmap, NULL);
    }

    /* Check inserted elements are equal to removed */
    BH_VERIFY(added == removed);

    BH_HashmapFree(hashmap);
    return 0;
}


static int Lookup(void)
{
    BH_Hashmap *hashmap;
    size_t i;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);

    /* Insert elements into hashmap */
    for (i = 0; i < 256; i++)
        BH_VERIFY(BH_HashmapInsert(hashmap, BH_INT2PTR(i * 4), BH_INT2PTR(i)) == 0);

    /* Lookup inserted elements */
    for (i = 0; i < 256; i++)
    {
        void *value;

        BH_VERIFY(BH_HashmapAt(hashmap, BH_INT2PTR(i * 4), NULL) == BH_OK);
        BH_VERIFY(BH_HashmapAt(hashmap, BH_INT2PTR(i * 4), &value) == BH_OK);
        BH_VERIFY(BH_PTR2INT(value) == (int)i);
    }

    /* Lookup non-existing elements */
    for (i = 256; i < 512; i++)
    {
        void *value;

        BH_VERIFY(BH_HashmapAt(hashmap, BH_INT2PTR(i * 4), NULL) != BH_OK);
        BH_VERIFY(BH_HashmapAt(hashmap, BH_INT2PTR(i * 4), &value) != BH_OK);
    }

    BH_HashmapFree(hashmap);
    return 0;
}


static int Clear(void)
{
    BH_Hashmap *hashmap;
    size_t i;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);

    /* Insert elements into hashmap */
    for (i = 0; i < 128; i++)
        BH_VERIFY(BH_HashmapInsert(hashmap, BH_INT2PTR(i), 0) == 0);

    BH_HashmapClear(hashmap);

    /* Remove non-existing elements */
    for (i = 0; i < 128; i++)
        BH_HashmapRemove(hashmap, BH_INT2PTR(i));

    BH_HashmapFree(hashmap);
    return 0;
}


static int Fields(void)
{
    BH_Hashmap *hashmap;
    size_t i;

    hashmap = BH_HashmapNew(DBG_PtrIntEqual, DBG_PtrIntHash);
    BH_VERIFY(hashmap != NULL);
    BH_VERIFY(BH_HashmapEmpty(hashmap) == 1);

    /* Insert elements into hashmap */
    for (i = 0; i < 14; i++)
        BH_VERIFY(BH_HashmapInsert(hashmap, BH_INT2PTR(i), NULL) == 0);

    /* Check hashmap fields correspond to getter functions */
    BH_VERIFY(BH_HashmapSize(hashmap) == 14);
    BH_VERIFY(BH_HashmapCapacity(hashmap) >= 14);
    BH_VERIFY(BH_HashmapEmpty(hashmap) == 0);

    BH_HashmapFree(hashmap);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* Add unit tests */
    BH_UnitAdd("NewFree", NewFree);
    BH_UnitAdd("GrowShrink", GrowShrink);
    BH_UnitAdd("InsertRemove", InsertRemove);
    BH_UnitAdd("Lookup", Lookup);
    BH_UnitAdd("Clear", Clear);
    BH_UnitAdd("Fields", Fields);

    return BH_UnitRun();
}
