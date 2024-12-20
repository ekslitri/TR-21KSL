#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "MyClass.h"

void testMyClass() {
    MyClass obj;
    double expectedValue = 1.54308; // Example expected value
    double result = obj.FuncA(10, 1.0); // Assuming FuncA is the method to test
    double tolerance = 1e-5; // Tolerance for floating-point comparison
    std::cout << "Expected: " << expectedValue << ", Result: " << result << std::endl;
    assert(std::fabs(result - expectedValue) < tolerance);
    std::cout << "All tests passed!" << std::endl;
}

void testPerformance() {
    MyClass obj;
    std::vector<int> aValues;
    std::mt19937 mtre{123};
    std::uniform_int_distribution<int> distr{0, 2000000};

    for (int i = 0; i < 2000000; i++) {
        aValues.push_back(distr(mtre));
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 30; i++) {
        for (auto& val : aValues) {
            val = obj.FuncA(10, val);
        }
        std::sort(aValues.begin(), aValues.end());
        std::reverse(aValues.begin(), aValues.end());
    }

    std::sort(aValues.begin(), aValues.end()); // Sort in ascending order after calculations

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Performance test duration: " << duration << " ms" << std::endl;
}

int main() {
    testMyClass();
    testPerformance();
    return 0;
}
