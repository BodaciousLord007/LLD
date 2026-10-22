#pragma once
#include "Job.hpp"
#include<stdexcept>
class sumRangeJob: public Job{
private:
    int l, r;
public:
    sumRangeJob(int l, int r): l(l), r(r){};
    JobResult run() override{
        int ans = 0;
        for(int i = l; i <= r; i++)ans += i;
        JobResult result{true, "OK", ans};
        return result;
    };
};
class primeCountJob: public Job{
private:
    int l, r;
    bool isPrime(int x){
        if(x < 2)return false;
        for(int i = 2; i < x; i++){
            if(x % i == 0)return false;
        }
        return true;
    }
public:
    primeCountJob(int l, int r): l(l), r(r){};
    JobResult run() override {
        int ans = 0;
        for(int i = l; i <= r; i++){
            if(isPrime(i))ans++;
        }
        JobResult result{true, "OK", ans};
        return result;
    };
};
class failingJob : public Job
{
public:
    JobResult run() override
    {
        throw std::runtime_error("Simulated job failure");
    }
};
