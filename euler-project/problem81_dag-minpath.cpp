#include <iostream>
#include <Eigen/Dense>
#include "problem81.h"

struct SumNode 
{
	MatrixIndex parent{0,0};
	int sum{0};
	SumNode operator+(const SumNode& other) { return *this; }
	SumNode operator-(const SumNode& other) { return *this; }
	SumNode operator*(const SumNode& other) { return *this; }
	SumNode operator/(const SumNode& other) { return *this; }

	SumNode(int val = 0)
	{
		parent = {val, val};
		sum = val;
	}
	SumNode(MatrixIndex p, int s) :
		parent(p),
		sum(s){};

};

template<> class Eigen::NumTraits<SumNode> {
	public:
	typedef int Real;
	typedef int NonInteger;
	typedef int Literal;
	typedef int Nested;
	enum {
		IsComplex = false,
		IsInteger = false,
		ReadCost = 1, 
		AddCost = 1,
		MulCost = 1,
		RequireInitialization = false,
	};
	static int digits10() { return 10; }
	
};

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& stream, const SumNode& node)
{
	stream << node.parent << ":" << node.sum;
	return stream;
}

using MatrixNodes = Eigen::Matrix<SumNode, Eigen::Dynamic, Eigen::Dynamic>;

//Returns of nodes, each of which colds information to parent node
// from which path from node (0, 0) is minimal
MatrixNodes topologicSort(const Eigen::MatrixXi& matr)
{
	
	MatrixNodes nodeMatrix = MatrixNodes::Zero(matr.rows(), matr.cols());
	int counter = 0;
	for(int i = 0; i < matr.cols() + matr.rows() -1; i++)
	{
		
		auto currentIndex = MatrixIndex {
				(i < matr.cols() ? 0 : 1) * (i - matr.cols() + 1),
				(i < matr.cols()) ? i : matr.cols() - 1
		};
		while(currentIndex.row < matr.rows()
			  && currentIndex.col >= 0)
		{
				auto upperParent = currentIndex + MatrixIndex{-1, 0};
				auto leftParent = currentIndex + MatrixIndex{0, -1};
				std::optional<decltype(upperParent)> prefferedParent;
				if(upperParent.col >= 0 && upperParent.row >= 0
						&& leftParent.col >= 0 && leftParent.row >= 0)
				{	
					if(nodeMatrix(leftParent.row, leftParent.col).sum < nodeMatrix(upperParent.row, upperParent.col).sum)
						prefferedParent = leftParent;
					else
						prefferedParent = upperParent;
				}
				else if(upperParent.col >= 0 && upperParent.row >= 0
						&& (leftParent.col < 0 || leftParent.row < 0))
					prefferedParent = upperParent;
				else if((upperParent.col < 0 || upperParent.row < 0)
					  && leftParent.col >= 0 && leftParent.row >= 0)
					prefferedParent = leftParent;
				else
					prefferedParent = currentIndex;
				
				if(prefferedParent)
				{
					nodeMatrix(currentIndex.row, currentIndex.col) = SumNode{
						*prefferedParent, 
						nodeMatrix(prefferedParent->row, prefferedParent->col).sum + matr(currentIndex.row, currentIndex.col)
					};
				}
				currentIndex = currentIndex + MatrixIndex{+1, -1};
		}
	}
	return nodeMatrix;
}

int main(int ac, char** av)
{
	auto matrix = readoffMatrix(std::string(av[1]));
	std::cout << matrix << std::endl;
	auto mn = topologicSort(matrix);
	std::cout << mn << std::endl;
	std::cout << "min path sum: " << mn(mn.rows() - 1, mn.cols() - 1) << std::endl;
	return 0;
}
