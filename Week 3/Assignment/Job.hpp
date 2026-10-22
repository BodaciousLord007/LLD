#pragma once
#include <string>

struct JobResult
{
    bool success;
    std::string message; // e.g. "OK" or "Failed: <reason>"
    int value;           // example numeric output
};
class Job{
public:
    virtual ~Job() = 0;
    virtual JobResult run() = 0;
};

inline Job::~Job() = default;
