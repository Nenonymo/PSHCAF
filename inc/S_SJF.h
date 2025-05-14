#pragma once

#include "scheduler.h"
#include <queue>
#include <vector>

class S_SJF : public Scheduler
{
    public:
        S_SJF() = default;
        ~S_SJF() = default;

    protected:
        std::priority_queue<Task*, std::vector<Task*>, MinCostComp> taskPQueue; //Priority queue to hold tasks

        Task* selectNextTask(int workerId) override; //Selet next tak, blocking
        void enqueueTask(Task* task) override; //Enqueue a task, waking
        bool hasTasks() const override;
};
