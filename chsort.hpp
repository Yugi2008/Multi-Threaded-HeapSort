#ifndef CHSORT_HPP
#define CHSORT_HPP

#include <algorithm>
#include <thread>
#include <future>
#include <atomic>
#include <iostream>

#include <vector>
#include <stdexcept>
#include <cmath>

// CHSort class template
template <typename T>
class CHSort {
public:
    explicit CHSort(int max_threads);

    void operator()(T& vec);

    void testSequentialSort(T& vec, int start, int end) {
        sequentialSort(vec, start, end);
    }

private:
    int max_threads; // Max threads to use

    // Sequential heap sort
    void sequentialSort(T& vec, int start, int end);

    // comparing heap sort functions (has Concurrent Heap Sortres)
    void compareSort(T& vec, int start, int end, int current_threads);
};

#include "chsort.tpp"

#endif // CHSORT_HPP
