#include "taskParser.h"
#include "scheduler.h"
#include "S_FCFS.h"
#include "S_LCFS.h"
#include "S_SJF.h"
#include "S_LJF.h"
#include "S_RR.h"
#include "worker.h"

#include <thread>
#include <vector>

int main(int argc, char** argv) {
    //Read amount of arguments from command line
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <n_workers> <heuristic_ID> [verbose]" << std::endl;
        return 1;
    }

    std::string filePath = argv[1]; // Path to the FIFO file
    unsigned int nWorker = std::stoi(argv[2]); // Number of workers to create
    Verbose verbose(argv[4]); // Pointer to verbosity settings


    //Select Scheduler
    unsigned int scheduler_ID = std::stoi(argv[3]); // Scheduler ID from command line argument
    Scheduler* scheduler = nullptr;
    switch (scheduler_ID)
    {
        case 0: //FCFS
            scheduler = new S_FCFS(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: FCFS" << std::endl; }
            break;

        case 1: //LCFS
            scheduler = new S_LCFS(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: LCFS" << std::endl; }
            break;

        case 2: //SJF
            scheduler = new S_SJF(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: SJF" << std::endl; }
            break;

        case 3: //LJF
            scheduler = new S_LJF(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: LJF" << std::endl; }
            break;

        case 4: //LJF
            scheduler = new S_RR(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: RR" << std::endl; }
            break;
            
        default:
            std::cerr << "Invalid scheduler ID. Exiting..." << std::endl;
            return 1; // Exit if the scheduler ID is invalid
            break;
    }

    TaskParser parser(filePath, &verbose); // Create a FIFO task parser


    //Start worker threads
    Worker** workers = new Worker*[nWorker];
    for (unsigned int i = 0; i < nWorker; i++) {
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
    for (unsigned int i = 0; i < nWorker; ++i) {
        //std::cout << "Joining worker " << i << "..." << std::endl;
        workers[i]->join();
        delete workers[i]; // clean up each Worker
        if (verbose.debug) {std::cout << "Worker joined and deleted successfully" << std::endl; }
    }
    delete[] workers; // clean up the array itself


    return 0; // Return 0 to indicate success    

}