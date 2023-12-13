#pragma once
#include "CStation.h"
#include <iostream>
#include "Utils.h"

using namespace std;

uint32_t getInRange(uint32_t x1, uint32_t x2)
{
    uint32_t x;
    while ((std::cin >> x).fail() || x1 > x || x > x2)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    cerr << x << endl;
    return x;
}

double_t getCorrectPipeDiameter()
{
    double_t d;
    std::set<double_t> diameters = { 500, 700, 1400 };
    getCorrect(d);
    while (diameters.find(d) == diameters.end())
    {
        std::cout << "Enter right diameter: 500, 700 or 1400\n";
        getCorrect(d);
    }
    cerr << d << endl;
    return d;
}

