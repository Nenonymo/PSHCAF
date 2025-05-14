#include "taskParser.h"
#include "scheduler.h"
#include "S_FCFS.h"
#include "worker.h"

#include <thread>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <n_workers> [verbose]" << std::endl;
        return 1;
    }

    std::string filePath = argv[1]; // Path to the FIFO file
    unsigned int nWorkers = std::stoi(argv[2]); // Number of workers to create
    Verbose verbose(argv[3]); // Pointer to verbosity settings

    TaskParser parser(filePath, &verbose); // Create a FIFO task parser

    Scheduler* scheduler = new S_FCFS(); // Create a scheduler (FCFS in this case)

    //Start worker threads
    Worker** workers = new Worker*[nWorkers];
    for (unsigned int i = 0; i < nWorkers; i++) {
        workers[i] = new Worker(i, scheduler, &verbose); // Create a worker with the scheduler
        workers[i]->start(); // Start the worker thread
    }

    do
    {
        TaskParameters* params = parser.getTask(); // Get task parameters from the FIFO

        if (params == nullptr) {
            if (verbose.debug){std::cout << "Received end signal. Exiting..." << std::endl; }
            break; // Exit if the end signal is received
        }

        Task* task = new Task(params, &verbose); // Create a new task with the parameters
        scheduler->submitTask(task); // Submit the task to the scheduler

    } while (true);

    scheduler->finalize();
    
    if (verbose.debug) {std::cout << "exiting..." << std::endl; }

    //Cleaning up the workers
    for (unsigned int i = 0; i < nWorkers; ++i) {
        //std::cout << "Joining worker " << i << "..." << std::endl;
        workers[i]->join();
        delete workers[i]; // clean up each Worker
        if (verbose.debug) {std::cout << "Worker joined and deleted successfully" << std::endl; }
    }
    delete[] workers; // clean up the array itself


    return 0; // Return 0 to indicate success    

}