#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

std::vector<size_t> v = {
	75, 95, 64, 17, 47, 82, 18, 35, 87, 
	10, 20, 04, 82, 47, 65, 19, 01, 23, 
	75, 03, 34, 88, 02, 77, 73, 07, 63, 
	67, 99, 65, 04, 28, 06, 16, 70, 92, 
	41, 41, 26, 56, 83, 40, 80, 70, 33, 
	41, 48, 72, 33, 47, 32, 37, 16, 94, 
	29, 53, 71, 44, 65, 25, 43, 91, 52, 
	97, 51, 14, 70, 11, 33, 28, 77, 73, 
	17, 78, 39, 68, 17, 57, 91, 71, 52, 
	38, 17, 14, 91, 43, 58, 50, 27, 29, 
	48, 63, 66, 04, 68, 89, 53, 67, 30, 
	73, 16, 69, 87, 40, 31, 04, 62, 98, 
	27, 23, 9, 70, 98, 73, 93, 38, 53,
	60, 04, 23
};

size_t levelFromIndex(size_t index)
{
	if(!index)
		return 1;
	size_t n = 2;
	while(2 * (index + 1) > (n) * (n + 1))
		n++;
	return n;
}

size_t indexFromLevel(size_t level)
{
	assert(level >= 1);
	if(level == 1)
		return 0;
	return level * (level - 1) / 2;
}

void findMaxSum(const std::vector<size_t>& tree, size_t curElementIndex, size_t currentSum, size_t& currentMaxSum)
{
	assert(curElementIndex < tree.size());
	auto currentLevel = levelFromIndex(curElementIndex);
	assert(currentLevel <= levelFromIndex(tree.size() - 1));
	currentSum += tree[curElementIndex];
	//check if current element index is in the last level of the tree
	if(currentLevel == levelFromIndex(tree.size() - 1))
	{
		if(currentSum > currentMaxSum)
			currentMaxSum = currentSum;
		return;
	}

	findMaxSum(tree, indexFromLevel(currentLevel + 1) + (curElementIndex - indexFromLevel(currentLevel)), currentSum, currentMaxSum);
	findMaxSum(tree, indexFromLevel(currentLevel + 1) + (curElementIndex - indexFromLevel(currentLevel) + 1), currentSum, currentMaxSum);

}




int main()
{
	size_t level = 1;
	for(size_t i = 0; i < v.size(); i++)
	{
		size_t currentLevel = levelFromIndex(i);
		assert(currentLevel - level <= 1);
		if(level != currentLevel)
			std::cout << std::endl;
		std::cout << v[i] << ":" << indexFromLevel(currentLevel) << "\t";
		level = currentLevel;
	}

	std::cout << std::endl;
	size_t maxSum = 0;
	findMaxSum(v, 0, 0, maxSum);
	std::cout << "current max sum: " << maxSum << std::endl;
}

