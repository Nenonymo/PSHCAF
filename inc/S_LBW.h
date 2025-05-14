#pragma once

#include "scheduler.h"
#include <queue>

struct TaskQueue
{
    double cost = 0.0f;
    std::queue<Task*> tasks;
} typedef TaskQueue;

class S_LBW : public Scheduler
{
    public:
        S_LBW(unsigned int nWorker);
        ~S_LBW() override;

    protected:
        Task* selectNextTask(int workerId) override; //Selet next tak, blocking
        void enqueueTask(Task* task) override; //Enqueue a task, waking
        bool hasTasks() const override;
        bool hasTasks(unsigned int nWorker) const override;

    private:
        TaskQueue* taskQueues;
};
