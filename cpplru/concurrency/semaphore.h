#pragma once
#include <condition_variable>
#include <mutex>

class PrimitiveSemaphore
{
 public:
  explicit PrimitiveSemaphore(size_t permits = 0) : permits_(permits){};

  void Acquire()
  {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() { return permits_ > 0; });

    --permits_;
  }

  void Release()
  {
    std::unique_lock<std::mutex> lock(mutex_);
    ++permits_;
    cv_.notify_one();
  }

 private:
  std::mutex mutex_;
  size_t permits_;
  std::condition_variable cv_;
};