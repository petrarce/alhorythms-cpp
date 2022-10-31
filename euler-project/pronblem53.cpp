#undef NDEBUG
#include "prime.h"
#include "custom_iostream.hpp"
#include <algorithm>
#include <numeric>
#include <cassert>


template<class T>
T pickRfromN(const T r, const T n)
{
	std::map<T, T> divisorsN;
	std::map<T, T> divisorsR;
	if(r == 0)
		return 1;

	auto prepareDivisors = [](std::map<T, T>& divisors, T N, T R)
	{
		if (R > N)
			throw std::runtime_error("R > N");

		for(T val = N; val > N - R; val--)
		{
			auto currentDivisors = primeDivisors(val);
			for(auto [divisor, count] : currentDivisors)
			{
				if(divisors.contains(divisor))
					divisors.at(divisor) += count;
				else
					divisors[divisor] = count;
			}
		}
	};

	prepareDivisors(divisorsN, n, r);
	prepareDivisors(divisorsR, r, r - 1);

	for(const auto [divisor, count] : divisorsR)
		divisorsN.at(divisor) -= count;

	T product = std::accumulate(
				divisorsN.begin(),
				divisorsN.end(),
				1,
				[](T prod, const std::pair<T, T>& val) { return prod * std::pow(val.first, val.second); });

	return product;
}

int main(int ac, char** av)
{


	unsigned long long picksLargerTehnMil = 0;
	auto valBound = std::stoull(av[2]);
	auto nBound = std::stoull(av[1]);
	for(unsigned long long n = nBound; n >= 1; n--)
	{

		unsigned long long minR = 0;
		for(; minR <= n / 2; minR++)
		{
			if (pickRfromN(minR, n) > valBound)
				break;
		}
		if(minR < n / 2 )
		{
			assert(pickRfromN(minR - 1, n) <= valBound);
			assert(pickRfromN(minR, n) > valBound);

			picksLargerTehnMil += n + 1 - std::min(n + 1, 2 * (minR));
		}
	}

	std::cout << picksLargerTehnMil;
	return 0;
}
