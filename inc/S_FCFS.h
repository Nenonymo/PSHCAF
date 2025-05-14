#pragma once

#include "scheduler.h"
#include <queue>

class S_FCFS : public Scheduler
{
    public:
        S_FCFS(unsigned int nWorker);
        ~S_FCFS() = default;

    protected:
        std::queue<Task*> taskQueue; // Queue to hold tasks

        Task* selectNextTask(int workerId) override; // Select the next task for the worker
        void enqueueTask(Task* task) override; // Enqueue a task
        bool hasTasks() const override; // Check if there are tasks available
        bool hasTasks(unsigned int workerId) const override;
};