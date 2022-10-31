#include <iostream>
#include <vector>
#include <list>
int main(int ac, char** av)
{
	using IntType = size_t;
	IntType bound = std::stoull(av[1]);
	
	auto is_palindrome = [](const IntType& val, IntType base)
	{
		auto observedVal = val;
		IntType reversed = 0;

		while (observedVal)
		{
			reversed = base * reversed + observedVal % base;
			observedVal /= base;
		}

		return reversed == val;
	};
	
	auto generatePalindrome = []()
	{
		
	};
	
	IntType sum = 0;
	for(IntType i = 1; i < bound; i += 2)
	{
		if(is_palindrome(i, 10) && is_palindrome(i, 2))
		{
			sum += i;
			std::cout << "palindrome: " << i << std::endl;
		}
	}
	std::cout << "sum: " << sum << std::endl;
	return 0;
}
