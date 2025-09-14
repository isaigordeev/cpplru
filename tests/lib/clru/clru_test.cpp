//
// Created by Isai Gordeev on 03/08/2025.
//

#include <gtest/gtest.h>

extern "C" {
#include "lru.h"
}

TEST(ClruTest, InsertAndEvict) {
  LRU* lru = lru_init(2, 10);

  lru_put(lru, 6);
  lru_put(lru, 8);

  // Example: ensure that size == 2
  EXPECT_EQ(lru->chain->size, 2);

  lru_put(lru, 5);  // should evict something
  EXPECT_EQ(lru->chain->size, 2);

  lru_free(lru);
}
