#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

#include "task.h"

class Scheduler
{
    public:
        Scheduler(unsigned int nWorker);
        virtual ~Scheduler() = default;

        // public interface for workers to get the next task
        Task* getNextTask(unsigned int workerId);

        // public interface for the main thread to add a task to the queue
        void submitTask(Task* task);

        void finalize();

    protected:
        const unsigned int nWorker;
        std::mutex mtx;
        std::condition_variable cv;
        bool finalized = false; // flag to indicate if the scheduler is finalized

        // Virtual methods to be overridden by derived classes
        virtual Task* selectNextTask(int workerId) = 0;
        virtual void enqueueTask(Task* task) = 0;
        virtual bool hasTasks() const = 0;
        virtual bool hasTasks(unsigned int workerId) const = 0;
};