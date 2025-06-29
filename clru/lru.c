//
// Created by Isai Gordeev on 15/06/2025.
//

#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

LRU *lru_create() {

  LRU *lru = malloc(sizeof(*lru));

  if (!lru) {
    perror("Failed to allocate memory for hash_table");
    return NULL;
  }
  return lru;
}

LRU *lru_init(int hash_table_size, int queue_capacity) {

  LRUHashTable *hash_table = initLRUHashTable(hash_table_size);
  if (!hash_table) {
    fprintf(stderr, "Failed to initialize LRUHashTable\n");
    return NULL;
  }

  LRUCacheChain *chain = initLRUCacheChain(queue_capacity, NULL, NULL);
  if (!chain) {
    fprintf(stderr, "Failed to initialize LRUCacheChain\n");
    freeLRUHashTable(hash_table);
    return NULL;
  }

  LRU *lru = lru_create();

  lru->hash_size = hash_table_size;
  lru->queue_capacity = queue_capacity;
  lru->chain = chain;
  lru->hash_table = hash_table;

  return lru;
}

int lru_put(LRU *lru, int value) {
  LRUHashTable *hash_table = lru->hash_table;
  LRUCacheChain *chain = lru->chain;

  Node *node = NULL;
  int ht_status = hash_table_put(hash_table, value, &node);
  if (ht_status == LRU_ERR_NULL) {
    return ht_status;
  }
  int chain_status = add_node_to_head(chain, node);

  return ht_status;
}

void lru_free(LRU *lru) {
  if (!lru) {
    printf("[lru_free] Warning: NULL LRU pointer, nothing to free\n");
    return;
  }

  if (lru->chain) {
    printf("[lru_free] Freeing LRUCacheChain at %p\n", (void *) lru->chain);
    freeLRUCacheChain(lru->chain);
    lru->chain = NULL;
  } else {
    printf("[lru_free] LRUCacheChain is already NULL\n");
  }

  if (lru->hash_table) {
    printf("[lru_free] Freeing LRUHashTable at %p\n", (void *) lru->hash_table);
    freeLRUHashTable(lru->hash_table);
    lru->hash_table = NULL;
  } else {
    printf("[lru_free] LRUHashTable is already NULL\n");
  }

  printf("[lru_free] Freeing LRU struct at %p\n", (void *) lru);
  free(lru);
}
