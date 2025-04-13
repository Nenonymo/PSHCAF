#include "FCFSScheduler.h"

Task* FCFSScheduler::selectNextTask(int workerId) {
    Task* task = taskQueue.front(); // Get the front task from the queue
    taskQueue.pop(); // Remove the task from the queue
    task->recordDequeueTime();
    return task; // Return the selected task
}

void FCFSScheduler::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskQueue.push(task); // Add the task to the queue
}

bool FCFSScheduler::hasTasks() const {
    return !taskQueue.empty(); // Check if the queue is not empty
}

