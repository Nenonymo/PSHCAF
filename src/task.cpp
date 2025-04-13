#include "task.h"


Task::Task(TaskParameters* params) {
    this->params = params;
}

Task::~Task() {
    delete params; // Clean up the allocated memory for params
}

unsigned int Task::run()
{
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