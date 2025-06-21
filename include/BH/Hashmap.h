#ifndef BH_HASHMAP_H
#define BH_HASHMAP_H


#include "Common.h"


typedef struct BH_Hashmap BH_Hashmap;


BH_Hashmap *BH_HashmapNew(BH_EqualCallback equal,
                          BH_HashCallback hash);


void BH_HashmapFree(BH_Hashmap *hashmap);


void BH_HashmapClear(BH_Hashmap *hashmap);


int BH_HashmapReserve(BH_Hashmap *hashmap,
                      size_t size);


int BH_HashmapInsert(BH_Hashmap *hashmap,
                     void *key,
                     void *value);


void BH_HashmapRemove(BH_Hashmap *hashmap,
                      void *key);


int BH_HashmapAt(BH_Hashmap *hashmap,
                 void *key,
                 void **value);


int BH_HashmapEmpty(BH_Hashmap *hashmap);


size_t BH_HashmapSize(BH_Hashmap *hashmap);


size_t BH_HashmapCapacity(BH_Hashmap *hashmap);


float BH_HashmapFactor(BH_Hashmap *hashmap);


void BH_HashmapSetFactor(BH_Hashmap *hashmap,
                         float factor);


void *BH_HashmapIterAt(BH_Hashmap *hashmap,
                       void *key);


void *BH_HashmapIterNext(BH_Hashmap *hashmap,
                         void *iter);


void BH_HashmapIterRemove(BH_Hashmap *hashmap,
                          void *iter);


void *BH_HashmapIterKey(void *iter);


void *BH_HashmapIterValue(void *iter);


#endif /* BH_HASHMAP_H */
