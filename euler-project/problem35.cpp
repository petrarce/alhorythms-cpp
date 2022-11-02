#include <iostream>
#include "custom_iostream.hpp"
#include "prime.h"

template<typename T>
T rotate(T val) 
{
	
	T power = 0;
	auto curVal(val);
	while (curVal > 10)
	{
		power++;
		curVal /= 10;
	}
	
	if (!power)
		return val;
	
	T decPow = std::pow(10, power);
	return val % decPow * 10 + curVal;
};

template<typename T>
std::set<T> rotateList(T val)
{
	std::set<T> rotations = {val};
	auto rotation = rotate(val);

	while(rotation != val)
	{
		rotations.insert(rotation);
		rotation = rotate(rotation);
	}

	return rotations;
}

int main(int ac, char** av)
{
	using IT = unsigned long;
	IT bound = std::stoul(av[1]);
	
	std::set<IT> circularPrimes = {2, 3, 5};
	
	for(IT v = 7; v <= bound; v+=2)
	{
		auto vStr = std::to_string(v);
		if(vStr.find('0') != std::string::npos)
			continue;
		
		auto rotates = rotateList(v);
		decltype(circularPrimes) rotates_intersection;
		std::set_intersection(
					rotates.begin(), rotates.end(),
					circularPrimes.begin(), circularPrimes.end(),
					std::inserter(rotates_intersection, rotates_intersection.begin()));
		decltype(circularPrimes) rotates_difference;
		std::set_difference(
					rotates.begin(), rotates.end(),
					rotates_intersection.begin(), rotates_intersection.end(),
					std::inserter(rotates_difference, rotates_difference.begin()));
		
		if (is_prime(rotates_difference.begin(), rotates_difference.end()))
			circularPrimes.insert(rotates_difference.begin(), rotates_difference.end());
	}
	
	std::cout << "circular primes: " << circularPrimes << std::endl;
	std::cout << "circular primes{count}: " << circularPrimes.size() << std::endl;
	
	return 0;
}
