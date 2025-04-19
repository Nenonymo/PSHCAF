#include "worker.h"

#include <iostream>
#include <chrono>

Worker::Worker(int id, Scheduler* scheduler, Verbose* verbose)
{
    workerId = id; // Initialize the worker ID
    this->scheduler = scheduler; // Initialize the scheduler pointer
    this->verbose = verbose; // Initialize the verbosity settings
}

void Worker::start()
{
    workerThread = std::thread(&Worker::run, this); // Start the worker thread
}

void Worker::join()
{
    if (workerThread.joinable())
    {
        workerThread.join(); // Wait for the worker thread to finish
    }
}

void Worker::run()
{
    while (true)
    {
        auto t1 = std::chrono::high_resolution_clock::now(); // Start overhead timer
        Task* task = scheduler->getNextTask(workerId); // Get the next task from the scheduler
        overheadTime += std::chrono::high_resolution_clock::now() - t1; // Calculate overhead time


        if (!task) //Scheduler finalized
        {
            break;
        }
        t1 = std::chrono::high_resolution_clock::now(); // Start task timer
        task->run(); // Run the task
        delete task; // Delete the task after running it
        taskTime += std::chrono::high_resolution_clock::now() - t1; // Calculate task time
    }
}