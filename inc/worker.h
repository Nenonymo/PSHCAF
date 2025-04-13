#pragma once

#include "scheduler.h"
#include "task.h"

#include <thread>
#include <atomic>
#include <functional>

class Worker
{
    public:
        Worker(int id, Scheduler* scheduler);
        void start();
        void join();

    private:
        int workerId;
        Scheduler* scheduler; // Pointer to the scheduler
        std::thread workerThread; // Thread for the worker

        std::chrono::duration<double> overheadTime{0}; // Overhead time for the worker
        std::chrono::duration<double> taskTime{0}; // Task time for the worker

        void run();
};