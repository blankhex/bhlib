#ifndef BH_HASHMAP_H
#define BH_HASHMAP_H


#include "common.h"


typedef struct bh_hashmap_s bh_hashmap_t;


/**
 * Creates the new hashmap handle.
 *
 * \param equal  Comparision function
 * \param hash   Key hash function
 *
 * \return On success, returns hashmap handle.
 * \return On failure, returns a null pointer.
 */
bh_hashmap_t *bh_hashmap_new(bh_equal_cb_t equal,
                             bh_hash_cb_t hash);


/**
 * Destroys the hashmap.
 *
 * \param hashmap  Hashmap handle
 */
void bh_hashmap_free(bh_hashmap_t *hashmap);


/**
 * Clears the hashmap.
 *
 * \param hashmap  Hashmap handle
 */
void bh_hashmap_clear(bh_hashmap_t *hashmap);


/**
 * Reserves space in the hashmap.
 *
 * This function can both expand and shrink the available space in hashmap.
 * This function takes into account current hashmap load factor.
 *
 * \param hashmap  Hahsmap handle
 * \param size     Capacity
 *
 * \note Calling this function will invalidate iterators.
 * \note Actual hashmap capacity can be bigger then requested.
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_hashmap_reserve(bh_hashmap_t *hashmap,
                       size_t size);


/**
 * Inserts the pair of key-value into the hashmap.
 *
 * \param hashmap  Hashmap handle
 * \param key      Key
 * \param value    Value
 *
 * \note This function allows duplicates to be inserted.
 * \note Calling this function will invalidate iterators.
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_hashmap_insert(bh_hashmap_t *hashmap,
                      void *key,
                      void *value);


/**
 * Removes value from the hashmap.
 *
 * \param hashmap  Hashmap handle
 * \param key      Key
 *
 * \note Calling this function will invalidate iterators.
 * \note If hashmap contains several elements with the same key, this function
 *       will remove only one key-value pair.
 */
void bh_hashmap_remove(bh_hashmap_t *hashmap,
                       void *key);


/**
 * Returns value from the hashmap by key.
 *
 * \param hashmap  Hashmap handle
 * \param key      Key
 * \param value    Value (optional)
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int bh_hashmap_at(bh_hashmap_t *hashmap,
                  void *key,
                  void **value);


/**
 * Checks if the hashmap is empty.
 *
 * \param hashmap  Hashmap handle
 *
 * \return If hashmap is empty, returns non-zero value
 * \return If hashmap is not empty, returns zero value
 */
int bh_hashmap_empty(bh_hashmap_t *hashmap);


/**
 * Returns the size of the hashmap.
 *
 * \param hashmap  Hashmap handle
 *
 * \return Returns the size of the hashmap.
 */
size_t bh_hashmap_size(bh_hashmap_t *hashmap);


/**
 * Returns the capacity of the hashmap.
 *
 * \param hashmap  Hashmap handle
 *
 * \return Returns the capacity of the hashmap.
 */
size_t bh_hashmap_capacity(bh_hashmap_t *hashmap);


/**
 * Returns the load factor of the hashmap.
 *
 * \param hashmap  Hashmap handle
 *
 * \return Returns the load factor of the hashmap.
 */
float bh_hashmap_factor(bh_hashmap_t *hashmap);


/**
 * Sets the load factor of the hashmap.
 *
 * \param hashmap  Hashmap handle
 * \param factor   Load factor
 *
 * \note New load factor will be applied on the next reserve/insert operation.
 */
void bh_hashmap_set_factor(bh_hashmap_t *hashmap,
                           float factor);


/**
 * Returns the iterator to the element in the hashmap with specified key.
 *
 * \param hashmap  Hashmap handle
 * \param iter     Iterator
 *
 * \return On success, returns iterator value.
 * \return On failure, returns NULL pointer.
 *
 * \note If hashmap contains several elements with the same key, this function
 *       will return iterator to one of them
 */
void *bh_hashmap_iter_at(bh_hashmap_t *hashmap,
                         void *key);


/**
 * Returns the iterator to the next element in the hashmap.
 *
 * If the iterator is NULL pointer, this function will return iterator to the
 * first element of the hashmap.
 *
 * \param hashmap  Hashmap handle
 * \param iter     Iterator
 *
 * \return On success, returns new iterator value for the next element.
 * \return On failure, returns NULL pointer.
 */
void *bh_hashmap_iter_next(bh_hashmap_t *hashmap,
                           void *iter);


/**
 * Removes value from the hashmap pointed by by iterator.
 *
 * \param hashmap  Hashmap handle
 * \param iter     Iterator
 *
 * \note Calling this function will invalidate iterators.
 */
void bh_hashmap_iter_remove(bh_hashmap_t *hashmap,
                            void *iter);


/**
 * Returns key, pointed by the iterator.
 *
 * \param iter  Iterator
 *
 * \return Returns key.
 */
void *bh_hashmap_iter_key(void *iter);


/**
 * Returns value, pointed by the iterator.
 *
 * \param iter  Iterator
 *
 * \return Returns value.
 */
void *bh_hashmap_iter_value(void *iter);


#endif /* BH_HASHMAP_H */
