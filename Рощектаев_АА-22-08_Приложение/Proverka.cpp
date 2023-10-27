#include <iostream>
#include "Proverka.h"

double getInRange(double x1, double x2)
{
    double x;
    while ((std::cin >> x).fail() || x1 > x || x > x2)
    {
        std::cout << "Неправильное число, попробуйте ещё раз: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}