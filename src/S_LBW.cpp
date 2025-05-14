#include "S_RR.h"

S_RR::S_RR(unsigned int nWorker)
    : Scheduler(nWorker)
    , taskQueues(new std::queue<Task*>[nWorker])
    , nextWorker(0) 
{}

S_RR::~S_RR() { //Clean the array of queues
    delete[] taskQueues;
}

Task* S_RR::selectNextTask(int workerId) {
    Task* task = taskQueues[workerId].front();
    taskQueues[workerId].pop();
    task->recordDequeueTime();
    return task;
}

void S_RR::enqueueTask(Task* task) {
    task->recordQueueTime();
    taskQueues[nextWorker].push(task);
    incrementWorker();
}

bool S_RR::hasTasks() const {
    for (unsigned int wId = 0; wId < nWorker; wId++) {
        if (!taskQueues[wId].empty())
        {
            return true;
        }
    }
    return false;
}

bool S_RR::hasTasks(unsigned int workerId) const {
    return !taskQueues[workerId].empty();
}

void S_RR::incrementWorker() {
    nextWorker = (nextWorker+1) % nWorker;
}