#include <iostream>
#include "MyClass.h"

int main() {
    MyClass obj;
    int n = 10; // Example value for the number of elements
    double x = 1.0; // Example value for the argument x
    std::cout << "Result: " << obj.FuncA(n, x) << std::endl;
    return 0;
}