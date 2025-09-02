#include <scheduler.h>

/************************
 * MAIN CLASS INTERFACE *
 ************************/

Scheduler::Scheduler(unsigned int nWorker) 
    : nWorker(nWorker) {}

Task* Scheduler::getNextTask(unsigned int workerId) {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex for thread safety

    // Wait until there are tasks available or the scheduler is finalized
    cv.wait(lock, [&] { return hasTasks(workerId) || (finalized && !hasTasks(workerId)); });

    if (finalized && !hasTasks(workerId)) {
        return nullptr; // Return nullptr if the scheduler is finalized or has no more tasks
    }

    return selectNextTask(workerId); // Select the next task for the worker
}

void Scheduler::submitTask(Task* task) {
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex for thread safety
        enqueueTask(task); // Enqueue the task
    }
    cv.notify_one(); // Notify one waiting thread that a task is available
}

void Scheduler::finalize() {
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex for thread safety
    finalized = true; // Set the finalized flag to true
    cv.notify_all(); // Notify all waiting threads that the scheduler is finalized
}