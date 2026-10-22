#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

struct JobResult
{
    bool success;
    std::string message; // e.g. "OK" or "Failed: <reason>"
    int value;           // example numeric output
};
class Job{
public:
    virtual ~Job() = default;
    virtual JobResult run() = 0;
};

class JobQueue
{
private:
    std::mutex m;
    std::queue<std::unique_ptr<Job>> q;
public:
    void push(std::unique_ptr<Job> job){
        std::lock_guard<std::mutex> lk(m);
        q.push(std::move(job));
    };
    std::unique_ptr<Job> tryPop(){
        std::lock_guard<std::mutex> lk(m);
        
        if(q.empty() == true)return nullptr;
        
        auto ans = std::move(q.front());
        q.pop();
        
        return ans;
    }; // returns nullptr if empty
};
