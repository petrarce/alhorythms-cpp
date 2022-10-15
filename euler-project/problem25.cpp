#include <list>
#include <cassert>
#include <vector>
#include <set>
#include <iostream>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/factorials.hpp>
using namespace boost::multiprecision;
uint128_t cnt(int i);

uint128_t nFromK(int  n, int k)
{
	assert(n <= k);
	if(n == 0 || n == k)
		return 1;
	uint128_t nominator = k;
	uint128_t denominator = n;
	for(int i = 1; i < n; i++)
	{
		assert( n - i > 0);
		denominator *= (n - i);
		nominator *= (k - i);

		std::vector<uint128_t> factors = {2,3,5,7,11,13,17,19, 23, 29, 31, 37, 41, 43, 53};
		for(auto f : factors)
		{
			if((nominator%f) == 0 && (denominator%f) == 0)
			{
				nominator /= f;
				denominator /= f;
			}
		}

	}
	assert(nominator > denominator);
	assert((nominator%denominator) == 0);
	return nominator / denominator;

}

uint128_t cnt(int i, int k)
{
	uint128_t m = cnt(i);
	uint128_t sum = 0;
	for(int j = 0; j < m; j++)
	{
		uint128_t part = nFromK(k-1, j + k - 1);
		assert(sum + part >= sum);
		sum += nFromK(k-1, j + k - 1);
	}
	return sum;
}

uint128_t cnt(int i)
{
	switch(i)
	{
	case 1:
		return 1;
	case 2:
		return  1 + cnt(1);
	case 5:
		return 1 + + cnt(1) +  cnt(1,3) + cnt(1, 5) ;
	case 10:
		return 1 + cnt(5,2);
	case 20:
		return 1 + cnt(10,2);
	case 50:
		return 1 + cnt(10) + cnt(10,3) + cnt(10,5);
	case 100:
		return 1 + cnt(50, 2);
	case 200:
		return 1 + cnt(100, 2);
	default:
		assert(0 && "value not supported");
	}
}

int task25(int val)
{
	std::cout << "coin combinations of " << val << ": " << cnt(val) << std::endl;
	return 0;
}
int main(int argc, char** argv)
{
	// if(argv[2][0] == '1')
	// 	return combinator(argv);
	// else
	// 	return iterative(argv);
	return task25(std::stoi(argv[1]));
}
