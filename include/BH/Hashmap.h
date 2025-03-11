#ifndef BH_HASHMAP_H
#define BH_HASHMAP_H


#include "Common.h"


typedef struct BH_Hashmap BH_Hashmap;


/**
 * Creates the new hashmap with specified \a equal and \a hash callbacks.
 *
 * \param equal  Comparision function
 * \param hash   Key hash function
 *
 * \return On success, returns hashmap pointer.
 * \return On failure, returns a null pointer.
 */
BH_Hashmap *BH_HashmapNew(BH_EqualCallback equal,
                          BH_HashCallback hash);


/**
 * Destroys the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 */
void BH_HashmapFree(BH_Hashmap *hashmap);


/**
 * Clears the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 */
void BH_HashmapClear(BH_Hashmap *hashmap);


/**
 * Reserves space for \a size amount of elements in the \a hashmap.
 *
 * This function can both expand and shrink the available space in hashmap.
 * This function takes into account current hashmap load factor.
 *
 * \param hashmap  Hahsmap pointer
 * \param size     Capacity
 *
 * \note Calling this function will invalidate iterators.
 * \note Actual hashmap capacity can be bigger then requested.
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_HashmapReserve(BH_Hashmap *hashmap,
                      size_t size);


/**
 * Inserts the pair \a key \a value pair into the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 * \param key      Key
 * \param value    Value
 *
 * \note This function allows duplicates to be inserted.
 * \note Calling this function will invalidate iterators.
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_HashmapInsert(BH_Hashmap *hashmap,
                     void *key,
                     void *value);


/**
 * Removes value from the \a hashmap by \a key.
 *
 * \param hashmap  Hashmap pointer
 * \param key      Key
 *
 * \note Calling this function will invalidate iterators.
 * \note If hashmap contains several elements with the same key, this function
 *       will remove only one key-value pair.
 */
void BH_HashmapRemove(BH_Hashmap *hashmap,
                      void *key);


/**
 * Returns \a value from the \a hashmap by \a key.
 *
 * \param hashmap  Hashmap pointer
 * \param key      Key
 * \param value    Value (optional)
 *
 * \return On success, returns zero.
 * \return On failure, returns error code.
 */
int BH_HashmapAt(BH_Hashmap *hashmap,
                 void *key,
                 void **value);


/**
 * Checks if the \a hashmap is empty.
 *
 * \param hashmap  Hashmap pointer
 *
 * \return If hashmap is empty, returns non-zero value
 * \return If hashmap is not empty, returns zero
 */
int BH_HashmapEmpty(BH_Hashmap *hashmap);


/**
 * Returns the size of the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 *
 * \return Returns the size of the hashmap.
 */
size_t BH_HashmapSize(BH_Hashmap *hashmap);


/**
 * Returns the capacity of the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 *
 * \return Returns the capacity of the hashmap.
 */
size_t BH_HashmapCapacity(BH_Hashmap *hashmap);


/**
 * Returns the load factor of the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 *
 * \return Returns the load factor of the hashmap.
 */
float BH_HashmapFactor(BH_Hashmap *hashmap);


/**
 * Sets the load \a factor of the \a hashmap.
 *
 * \param hashmap  Hashmap pointer
 * \param factor   Load factor
 *
 * \note New load factor will be applied on the next reserve/insert operation.
 */
void BH_HashmapSetFactor(BH_Hashmap *hashmap,
                         float factor);


/**
 * Returns the iterator to the element in the \a hashmap by \a key.
 *
 * \param hashmap  Hashmap pointer
 * \param iter     Iterator
 *
 * \return On success, returns iterator value.
 * \return On failure, returns NULL pointer.
 *
 * \note If hashmap contains several elements with the same key, this function
 *       will return iterator to one of them
 */
void *BH_HashmapIterAt(BH_Hashmap *hashmap,
                       void *key);


/**
 * Returns next element \a iter in the \a hashmap.
 *
 * If \a iter is NULL pointer, then this function will return iter to the
 * first element of the hashmap.
 *
 * \param hashmap  Hashmap pointer
 * \param iter     Iterator
 *
 * \return On success, returns new iterator value for the next element.
 * \return On failure, returns NULL pointer.
 */
void *BH_HashmapIterNext(BH_Hashmap *hashmap,
                         void *iter);


/**
 * Removes key-value from the \a hashmap pointed by \a iter.
 *
 * \param hashmap  Hashmap pointer
 * \param iter     Iterator
 *
 * \note Calling this function will invalidate iterators.
 */
void BH_HashmapIterRemove(BH_Hashmap *hashmap,
                          void *iter);


/**
 * Returns key, pointed by the \a iter.
 *
 * \param iter  Iterator
 *
 * \return Returns key.
 */
void *BH_HashmapIterKey(void *iter);


/**
 * Returns value, pointed by the \a iter.
 *
 * \param iter  Iterator
 *
 * \return Returns value.
 */
void *BH_HashmapIterValue(void *iter);


#endif /* BH_HASHMAP_H */
