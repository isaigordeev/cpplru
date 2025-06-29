//
// Created by Isai Gordeev on 29/06/2025.
//

#include "lru/hash.h"
#include <gtest/gtest.h>

TEST(LRUHashTableTest, HashKey)
{
    LRUHashTable<std::string> table;

    std::string key = "example_key";
    size_t expected_hash = std::hash<std::string>{}(key);
    size_t actual_hash = table.hash(key);

    EXPECT_EQ(expected_hash, actual_hash);
}

TEST(LRUHashTableTest, HashNode)
{
    LRUHashTable<std::string> table;

    std::string key = "node_key";
    PrimitiveNode<std::string> node(key);
    size_t expected_hash = std::hash<std::string>{}(key);
    size_t actual_hash = table.hash_node(node);

    EXPECT_EQ(expected_hash, actual_hash);
}
