#include <vector>
#include <set>
#include <cmath>
#include <cassert>

std::set<size_t> getPrimesUpTo(size_t ubound)
{
	std::set<size_t> primes({2});
	for(size_t i = 3; i <= ubound; i+=2)
	{
		bool is_prime = true;
		for(auto p : primes)
		{
			if(p*2 > i)
				break;
			if(i%p == 0)
			{
				is_prime = false;
				break;
			}
		}
		if(is_prime)
			primes.insert(i);
		assert(i + 2 > i);
	}
	return primes;

}

size_t getDivisorsSum(size_t val, const std::set<size_t> & primes)
{
	size_t sum = 1;
	size_t initVal = val;
	for(auto p : primes)
	{
		if(val == 1)
			break;
		int primeCnt = 1;
		while( val%p == 0)
		{
			val /= p;
			primeCnt++;
		}
		assert(sum * (std::pow(p, primeCnt) - 1) / (p-1) >= sum);
		sum *= (std::pow(p, primeCnt) - 1) / (p-1);
	}
	assert(sum - initVal < sum);
	return sum - initVal;
}


size_t getDivisorsSum(size_t val)
{
	auto primes = getPrimesUpTo(val);
	return getDivisorsSum(val, primes);

}

bool isAbundant(size_t val)
{
	size_t sum = 0;
	for(int i = 1; 2*i <= val; i++)
	{
		if( val%i == 0 )
			sum += i;
	}

	return sum > val;
}
