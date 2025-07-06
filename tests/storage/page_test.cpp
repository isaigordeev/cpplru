//
// Created by Isai GORDEEV on 06/07/2025.
//

#include "storage/page.h"
#include "storage/record.h"
#include <gtest/gtest.h>

class PrimitivePageTest : public ::testing::Test
{
  protected:
    PrimitivePage page;
};

TEST_F(PrimitivePageTest, InsertUntilFull)
{
    for (int i = 0; i < PrimitivePage::MAX_RECORDS; i++) {
        PrimitiveRecord rec{i};
        EXPECT_TRUE(page.insertRecord(rec));
        EXPECT_EQ(page.size, i + 1);
        EXPECT_EQ(page.data.back(), rec);
    }
    // Page should now be full
    PrimitiveRecord extra{9999};
    EXPECT_FALSE(page.insertRecord(extra));
    EXPECT_EQ(page.size, PrimitivePage::MAX_RECORDS);
}

TEST_F(PrimitivePageTest, InitiallyEmpty)
{
    EXPECT_EQ(page.size, 0);
    EXPECT_TRUE(page.data.empty());
}