#include "MyClass.h"
#include <cmath> // Для використання pow

// Обчислення факторіала
double factorial(int num) {
    double fact = 1;
    for (int i = 1; i <= num; ++i) {
        fact *= i;
    }
    return fact;
}

// Функція для обчислення наближеного значення ch(x) за допомогою ряду
double MyClass::FuncA(int n, double x) {  // Тепер параметр n передається для кількості елементів
    double result = 0;
    for (int i = 0; i < n; ++i) {  // Використовуємо параметр n для визначення кількості елементів
        result += pow(x, 2 * i) / factorial(2 * i);  // Сума елементів ряду для ch(x)
    }
    return result;  // Повертаємо наближене значення
}

