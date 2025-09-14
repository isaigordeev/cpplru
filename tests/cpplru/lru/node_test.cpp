//
// Created by Isai Gordeev on 29/06/2025.
//

#include "lru/node.h"
#include <gtest/gtest.h>

TEST(PrimitiveNodeTest, ConstructorInitializesValues)
{
    PrimitiveNode<int> node(42);

    EXPECT_EQ(node.key, 42);
    EXPECT_EQ(node.next, nullptr);
    EXPECT_TRUE(node.prev.expired());
    EXPECT_EQ(node.bucket_next, nullptr);
}

TEST(PrimitiveNodeTest, CanLinkNextAndPrev)
{
    auto node1 = std::make_shared<PrimitiveNode<int>>(1);
    auto node2 = std::make_shared<PrimitiveNode<int>>(2);

    node1->next = node2;
    node2->prev = node1;

    EXPECT_EQ(node1->next, node2);
    EXPECT_FALSE(node2->prev.expired());
    EXPECT_EQ(node2->prev.lock(), node1);
}

TEST(PrimitiveNodeTest, CanSetBucketNext)
{
    auto node1 = std::make_shared<PrimitiveNode<std::string>>("one");
    auto node2 = std::make_shared<PrimitiveNode<std::string>>("two");

    node1->bucket_next = node2;

    EXPECT_EQ(node1->bucket_next, node2);
}