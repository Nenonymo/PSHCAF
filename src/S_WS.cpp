#include "S_WS.h"

S_WS::S_WS(unsigned int nWorker)
    : Scheduler(nWorker)
    , taskDeques(new std::deque<Task*>[nWorker])
{}

S_WS::~S_WS() { //Clean the array of queues
    delete[] taskDeques;
}

Task* S_WS::selectNextTask(int workerId) {
    Task* task = nullptr;
    if (!taskDeques[workerId].empty()) { //Tasks available for own worker
        task = taskDeques[workerId].front();
        taskDeques[workerId].pop_front();
    }
    else {
        unsigned int bd = findBiggestDeque();
        task = taskDeques[bd].back();
        taskDeques[bd].pop_back();
    }
    task->recordDequeueTime();
    return task;
}

void S_WS::enqueueTask(Task* task) {
    unsigned int sd = findSmallestDeque();
    task->recordQueueTime();
    taskDeques[sd].push_back(task);
}

bool S_WS::hasTasks() const {
    for (unsigned int wId = 0; wId < nWorker; wId++) {
        if (!taskDeques[wId].empty())
        {
            return true;
        }
    }
    return false;
}

bool S_WS::hasTasks(unsigned int workerId) const {
    if (taskDeques[workerId].empty())
    {return hasTasks(); }
    return true;
}

unsigned int S_WS::findSmallestDeque() {
    unsigned int sq = 0;
    for (unsigned int i = 1; i < nWorker; i++) {
        if (taskDeques[i].size() < taskDeques[sq].size())
        {sq = i; }
    }
    return sq;
}

unsigned int S_WS::findBiggestDeque() {
    unsigned int bq = 0;
    for (unsigned int i = 0; i < nWorker; i++) {
        if (taskDeques[i].size() > taskDeques[bq].size())
        {bq = i; }
    }
    return bq;
}