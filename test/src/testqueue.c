#include <bh/queue.h>
#include <bh/unit.h>


static int NewFree(void)
{
    BH_Queue *queue;

    queue = BH_QueueNew();
    BH_VERIFY(queue != NULL);
    BH_VERIFY(BH_QueueSize(queue) == 0);
    BH_VERIFY(BH_QueueCapacity(queue) == 0);
    BH_VERIFY(BH_QueueEmpty(queue) != 0);

    BH_QueueFree(queue);
    return 0;
}


static int GrowShrink(void)
{
    BH_Queue *queue;
    void *value;

    queue = BH_QueueNew();
    BH_VERIFY(queue != NULL);

    /* Reserve 1024 elements and insert item into queue */
    BH_VERIFY(BH_QueueReserve(queue, 1024) == BH_OK);
    BH_VERIFY(BH_QueueInsert(queue, BH_INT2PTR(1337)) == BH_OK);
    BH_VERIFY(BH_QueueCapacity(queue) >= 1024);
    BH_VERIFY(BH_QueueSize(queue) == 1);
    BH_VERIFY(BH_QueueEmpty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(BH_QueueFront(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Grow queue */
    BH_VERIFY(BH_QueueReserve(queue, 8192) == BH_OK);
    BH_VERIFY(BH_QueueCapacity(queue) >= 8192);
    BH_VERIFY(BH_QueueSize(queue) == 1);
    BH_VERIFY(BH_QueueEmpty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(BH_QueueFront(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Shrink the queue */
    BH_VERIFY(BH_QueueReserve(queue, 0) == BH_OK);
    BH_VERIFY(BH_QueueCapacity(queue) >= 1);
    BH_VERIFY(BH_QueueCapacity(queue) < 8192);
    BH_VERIFY(BH_QueueSize(queue) == 1);
    BH_VERIFY(BH_QueueEmpty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(BH_QueueFront(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Shrink to 0 (deallocate) */
    BH_QueueClear(queue);
    BH_VERIFY(BH_QueueSize(queue) == 0);
    BH_VERIFY(BH_QueueEmpty(queue) != 0);
    BH_VERIFY(BH_QueueCapacity(queue) >= 1);

    BH_VERIFY(BH_QueueReserve(queue, 0) == BH_OK);
    BH_VERIFY(BH_QueueSize(queue) == 0);
    BH_VERIFY(BH_QueueEmpty(queue) != 0);
    BH_VERIFY(BH_QueueCapacity(queue) == 0);

    BH_QueueFree(queue);
    return 0;
}


static int InsertRemove(void)
{
    BH_Queue *queue;
    size_t i, added, removed;
    void *iter;

    queue = BH_QueueNew();
    BH_VERIFY(queue != NULL);

    added = 0;
    for (i = 0; i < 256; i++)
    {
        added += i * 2;
        BH_VERIFY(BH_QueueInsert(queue, BH_INT2PTR(i * 2)) == BH_OK);
    }

    removed = 0;
    iter = BH_QueueIterNext(queue, NULL);
    while (iter)
    {
        void *value;

        BH_VERIFY(BH_QueueFront(queue, &value) == BH_OK);
        removed += BH_PTR2INT(value);

        BH_QueueRemove(queue);
        iter = BH_QueueIterNext(queue, NULL);
    }

    BH_VERIFY(added == removed);
    BH_VERIFY(BH_QueueEmpty(queue) != 0);
    BH_VERIFY(BH_QueueSize(queue) == 0);

    BH_QueueFree(queue);
    return 0;
}


static int Rollover(void)
{
    BH_Queue *queue;
    size_t i, j, capacity;

    queue = BH_QueueNew();
    BH_VERIFY(queue != NULL);

    BH_VERIFY(BH_QueueReserve(queue, 128) == 0);
    capacity = BH_QueueCapacity(queue);

    for (i = 0; i < 128; i++)
    {
        for (j = 0; j < 3; j++)
            BH_QueueRemove(queue);

        for (j = 0; j < 4 && BH_QueueSize(queue) < 128; j++)
            BH_VERIFY(BH_QueueInsert(queue, BH_INT2PTR(i * 4 + j)) == 0);
    }

    BH_VERIFY(BH_QueueSize(queue) == 128);
    BH_VERIFY(BH_QueueCapacity(queue) == capacity);

    BH_QueueFree(queue);
    return 0;
}


static int Fields(void)
{
    BH_Queue *queue;

    queue = BH_QueueNew();
    BH_VERIFY(queue != NULL);

    BH_VERIFY(BH_QueueInsert(queue, BH_INT2PTR(1337)) == 0);
    BH_VERIFY(BH_QueueSize(queue) == 1);
    BH_VERIFY(BH_QueueEmpty(queue) == 0);
    BH_VERIFY(BH_QueueCapacity(queue) >= 1);

    BH_QueueFree(queue);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UnitAdd("NewFree", NewFree);
    BH_UnitAdd("GrowShrink", GrowShrink);
    BH_UnitAdd("InsertRemove", InsertRemove);
    BH_UnitAdd("Rollover", Rollover);
    BH_UnitAdd("Fields", Fields);

    return BH_UnitRun();
}
