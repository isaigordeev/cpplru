//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "node.h"
constexpr int DEFAULT_CAPACITY=1000;

template<typename K>
class LRUCacheChain {
public:
	explicit LRUCacheChain<K>(int capacity = DEFAULT_CAPACITY);
private:
	int size = 0;
	int capacity = DEFAULT_CAPACITY;

	std::shared_ptr<PrimitiveNode<K>> head;  // Most recently used (MRU) sentinel
	std::shared_ptr<PrimitiveNode<K>> tail;  // Least recently used (LRU) sentinel
};
