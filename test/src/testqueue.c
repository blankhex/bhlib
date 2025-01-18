#include <bh/queue.h>
#include <bh/unit.h>


static int new_free(void)
{
    bh_queue_t *queue;

    queue = bh_queue_new();
    BH_VERIFY(queue != NULL);
    BH_VERIFY(bh_queue_size(queue) == 0);
    BH_VERIFY(bh_queue_capacity(queue) == 0);
    BH_VERIFY(bh_queue_empty(queue) != 0);

    bh_queue_free(queue);
    return 0;
}


static int grow_shrink(void)
{
    bh_queue_t *queue;
    void *value;

    queue = bh_queue_new();
    BH_VERIFY(queue != NULL);

    /* Reserve 1024 elements and insert item into queue */
    BH_VERIFY(bh_queue_reserve(queue, 1024) == BH_OK);
    BH_VERIFY(bh_queue_insert(queue, BH_INT2PTR(1337)) == BH_OK);
    BH_VERIFY(bh_queue_capacity(queue) >= 1024);
    BH_VERIFY(bh_queue_size(queue) == 1);
    BH_VERIFY(bh_queue_empty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(bh_queue_front(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Grow queue */
    BH_VERIFY(bh_queue_reserve(queue, 8192) == BH_OK);
    BH_VERIFY(bh_queue_capacity(queue) >= 8192);
    BH_VERIFY(bh_queue_size(queue) == 1);
    BH_VERIFY(bh_queue_empty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(bh_queue_front(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Shrink the queue */
    BH_VERIFY(bh_queue_reserve(queue, 0) == BH_OK);
    BH_VERIFY(bh_queue_capacity(queue) >= 1);
    BH_VERIFY(bh_queue_capacity(queue) < 8192);
    BH_VERIFY(bh_queue_size(queue) == 1);
    BH_VERIFY(bh_queue_empty(queue) == 0);

    /* Check queue content */
    BH_VERIFY(bh_queue_front(queue, &value) == BH_OK);
    BH_VERIFY(BH_PTR2INT(value) == 1337);

    /* Shrink to 0 (deallocate) */
    bh_queue_clear(queue);
    BH_VERIFY(bh_queue_size(queue) == 0);
    BH_VERIFY(bh_queue_empty(queue) != 0);
    BH_VERIFY(bh_queue_capacity(queue) >= 1);

    BH_VERIFY(bh_queue_reserve(queue, 0) == BH_OK);
    BH_VERIFY(bh_queue_size(queue) == 0);
    BH_VERIFY(bh_queue_empty(queue) != 0);
    BH_VERIFY(bh_queue_capacity(queue) == 0);

    bh_queue_free(queue);
    return 0;
}


static int insert_remove(void)
{
    bh_queue_t *queue;
    size_t i, added, removed;
    void *iter;

    queue = bh_queue_new();
    BH_VERIFY(queue != NULL);

    added = 0;
    for (i = 0; i < 256; i++)
    {
        added += i * 2;
        BH_VERIFY(bh_queue_insert(queue, BH_INT2PTR(i * 2)) == BH_OK);
    }

    removed = 0;
    iter = bh_queue_iter_next(queue, NULL);
    while (iter)
    {
        void *value;

        BH_VERIFY(bh_queue_front(queue, &value) == BH_OK);
        removed += BH_PTR2INT(value);

        bh_queue_remove(queue);
        iter = bh_queue_iter_next(queue, NULL);
    }

    BH_VERIFY(added == removed);
    BH_VERIFY(bh_queue_empty(queue) != 0);
    BH_VERIFY(bh_queue_size(queue) == 0);

    bh_queue_free(queue);
    return 0;
}


static int rollover(void)
{
    bh_queue_t *queue;
    size_t i, j, capacity;

    queue = bh_queue_new();
    BH_VERIFY(queue != NULL);

    BH_VERIFY(bh_queue_reserve(queue, 128) == 0);
    capacity = bh_queue_capacity(queue);

    for (i = 0; i < 128; i++)
    {
        for (j = 0; j < 3; j++)
            bh_queue_remove(queue);

        for (j = 0; j < 4 && bh_queue_size(queue) < 128; j++)
            BH_VERIFY(bh_queue_insert(queue, BH_INT2PTR(i * 4 + j)) == 0);
    }

    BH_VERIFY(bh_queue_size(queue) == 128);
    BH_VERIFY(bh_queue_capacity(queue) == capacity);

    bh_queue_free(queue);
    return 0;
}


static int fields(void)
{
    bh_queue_t *queue;

    queue = bh_queue_new();
    BH_VERIFY(queue != NULL);

    BH_VERIFY(bh_queue_insert(queue, BH_INT2PTR(1337)) == 0);
    BH_VERIFY(bh_queue_size(queue) == 1);
    BH_VERIFY(bh_queue_empty(queue) == 0);
    BH_VERIFY(bh_queue_capacity(queue) >= 1);

    bh_queue_free(queue);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    bh_unit_add("new_free", new_free);
    bh_unit_add("grow_shrink", grow_shrink);
    bh_unit_add("insert_remove", insert_remove);
    bh_unit_add("rollover", rollover);
    bh_unit_add("fields", fields);

    return bh_unit_run();
}
