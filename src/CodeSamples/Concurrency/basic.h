#pragma once

#include <thread>
#include <atomic>
#include <mutex>

#include "fmt/core.h"


void testConcurrancyRaceCondition()
{
    int counter = 0;

    auto incrementer = [&counter]()
    {
        for (int i = 0; i < 10000; i++)
        {
            counter++;
        }
    };

    std::thread t1(incrementer);
    std::thread t2(incrementer);

    t1.join();
    t2.join();

    fmt::println("Counter {}", counter);
}

void testConcurrancyRaceConditionAtomic()
{
    std::atomic<int> counter = 0;

    auto incrementer = [&counter]()
    {
        for (int i = 0; i < 10000; i++)
        {
            counter++;
        }
    };

    std::thread t1(incrementer);
    std::thread t2(incrementer);

    t1.join();
    t2.join();

    fmt::println("Counter {}", counter.load());
}

void testConcurrancyRaceConditionMutex()
{
    std::mutex lock;
    int counter = 0;

    auto incrementer = [&counter, &lock]()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::lock_guard<std::mutex> guard(lock);
            counter++;
        }
    };

    std::thread t1(incrementer);
    std::thread t2(incrementer);

    t1.join();
    t2.join();

    fmt::println("Counter {}", counter);
}