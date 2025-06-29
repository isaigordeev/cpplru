//
// Created by Isai Gordeev on 29/06/2025.
//

#include "chain.h"

template <typename K>
LRUCacheChain<K>::LRUCacheChain(int capacity)
    : capacity(capacity),
      head(std::make_shared<PrimitiveNode<K>>(K{})),
      tail(std::make_shared<PrimitiveNode<K>>(K{}))
{
    head->next = tail;
    tail->prev = head;
}
