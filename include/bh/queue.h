#ifndef BH_QUEUE_H
#define BH_QUEUE_H


#include "common.h"


typedef struct BH_Queue BH_Queue;


/**
 * Creates the new queue object.
 *
 * \return  On success, returns the pointer to the new queue object.
 * \return  On failure, returns a null pointer.
 */
BH_Queue *BH_QueueNew(void);


/**
 * Frees the \a queue object.
 *
 * \param queue Pointer to the queue object to be freed
 */
void BH_QueueFree(BH_Queue *queue);


/**
 * Clears the \a queue object.
 *
 * \param queue Pointer to the queue object to be cleared
 */
void BH_QueueClear(BH_Queue *queue);


/**
 * Reserves the space for \a size elements in the \a queue.
 *
 * This function can both expand and shrink the available space in \a queue.
 *
 * \param queue Pointer to the queue object to be resized in terms of capacity
 * \param size  New capacity of the queue
 *
 * \note Calling this function will invalidate iterators.
 * \note Actual hashmap capacity can be bigger then requested.
 *
 * \return  On success, returns zero value.
 * \return  On failure, returns error code.
 */
int BH_QueueReserve(BH_Queue *queue,
                    size_t size);


/**
 * Inserts the \a value into the \a queue.
 *
 * \param queue Pointer to the queue object
 * \param value Value to be inserted
 *
 * \note Calling this function will invalidate iterators.
 *
 * \return  On success, returns zero value.
 * \return  On failure, returns error code.
 */
int BH_QueueInsert(BH_Queue *queue,
                   void *value);


/**
 * Removes front value from the \a queue.
 *
 * \param queue Pointer to the queue object
 *
 * \note Calling this function will invalidate iterators.
 */
void BH_QueueRemove(BH_Queue *queue);


/**
 * Returns front value from the \a queue.
 *
 * \param queue Pointer to the queue object
 *
 * \return  On success, returns front value from the queue.
 * \return  On failure, returns null pointer.
 */
int BH_QueueFront(BH_Queue *queue,
                  void **value);


/**
 * Checks if the \a queue is empty.
 *
 * \param queue Pointer to the queue object
 *
 * \return  If queue is empty, returns non-zero value
 * \return  If queue is not empty, returns zero value
 */
int BH_QueueEmpty(BH_Queue *queue);


/**
 * Returns the size of the \a queue.
 *
 * \param queue Pointer to the queue object
 *
 * \return  Returns the size of the queue.
 */
size_t BH_QueueSize(BH_Queue *queue);


/**
 * Returns the capacity of the \a queue.
 *
 * \param queue Pointer to the queue object
 *
 * \return  Returns the capacity of the queue.
 */
size_t BH_QueueCapacity(BH_Queue *queue);


/**
 * Returns the iterator to the next element in the \a queue.
 *
 * \param queue Pointer to the queue object
 * \param iter  Opaque iterator value
 *
 * \return  If the \a iter doesn't point to the last element of the queue,
 *          returns next iterator value.
 * \return  If the \a iter point to the last element of the queue, returns
 *          null pointer.
 * \return  If the \a iter is the null pointer, returns iterator to the
 *          first element of the queue.
 */
void *BH_QueueIterNext(BH_Queue *queue,
                       void *iter);


/**
 * Returns the value, pointed by the queue iterator \a iter.
 *
 * \param iter  Opaque iterator value
 *
 * \return  Returns value, pointed by iterator.
 */
void *BH_QueueIterValue(void *iter);


#endif /* BH_QUEUE_H */
