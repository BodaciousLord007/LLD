#pragma once

#include "Job.hpp"
#include <iostream>
#include <stdexcept>

class sumRangeJob : public Job {
private:
    int l;
    int r;

public:
    sumRangeJob(int l, int r) : l(l), r(r) {}

    JobResult run() override {
        int ans = 0;
        for (int i = l; i <= r; ++i) {
            ans += i;
        }

        std::cout << "Doing Sum Range:\n";
        std::cout << std::boolalpha << "Status: true, Content: OK, Value: "
                  << ans << '\n';
        return {true, "OK", ans};
    }
};

class primeCountJob : public Job {
private:
    int l;
    int r;

    bool isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i <= x / i; ++i) {
            if (x % i == 0) return false;
        }
        return true;
    }

public:
    primeCountJob(int l, int r) : l(l), r(r) {}

    JobResult run() override {
        int ans = 0;
        for (int i = l; i <= r; ++i) {
            if (isPrime(i)) ++ans;
        }

        std::cout << "Doing Prime Count:\n";
        std::cout << std::boolalpha << "Status: true, Content: OK, Value: "
                  << ans << '\n';
        return {true, "OK", ans};
    }
};

class failingJob : public Job {
public:
    JobResult run() override {
        std::cout << "Running failing job...\n";
        throw std::runtime_error("Simulated job failure");
    }
};
