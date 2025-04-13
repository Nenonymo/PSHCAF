#include "task.h"


Task::Task(TaskParameters* params) {
    this->params = params;
}

Task::~Task() {
    this->outStatistics(); // Output statistics before destruction
    delete params; // Clean up the allocated memory for params
}

unsigned int Task::run()
{
    startTime = std::chrono::high_resolution_clock::now(); // Start the task timer
    double x0 = -0.5;
    double y0 = 0.0;
    double s = 1.0 / params->zoom;

    for (unsigned int i=0; i<params->resolution; i++) {
        for (unsigned int j=0; j<params->resolution; j++) {
            double cx = x0 + ((i-params->resolution/2.0)-s)/params->resolution;
            double cy = y0 + ((j-params->resolution/2.0)-s)/params->resolution;
            double x = 0.0;
            double y = 0.0;
            double k = 0.0;
            while (x*x + y*y < 4.0 && k < params->max_iter) {
                double xtemp = x*x - y*y + cx;
                y = 2*x*y + cy;
                x = xtemp;
                k++;
            }
        }
    }

    taskTime = std::chrono::high_resolution_clock::now() - startTime; // Calculate task time
    return 0; // Return 0 to indicate success
}


std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "Task Parameters: " << std::endl;
    os << "ID: " << task.getTaskId() << std::endl;
    os << "Zoom: " << task.getZoom() << std::endl;
    os << "Max Iter: " << task.getMaxIter() << std::endl;
    os << "Resolution: " << task.getResolution() << std::endl;
    return os;
}

double getCostEsitmation(TaskParameters* params) {
    // Estimate the cost of the task based on its parameters
    // This is a placeholder function and should be replaced with a proper cost estimation algorithm
    return params->max_iter * params->resolution * params->resolution * (1.0 + std::log10(std::max(params->zoom, 1.0))) / 1e6;
}

void Task::recordQueueTime() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Task::recordDequeueTime() {
    queueTime += std::chrono::high_resolution_clock::now() - startTime;
}

void Task::outStatistics() {
    std::cout << "task;" << params->taskId << ";" << queueTime.count() << ";" << taskTime.count() << std::endl;
}