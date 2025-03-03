// ------------------------------------------------
// You should not need to edit any files below here
// ------------------------------------------------

#include "catch.hpp"

#include <string>
#include <sstream>

#include "chsort.hpp"

template <typename T>
bool is_sorted(const T &vec) {
    for (auto i = 1; i < vec.size(); ++i) {
        if (vec[i-1] > vec[i]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Sequential sort of a vector of integers", "[chsort]") {
    // Test vector
    std::vector<int> v = {2, 4, 1, 3};

    // CHSort for an int vector with zero additional threads (sequential)
    CHSort<std::vector<int>> chsort(0);

    // Sort
    chsort(v);

    // Test
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Sequential sort of a vector of strings", "[chsort]") {
    // Test vector
    std::vector<std::string> v = {"d", "a", "c", "b"};

    // CHSort for a string vector with zero additional threads (sequential)
    CHSort<std::vector<std::string>> chsort(0);

    // Sort
    chsort(v);

    // Test
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Parallel sort of a vector of integers", "[chsort]") {
    // Test vector
    std::vector<int> v = {2, 4, 1, 3};

    // CHSort for an int vector with two additional threads (parallel)
    CHSort<std::vector<int>> chsort(2);

    // Sort
    chsort(v);

    // Test
    REQUIRE(is_sorted(v) == true);
}

TEST_CASE("Parallel sort of a vector of strings", "[chsort]") {
    // Test vector
    std::vector<std::string> v = {"d", "a", "c", "b"};

    // CHSort for a string vector with two additional threads (parallel)
    CHSort<std::vector<std::string>> chsort(2);

    // Sort
    chsort(v);

    // Test
    REQUIRE(is_sorted(v) == true);
}
