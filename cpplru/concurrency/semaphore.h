#pragma once
#include <condition_variable>
#include <mutex>
#include <thread>

template <typename Derived>
class SemaphoreBase {
 public:
  void Acquire() { static_cast<Derived*>(this)->AcquireImpl(); };

  void Release() { static_cast<Derived*>(this)->ReleaseImpl(); };
};

class PrimitiveClassicSemaphore {
 public:
  explicit PrimitiveClassicSemaphore(size_t permits = 0) : permits_(permits){};

  void AcquireImpl() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() { return permits_ > 0; });

    --permits_;
  }

  void ReleaseImpl() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++permits_;
    cv_.notify_one();
  }

 private:
  std::mutex mutex_;
  size_t permits_;
  std::condition_variable cv_;
};

class PrimitiveSpinSemaphore : SemaphoreBase<PrimitiveSpinSemaphore> {
 public:
  void AcquireImpl() {
    size_t expected;

    while (true) {
      expected = permits_.load(std::memory_order_seq_cst);
      if (expected && permits_.compare_exchange_weak(
                          expected, expected - 1, std::memory_order_seq_cst)) {
        return;
      }
      std::this_thread::yield();
    }
  };
  void ReleaseImpl() { permits_.fetch_add(1, std::memory_order_seq_cst); };

 private:
  std::atomic<size_t> permits_;
};