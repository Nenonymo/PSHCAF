#include "taskParser.h"

struct nbsp_ctype : std::ctype<char> {
    using base = std::ctype<char>;
    std::vector<mask> table_;
    nbsp_ctype() : base(get_table()) {}
    static const mask* get_table() {
        static std::vector<mask> v(table_size, mask());
        static bool init = []{
            // Start from classic table
            for (std::size_t i=0;i<table_size;++i) v[i] = std::ctype<char>::classic_table()[i];
            // Mark NBSP byte (0xA0) as space in Latin-1 single-byte encodings
            v[0xA0] |= space;
            return true;
        }();
        (void)init;
        return &v[0];
    }
};


TaskParser::TaskParser(const std::string& filePath, Verbose* verbose) {
    this->verbose = verbose; // Initialize the verbosity settings
    fileStream.open(filePath, std::ios::in); // Open the file to read
    if (!fileStream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    loc = std::locale(std::locale::classic(), new nbsp_ctype());

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
    line.erase(line.find_last_not_of(" \t\r\n") + 1);    // right-trim

    if(line == "END") {
        return nullptr; // Return nullptr if the end of the stream is reached
    }
    
    std::istringstream iss(line); // Create a stream from the line read from the file
    iss.imbue(loc); // Ensure '.' is treated as decimal separator
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