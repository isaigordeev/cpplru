//
// Created by Isai Gordeev on 15/06/2025.
//

#ifndef LRU_LRU_H_
#define LRU_LRU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "chain.h"
#include "hash.h"

typedef struct LRU
{
    int queue_capacity;
    int hash_size;
    LRUCacheChain* chain;
    LRUHashTable* hash_table;
} LRU;

// Initialize LRU cache with given hash_table_size
LRU* lru_init(int hash_table_size, int queue_capacity);
LRU* lru_create();

// Free the LRU cache and all associated resources
void lru_free(LRU* lru);

// Add a value to the LRU cache (or update if it exists)
// Returns 1 if added or updated successfully, 0 on failure
int lru_put(LRU* lru, int value);

// Get a value by key from the LRU cache
// Returns 1 and sets *value if found, else returns 0
const int lru_get_head_value(const LRU* lru);
const int lru_get_tail_value(const LRU* lru);

// Check if a key exists in the LRU cache
int lru_contains(LRU* lru, int key);

// Remove a key from the LRU cache
// Returns 1 if removed, 0 if not found
int lru_remove(LRU* lru, int key);

// Get current size of the cache
const int lru_size(const LRU* lru);

// Return pointer to the head (most recently used) node
const Node* lru_get_head(const LRU* lru);

// Return pointer to the tail (least recently used) node
const Node* lru_get_tail(const LRU* lru);

#ifdef __cplusplus
}
#endif

#endif // LRU_LRU_H_
