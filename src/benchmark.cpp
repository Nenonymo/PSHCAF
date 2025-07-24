#include "taskParser.h"
#include "scheduler.h"
#include "S_FCFS.h"
#include "S_LCFS.h"
#include "S_SJF.h"
#include "S_LJF.h"
#include "S_RR.h"
#include "S_LBW.h"
#include "S_WS.h"
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
    std::chrono::duration<double> queuingTime{0}; // Variable to hold the queuing time
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

        case 4: //RR
            scheduler = new S_RR(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: RR" << std::endl; }
            break;

        case 5: //LBW
            scheduler = new S_LBW(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: LBW" << std::endl; }
            break;
            
        case 6: //WS
            scheduler = new S_WS(nWorker);
            if (verbose.debug) {std::cout << "Scheduler: WS" << std::endl; }
            break;

        default:
            std::cerr << "Invalid scheduler ID. Exiting..." << std::endl;
            return 1; // Exit if the scheduler ID is invalid
            break;
    }

    TaskParser parser(filePath, &verbose); // Create a FIFO task parser

    //Start worker threads
    if (verbose.debug) {printf("Starting worker threads\n"); }
    Worker** workers = new Worker*[nWorker];
    for (unsigned int i = 0; i < nWorker; i++) {
        workers[i] = new Worker(i, scheduler, &verbose); // Create a worker with the scheduler
        workers[i]->start(); // Start the worker thread
    }

    if(verbose.debug) {printf("Starting parsing\n"); }
    do
    {
        TaskParameters* params = parser.getTask(); // Get task parameters from the FIFO

        if (params == nullptr) {
            if (verbose.debug){printf("Received end signal.\n"); }
            break; // Exit if the end signal is received
        }
        
        //Scheduling task
        auto t1 = std::chrono::high_resolution_clock::now(); // Start the timer for task enqueuing
        Task* task = new Task(params, &verbose); // Create a new task with the parameters
        scheduler->submitTask(task); // Submit the task to the scheduler
        queuingTime += std::chrono::high_resolution_clock::now() - t1; // Calculate the queuing time

    } while (true);

    scheduler->finalize();
    
    if (verbose.debug) {printf("Starting exit procedure\n"); }

    // Print the queuing time
    if (verbose.ThreadStat) {printf("M0:%f\n", queuingTime.count()); }

    //Cleaning up the workers
    for (unsigned int i = 0; i < nWorker; ++i) {
        //std::cout << "Joining worker " << i << "..." << std::endl;
        workers[i]->join();
        delete workers[i]; // clean up each Worker
        if (verbose.debug) {printf("Worker %u joined and deleted successfully\n", i); }
    }
    delete[] workers; // clean up the array itself


    return 0; // Return 0 to indicate success    

}