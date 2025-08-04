#include <BH/Queue.h>
#include <stdlib.h>
#include <string.h>


struct BH_Queue
{
    void **data;
    size_t size;
    size_t head;
    size_t tail;
    size_t capacity;
};


static void BH_QueueInit(BH_Queue *queue)
{
    memset(queue, 0, sizeof(*queue));
}


static void BH_QueueDestroy(BH_Queue *queue)
{
    if (queue->capacity)
        free(queue->data);
}


static void BH_QueueCopy(BH_Queue *dest,
                         BH_Queue *src)
{
    void *iter;

    /* Iterate over old queue and insert data into new queue */
    iter = BH_QueueIterNext(src, NULL);
    while (iter)
    {
        BH_QueueInsert(dest, BH_QueueIterValue(iter));
        iter = BH_QueueIterNext(src, iter);
    }
}


BH_Queue *BH_QueueNew(void)
{
    BH_Queue *result;

    result = malloc(sizeof(*result));
    if (result)
        BH_QueueInit(result);

    return result;
}


void BH_QueueFree(BH_Queue *queue)
{
    BH_QueueDestroy(queue);
    free(queue);
}


void BH_QueueClear(BH_Queue *queue)
{
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}


int BH_QueueReserve(BH_Queue *queue,
                    size_t size)
{
    BH_Queue other;

    /* New capacity should be great or equal to current size */
    if (size < queue->size)
        size = queue->size;

    /* Catch malloc overflow */
    if (BH_CHECK_UMUL_WRAP(size, sizeof(void *), size_t))
        return BH_OOM;

    /* Prevent same size memory reallocation */
    if (size == queue->capacity)
        return BH_OK;

    /* Prepare new empty queue */
    BH_QueueInit(&other);
    if (size)
    {
        /* Allocate new capacity for the queue */
        other.data = malloc(size * sizeof(void *));
        other.capacity = size;
        if (!other.data)
            return BH_OOM;

        /* Iterate over old queue and insert data into new queue */
        BH_QueueCopy(&other, queue);
    }

    /* If old queue had allocated data - free it */
    if (queue->capacity)
        free(queue->data);

    /* Copy queue information */
    *queue = other;
    return BH_OK;
}


int BH_QueueInsert(BH_Queue *queue,
                   void *value)
{
    /* Check if queue can contain new element */
    if (queue->size + 1 > queue->capacity)
    {
        size_t capacity;

        /* Check for capacity overflow and reserve capacity */
        capacity = (queue->capacity) ? (queue->capacity * 2) : (16);
        if (capacity < queue->capacity || BH_QueueReserve(queue, capacity))
            return BH_OOM;
    }

    /* Increase queue size and advance tail index */
    queue->data[queue->tail] = value;
    queue->size++;
    if (++queue->tail >= queue->capacity)
        queue->tail = 0;

    return BH_OK;
}


void BH_QueueRemove(BH_Queue *queue)
{
    /* Do nothing if queue is empty */
    if (!queue->size)
        return;

    /* Decrease queue size and advance head index */
    queue->size--;
    if (++queue->head >= queue->capacity)
        queue->head = 0;
}


int BH_QueueFront(BH_Queue *queue, void **value)
{
    /* Do nothing if queue is empty */
    if (!queue->size)
        return BH_ERROR;

    /* Return front element */
    *value = queue->data[queue->head];
    return BH_OK;
}


int BH_QueueEmpty(BH_Queue *queue)
{
    return !queue->size;
}


size_t BH_QueueSize(BH_Queue *queue)
{
    return queue->size;
}


size_t BH_QueueCapacity(BH_Queue *queue)
{
    return queue->capacity;
}


void *BH_QueueIterNext(BH_Queue *queue,
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


void *BH_QueueIterValue(void *iter)
{
    return *(void **)iter;
}
