//
// Created by Isai GORDEEV on 05/08/2025.
//
#pragma once

#include <atomic>
#include <thread>

class Mutex
{
 public:
  void Lock()
  {
    uint32_t expected = 0;

    if (locked_.compare_exchange_strong(
                expected, 1, std::memory_order_acquire)) {
      return;
    }

    while (true) {
      expected = 0;
      if (locked_.load(std::memory_order_relaxed) == 0) {
        if (locked_.compare_exchange_strong(
                    expected, 1, std::memory_order_acquire)) {
          return;
        }
      }
      std::this_thread::yield();  // fallback when waiting, as std::futex
                                  // is not standard yet
    }
  }

  void Unlock() { locked_.store(0, std::memory_order_release); }

  // BasicLockable
  void lock() { Lock(); }

  void unlock() { Unlock(); }

 private:
  std::atomic_uint32_t locked_{0};
};