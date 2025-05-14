#include "S_LJF.h"

S_LJF::S_LJF (unsigned int nWorker)
    : Scheduler(nWorker)
{}

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

bool S_LJF::hasTasks(unsigned int workerId) const {
    return hasTasks();
}