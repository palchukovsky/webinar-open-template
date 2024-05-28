#include <cstddef>
#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------

template<int a, int b>
int add() {
    return a + b; // But only for integers, constexpr and enums!
}

//-----------------------------------------------------------------------------

// n! = n * (n - 1) * (n - 2) * ... * 1

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

//-----------------------------------------------------------------------------

template <int n>
int factorial_static()
{
    return n * factorial_static<n - 1>();
}

template <>
int factorial_static<0>()
{
    return 1;
}

//-----------------------------------------------------------------------------

int main()
{
    std::cout << "add<2, 3>(): " << add<2, 3>() << std::endl;

    std::cout << "factorial runtime: " << factorial(5) << std::endl;
    std::cout << "factorial static : " << factorial_static<5>() << std::endl;

    return 0;
}
