#pragma once

#include "scheduler.h"
#include <stack>

class S_LCFS: public Scheduler
{
    public:
        S_LCFS() = default;
        ~S_LCFS() = default;

    protected:
        std::stack<Task*> taskStack; // Queue to hold tasks

        Task* selectNextTask(int workerId) override; // Select the next task for the worker
        void enqueueTask(Task* task) override; // Enqueue a task
        bool hasTasks() const override; // Check if there are tasks available
};