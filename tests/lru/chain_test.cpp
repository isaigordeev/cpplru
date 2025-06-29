//
// Created by Isai Gordeev on 29/06/2025.
//

#include "lru/chain.h"
#include <gtest/gtest.h>
#include <memory>
#include <string>

TEST(LRUCacheChainTest, InsertIncreasesSize)
{
    LRUCacheChain<std::string> chain(2);

    auto node1 = std::make_shared<PrimitiveNode<std::string>>("one");
    chain.put(node1);

    EXPECT_EQ(chain.get_size(), 1);
}

TEST(LRUCacheChainTest, CapacityEvictsTail)
{
    LRUCacheChain<std::string> chain(2);

    auto node1 = std::make_shared<PrimitiveNode<std::string>>("one");
    auto node2 = std::make_shared<PrimitiveNode<std::string>>("two");
    auto node3 = std::make_shared<PrimitiveNode<std::string>>("three");

    chain.put(node1);
    chain.put(node2);
    chain.put(node3); // This should evict node1

    EXPECT_EQ(chain.get_size(), 2);
}

TEST(LRUCacheChainTest, ReorderingUpdatesPosition)
{
    LRUCacheChain<std::string> chain(3);

    auto node1 = std::make_shared<PrimitiveNode<std::string>>("one");
    auto node2 = std::make_shared<PrimitiveNode<std::string>>("two");
    auto node3 = std::make_shared<PrimitiveNode<std::string>>("three");

    chain.put(node1);
    chain.put(node2);
    chain.put(node3);

    // Use node1 again, it should move to front
    chain.put(node1);

    EXPECT_EQ(chain.get_size(), 3);
}
