// taskgen.cpp
// Author: Némo Chentre
// Date: 2023-10-01
// Description: Generates a dynamic workload for the benchmark using fed parameters

#include <iostream>
#include <string>
#include <vector>
#include <random>

// Add your function declarations and other necessary includes here

struct FractalTaskParams {
    double zoom;
    int max_iter;
    int resolution;
    int delay;
};

FractalTaskParams generateFractalTaskParams(std::mt19937 &generator, unsigned int time, double variance) {
    // Initialize domain for the fractal parameters
    std::uniform_real_distribution<double> zoom_dist(0.1, 10.0);
    std::uniform_int_distribution<int> max_iter_dist(1000, 10000);
    std::uniform_int_distribution<int> resolution_dist(100, 1000);
    std::uniform_int_distribution<int> delay_dist(0, time);

    // Generate parameters using seeded randomness
    //TODO: The variance need to be added later
    // For now, we will just use the uniform distributions
    FractalTaskParams params;
    params.zoom = zoom_dist(generator);
    params.max_iter = max_iter_dist(generator);
    params.resolution = resolution_dist(generator);
    params.delay = delay_dist(generator);

    return params;
}

void outTask(FractalTaskParams params) {
    // Output the task parameters in a format suitable for the benchmark
    std::cout << params.zoom << " " << params.max_iter << " " << params.resolution << " " << params.delay << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <Size> <Seed> <Time> <Variance>" << std::endl;
        return 1;
    }

    unsigned int size = std::stoi(argv[1]); //Amount of test elements generated
    int seed = std::stoi(argv[2]); //Seed for the random number generator
    unsigned int time = std::stoi(argv[3]); //max delay in ms
    double variance = std::stod(argv[4]);

    std::mt19937 generator(seed); // Mersenne Twister random number generator

    std::cout << "Zoom, Max Iter, Resolution, Delay" << std::endl; // Header for the output
    
    for (unsigned int i = 0; i < size; ++i) {
        FractalTaskParams task = generateFractalTaskParams(generator, time, variance); // Generate task parameters
        outTask(task); // Output the generated task parameters
    }

    return 0;
}