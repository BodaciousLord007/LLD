#pragma once

#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <utility>

struct JobResult {
    bool success;
    std::string message;
    int value;
};

class Job {
public:
    virtual ~Job() = default;
    virtual JobResult run() = 0;
};

class JobQueue {
private:
    std::mutex m;
    std::queue<std::unique_ptr<Job>> q;

public:
    void push(std::unique_ptr<Job> job) {
        std::lock_guard<std::mutex> lock(m);
        q.push(std::move(job));
    }

    std::unique_ptr<Job> tryPop() {
        std::lock_guard<std::mutex> lock(m);

        if (q.empty()) {
            return nullptr;
        }

        auto job = std::move(q.front());
        q.pop();
        return job;
    }
};
