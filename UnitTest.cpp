#include <iostream>
#include <cassert>
#include "MyClass.h"

void testMyClass() {
    MyClass obj;
    int expectedValue = 42; // Example expected value
    assert(obj.FuncA(10, 1.0) == expectedValue); // Assuming FuncA is the method to test
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testMyClass();
    return 0;
}
