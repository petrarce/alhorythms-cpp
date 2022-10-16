#include <eigen3/Eigen/Dense>
#include <fstream>
#include <ranges>
#include <string_view>
#include <sstream>
#include <regex>
#include <iostream>
#include <stack>
Eigen::MatrixXi readoffMatrix(const std::string& filename)
{
	std::fstream file(filename, std::ios_base::in);
	if(!file.is_open())
		throw std::runtime_error("cannot open file " + filename);

	std::stringstream ss;
	ss << file.rdbuf();
	std::string fileContent = ss.str();

	std::optional<Eigen::MatrixXi> matrix;
	std::regex rowRegex = std::regex("[0-9, ]+\n");
	std::sregex_token_iterator rowMatches;
	int crow = 0;
	auto row_it = std::sregex_token_iterator(fileContent.cbegin(), fileContent.cend(), rowRegex);
	for( ;
		row_it != std::sregex_token_iterator();
		row_it++)
	{
		auto row = row_it->str();
		auto col_regex = std::regex("[0-9]+");
		auto col_it = std::sregex_token_iterator(row.begin(), row.end(), col_regex);
		if(!matrix)
		{
			int rows = std::distance(row_it, std::sregex_token_iterator());
			int cols = std::distance(col_it, std::sregex_token_iterator());
			std::cout << "(" << rows << ", " << cols << ")" << std::endl;
			matrix = Eigen::MatrixXi::Zero(rows, cols);
		}
		int ccol = 0;
		for(;
			col_it != std::sregex_token_iterator();
			col_it++)
		{
			matrix->operator()(crow, ccol) = std::stoul(col_it->str());
			ccol++;
		}
		crow++;
	}

	return matrix ? *matrix : Eigen::MatrixXi::Zero(0, 0);
}

struct MatrixIndex {
	long row{0};
	long col{0};
	MatrixIndex operator+(const MatrixIndex& right) const
	{
		MatrixIndex newIndex(*this);
		newIndex.row += right.row;
		newIndex.col += right.col;
		return newIndex;
	}
	bool operator==(const MatrixIndex& other) const
	{
		return this->row == other.row && this->col == other.col;
	}
};

enum class Step {
	Row,
	Col
};

/// minSumIndex - sum for indeces (initIndex, minSumIndex]
/// minSumIndex - position, where sum reaches its minimum for current sequence
/// currentPath - path from (initIndex, minSumIndex]
void lookageadMinSumPath(long lookaheadSize,
						const Eigen::MatrixXi& matr,
						 std::optional<int>& minSum,
						 MatrixIndex& minSumIndex,
						 std::vector<MatrixIndex>& minSumPath,
						 int currentSum = 0,
						 MatrixIndex currentIndex = MatrixIndex{0, 0},
						 std::vector<MatrixIndex> currentPath = {})
{

	const int rowSteps = std::min(matr.rows() - currentIndex.row - 1, lookaheadSize);
	const int colSteps = std::min(matr.cols() - currentIndex.col - 1, lookaheadSize);

	if(!rowSteps && !colSteps)
	{
		if(!minSum.has_value() || *minSum > currentSum)
		{
			minSumIndex = currentIndex;
			minSum = currentSum;
			minSumPath = currentPath;
		}
		return;
	}


	for(auto step : std::vector({Step::Row, Step::Col}))
	{
		auto newIndex = currentIndex;
		auto newPath = currentPath;
		if(step == Step::Row && rowSteps  > 0)
			newIndex = newIndex + MatrixIndex({1, 0});
		else if(colSteps > 0)
			newIndex = newIndex + MatrixIndex({0, 1});
		else
			continue;

		newPath.push_back(newIndex);
		auto newSum = currentSum + matr(newIndex.row, newIndex.col);
		lookageadMinSumPath(
					lookaheadSize - 1,
					matr,
					minSum,
					minSumIndex,
					minSumPath,
					newSum,
					newIndex,
					newPath
					);
	}
}

//arg1 - path to file
// arg2 - left top to right bottom sum (otherwice right top to left bottom)
int main(int ac, char** av)
{

	auto matr = readoffMatrix(std::string(av[1]));
	std::cout << matr;
	int lookaheadSize = ac > 2 ? std::stoi(av[2]) : 1;
	MatrixIndex currentIndex{0,0};
	int currentSum = matr(0,0);
	std::vector<MatrixIndex> currentPath {MatrixIndex{0,0}};
	while(currentIndex != MatrixIndex{matr.rows() - 1, matr.cols() - 1})
	{
		std::optional<int> tmpMinSum = std::nullopt;
		std::vector<MatrixIndex> tmpCurrentPath {};
		MatrixIndex tmpCurrentIndex;
		lookageadMinSumPath(lookaheadSize,
							matr,
							tmpMinSum,
							tmpCurrentIndex,
							tmpCurrentPath,
							currentSum,
							currentIndex);
		assert(tmpMinSum);
		currentSum = *tmpMinSum;
		currentPath.insert(currentPath.end(), tmpCurrentPath.begin(), tmpCurrentPath.end());
		currentIndex = tmpCurrentIndex;
	}
	std::cout << "current min path: " << std::endl;
	for(auto index : currentPath)
		std::cout << "(" << index.row << "," << index.col << ")";
	std::cout << std::endl;

	int minPathSumCheck = 0;
	for(auto node : currentPath)
		minPathSumCheck += matr(node.row, node.col);
	if(minPathSumCheck != currentSum)
		throw std::runtime_error("sum doesnt match:\n sum from path: "
			+ std::to_string(minPathSumCheck)
			+ "\n calculated: "
			+ std::to_string(currentSum));


	std::cout << "min sum path: " << currentSum << std::endl;

	return 0;
}
