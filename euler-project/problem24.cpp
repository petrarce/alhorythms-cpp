#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

size_t factorial(size_t n)
{
	size_t sum = 1;
	for(int i = 2; i <= n; i++)
	{
		assert(sum * i > sum);
		assert((sum * i) / i == sum);
		sum *= i;
	}
	return sum;
}

int main(int argc, char** argv)
{
	int numVal = stoul(argv[1]);
	size_t permut = stoul(argv[2]);
	vector<size_t> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::string finalPermutation;
	size_t cnt = 1;
	for(int i = numVal; i >= 1; i--)
		for(int j = 1; j <= i; j++)
		{
			size_t fact = factorial(i-1);
			if(cnt + fact > permut)
			{
				finalPermutation.push_back('0' + values[j-1]);
				values.erase(values.begin() + j - 1);
				break;
			}
			cnt += fact;
		}

	cout << "final sum: " << cnt << ", final value: " << finalPermutation << std::endl;

}
