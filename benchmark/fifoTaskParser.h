#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "taskParameters.h"

class FifoTaskParser {
    private:
        std::ifstream fifoStream; // Stream for reading from the FIFO file

        void close();

    public: 
        /**
         * @brief Construct a new Fifo Task Parser with the intent to read task parameters from a FIFO file.
         * @throws std::runtime_error if the FIFO file cannot be opened
         * @param fifoPath path to the fifo file to use as input
         */
        FifoTaskParser(const std::string& fifoPath);

        /**
         * @brief Destroy the Fifo Task Parser:: Fifo Task Parser object
         */
        ~FifoTaskParser();

        /**
         * @brief Read a task from the FIFO file and return the parameters.
         * @return TaskParameters* pointer to the task parameters read from the FIFO
         * @throws std::runtime_error if reading from the FIFO fails
         */
        TaskParameters* getTask(); // Method to read a task from the FIFO
   
};