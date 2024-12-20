#include <iostream>
#include <sys/wait.h>
#include "MyClass.h"
#include "HTTP_Server.h" // Include the HTTP server header

void sigchldHandler(int s) {
    printf("SIGCHLD received\n");
    pid_t pid;
    int status;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0);
    {
        if (WIFEXITED(status)) {
            printf("Child %d terminated with status: %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child %d terminated abnormally\n", pid);
        }
    }
}

void siginHandler(int s) {
    printf("Caught signal %d\n", s);
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, 0)) > 0);
    {
        if (WIFEXITED(status)) {
            printf("Child %d terminated with status: %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child %d terminated abnormally\n", pid);
        }
        if (pid == -1) {
            printf("No more child processes\n");
        }
    }
}

int main() {
        
    signal(SIGCHLD, sigchldHandler);
    signal(SIGINT, siginHandler);
    
    MyClass obj;
    int n = 10; // Example value for the number of elements
    double x = 1.0; // Example value for the argument x
    std::cout << "Result: " << obj.FuncA(n, x) << std::endl;

    HTTP_Server server; // Create an instance of the HTTP server
    server.start(); // Start the HTTP server

    return 0;
}