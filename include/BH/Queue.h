#ifndef BH_QUEUE_H
#define BH_QUEUE_H


#include "Common.h"


typedef struct BH_Queue BH_Queue;


BH_Queue *BH_QueueNew(void);


void BH_QueueFree(BH_Queue *queue);


void BH_QueueClear(BH_Queue *queue);


int BH_QueueReserve(BH_Queue *queue,
                    size_t size);


int BH_QueueInsert(BH_Queue *queue,
                   void *value);


void BH_QueueRemove(BH_Queue *queue);


int BH_QueueFront(BH_Queue *queue,
                  void **value);


int BH_QueueEmpty(BH_Queue *queue);


size_t BH_QueueSize(BH_Queue *queue);


size_t BH_QueueCapacity(BH_Queue *queue);


void *BH_QueueIterNext(BH_Queue *queue,
                       void *iter);


void *BH_QueueIterValue(void *iter);


#endif /* BH_QUEUE_H */
