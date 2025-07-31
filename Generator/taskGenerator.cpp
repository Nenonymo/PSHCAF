// taskgen.cpp
// Author: Nemo Chentre
// Date: 2023-13-01
// Description: Generates a dynamic workload for the benchmark using fed parameters

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>


#define MIN_ZOOM 0.01
#define MAX_ZOOM 12.0
#define MIN_MAX_ITER 500
#define MAX_MAX_ITER 2000
#define MIN_RESOLUTION 200
#define MAX_RESOLUTION 700
#define MIN_DELAY 0
#define MAX_DELAY 275

// Add your function declarations and other necessary includes here

struct FractalTaskParams {
    double zoom;
    int max_iter;
    int resolution;
    int delay;
};

int sampleControlled(int min, int max, double variance, std::mt19937 &generator) {
    int median = (min + max) / 2;
    // Edge cases
    if (variance <= 0.0) return median;
    if (variance >= 1.0) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(generator); // Uniform distribution for high variance
    }

    int maxDeviation = std::max(median-min, max-median); //worst case deviation
    double stddev = maxDeviation * variance; //standard deviation

    std::normal_distribution<> dist(median, stddev); // Normal distribution centered around the median
    int val = static_cast<int>(dist(generator)); // Sample from the distribution

    return std::clamp(val, min, max); // Ensure the value is within the bounds
}

double sampleControlled(double min, double max, double variance, std::mt19937 &generator) {
    double median = (min + max) / 2;
    // Edge cases
    if (variance <= 0.0) return median;
    if (variance >= 1.0) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(generator); // Uniform distribution for high variance
    }

    double maxDeviation = std::max(median-min, max-median); //worst case deviation
    double stddev = maxDeviation * variance; //standard deviation

    std::normal_distribution<double> dist(median, stddev); // Normal distribution centered around the median
    double val = dist(generator); // Sample from the distribution

    return std::clamp(val, min, max); // Ensure the value is within the bounds
}

FractalTaskParams generateFractalTaskParams(std::mt19937 &generator, double variance, bool backlog = false) {
    // Generate parameters using seeded randomness
    FractalTaskParams params;
    params.zoom = sampleControlled(MIN_ZOOM, MAX_ZOOM, variance, generator);
    params.max_iter = sampleControlled(MIN_MAX_ITER, MAX_MAX_ITER, variance, generator);
    params.resolution = sampleControlled(MIN_RESOLUTION, MAX_RESOLUTION, variance, generator);
    if (backlog) {
        // If backlog is true, set a fixed delay
        params.delay = 0; // No delay for backlog tasks
    } else {
        // Otherwise, sample a delay based on the variance
        params.delay = sampleControlled(MIN_DELAY, MAX_DELAY, variance, generator);
    }

    return params;
}

double estimateCost(FractalTaskParams params) {
    // Estimate the cost of the task based on its parameters
    // This is a placeholder function and should be replaced with a proper cost estimation algorithm
    return params.max_iter * params.resolution * params.resolution * (1.0 + std::log10(std::max(params.zoom, 1.0))) / 1e6;
}

void outTask(FractalTaskParams params) {
    // Output the task parameters in a format suitable for the benchmark
    std::cout << params.delay << " " << params.zoom << " " << params.max_iter << " " << params.resolution << " " << estimateCost(params) << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <Size> <Seed> <Variance> [backlog]" << std::endl;
        return 1;
    }
    

    unsigned int size = std::stoi(argv[1]); //Amount of test elements generated
    int seed = std::stoi(argv[2]); //Seed for the random number generator
    double variance = std::stod(argv[3]);
    unsigned int backlog = 0; // Default backlog value
    if (argc > 4) {backlog = std::stoi(argv[4]); }

    std::mt19937 generator(seed); // Mersenne Twister random number generator

    std::cout << "Delay, Zoom, Max Iter, Resolution, Estimated cost" << std::endl; // Header for the output
    
    for (unsigned int i = 0; i < size; ++i) {
        FractalTaskParams task = generateFractalTaskParams(generator, variance, i < backlog); // Generate task parameters
        outTask(task); // Output the generated task parameters
    }

    std::cout << "END" << std::endl; // Signal the end of the task generation

    return 0;
}