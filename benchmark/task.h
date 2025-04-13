#pragma once

#include "taskParameters.h"

class Task {
    private:
        TaskParameters* params;

    public:
        Task(TaskParameters* params);
        ~Task();

        unsigned int run();
};