#include "taskParser.h"


TaskParser::TaskParser(const std::string& filePath, Verbose* verbose) {
    this->verbose = verbose; // Initialize the verbosity settings
    fileStream.open(filePath, std::ios::in); // Open the file to read
    if (!fileStream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::string dummy;
    std::getline(fileStream, dummy);
}


TaskParser::~TaskParser() {
    close(); // Ensure the file is closed when the parser is destroyed
}

void TaskParser::close() {
    if (fileStream.is_open()) {
        fileStream.close(); // Close the file stream
    }
}

TaskParameters* TaskParser::getTask() {
    if (!fileStream.is_open()) {
        throw std::runtime_error("file stream is not open.");
    }

    std::string line;
    if (!std::getline(fileStream, line)) {
        throw std::runtime_error("Failed to read from file.");
    }

    // Trim leading and trailing non-printable chars (including BOM)
    line.erase(0, line.find_first_not_of(" \t\r\n\xEF\xBB\xBF")); // left-trim
    line.erase(line.find_last_not_of(" \t\r\n") + 1);              // right-trim

    if(line == "END") {
        return nullptr; // Return nullptr if the end of the stream is reached
    }
    
    std::istringstream iss(line); // Create a stream from the line read from the file
    int delay;
    TaskParameters* params = new TaskParameters(); // Create a new TaskParameters object

    // Read parameters from the file file
    if (!(iss >> delay >> params->zoom >> params->max_iter >> params->resolution)) {
        std::cerr << "Parsing failed on line: " << line << std::endl;
        std::cerr << "Stream state - failbit: " << iss.fail() << ", badbit: " << iss.bad() << std::endl;
        delete params; // Clean up if reading fails
        throw std::runtime_error("Failed to read task parameters from file.");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // Simulate delay

    params->taskId = taskCounter; // Assign a unique task ID
    taskCounter++; //increment counter for the next task

    return params; // Return the populated TaskParameters object
}