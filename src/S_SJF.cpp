#include "S_SJF.h"

S_SJF::S_SJF (unsigned int nWorker)
    : Scheduler(nWorker)
{}

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

bool S_SJF::hasTasks(unsigned int workerId) const {
    return hasTasks();
}