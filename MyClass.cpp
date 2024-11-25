#include "MyClass.h"
#include <cmath>

double factorial(int num) {
    double fact = 1;
    for (int i = 1; i <= num; ++i) {
        fact *= i;
    }
    return fact;
}

double MyClass::FuncA(double x) {
    double result = 0;
    for (int i = 0; i < 3; ++i) {
        result += pow(x, 2 * i) / factorial(2 * i);
    }
    return result;
}

