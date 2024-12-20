#include <iostream>
#include <cassert>
#include "MyClass.h"

void testMyClass() {
    MyClass obj;
    double expectedValue = 1.54308; // Example expected value
    double result = obj.FuncA(10, 1.0); // Assuming FuncA is the method to test
    std::cout << "Result: " << result << std::endl;
    assert(result == expectedValue);
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testMyClass();
    return 0;
}
