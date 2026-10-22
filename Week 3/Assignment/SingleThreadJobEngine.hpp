#pragma once

#include "Job.hpp"
class SingleThreadJobEngine
{
public:
    JobResult executeNow(Job& job){
        return job.run();
    }
};