#pragma once

#include "scheduler.h"
#include <deque>

class S_WS : public Scheduler
{
    public:
        S_WS(unsigned int nWorker);
        ~S_WS() override;

    protected:
        Task* selectNextTask(int workerId) override; //Selet next tak, blocking
        void enqueueTask(Task* task) override; //Enqueue a task, waking
        bool hasTasks() const override;
        bool hasTasks(unsigned int nWorker) const override;

    private:
        std::deque<Task*>* taskDeques; //Priority queue to hold tasks
        unsigned int findSmallestDeque();
        unsigned int findBiggestDeque();

    };
