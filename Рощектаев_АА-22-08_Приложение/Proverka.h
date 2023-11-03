#pragma once
#include <iostream>

template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x < 0)
    {
        std::cout << "Неправильное число, попробуйте ещё раз: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

double getInRange(double x1, double x2);