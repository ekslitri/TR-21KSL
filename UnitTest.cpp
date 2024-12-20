#include <iostream>
#include <cassert>
#include <cmath>
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

int main() {
    testMyClass();
    return 0;
}
