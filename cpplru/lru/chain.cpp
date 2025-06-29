//
// Created by Isai Gordeev on 29/06/2025.
//

#include "chain.h"

template<typename K, typename V>
LRUCacheChain<K, V>::LRUCacheChain(int capacity)
		: capacity(capacity), size(0),
		  head(std::make_shared<PrimitiveNode<K, V>>(K{}, V{})),
		  tail(std::make_shared<PrimitiveNode<K, V>>(K{}, V{}))
{
	head->next = tail;
	tail->prev = head;
}
