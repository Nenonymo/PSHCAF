#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>


int main(int argc, char** argv) {
    //Check arguments count
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <fifo_path>" << std::endl;
        return 1;
    }

    const std::string inputFilePath = argv[1];
    const std::string fifoPath = argv[2];

    //Init input and output streams
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open input file: " << inputFilePath << std::endl;
        return 1;
    }
    std::ofstream fifoStream(fifoPath);
    if (!fifoStream.is_open()) {
        std::cerr << "Error: Cannot open FIFO: " << fifoPath << std::endl;
        return 1;
    }

    // Read the input file line by line
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line == "END") {
            fifoStream << "END" << std::endl;
            fifoStream.flush();
            break;
        }

        std::istringstream iss(line);

        // Extract the delay value
        unsigned int delayMs;
        iss >> delayMs;
        if (iss.fail()) {
            std::cerr << "Warning: Failed to parse delay on line: " << line << std::endl;
            continue;
        }

        // Extract the rest of the line
        std::string taskData;
        std::getline(iss, taskData);
        if (taskData.empty()) {
            std::cerr << "Warning: No task data after delay on line: " << line << std::endl;
            continue;
        }

        // Trim leading space
        taskData.erase(0, taskData.find_first_not_of(" \t"));

        // Wait for the delay
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

        // Send task to FIFO
        fifoStream << taskData << std::endl;
        fifoStream.flush();
    }

    fifoStream.close();
    inputFile.close();

    std::cout << "Injection completed." << std::endl;
    return 0;
}