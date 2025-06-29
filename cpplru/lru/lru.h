//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "chain.h"
#include "hash.h"
#include <memory>

constexpr int HASH_CAPACITY = 100;
constexpr int CHAIN_CAPACITY = 100;

struct LRUConfig
{
    int hash_capacity = HASH_CAPACITY;
    int chain_capacity = CHAIN_CAPACITY;
};

template <typename K> class LRU
{
  private:
    LRUConfig lruConfig;
    std::unique_ptr<LRUHashTable<K>> lruHashTable;
    std::unique_ptr<LRUCacheChain<K>> lruChain;

  public:
    explicit LRU()
        : lruConfig(LRUConfig{}),
          lruHashTable(
                  std::make_unique<LRUHashTable<K>>(lruConfig.hash_capacity)),
          lruChain(std::make_unique<LRUCacheChain<K>>(
                  lruConfig.chain_capacity)){};

    explicit LRU(const LRUConfig& lruConfig)
        : lruConfig(lruConfig),
          lruHashTable(
                  std::make_unique<LRUHashTable<K>>(lruConfig.hash_capacity)),
          lruChain(std::make_unique<LRUCacheChain<K>>(
                  lruConfig.chain_capacity)){};

    void put(const std::shared_ptr<PrimitiveNode<K>>& node)
    {
        lruHashTable->put(node);
        lruChain->put(node);
    }

    std::shared_ptr<PrimitiveNode<K>> get_head() const
    {
        return lruChain->get_head();
    }
};