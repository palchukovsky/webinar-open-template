#include <iostream>

int add(int a, int b)
{
	return a + b;
}

int main()
{
	std::cout << "sum(2, 3) = " << add(2, 3) << std::endl;

	std::cout << "add(2.5f, 3.5f) = " << add(2.5f, 3.5f) << std::endl; // NOLINT

	// std::cout << "add(str, str) = "
	//  	       << add(std::string("Hello, "), std::string("world")) << std::endl;

	return 0;
}