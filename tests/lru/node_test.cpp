//
// Created by Isai Gordeev on 29/06/2025.
//

#include <gtest/gtest.h>
#include "lru/node.h"

TEST(PrimitiveNodeTest, ConstructorInitializesValues) {
PrimitiveNode<int, std::string> node(42, "value");

EXPECT_EQ(node.key, 42);
EXPECT_EQ(node.value, "value");
EXPECT_EQ(node.next, nullptr);
EXPECT_TRUE(node.prev.expired());
EXPECT_EQ(node.bucket_next, nullptr);
}

TEST(PrimitiveNodeTest, CanLinkNextAndPrev) {
auto node1 = std::make_shared<PrimitiveNode<int, std::string>>(1, "one");
auto node2 = std::make_shared<PrimitiveNode<int, std::string>>(2, "two");

node1->next = node2;
node2->prev = node1;

EXPECT_EQ(node1->next, node2);
EXPECT_FALSE(node2->prev.expired());
EXPECT_EQ(node2->prev.lock(), node1);
}

TEST(PrimitiveNodeTest, CanSetBucketNext) {
auto node1 = std::make_shared<PrimitiveNode<int, std::string>>(1, "one");
auto node2 = std::make_shared<PrimitiveNode<int, std::string>>(2, "two");

node1->bucket_next = node2;

EXPECT_EQ(node1->bucket_next, node2);
}