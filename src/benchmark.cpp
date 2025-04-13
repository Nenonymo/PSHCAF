#include "task.h"
#include "fifoTaskParser.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <fifo_path>" << std::endl;
        return 1;
    }

    std::string fifoPath = argv[1]; // Path to the FIFO file
    FifoTaskParser parser(fifoPath); // Create a FIFO task parser


    do
    {
        TaskParameters* params = parser.getTask(); // Get task parameters from the FIFO

        if (params == nullptr) {
            std::cout << "Received end signal. Exiting..." << std::endl;
            break; // Exit if the end signal is received
        }

        //start overhead timer
        Task task(params); // Create a new task with the parameters
        std::cout << task << std::endl; // Print the task parameters
        //task.run(); // Run the task
        //end overhead timer
        
    } while (true);
    
    std::cout << "exiting..." << std::endl;


    return 0; // Return 0 to indicate success    

}