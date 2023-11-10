#pragma once
#include <chrono>
#include <iostream>

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

template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x < 0)
    {
        std::cout << "Неправильное число, попробуйте ещё раз: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    cerr << x << endl;
    return x;
}

double getInRange(double x1, double x2);