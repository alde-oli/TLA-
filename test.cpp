#include "inc/math.hpp"

#include <iostream>
#include <cmath>

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Usage: " << av[0] << " <number> <number>" << std::endl;
		return 1;
	}
	double x = std::stod(av[1]);
	// test floor
	double y = std::stod(av[2]);
	std::cout << "cmath root(" << x << ", " << y << ") = " << std::pow(x, 1 / y) << std::endl;
	std::cout << "tlap root(" << x << ", " << y << ") = " << tlap::root(x, y) << std::endl;
	return 0;
}