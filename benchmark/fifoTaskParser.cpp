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

    TaskParameters* params = new TaskParameters(); // Create a new TaskParameters object

    // Read parameters from the FIFO file
    if (!(fifoStream >> params->zoom >> params->max_iter >> params->resolution)) {
        delete params; // Clean up if reading fails
        throw std::runtime_error("Failed to read task parameters from FIFO.");
    }

    return params; // Return the populated TaskParameters object
}