#pragma once

#include <iostream>
#include <chrono>
#include "taskParameters.h"

/**
 * @brief Class representing a task to be executed.
 * @note Does not return any value, but can be used to measure the time taken to execute the task.
 */
class Task {
    private:
        TaskParameters* params;

        std::chrono::duration<double> taskTime{0}; // Task time for the task
        std::chrono::duration<double> queueTime{0}; // Queue time for the task
        std::chrono::high_resolution_clock::time_point startTime; // Start time for the task
        
        void outStatistics();

    public:
        /**
         * @brief Initialize a Task based on the given parameters.run
         * @arg params pointer to the task parameters to use for the task
         * @note The task will take ownership of the parameters and will delete them when done
         */
        Task(TaskParameters* params);

        /**
         * @brief Destroy the Task object
         * @note Deletes the task parameters
         */
        ~Task();

        /**
         * @brief Runs the task
         * @return 0 when done
         */
        unsigned int run();

        double getZoom() const { return params->zoom; }
        int getMaxIter() const { return params->max_iter; }
        int getResolution() const { return params->resolution; }
        unsigned int getTaskId() const { return params->taskId; }

        void recordQueueTime();
        void recordDequeueTime();
};

std::ostream& operator<<(std::ostream& os, const Task& task);