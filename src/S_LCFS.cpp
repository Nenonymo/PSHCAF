#include "S_LCFS.h"

Task* S_LCFS::selectNextTask(int workerId) {
    Task* task = taskStack.top(); // Get the front task from the queue
    taskStack.pop(); // Remove the task from the queue
    task->recordDequeueTime();
    return task; // Return the selected task
}

void S_LCFS::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskStack.push(task); // Add the task to the queue
}

bool S_LCFS::hasTasks() const {
    return !taskStack.empty(); // Check if the queue is not empty
}

