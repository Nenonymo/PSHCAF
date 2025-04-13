#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "taskParameters.h"

class TaskParser {
    private:
        std::ifstream fileStream; // Stream for reading from the file
        unsigned int taskCounter = 0;

        void close();

    public: 
        /**
         * @brief Construct a new Task Parser with the intent to read task parameters from a file.
         * @throws std::runtime_error if the file cannot be opened
         * @param filePath path to the file to use as input
         */
        TaskParser(const std::string& filePath);

        /**
         * @brief Destroy the Task Parser:: Task Parser object
         */
        ~TaskParser();

        /**
         * @brief Read a task from the file and return the parameters.
         * @return TaskParameters* pointer to the task parameters read from the file, null if received end signal
         * @throws std::runtime_error if reading from the file fails
         */
        TaskParameters* getTask(); // Method to read a task from the file
   
};