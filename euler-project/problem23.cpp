#include "Algorythms.h"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

int main(int argc, char** argv)
{
	size_t val = stoi(argv[1]);
	auto primes = getPrimesUpTo(val);
	cout << "primes up to " << val << ": ";
	for(auto p : primes)
		cout << p << ", ";
	cout << std::endl;
	cout << "div sum for "<< val << ": " <<  getDivisorsSum(val, primes) << std::endl;

	auto allPrimes = getPrimesUpTo(28123);
	boost::multiprecision::cpp_int abandSum = 0;
	//find abundands up to 28123
	for(int i = 12; i <= 28123; i++)
	{
		if(isAbundant(i))

			abandSum += i;
		std::cout << "\r" << int((static_cast<float>(i) / 28123) * 100) << "% of abundands are processed, sum=" << abandSum;
		std::cout.flush();
	}
	std::cout << std::endl;

//	//generate sums of abundands
//	std::set<size_t> abundSums;
//	for(size_t i = 0; i < abundands.size(); i++)
//	{
//		if(2 * abundands[i] > 28123)
//			break;
//		for(size_t j = i; j < abundands.size(); j++)
//		{
//			if(abundands[i] + abundands[j] > 28123)
//				break;
//			abundSums.insert(abundands[i] + abundands[j]);
//		}
//	}

//	//from 1 to 28123 sum up all numbers that are not in abundands
//	int sum = 0;
//	for(size_t i = 1; i <= 28123; i++)
//	{
//		auto fronAbundVal = *abundSums.begin();
//		if(i == fronAbundVal)
//		{
//				abundSums.erase(abundSums.begin());
//				continue;
//		}
//		sum += i;
//	}
	boost::multiprecision::cpp_int total = 28123;
	total = total * 28124 / 2;
	total -= abandSum;
	cout << "sum of non abundands: " << total << std::endl;
	return 0;
}
