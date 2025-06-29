//
// Created by Isai Gordeev on 29/06/2025.
//

#include "lru/hash.h"
#include <gtest/gtest.h>

TEST(LRUHashTableTest, HashKey)
{
    LRUHashTable<std::string> table;

    std::string key = "example_key";
    size_t expected_hash = std::hash<std::string>{}(key) % table.get_capacity();
    size_t actual_hash = table.hash(key);

    EXPECT_EQ(expected_hash, actual_hash);
}

TEST(LRUHashTableTest, HashNode)
{
    LRUHashTable<std::string> table;

    std::string key = "node_key";
    PrimitiveNode<std::string> node(key);
    size_t expected_hash = std::hash<std::string>{}(key) % table.get_capacity();
    size_t actual_hash = table.hash_node(node);

    EXPECT_EQ(expected_hash, actual_hash);
}

class LRUHashTableTestExists : public ::testing::Test
{
  protected:
    LRUHashTable<std::string> table{10};

    std::shared_ptr<PrimitiveNode<std::string>> node1 =
            std::make_shared<PrimitiveNode<std::string>>("key1");
    std::shared_ptr<PrimitiveNode<std::string>> node2 =
            std::make_shared<PrimitiveNode<std::string>>("key2");
};

TEST_F(LRUHashTableTestExists, ExistsInitiallyFalse)
{
    EXPECT_FALSE(table.exists(node1));
    EXPECT_FALSE(table.exists(node2));
}

TEST_F(LRUHashTableTestExists, ExistsAfterPut)
{
    table.put(node1);
    EXPECT_TRUE(table.exists(node1));
    EXPECT_FALSE(table.exists(node2));
}

TEST_F(LRUHashTableTestExists, ExistsForSameKeyDifferentObject)
{
    table.put(node1);
    auto node1_copy = std::make_shared<PrimitiveNode<std::string>>("key1");
    EXPECT_TRUE(table.exists(node1_copy)); // Because key is same, hash is same
}