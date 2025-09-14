//
// Created by Isai GORDEEV on 06/08/2025.
//

#include "concurrency/mutex.h" // Adjust path if needed
#include <atomic>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

TEST(MutexTest, LockUnlockSingleThread)
{
    Mutex mtx;

    EXPECT_NO_THROW({
        mtx.Lock();
        mtx.Unlock();
    });
}

TEST(MutexTest, LockUnlockWithStdLockGuard)
{
    Mutex mtx;

    EXPECT_NO_THROW({
        std::lock_guard<Mutex> guard(mtx);
        // Mutex should be locked here
    });
    // Mutex should be unlocked here
}

TEST(MutexTest, MutexEnsuresMutualExclusion)
{
    Mutex mtx;
    int shared_counter = 0;

    auto worker = [&]() {
        for (int i = 0; i < 10000; ++i) {
            std::lock_guard<Mutex> lock(mtx);
            ++shared_counter;
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    EXPECT_EQ(shared_counter, 20000);
}

TEST(MutexTest, ContentionTest)
{
    Mutex mtx;
    std::atomic<int> active_threads{0};
    const int num_threads = 10;
    const int iterations = 1000;

    auto worker = [&]() {
        for (int i = 0; i < iterations; ++i) {
            mtx.Lock();
            int before = active_threads.fetch_add(1);
            EXPECT_EQ(before, 0)
                    << "More than one thread inside critical section!";
            std::this_thread::sleep_for(
                    std::chrono::microseconds(1)); // Simulate work
            active_threads.store(0);
            mtx.Unlock();
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker);
    }

    for (auto& t : threads) {
        t.join();
    }
}