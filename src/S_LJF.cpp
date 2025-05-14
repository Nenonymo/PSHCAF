#include "S_LJF.h"

Task* S_LJF::selectNextTask(int workerId) {
    Task* task = taskPQueue.top();
    taskPQueue.pop();
    task->recordDequeueTime();
    return task;
}

void S_LJF::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskPQueue.push(task);
}

bool S_LJF::hasTasks() const {
    return !taskPQueue.empty();
}