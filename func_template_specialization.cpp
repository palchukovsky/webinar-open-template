#include <iostream>

template<typename T>
T add(const T &a, const T &b)
{
	return a + b;
}

template<>
std::string add(const std::string &a, const std::string &b)
{
	return a + " ---===***===--- " + b;
}

float add(float a, float b)
{
	return a - b;
}


int main()
{
	std::cout << "sum(2, 3) = " << add(2, 3) << std::endl;

	std::cout << "add(2.5f, 3.5f) = " << add(2.5f, 3.5f) << std::endl; // NO NO LINT!

	std::cout << "add(str, str) = "
			      << add(std::string("Hello, "), std::string("world")) << std::endl;

	return 0;
}