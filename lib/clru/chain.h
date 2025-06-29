//
// Created by Isai Gordeev on 25/05/2025.
//

#ifndef LRU_CHAIN_H
#define LRU_CHAIN_H

#include "node.h"

typedef struct LRUCacheChain {
  int capacity;
  int size;
  Node *head;
  Node *tail;
} LRUCacheChain;

// Create an empty LRUCacheChain (allocation only)
LRUCacheChain *createLRUCacheChain(void);

// Initialize an LRUCacheChain with hash_table_size and optional head/tail nodes
LRUCacheChain *initLRUCacheChain(int capacity, Node *head, Node *tail);

// Free the LRUCacheChain and all nodes it hash_table_contains
void freeLRUCacheChain(LRUCacheChain *chain);

// Add a new node with key,value at the front (head) of the chain
int add_node_to_head(LRUCacheChain *chain, Node *node);

// Remove a node from anywhere in the chain
void removeNode(LRUCacheChain *chain, Node *node);

// Move a given node to the head of the chain (most recently used)
void moveToHead(LRUCacheChain *chain, Node *node);

// Remove the tail node (least recently used) and return it
Node *removeTail(LRUCacheChain *chain);

// Getters
int getCapacity(const LRUCacheChain *chain);
int getSize(const LRUCacheChain *chain);
Node *getHead(const LRUCacheChain *chain);
Node *getTail(const LRUCacheChain *chain);

// Get key and value from a node
int getNodeKey(const Node *node);
int getNodeValue(const Node *node);

void print_chain(LRUCacheChain *chain);

#endif // LRU_CHAIN_H
