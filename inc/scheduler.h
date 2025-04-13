#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

#include "task.h"

class Scheduler
{
    public:
        Scheduler() = default;
        ~Scheduler() = default;

        // public interface for workers to get the next task
        Task* getNextTask(int workerId);

        // public interface for the main thread to add a task to the queue
        void submitTask(Task* task);

        void finalize();

    protected:
        std::mutex mtx;
        std::condition_variable cv;
        bool finalized = false; // flag to indicate if the scheduler is finalized

        // Virtual methods to be overridden by derived classes
        virtual Task* selectNextTask(int workerId) = 0;
        virtual void enqueueTask(Task* task) = 0;
        virtual bool hasTasks() const = 0;
};