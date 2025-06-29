//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "node.h"

constexpr int DEFAULT_HASH_TABLE_CAPACITY = 1000;

template <typename K> class LRUHashTable
{
  private:
    std::hash<K> hasher;
    int capacity = DEFAULT_HASH_TABLE_CAPACITY;
    std::vector<std::shared_ptr<PrimitiveNode<K>>> hashtable;

  public:
    explicit LRUHashTable(int capacity = DEFAULT_HASH_TABLE_CAPACITY)
        : capacity(capacity), hashtable(capacity){};

    size_t hash(const K& key) const { return hasher(key) % capacity; }

    size_t hash_node(const PrimitiveNode<K>& node) const
    {
        return hash(node.get_key());
    }

    int get_capacity() { return capacity; }

    void put(std::shared_ptr<PrimitiveNode<K>> node)
    {
        int idx = hash_node(*node);
        hashtable[idx] = std::move(node);
    }

    std::shared_ptr<PrimitiveNode<K>> get(int idx) const
    {
        return hashtable[idx];
    }

    bool exists(const std::shared_ptr<PrimitiveNode<K>> node) const
    {
        int idx = hash_node(*node);
        return static_cast<bool>(get(idx));
    }
};
