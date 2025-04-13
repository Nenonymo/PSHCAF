#pragma once

#include "taskParameters.h"

/**
 * @brief Class representing a task to be executed.
 * @note Does not return any value, but can be used to measure the time taken to execute the task.
 */
class Task {
    private:
        TaskParameters* params;

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
};