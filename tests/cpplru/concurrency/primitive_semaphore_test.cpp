#include "concurrency/primitive_semaphore.h"

#include <gtest/gtest.h>

#include <atomic>
#include <thread>
#include <vector>

// =============================
// Classic Semaphore Tests
// =============================
TEST(PrimitiveClassicSemaphoreTest, InitialPermits) {
  PrimitiveClassicSemaphore sem(2);

  // Acquire twice should succeed without blocking
  sem.Acquire();
  sem.Acquire();

  // Start a thread that tries to acquire (should block)
  std::atomic<bool> acquired{false};
  std::thread t([&]() {
    sem.Acquire();
    acquired = true;
  });

  // Sleep briefly to ensure thread is waiting
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_FALSE(acquired);

  sem.Release();  // Release one permit
  t.join();
  EXPECT_TRUE(acquired);
}

TEST(PrimitiveClassicSemaphoreTest, ReleaseIncrementsPermits) {
  PrimitiveClassicSemaphore sem(0);

  std::atomic<bool> acquired{false};
  std::thread t([&]() {
    sem.Acquire();
    acquired = true;
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_FALSE(acquired);

  sem.Release();
  t.join();
  EXPECT_TRUE(acquired);
}

// =============================
// Spin Semaphore Tests
// =============================
TEST(PrimitiveSpinSemaphoreTest, BasicAcquireRelease) {
  PrimitiveSpinSemaphore sem;

  // Initialize permits
  sem.ReleaseImpl();  // permits_ = 1

  // Acquire should succeed immediately
  sem.AcquireImpl();

  // No exception / crash should occur
  SUCCEED();
}

TEST(PrimitiveSpinSemaphoreTest, MultithreadedAcquireRelease) {
  PrimitiveSpinSemaphore sem;
  const int thread_count = 4;
  const int permits = 2;

  // Initialize permits
  for (int i = 0; i < permits; ++i) sem.ReleaseImpl();

  std::atomic<int> acquired_count{0};
  std::vector<std::thread> threads;

  for (int i = 0; i < thread_count; ++i) {
    threads.emplace_back([&]() {
      sem.AcquireImpl();
      acquired_count.fetch_add(1);
    });
  }

  // Sleep briefly to let some threads acquire
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_LE(acquired_count.load(), permits);

  // Release remaining permits
  for (int i = 0; i < thread_count; ++i) {
    sem.ReleaseImpl();
  }

  for (auto& t : threads) t.join();
  EXPECT_EQ(acquired_count.load(), thread_count);
}
