//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "node.h"
constexpr int DEFAULT_CAPACITY=1000;

template<typename K, typename V>
class LRUCacheChain {
public:
	explicit LRUCacheChain<K,V>(int capacity = DEFAULT_CAPACITY);
private:
	int size = 0;
	int capacity = DEFAULT_CAPACITY;

	std::shared_ptr<PrimitiveNode<K, V>> head;  // Most recently used (MRU) sentinel
	std::shared_ptr<PrimitiveNode<K, V>> tail;  // Least recently used (LRU) sentinel
};
