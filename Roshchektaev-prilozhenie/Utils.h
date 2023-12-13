#pragma once
#include <iostream>
#include <cstdint>
#include "CPipe.h"

using namespace std;

class redirect_output_wrapper
{
    ostream& stream;
    streambuf* const old_buf;
public:
    redirect_output_wrapper(ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }

    void redirect(ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

// функции для проверки
template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x <= 0)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    cerr << x << endl;
    return x;
}

uint32_t getInRange(uint32_t x1, uint32_t x2);

double_t getCorrectPipeDiameter();

//поиск объектов

template<typename T>
uint32_t SearchId(const T& map, uint32_t id)
{
    if (map.find(id) != map.end()) return id;
    return -1;
}