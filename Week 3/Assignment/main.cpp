#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "Jobs.hpp"
#include "SingleThreadJobEngine.hpp"

void producer(JobQueue& queue, int jobCount) {
    for (int i = 0; i < jobCount; ++i) {
        if (i % 2 == 0) {
            queue.push(std::make_unique<primeCountJob>(100, 200));
        } else {
            queue.push(std::make_unique<sumRangeJob>(100, 200));
        }
    }
}

int main() {
    constexpr int jobCount = 100;
    JobQueue queue;
    SingleThreadJobEngine engine;

    // Phase 1: Test jobs directly through the single-threaded engine.
    sumRangeJob sumTest(1, 10);
    primeCountJob primeTest(1, 100);
    failingJob failureTest;

    engine.executeNow(sumTest);
    engine.executeNow(primeTest);
    try {
        engine.executeNow(failureTest);
    } catch (const std::exception& error) {
        std::cout << "Expected job failure: " << error.what() << '\n';
    }

    // Phase 2: Consume jobs from the mutex-protected shared queue.
    std::thread producerThread(producer, std::ref(queue), jobCount);

    int completed = 0;
    while (completed < jobCount) {
        std::unique_ptr<Job> job = queue.tryPop();
        if (!job) {
            // This phase polls the queue; a later condition-variable version
            // can wake the consumer without periodic checking.
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        JobResult result = engine.executeNow(*job);
        std::cout << "Completed job " << completed + 1 << ": "
                  << result.message << ", value = " << result.value << '\n';
        ++completed;
    }

    producerThread.join();
    return 0;
}
