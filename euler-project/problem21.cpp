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

std::vector<size_t> findPrimeFactors(int val, const std::set<size_t>& primes)
{
	std::vector<size_t> factors;
	int curVal = val;
	for(auto p : primes)
	{
		while((curVal%p) == 0)
		{
			factors.push_back(p);
			curVal /= p;
		}
		if(curVal == 1)
			break;
	}
	return factors;
}

void composeFactors(int cnt, std::vector<size_t> primeFactors, std::set<size_t>& factors)
{
	assert(primeFactors.size() >= cnt);
	std::vector<size_t> pointers(cnt);
	for(size_t i = 0; i < pointers.size(); i++)
		pointers[i] = i;

	do
	{
		size_t factor = 1;
		for(auto p : pointers)
			factor *= primeFactors[p];
		factors.insert(factor);

		pointers.back()++;
		if(pointers.back() >= primeFactors.size())
		{
			for(size_t i = 1; i < pointers.size(); i++)
			{
				if(pointers[i] >= primeFactors.size() - cnt + i)
				{
					pointers[i-1]++;
					for(size_t j = i; j < pointers.size(); j++)
						pointers[j] = pointers[j - 1] + 1;
					break;
				}
			}
		}
	}while(pointers.back() <= primeFactors.size() - 1);

};

int task21()
{
	std::vector<size_t> amicSums(10000, -1);
	auto primes = findPrimes(10000);

	std::cout << "primes up to 5000: " << primes.size() << std::endl;

	for(int i = 2; i < 10000; i++)
	{
		auto factors = findPrimeFactors(i, primes);
		std::cerr << "prime factors "<< i << ": ";
		for(auto f : factors)
			std::cerr << f << ",";
		std::cerr << std::endl;

		size_t pfCnt = factors.size();
		std::set<size_t> uniqueFactors;
		for(size_t j = 1; j <= pfCnt; j++)
			composeFactors(j, factors, uniqueFactors);
		uniqueFactors.erase(i);
		uniqueFactors.insert(1);

		std::cerr << "factors "<< i << ": ";
		for(auto f : uniqueFactors)
			std::cerr << f << ",";
		std::cerr << std::endl;
		auto sum = std::accumulate(uniqueFactors.begin(), uniqueFactors.end(), 0);
		std::cerr << "amic sum "<< i << ": " << sum << std::endl;
		amicSums[i] = sum;

	}

	int sum = 0;
	std::set<size_t> amicables;
	for(size_t i = 2; i < amicSums.size(); i++)
	{
		assert(amicSums[i] != -1 );
		if(amicSums[i] >= amicSums.size() || amicSums[i] == i)
			continue;
		if(amicSums[amicSums[i]] == i)
		{
			amicables.insert(i);
		}
	}
	std::cerr << "amicables:";
	for(auto f : amicables)
	{
		std::cerr << f << ",";
	}
	std::cerr << std::endl;

	std::cout << "\namic-sum:" <<  std::accumulate(amicables.begin(), amicables.end(), 0) << std::endl;

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
