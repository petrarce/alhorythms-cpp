#undef NDEBUG
#include <iostream>
#include <cassert>
#include "prime.h"
#include "custom_iostream.hpp"
int main(int ac, char** av)
{
	size_t maxFactors = std::stoull(av[1]);
	for(size_t i = 2; i <= 61; i++)
	{
		float val = std::sqrt(i);
		auto factors = factorize<float, size_t>(val, maxFactors);
		std::cout << val << " factors:" <<  factors << std::endl;
		auto [nom, denom] = defactorize(factors);
		float valDefactorized = static_cast<float>(nom) / denom;
		std::cout << val << "[sqrt(" << i << ")]:" << nom << "/" << denom << " = " << valDefactorized << std::endl;
		assert(std::abs(std::abs(valDefactorized) - val) < 1e-3);
	}
	return 0;
}
