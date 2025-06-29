//
// Created by Isai Gordeev on 25/05/2025.
//

#ifndef LRU_NODE_H
#define LRU_NODE_H

#include "stdlib.h"

typedef struct Node {
  int key;
  int value;
  struct Node *prev;
  struct Node *next;
  struct Node *bucket_next;
} Node;

Node *createNode(int key, int value, struct Node *bucket_node, struct Node *prev, struct Node *next);
void freeNode(Node *node);

#endif //LRU_NODE_H
