#pragma once

#include <cstring>

class Verbose {
    public:
        // Program verbosity settings
        bool debug;

        //Thread verbosity settings
        bool ThreadStat;

        //Task verbosity settings
        bool TaskId;
        bool TaskWorkerID;
        bool TaskTime;
        bool TaskQueue;
        bool TaskCost;

        Verbose(char* arg);
};
