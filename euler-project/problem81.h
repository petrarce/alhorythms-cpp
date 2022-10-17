#include <Eigen/Dense>
#include <iostream>
#include <regex>
#include <fstream>

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

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& stream, const MatrixIndex& index)
{
	stream << "(" << index.row << "," << index.col << ")";
	return stream;
}


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

