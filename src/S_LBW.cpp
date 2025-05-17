#include "S_LBW.h"

TaskQueue* leastBusyQueue(TaskQueue* taskQueues, unsigned int nWorker) {
    unsigned int lbq = 0;
    for (unsigned int i = 1; i < nWorker; i++) {
        if (taskQueues[i].cost < taskQueues[lbq].cost) {
            lbq = i;
        }
    }
    return &(taskQueues[lbq]);
}

S_LBW::S_LBW(unsigned int nWorker)
    : Scheduler(nWorker)
{
    taskQueues = new TaskQueue[nWorker];
}

S_LBW::~S_LBW() { //Clean the array of queues
    delete[] taskQueues;
}

Task* S_LBW::selectNextTask(int workerId) {
    Task* task = taskQueues[workerId].tasks.front();
    taskQueues[workerId].tasks.pop();
    taskQueues[workerId].cost = taskQueues[workerId].cost - task->getCostEstimation();
    task->recordDequeueTime();
    return task;
}

void S_LBW::enqueueTask(Task* task) {
    task->recordQueueTime();
    TaskQueue* lbq = leastBusyQueue(taskQueues, nWorker);
    lbq->cost = lbq->cost + task->getCostEstimation();
    lbq->tasks.push(task);
}

bool S_LBW::hasTasks() const {
    for (unsigned int wId = 0; wId < nWorker; wId++) {
        if (!taskQueues[wId].tasks.empty())
        {
            return true;
        }
    }
    return false;
}

bool S_LBW::hasTasks(unsigned int workerId) const {
    return !taskQueues[workerId].tasks.empty();
}