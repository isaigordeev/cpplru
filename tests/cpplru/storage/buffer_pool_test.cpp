#include "storage/buffer_pool.hpp"

#include <filesystem>

#include "gtest/gtest.h"
#include "storage/record.h"

class BufferTest : public ::testing::Test {
 protected:
  const std::string filename = "gtest_data.bin";

  void SetUp() override {
    // Remove old test file if exists
    if (std::filesystem::exists(filename)) {
      std::filesystem::remove(filename);
    }
  }

  void TearDown() override {
    if (std::filesystem::exists(filename)) {
      std::filesystem::remove(filename);
    }
  }
};

// Test writing and reading a single page
TEST_F(BufferTest, WriteAndReadPage) {
  DiskManager dm(filename);
  BufferPool buffer(&dm, 2);

  BufferPage* p0 = buffer.fetchPage(0);
  for (int i = 0; i < 5; i++) {
    p0->page.insertRecord(PrimitiveRecord(i));
  }
  buffer.markDirty(0);
  buffer.flushAll();

  BufferPage* reload = buffer.fetchPage(0);
  ASSERT_EQ(reload->page.size, 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(reload->page.data[i].idx, i);
  }
}

// Test LRU eviction policy
TEST_F(BufferTest, LRUEviction) {
  DiskManager dm(filename);
  BufferPool buffer(&dm, 2);  // max 2 pages

  BufferPage* p0 = buffer.fetchPage(0);
  BufferPage* p1 = buffer.fetchPage(1);
  buffer.markDirty(0);
  buffer.markDirty(1);

  // Access p0 to make it recently used
  buffer.fetchPage(0);

  // Fetch a new page, should evict p1
  BufferPage* p2 = buffer.fetchPage(2);
  buffer.markDirty(2);

  // p1 should be evicted and reloaded correctly
  BufferPage* p1Reloaded = buffer.fetchPage(1);
  EXPECT_EQ(p1Reloaded->pageId, 1);
}

// Test flushing dirty pages
TEST_F(BufferTest, DirtyPageFlush) {
  DiskManager dm(filename);
  BufferPool buffer(&dm, 2);

  BufferPage* p0 = buffer.fetchPage(0);
  p0->page.insertRecord(PrimitiveRecord(42));
  buffer.markDirty(0);
  buffer.flushAll();

  // Re-read directly from disk
  PrimitivePage page = dm.readPage(0);
  ASSERT_EQ(page.size, 1);
  EXPECT_EQ(page.data[0].idx, 42);
}
