#pragma once
#include <set>
#include <tuple>
#include <map>
#include <math.h>
#include <vector>
#include <numeric>
#include <limits>
#include <ranges>
#include <iostream>
bool testPrime(const size_t val)
{

	if(val % 2 == 0 || val % 3 == 0)
		return false;

	for( int cv = 5; cv * cv <= val; cv += 6)
		if (val % cv == 0 || val % (cv + 2) == 0)
			return false;

	return true;
}

template<typename T>
std::map<T, T> primeDivisors(const T val)
{

	std::map<T, T> primeDivisorsList;
	auto currentVal = val;

	if (val == 0)
		return primeDivisorsList;

	auto testDivisor = [&primeDivisorsList, &currentVal](
			const T currentDivisor)
	{
		int numDivisors = 0;
		while ( currentVal % currentDivisor == 0 )
		{
			currentVal /= currentDivisor;
			numDivisors++;
		}
		if(numDivisors)
			primeDivisorsList[currentDivisor] = numDivisors;
	};


	testDivisor(2);
	testDivisor(3);

	auto currentDivisor = 5;
	while(currentVal != 1)
	{
		testDivisor(currentDivisor);
		testDivisor(currentDivisor + 2);
		currentDivisor += 4;
	}

	return primeDivisorsList;
}


template<typename T>
std::tuple<std::enable_if_t<std::is_floating_point_v<T> != true, T>, T>
defactorize(const std::vector<T>& factors)
{

	auto pn_plus_1 = [](T an, T Pn, T Qn)
	{
		return an * Pn + Qn;
	};
	T Pn = 1;
	T Qn = 0;
	for(auto a : std::ranges::reverse_view(factors))
	{
		auto Qn_tmp = Qn;
		Qn = Pn;
		Pn = pn_plus_1(a, Pn, Qn_tmp);
	}
	return std::make_tuple(Pn, Qn);
}

template<typename FloatingPointType, typename FactorType>
std::vector<std::enable_if_t<std::is_floating_point_v<FactorType> == false, FactorType>>
factorize(
		const FloatingPointType& val,
		const std::optional<FactorType>& maxFactors = std::nullopt,
		const std::optional<FloatingPointType>& threshold = 1e-6)
{
	
	auto predicate = [&maxFactors, &threshold, &val](
			const std::vector<FactorType>& factors,
			int iteration) -> bool
	{
		if(threshold)
		{
			auto [nom, denom] = defactorize(factors);
			FloatingPointType currentVal = static_cast<FloatingPointType>(nom) / denom;
			return std::abs(currentVal - val) > *threshold;
		}
		else if (maxFactors)
			return *maxFactors <= iteration;
		else
			throw std::runtime_error("Either iterations or threshold must be initialized");
		return false;
		
	};
	auto currentVal = val;
	std::vector<FactorType> factors;
	factors.push_back(std::floor(currentVal));
	for (int i = 0
		 ; predicate(factors, i)
		 ; i++)
	{
		currentVal = 1 / ( currentVal - factors.back());
		factors.push_back(std::floor(currentVal));
	}

	return factors;
}
