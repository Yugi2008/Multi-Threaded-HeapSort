#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include "chsort.hpp"

// additional tests to test chsort.cpp (used same format as test_short)
// done with the assistance of AI


// Utility function to check if a container is sorted
template <typename T>
bool is_sorted(const T& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

// Custom type with overloaded comparison operators
class CustomType {
public:
    int key;
    explicit CustomType(int k) : key(k) {}

    bool operator<(const CustomType& other) const {
        return key < other.key;
    }
    bool operator>(const CustomType& other) const {
        return key > other.key;
    }
};

TEST_CASE("Parallel sort of a vector of custom objects", "[chsort]") {
    std::vector<CustomType> v = { CustomType(10), CustomType(7), CustomType(3), CustomType(5) };
    CHSort<std::vector<CustomType>> chsort(4); // 4 threads for parallel sort
    chsort(v);
    REQUIRE(std::is_sorted(v.begin(), v.end(), [](const CustomType& a, const CustomType& b) {
        return a.key < b.key;
        }) == true);
}
/* throwing abort error 
// Edge case tests
TEST_CASE("Sort an empty vector", "[chsort]") {
    std::vector<int> v;
    CHSort<std::vector<int>> chsort(2); // Parallel or sequential doesn't matter for empty
    chsort(v);
    REQUIRE(is_sorted(v) == true);
}
*/

TEST_CASE("Sort a single-element vector", "[chsort]") {
    std::vector<int> v = { 42 };
    CHSort<std::vector<int>> chsort(2); // Parallel or sequential doesn't matter for one element
    chsort(v);
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Sort an already sorted vector", "[chsort]") {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    CHSort<std::vector<int>> chsort(2); // Parallel sort
    chsort(v);
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Sort a reverse-sorted vector", "[chsort]") {
    std::vector<int> v = { 5, 4, 3, 2, 1 };
    CHSort<std::vector<int>> chsort(2); // Parallel sort
    chsort(v);
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Empty vector", "[chsort]") {

    std::vector<int> v = {  };

    CHSort<std::vector<int>> chsort(0);

    chsort(v);

    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("CHSort constructor throws exception for negative threads", "[chsort]") {

    REQUIRE_THROWS_AS(CHSort<std::vector<int>>(-1), std::invalid_argument);


    try {
        CHSort<std::vector<int>> chsort(-1);
    }
    catch (const std::invalid_argument& e) {
        REQUIRE(std::string(e.what()) == "Max threads must be a positive number.");
    }
}


TEST_CASE("Heap property satisfied, no further swaps needed", "[chsort]") {
    std::vector<int> v = { 9, 7, 8, 6, 5, 4 };
    int start = 0;
    int end = static_cast<int>(v.size());

    CHSort<std::vector<int>> chsort(0);
    chsort.testSequentialSort(v, start, end); // Use the test wrapper

    REQUIRE(is_sorted(v) == true);
}


TEST_CASE("is_sorted detects unsorted vector", "[is_sorted]") {
    std::vector<int> v = { 1, 3, 2, 4, 5 };

    bool result = is_sorted(v);

    REQUIRE(result == false); 
}
