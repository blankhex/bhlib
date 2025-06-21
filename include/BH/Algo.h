#ifndef BH_ALGO_H
#define BH_ALGO_H


#include "Common.h"


void BH_Swap(void *dest,
             void *src,
             size_t size);


void *BH_Partition(void *pivot,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


void BH_Sort(void *array,
             size_t size,
             size_t element,
             BH_EqualCallback equal);


void BH_HeapMake(void *array,
                 size_t size,
                 size_t element,
                 BH_EqualCallback equal);


void BH_HeapRemove(void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


void BH_HeapInsert(void *value,
                   void *array,
                   size_t size,
                   size_t element,
                   BH_EqualCallback equal);


void BH_HeapReplace(void *value,
                    void *array,
                    size_t size,
                    size_t element,
                    BH_EqualCallback equal);


#endif /* BH_ALGO_H */
