#include <iostream>
#include <cassert>
#include "MyClass.h"

void testMyClass() {
    MyClass obj;
    assert(obj.someMethod() == expectedValue);
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testMyClass();
    return 0;
}
