#include "FifoTaskParser.h"


FifoTaskParser::FifoTaskParser(const std::string& fifoPath) {
    fifoStream.open(fifoPath, std::ios::in); // Open the FIFO for reading
    if (!fifoStream.is_open()) {
        throw std::runtime_error("Failed to open FIFO: " + fifoPath);
    }
}


FifoTaskParser::~FifoTaskParser() {
    close(); // Ensure the FIFO is closed when the parser is destroyed
}

void FifoTaskParser::close() {
    if (fifoStream.is_open()) {
        fifoStream.close(); // Close the FIFO stream
    }
}

TaskParameters* FifoTaskParser::getTask() {
    if (!fifoStream.is_open()) {
        throw std::runtime_error("FIFO stream is not open.");
    }

    std::string line;
    if (!std::getline(fifoStream, line)) {
        throw std::runtime_error("Failed to read from FIFO.");
    }

    if(line == "END") {
        return nullptr; // Return nullptr if the end of the stream is reached
    }
    
    std::istringstream iss(line); // Create a stream from the line read from the FIFO
    TaskParameters* params = new TaskParameters(); // Create a new TaskParameters object

    // Read parameters from the FIFO file
    if (!(iss >> params->zoom >> params->max_iter >> params->resolution)) {
        delete params; // Clean up if reading fails
        throw std::runtime_error("Failed to read task parameters from FIFO.");
    }

    params->taskId = taskCounter; // Assign a unique task ID
    taskCounter++; //increment counter for the next task

    return params; // Return the populated TaskParameters object
}