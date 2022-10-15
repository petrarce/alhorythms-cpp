#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <set>
#include <algorithm>


class Node{
	int mValue;
	std::vector<std::shared_ptr<Node>> mChildren;

public:
	Node(int value)
	{
		this->mValue = value;
		switch(value){
		case 200:
			mChildren.push_back(std::make_unique<Node>(100));
			mChildren.push_back(std::make_unique<Node>(100));
			break;

		case 100:
			mChildren.push_back(std::make_unique<Node>(50));
			mChildren.push_back(std::make_unique<Node>(50));
			break;

		case 50:
			mChildren.push_back(std::make_unique<Node>(20));
			mChildren.push_back(std::make_unique<Node>(20));
			mChildren.push_back(std::make_unique<Node>(10));
			break;

		case 20:
			mChildren.push_back(std::make_unique<Node>(10));
			mChildren.push_back(std::make_unique<Node>(10));
			break;

		case 10:
			mChildren.push_back(std::make_unique<Node>(5));
			mChildren.push_back(std::make_unique<Node>(5));
			break;

		case 5:
			mChildren.push_back(std::make_unique<Node>(2));
			mChildren.push_back(std::make_unique<Node>(2));
			mChildren.push_back(std::make_unique<Node>(1));
			break;

		case 2:
			mChildren.push_back(std::make_unique<Node>(1));
			mChildren.push_back(std::make_unique<Node>(1));
			break;

		case 1:
			break;

		default:
			assert(0 && "unknown value for tree node");

		}
	}
	void printTree(int level = 0)
	{
		std::cout << std::string(level, '\t') << mValue << std::endl;
		for(auto  child : mChildren)
			child->printTree(level + 1);

	}

	int wrapsCount() const
	{
		if(mChildren.size() == 0)
			return 0;
		int wrapCount = 1;
		for(auto child : mChildren)
			wrapCount += child->wrapsCount();
		return wrapCount;
	}



};

class Tree{
	Node Root;
public:
	Tree(int rootValue):
		Root(rootValue){};
	void printTree()
	{
		Root.printTree();
	}

	int wraps() const { return Root.wrapsCount(); }

};

std::vector<std::vector<int>> split(int val)
{
	std::vector<std::vector<int>> result;
	std::vector<int> splitedValues;
	switch(val)
	{
	case 200:
		splitedValues.push_back(100);
		splitedValues.push_back(100);
		break;

	case 100:
		splitedValues.push_back(50);
		splitedValues.push_back(50);
		result.push_back(std::move(splitedValues));
		splitedValues = {20, 20, 20, 20, 20};
		break;
	case 50:
		splitedValues = {20, 20, 10};
		break;
	case 20:
		splitedValues.push_back(10);
		splitedValues.push_back(10);
		break;

	case 10:
		splitedValues.push_back(5);
		splitedValues.push_back(5);
		result.push_back(std::move(splitedValues));
		splitedValues = {2, 2, 2, 2, 2};
		break;
	case 5:
		splitedValues.push_back(2);
		splitedValues.push_back(2);
		splitedValues.push_back(1);
		break;
	case 2:
		splitedValues.push_back(1);
		splitedValues.push_back(1);
		break;
	case 1:
		break;
	default:
		assert(0 && "invalid value");
	}
	result.push_back(std::move(splitedValues));
	return result;
}

int main(int argc, char** argv)
{
	std::set<std::vector<int>> vectorsToSplit;
	std::set<std::vector<int>> finalVectors;

	vectorsToSplit.insert({std::stoi(argv[1])});

	while(!vectorsToSplit.empty())
	{
		auto toBeSplitted = *vectorsToSplit.begin();
		vectorsToSplit.erase(vectorsToSplit.begin());
		if(finalVectors.count(toBeSplitted))
			continue;
		finalVectors.insert(toBeSplitted);
		int lastElement = -1;
		for(size_t i = 0; i < toBeSplitted.size(); i++)
		{
			lastElement = toBeSplitted[i];
			auto splittedElementsSet = split(toBeSplitted[i]);
			for(const auto& splittedElements : splittedElementsSet)
			{
				if(splittedElements.size())
				{
					auto newCoinsSet = toBeSplitted;
					newCoinsSet.erase(newCoinsSet.begin() + i);
					newCoinsSet.insert(newCoinsSet.end(), splittedElements.begin(), splittedElements.end());
					std::sort(newCoinsSet.begin(), newCoinsSet.end());
					vectorsToSplit.insert(newCoinsSet);
				}
			}
		}
	}
	std::cout << "coun sets: " << finalVectors.size();
	return 0;
}
