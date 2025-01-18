#include <bh/queue.h>
#include <stdlib.h>
#include <string.h>


struct bh_queue_s
{
    void **data;
    size_t size;
    size_t head;
    size_t tail;
    size_t capacity;
};


static void bh_queue_init(bh_queue_t *queue)
{
    memset(queue, 0, sizeof(*queue));
}


static void bh_queue_destroy(bh_queue_t *queue)
{
    if (queue->capacity)
        free(queue->data);
}


static void queue_copy(bh_queue_t *dest,
                       bh_queue_t *src)
{
    void *iter;

    /* Iterate over old queue and insert data into new queue */
    iter = bh_queue_iter_next(src, NULL);
    while (iter)
    {
        bh_queue_insert(dest, bh_queue_iter_value(iter));
        iter = bh_queue_iter_next(src, iter);
    }
}


bh_queue_t *bh_queue_new(void)
{
    bh_queue_t *result;

    result = malloc(sizeof(*result));
    if (result)
        bh_queue_init(result);

    return result;
}


void bh_queue_free(bh_queue_t *queue)
{
    bh_queue_destroy(queue);
    free(queue);
}


void bh_queue_clear(bh_queue_t *queue)
{
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}


int bh_queue_reserve(bh_queue_t *queue,
                     size_t size)
{
    bh_queue_t other;

    /* New capacity should be great or equal to current size */
    if (size < queue->size)
        size = queue->size;

    /* Catch malloc overflow */
    if (size >= ((size_t)-1) / sizeof(void *))
        return BH_OOM;

    /* Prevent same size memory reallocation */
    if (size == queue->capacity)
        return BH_OK;

    /* Prepare new empty queue */
    bh_queue_init(&other);
    if (size)
    {
        /* Allocate new capacity for the queue */
        other.data = malloc(size * sizeof(void *));
        other.capacity = size;
        if (!other.data)
            return BH_OOM;

        /* Iterate over old queue and insert data into new queue */
        queue_copy(&other, queue);
    }

    /* If old queue had allocated data - free it */
    if (queue->capacity)
        free(queue->data);

    /* Copy queue information */
    *queue = other;
    return BH_OK;
}


int bh_queue_insert(bh_queue_t *queue,
                    void *value)
{
    /* Check if queue can contain new element */
    if (queue->size + 1 > queue->capacity)
    {
        size_t capacity;

        /* Check for capacity overflow and reserve capacity */
        capacity = (queue->capacity) ? (queue->capacity * 2) : (16);
        if (capacity < queue->capacity || bh_queue_reserve(queue, capacity))
            return BH_OOM;
    }

    /* Increase queue size and advance tail index */
    queue->data[queue->tail] = value;
    queue->size++;
    if (++queue->tail >= queue->capacity)
        queue->tail = 0;

    return BH_OK;
}


void bh_queue_remove(bh_queue_t *queue)
{
    /* Do nothing if queue is empty */
    if (!queue->size)
        return;

    /* Decrease queue size and advance head index */
    queue->size--;
    if (++queue->head >= queue->capacity)
        queue->head = 0;
}


int bh_queue_front(bh_queue_t *queue, void **value)
{
    /* Do nothing if queue is empty */
    if (!queue->size)
        return BH_ERROR;

    /* Return front element */
    *value = queue->data[queue->head];
    return BH_OK;
}


int bh_queue_empty(bh_queue_t *queue)
{
    return !queue->size;
}


size_t bh_queue_size(bh_queue_t *queue)
{
    return queue->size;
}


size_t bh_queue_capacity(bh_queue_t *queue)
{
    return queue->capacity;
}


void *bh_queue_iter_next(bh_queue_t *queue,
                         void *iter)
{
    void **element = (void **)iter;

    /* Do nothing if queue is empty */
    if (!queue->size)
        return NULL;

    /* Advance or set iterator */
    if (element)
    {
        element++;
        if (element == queue->data + queue->capacity)
            element = queue->data;

        /* Check if we reached the end */
        if (element == queue->data + queue->tail)
            return NULL;
    }
    else
        element = queue->data + queue->head;

    return element;
}


void *bh_queue_iter_value(void *iter)
{
    return *(void **)iter;
}
