#include "S_FCFS.h"

S_FCFS::S_FCFS (unsigned int nWorker)
    : Scheduler(nWorker)
{}

Task* S_FCFS::selectNextTask(int workerId) {
    Task* task = taskQueue.front(); // Get the front task from the queue
    taskQueue.pop(); // Remove the task from the queue
    task->recordDequeueTime();
    return task; // Return the selected task
}

void S_FCFS::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskQueue.push(task); // Add the task to the queue
}

bool S_FCFS::hasTasks() const {
    return !taskQueue.empty(); // Check if the queue is not empty
}

bool S_FCFS::hasTasks(unsigned int workerId) const {
    return hasTasks();
}
