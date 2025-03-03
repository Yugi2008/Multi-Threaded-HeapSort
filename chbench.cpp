#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <tuple>
#include "chsort.hpp"

#include <iomanip>
#include <numeric>
#include <thread>

// results
struct results {
    double min_time;
    double max_time;
    double avg_time;
};

// Generate random input (AI help)
std::vector<int> generate_random_vector(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });
    return vec;
}

// get average times for the sorting functions (had assistance with ai with timing)
template <typename T>
results benchmark_times(T& sorter, const std::vector<int>& input, int iterations) {
    std::vector<int> vec;
    std::vector<double> times;

    for (int i = 0; i < iterations; ++i) {
        vec = input; // reset vector each time

        auto start = std::chrono::high_resolution_clock::now();
        sorter(vec);
        auto end = std::chrono::high_resolution_clock::now();

        double duration = std::chrono::duration<double>(end - start).count();
        times.push_back(duration);
    }

    // Calculating min, max, and avg times
    double min_time = *std::min_element(times.begin(), times.end());
    double max_time = *std::max_element(times.begin(), times.end());
    double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    return { min_time, max_time, avg_time };
}

int main(int argc, char* argv[]) {
    // input sizes 1 to 10^6 increasing by powers of 10
    const std::vector<size_t> input_sizes = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
    const int iterations = 10;

    // hardware concurrency
    const int hardware_threads = std::thread::hardware_concurrency();
    const int max_threads = 2; // set to 4 becasue my computer has 4 cores

    std::cout << "Hardware threads available: " << hardware_threads << "\n";
    std::cout << "Using " << max_threads << " threads for concurrent sort.\n";

    // output file creation
    std::ofstream output("chbench_output.txt");
    if (!output) {
        std::cerr << "Failed to open output file.\n";
        return EXIT_FAILURE;
    }

    // file output format
    output << "Hardware Threads: " << hardware_threads << "\n";
    output << "Max Threads: " << max_threads << "\n\n";
    output << "List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)\n";
    output << "             min     max    average     min     max    average\n";
    output << "---------   -----   -----   -------    -----   -----   -------\n";

    // benchmarking
    for (size_t size : input_sizes) {
       
        std::vector<int> input = generate_random_vector(size);  // random input

        // sequential sort
        CHSort<std::vector<int>> sequential_sorter(0); 
        results sequential_result = benchmark_times(sequential_sorter, input, iterations); // get times

        // concurrent sort
        CHSort<std::vector<int>> concurrent_sorter(max_threads); 
        results concurrent_result = benchmark_times(concurrent_sorter, input, iterations); // get times

        // results display to the file
        output << std::setw(9) << size << "   "
            << std::fixed << std::setprecision(5)
            << sequential_result.min_time << "   "
            << sequential_result.max_time << "   "
            << sequential_result.avg_time << "    "
            << concurrent_result.min_time << "   "
            << concurrent_result.max_time << "   "
            << concurrent_result.avg_time << "\n";

        std::cout << "Size: " << size << " complete!" << "\n";
    }

    
    output.close(); // close output file and display on console 
    std::cout << "Benchmark results are in chbench_output.txt\n";

    return EXIT_SUCCESS;
}
