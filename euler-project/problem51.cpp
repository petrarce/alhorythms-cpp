#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <list>
#include "custom_iostream.hpp"
#include "prime.h"

auto substitutionIndices(size_t val) -> std::vector<std::list<size_t>>
{
	std::vector<std::list<size_t>> indexLists;
	auto valStr = std::to_string(val);
	for(int i = 1; i < valStr.size(); i++)
	{
		std::list<size_t> indices;
		indices.push_back(0);
		while(!indices.empty())
		{

			if(indices.back() >= valStr.size())
			{
				indices.pop_back();
				indices.back()++;
				continue;
			}

			if(indices.size() == i)
			{
				indexLists.push_back(indices);
				indices.back()++;
			}
			else {
				indices.push_back(indices.back() + 1);
			}

		}
	}
	return indexLists;
};
std::map<int, size_t> computePrimeFamilies(size_t bound)
{

	std::map<int, size_t> families;
	auto substitutes = [](size_t val, const std::list<size_t>& indices) -> std::vector<size_t>
	{
		const std::string valStr = std::to_string(val);
		std::vector<size_t> subs{};
		subs.reserve(valStr.length() * valStr.length());
		for(int c = '0'; c <= '9'; c++)
		{
			auto tmpValStr = valStr;
			for(auto ind : indices)
				tmpValStr[ind] = c;
			auto newVal = std::stoul(tmpValStr);
			auto newValStr = std::to_string(newVal);
			if(newValStr.length() == valStr.length())
				subs.push_back(newVal);
		}
		return subs;
	};
	auto updateFamilies = [&families, &substitutes](size_t val)
	{
		if (testPrime(val))
		{
			auto indexLists = substitutionIndices(val);
			for(const auto& indices : indexLists)
			{
				size_t minPrime = std::numeric_limits<size_t>::max();
				auto subs = substitutes(val, indices);
				int counter = 0;

				for(auto s : subs)
					if (testPrime(s))
					{
						counter++;
						if(minPrime > s)
							minPrime = s;
					}
				if(!families.contains(counter))
					families[counter] = minPrime;
			}
		}
	};
	updateFamilies(2);
	updateFamilies(3);
	for(size_t val = 5; val <= bound; val += 6)
	{
		updateFamilies(val);
		updateFamilies(val + 2);
	}
	return families;
}

int main(int ac, char** av)
{
//	std::cout << substitutionIndices(std::stoul(av[1])) << std::endl;
	std::cout << computePrimeFamilies(std::stoul(av[1])) << std::endl;
	return 0;
}
