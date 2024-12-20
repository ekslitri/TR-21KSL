#include <iostream>
#include "MyClass.h"
#include "HTTP_Server.h" // Include the HTTP server header

int main() {
    MyClass obj;
    int n = 10; // Example value for the number of elements
    double x = 1.0; // Example value for the argument x
    std::cout << "Result: " << obj.FuncA(n, x) << std::endl;

    HTTP_Server server; // Create an instance of the HTTP server
    server.start(); // Start the HTTP server

    return 0;
}