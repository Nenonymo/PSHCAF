#pragma once

#include "scheduler.h"
#include <queue>

class FCFSScheduler : public Scheduler
{
    public:
        FCFSScheduler() = default;
        ~FCFSScheduler() = default;

    protected:
        std::queue<Task*> taskQueue; // Queue to hold tasks

        Task* selectNextTask(int workerId) override; // Select the next task for the worker
        void enqueueTask(Task* task) override; // Enqueue a task
        bool hasTasks() const override; // Check if there are tasks available
};