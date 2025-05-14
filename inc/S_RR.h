#pragma once

#include "scheduler.h"
#include <queue>

class S_RR : public Scheduler
{
    public:
        S_RR(unsigned int nWorker);
        ~S_RR() override;

    protected:
        Task* selectNextTask(int workerId) override; //Selet next tak, blocking
        void enqueueTask(Task* task) override; //Enqueue a task, waking
        bool hasTasks() const override;
        bool hasTasks(unsigned int nWorker) const override;

    private:
        std::queue<Task*>* taskQueues; //Priority queue to hold tasks
        unsigned int nextWorker;
        void incrementWorker();
};
