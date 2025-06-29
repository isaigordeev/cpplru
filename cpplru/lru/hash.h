//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "node.h"

constexpr int DEFAULT_HASH_TABLE_CAPACITY = 1000;

template<typename K>
class LRUHashTable {
private:
    std::hash<K> hasher;
	int capacity;
	std::vector<K> hashtable;

public:
	explicit LRUHashTable(int capacity = DEFAULT_HASH_TABLE_CAPACITY): capacity(capacity),
	hashtable(capacity){};

	size_t hash_node(PrimitiveNode<K>& node);
    size_t hash(K& key);
};
