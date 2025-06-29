//
// Created by Isai Gordeev on 29/06/2025.
//

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include your headers
#include "lru/lru.h"

// Test fixture for LRU with string keys
class LRUStringTest : public ::testing::Test
{
  protected:
    LRU<std::string> cache;

    LRUStringTest() : cache() {}

    std::shared_ptr<PrimitiveNode<std::string>> make_node(
            const std::string& key)
    {
        return std::make_shared<PrimitiveNode<std::string>>(key);
    }
};

TEST_F(LRUStringTest, EmptyCacheHeadIsNull)
{
    // Initially, the head should be null or a sentinel node depending on your
    // implementation
    auto head = cache.get_head();
    EXPECT_EQ(
            head, nullptr); // or check for sentinel if implemented differently
}

TEST_F(LRUStringTest, PutSingleNode)
{
    auto node = make_node("one");
    cache.put(node);

    auto head = cache.get_head();
    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->get_key(), "one");
}

TEST_F(LRUStringTest, PutMultipleNodesUpdatesHead)
{
    auto node1 = make_node("one");
    auto node2 = make_node("two");

    cache.put(node1);
    cache.put(node2);

    auto head = cache.get_head();
    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->get_key(), "two"); // Most recently added should be head
}
