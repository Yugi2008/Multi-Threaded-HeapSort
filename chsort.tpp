#ifndef CHSORT_TPP
#define CHSORT_TPP

// geeks for geeks website helped me in implementing this
// url: https://www.geeksforgeeks.org/cpp-program-for-heap-sort/

template <typename T>
CHSort<T>::CHSort(int max_threads) : max_threads(max_threads) {
    if (max_threads < 0) { // error check,must use a positive numebr of threads
        throw std::invalid_argument("Max threads must be a positive number.");
    }
}


template <typename T>
void CHSort<T>::operator()(T& vec) {
    if (vec.empty()) { // if vector is empty
        return;
    }
    compareSort(vec, 0, vec.size(), max_threads); // comparing the heap sort functions
}

template <typename T>
void CHSort<T>::sequentialSort(T& vec, int start, int end) { // Sequential heap sort (many examples online)
    int size = static_cast<int>(end - start); // size to sort

    // making the heap
    for (int i = size / 2 - 1; i >= 0; --i) { 
        int root = i;
        while (2 * root + 1 < size) { // when the root has a child
            int child = 2 * root + 1;

            // checks if right child and is greater than the left child choose the right child
            if (child + 1 < size && vec[start + child] < vec[start + child + 1]) {
                child++;
            }
            // if the root is smaller than the largest child swap and continue
            if (vec[start + root] < vec[start + child]) {
                std::swap(vec[start + root], vec[start + child]);
                root = child;
            } 
            else {
                break;
            }
        }
    }

    // Extract elements from the heap
    for (int i = size - 1; i > 0; --i) {
        std::swap(vec[start], vec[start + i]);
        int root = 0;
        while (2 * root + 1 < i) {
            int child = 2 * root + 1;
            if (child + 1 < i && vec[start + child] < vec[start + child + 1]) {
                child++;
            }
            if (vec[start + root] < vec[start + child]) {
                std::swap(vec[start + root], vec[start + child]);
                root = child;
            } 
            else {
                break;
            }
        }
    }
}


template <typename T>
void CHSort<T>::compareSort(T& vec, int start, int end, int current_threads) { // Compare the heap sorts
    if (current_threads <= 1 || end - start <= 1) { // if valid start the sequential sort
        sequentialSort(vec, start, end);
        return;
    }

    // Concurrent Heap Sort (implementation format was assisted my AI)

    int mid = start + (end - start) / 2;

    // left half
    auto left_task = std::async(std::launch::async, [this, &vec, start, mid, current_threads]() {
        compareSort(vec, start, mid, current_threads / 2);
    });

    // right half
    auto right_task = std::async(std::launch::async, [this, &vec, mid, end, current_threads]() {
        compareSort(vec, mid, end, current_threads / 2);
    });

    // waiting for complete
    left_task.get();
    right_task.get();

    // merge the halves
    std::inplace_merge(vec.begin() + start, vec.begin() + mid, vec.begin() + end);
}

#endif // CHSORT_TPP
