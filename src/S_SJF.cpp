#include "S_SJF.h"

Task* S_SJF::selectNextTask(int workerId) {
    Task* task = taskPQueue.top();
    taskPQueue.pop();
    task->recordDequeueTime();
    return task;
}

void S_SJF::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskPQueue.push(task);
}

bool S_SJF::hasTasks() const {
    return !taskPQueue.empty();
}