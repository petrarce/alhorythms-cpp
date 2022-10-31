#include <iostream>
#include <limits>
int main()
{
	auto vLim = std::numeric_limits<unsigned long long>::max();
	auto vvLim = vLim * 3;
	std::cout << vLim << std::endl;
	std::cout << vvLim << std::endl;
	return 0;
}
