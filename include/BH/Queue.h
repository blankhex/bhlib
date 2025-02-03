#ifndef BH_QUEUE_H
#define BH_QUEUE_H


#include "Common.h"


typedef struct BH_Queue BH_Queue;


/**
 * Creates the new queue.
 *
 * \return  On success, returns the queue pointer.
 * \return  On failure, returns a null pointer.
 */
BH_Queue *BH_QueueNew(void);


/**
 * Frees the \a queue.
 *
 * \param queue  Queue pointer
 */
void BH_QueueFree(BH_Queue *queue);


/**
 * Clears the \a queue.
 *
 * \param queue  Queue pointer
 */
void BH_QueueClear(BH_Queue *queue);


/**
 * Reserves the space for \a size amount of value in the \a queue.
 *
 * This function can both expand and shrink the available space in queue.
 *
 * \param queue  Queue pointer
 * \param size   Capacity
 *
 * \note Calling this function will invalidate iterators.
 * \note Actual queue capacity can be bigger then requested.
 *
 * \return  On success, returns zero.
 * \return  On failure, returns error code.
 */
int BH_QueueReserve(BH_Queue *queue,
                    size_t size);


/**
 * Inserts the \a value into the \a queue.
 *
 * \param queue  Queue pointer
 * \param value  Value
 *
 * \note Calling this function will invalidate iterators.
 *
 * \return  On success, returns zero.
 * \return  On failure, returns error code.
 */
int BH_QueueInsert(BH_Queue *queue,
                   void *value);


/**
 * Removes front value from the \a queue.
 *
 * \param queue  Queue pointer
 *
 * \note Calling this function will invalidate iterators.
 */
void BH_QueueRemove(BH_Queue *queue);


/**
 * Returns front \a value from the \a queue.
 *
 * \param queue  Queue pointer
 * \param value  Value
 *
 * \return  On success, returns zero.
 * \return  On failure, returns error code.
 */
int BH_QueueFront(BH_Queue *queue,
                  void **value);


/**
 * Checks if the \a queue is empty.
 *
 * \param queue  Queue pointer
 *
 * \return  If queue is empty, returns non-zero value
 * \return  If queue is not empty, returns zero
 */
int BH_QueueEmpty(BH_Queue *queue);


/**
 * Returns the size of the \a queue.
 *
 * \param queue  Queue pointer
 *
 * \return  Returns the size of the queue.
 */
size_t BH_QueueSize(BH_Queue *queue);


/**
 * Returns the capacity of the \a queue.
 *
 * \param queue  Queue pointer
 *
 * \return  Returns the capacity of the queue.
 */
size_t BH_QueueCapacity(BH_Queue *queue);


/**
 * Returns the iterator to the next element in the \a queue.
 *
 * \param queue  Queue pointer
 * \param iter   Iterator
 *
 * \return On success, returns new iterator value for the next element.
 * \return On failure, returns NULL pointer.
 */
void *BH_QueueIterNext(BH_Queue *queue,
                       void *iter);


/**
 * Returns the value, pointed by the \a iter.
 *
 * \param iter  Iterator
 *
 * \return  Returns value, pointed by iterator.
 */
void *BH_QueueIterValue(void *iter);


#endif /* BH_QUEUE_H */
