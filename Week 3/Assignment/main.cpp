#include <iostream>
#include <thread>
#include "BlockingJobQueue.hpp"
#include "Jobs.hpp"
#include "SingleThreadJobEngine.hpp"
#include <chrono>
#include <utility>
#include <memory>

JobQueue q;

void producer(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2)
        {
            q.push(std::make_unique<sumRangeJob>(100, 200));
        }
        else
        {
            q.push(std::make_unique<primeCountJob>(100, 200));
        }
    }
}

void producer(BlockingJobQueue &queue, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2)
        {
            queue.push(std::make_unique<sumRangeJob>(100, 200));
        }
        else
        {
            queue.push(std::make_unique<primeCountJob>(100, 200));
        }
    }
}

int main()
{
    // Phase 1: Testing
    /*
    SingleThreadJobEngine jbEngine;
    sumRangeJob s(1, 10);
    primeCountJob p(1, 100);
    failingJob f;

    jbEngine.executeNow(s);
    jbEngine.executeNow(p);
    jbEngine.executeNow(f);
    */
    // f.run();

    // Phase 2:Testing
    /*
    std::thread worker(producer, 100);
    worker.detach();

    SingleThreadJobEngine engine;
    for(int i = 0; i < 100; i++){
        while(1){
            auto j = q.tryPop();
            if(j == nullptr){
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            else{
                engine.executeNow(*j);
                break;
            }
        }
    }
    */
    // Phase 3 Testing

    BlockingJobQueue queue;
    constexpr int jobsPerProducer = 5;

    auto produceJobs = [&queue](int count)
    {
        for (int i = 0; i < count; ++i)
        {
            if (i % 2 == 0)
            {
                queue.push(std::make_unique<primeCountJob>(100, 200));
            }
            else
            {
                queue.push(std::make_unique<sumRangeJob>(100, 200));
            }
        }
    };

    std::thread consumer([&queue]
                         {
        while (auto job = queue.pop()) {
            JobResult result = job->run();
            std::cout << "Consumer result: "
                      << (result.success ? "success" : "failure")
                      << ", " << result.message
                      << ", value = " << result.value << '\n';
        }

        std::cout << "Consumer exiting: queue is shut down and empty.\n"; });

    std::thread producer1(produceJobs, jobsPerProducer);
    std::thread producer2(produceJobs, jobsPerProducer);

    producer1.join();
    producer2.join();

    queue.shutdown();
    consumer.join();
    return 0;
}
