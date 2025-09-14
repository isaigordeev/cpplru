//
// Created by Isai GORDEEV on 14/09/2025.
//

#pragma once

#include <list>
#include <unordered_map>

#include "buffer_page.h"
#include "disk_manager.hpp"

class BufferPool {
 public:
  BufferPool(DiskManager* dm, size_t pool_size)
      : diskManager(dm), maxPoolSize(pool_size) {}

  // Fetch a page from buffer or disk
  BufferPage* fetchPage(int page_id) {
    // Already in memory
    if (bufferMap.find(page_id) != bufferMap.end()) {
      touch(page_id);
      bufferMap[page_id].pinCount++;
      return &bufferMap[page_id];
    }

    // Load from disk
    if (bufferMap.size() >= maxPoolSize) evictPage();

    BufferPage bufPage;
    bufPage.page = diskManager->readPage(page_id);
    bufPage.pageId = page_id;
    bufPage.pinCount = 1;

    bufferMap[page_id] = bufPage;
    lruList.push_front(page_id);
    return &bufferMap[page_id];
  }

  // Mark a page as dirty
  void markDirty(int page_id) {
    if (bufferMap.find(page_id) != bufferMap.end())
      bufferMap[page_id].dirty = true;
  }

  // Flush all dirty pages to disk
  void flushAll() {
    for (auto& [id, bufPage] : bufferMap) {
      if (bufPage.dirty) {
        diskManager->writePage(id, bufPage.page);
        bufPage.dirty = false;
      }
    }
  }

 private:
  DiskManager* diskManager;
  size_t maxPoolSize;
  std::unordered_map<int, BufferPage> bufferMap;
  std::list<int> lruList;

  void touch(int page_id) {
    lruList.remove(page_id);
    lruList.push_front(page_id);
  }

  void evictPage() {
    for (auto it = lruList.rbegin(); it != lruList.rend(); ++it) {
      int page_id = *it;
      BufferPage& page = bufferMap[page_id];
      if (page.pinCount == 0) {
        if (page.dirty) diskManager->writePage(page_id, page.page);
        bufferMap.erase(page_id);
        lruList.remove(page_id);
        return;
      }
    }
    std::cerr << "Buffer pool full, no page to evict!\n";
  }
};