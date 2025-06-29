//
// Created by Isai Gordeev on 25/05/2025.
//

#include "hash.h"
#include "stdlib.h"
#include "stdio.h"
#include "errors.h"
#include <stdbool.h>
#include "node.h"

int primitive_hash(const LRUHashTable *hashtable, int key, int *out_hash) {
  if (!hashtable || hashtable->hash_table_size <= 0 || !out_hash) {
    return LRU_ERR_NULL;
  }
  *out_hash = key % hashtable->hash_table_size;
  return LRU_SUCCESS;
}

LRUHashTable *createLRUHashTable() {
  LRUHashTable *hash_table = malloc(sizeof(*hash_table));

  if (!hash_table) {
    perror("Failed to allocate memory for hash_table");
    return NULL;
  }

  return hash_table;
}

LRUHashTable *initLRUHashTable(int hash_table_size) {

  if (hash_table_size <= 0) {
    perror("Invalid hash_table_size");
    return NULL;
  }

  LRUHashTable *hash_table = createLRUHashTable();

  hash_table->hash_table_size = hash_table_size;
  hash_table->hashtable = calloc(hash_table_size, sizeof(Node *));

  if (!hash_table->hashtable) {
    perror("Failed to allocate memory for hash_table attribute ->hashtable");
    free(hash_table);
    return NULL;
  }

  return hash_table;
}

void freeLRUHashTable(LRUHashTable *hash_table) {

  if (!hash_table) {
    return;
  }

  // Free all nodes in the chain
  int i = 0;
  for (; i < hash_table->hash_table_size; i = i + 1) {
    Node *current = hash_table->hashtable[i];
    while (current) {
      Node *next = current->bucket_next;
      freeNode(current);
      current = next;
    }
  }

  free(hash_table->hashtable);
  free(hash_table);
}

int hash_table_put(LRUHashTable *hash_table, int value, Node **wrapped_node) {
  if (!hash_table || !hash_table->hashtable || !wrapped_node) {
    printf("[hash_table_put] Error: Null pointer input\n");
    return LRU_ERR_NULL;
  }

  // If wrapped_node is already allocated, assume it is already inserted
  if (*wrapped_node) {
    printf("[hash_table_put] Node already allocated at %p, no insertion performed\n", (void *) (*wrapped_node));
    return LRU_ERR_MEM_OWNERSHIP;
  }

  int out_hash;
  int hashing_status = primitive_hash(hash_table, value, &out_hash);

  if (hashing_status != LRU_SUCCESS) {
    return LRU_ERR_NULL;
  }

  printf("[hash_table_put] Calculated hash index: %d for value: %d\n", out_hash, value);
  Node *node = createNode(out_hash, value, NULL, NULL, NULL);
  if (!node) {
    printf("[hash_table_put] Error: Failed to allocate node\n");
    return LRU_ERR_ALLOC;
  }

  *wrapped_node = node;  /* memory delegation */
  printf("[hash_table_put] Created node at %p with value %d, delegating ownership\n", (void *) node, value);

  Node *last_node = hash_table_get_last_bucket_node(hash_table, out_hash);
  if (!last_node) {
    hash_table->hashtable[out_hash] = node;
    printf("[hash_table_put] Inserted node as first in bucket %d\n", out_hash);
  } else {
    last_node->bucket_next = node;
    printf("[hash_table_put] Appended node to end of bucket %d after node %p\n", out_hash, (void *) last_node);
  }

  return LRU_SUCCESS;
}

Node *hash_table_get_last_bucket_node(const LRUHashTable *hash_table, const int idx) {

  if (!hash_table) {
    printf("[hash_table_get_last_bucket_node] ERROR: hash_table is NULL\n");
    return NULL;
  }

  if (!hash_table->hashtable) {
    printf("[hash_table_get_last_bucket_node] ERROR: hashtable is NULL\n");
    return NULL;
  }

  if (idx < 0 || idx >= hash_table->hash_table_size) {
    printf("[hash_table_get_last_bucket_node] ERROR: idx %d out of bounds (size=%d)\n",
           idx,
           hash_table->hash_table_size);
    return NULL;
  }

  if (!(hash_table->hashtable[idx])) {
    printf("[hash_table_get_last_bucket_node] Bucket %d is empty\n", idx);
    return NULL;
  }

  Node *curr = hash_table->hashtable[idx];
  while (curr->bucket_next) {
    curr = curr->bucket_next;
  }
  return curr;
}

int hash_table_contains(LRUHashTable *hash_table, int value, int *found) {
  if (!hash_table || !found) {
    return LRU_ERR_NULL;
  }

  int *out_hash;
  int hashing_status = primitive_hash(NULL, value, out_hash);

  if (!hashing_status) {
    return LRU_ERR_NULL;
  }

  Node *current = hash_table->hashtable[*out_hash];

  while (current) {
    if (current->value == value) {
      *found = true;
      return LRU_SUCCESS;
    }
    current = current->bucket_next;
  }

  *found = false;
  return LRU_SUCCESS;
}

int hash_table_remove(LRUHashTable *hash_table, int value) {
  if (!hash_table) {
    return LRU_ERR_NULL;
  }

  int *out_hash;
  int hashing_status = primitive_hash(NULL, value, out_hash);

  if (!hashing_status) {
    return LRU_ERR_NULL;
  }
  Node *current = hash_table->hashtable[*out_hash];

  if (!current) {
    return LRU_SUCCESS;
  }

  Node *prev = NULL;

  while (current) {
    if (prev) {
      if (current->value == value) {
        prev->bucket_next = current->bucket_next;
        freeNode(current);
        return LRU_SUCCESS;
      }
    } else {
      hash_table->hashtable[*out_hash] = current->next;
      freeNode(current);
      return LRU_SUCCESS;
    }
    prev = current;
    current = current->bucket_next;
  }

  return LRU_SUCCESS;
}




