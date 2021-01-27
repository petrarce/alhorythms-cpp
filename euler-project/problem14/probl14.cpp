#include <list>
#include <cassert>
#include <vector>
#include <set>
#include <iostream>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;


int128_t nFromK(int128_t  n, int128_t k)
{
	assert(n <= k);
	if(n == 0 || n == k)
		return 1;
	int128_t nominator = k;
	int128_t denominator = n;
	for(int i = 1; i < n; i++)
	{
		assert( n - i > 0);
		denominator *= (n - i);
		nominator *= (k - i);

		std::vector<int128_t> factors = {2,3,5,7,11,13,17,19, 23, 29, 31, 37, 41, 43, 53};
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

int combinator(char** argv)
{
	int gridResolution = std::stoi(std::string(argv[1]));
	int pathCount = 0;

	std::cout << "pathCount: " << nFromK(gridResolution, gridResolution*2) << std::endl;
	return 0;
}
struct Node{
	size_t r;
	size_t d;
};
int iterative(char** argv)
{
	std::list<Node> paths(1);
	int gridResolution = std::stoi(std::string(argv[1]));
	int pathCount = 0;
	while(!paths.empty())
	{
		auto path = paths.front();
		paths.pop_front();
		if(path.d == gridResolution || path.r == gridResolution)
		{
			pathCount++;
			continue;
		}
		paths.push_back({path.r + 0, path.d + 1});

		paths.push_back({path.r + 1, path.d + 0});
	}
	std::cout << "pathCount: " << pathCount << std::endl;
	return 0;
}

int task15()
{
	cpp_int val = 1;
	for(int i = 2; i <= 100; i++)
	{
		assert(val * i > val);
		val *= i;
	}

	std::cout << "100! = " << val << std::endl;
	cpp_int sum = 0;
	
	while(val != 0)
	{
		assert(sum + val%10 >= sum);
		sum += (val%10);
		val /= 10;
	}
	
	std::cout << sum;
	return 0;
}

std::set<size_t> findPrimes(int ubound)
{
	std::set<size_t> primes({2});
	for(int i = 3; i <= ubound; i+=2)
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
	}
	return primes;
}

std::set<size_t> findFactors(int val, const std::set<size_t>& primes)
{
	std::set<size_t> factors;
	int curVal = val;
	for(auto p : primes)
	{
		while((curVal%p) == 0)
		{
			factors.insert(p);
			factors.insert(curVal / p);
			curVal /= p;
		}
		if(curVal == 1)
			break;
	}
	factors.erase(val);
	return factors;
}

int task21()
{
	std::vector<int> amicSums(10000, -1);
	auto primes = findPrimes(10000);

	std::cout << "primes up to 5000: " << primes.size() << std::endl;

	for(int i = 2; i < 10000; i++)
	{
		auto factors = findFactors(i, primes);
		std::cerr << "factors "<< i << ": ";
		for(auto f : factors)
			std::cerr << f << ",";
		std::cerr << std::endl;
		auto sum = std::accumulate(factors.begin(), factors.end(), 0);
		amicSums[i] = sum;

	}

	int sum = 0;
	for(int i = 2; i < 10000; i++)
	{
		assert(amicSums[i] != -1);
		if(amicSums[i] >= 10000 && amicSums[i] < i)
			continue;
		if(amicSums[amicSums[i]] == i)
			sum += i + amicSums[i];
	}
	std::cout << "amic-sum:" <<  sum << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	// if(argv[2][0] == '1')
	// 	return combinator(argv);
	// else
	// 	return iterative(argv);
	return task21();
}