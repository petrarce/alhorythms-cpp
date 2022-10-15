#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

template<typename Scalar, int Rows, int Cols, int options, int MaxRos, int MaxCols>
Matrix<Scalar, Rows, Cols, options, MaxRos, MaxCols> operator%(const Matrix<Scalar, Rows, Cols, options, MaxRos, MaxCols>& mat, Scalar val)
{
	auto newMat = mat;
	for(int i = 0; i < newMat.rows(); i++)
		for(int j = 0; j < newMat.cols(); j++)
		{
			Scalar newVal = static_cast<Scalar>(newMat(i, j) - std::floor(newMat(i, j) / val) * newMat(i, j));
			newMat(i, j) = newVal;
		}
	return newMat;
}
class GuasJordanAlgs
{
public:
	template<typename Scalar, int Rows, int Cols, int options, int MaxRos, int MaxCols>
	static void toRowEchelon(Matrix<Scalar, Rows, Cols, options, MaxRos, MaxCols>& matrix)
	{
		auto swap = [](Matrix<Scalar, Rows, Cols, options, MaxRos, MaxCols>& m, size_t i, size_t j)
		{
			if(i == j)
				return;
//			std::cout << "Before swap\n" << m.row(i) << "\n" << m.row(j) << std::endl;
			Matrix<Scalar, Rows, 1> tmp = m.row(i);
			m.row(i) = m.row(j);
			m.row(j) = tmp;
//			std::cout << "After swap\n" << m.row(i) << "\n" << m.row(j) << std::endl;

		};
		auto normalize = [](Matrix<Scalar, Rows, Cols, options, MaxRos, MaxCols>& m, int i)
		{
			if(m(i,i) == 0)
				return;
//			std::cout << "Before normalize\n" << m.row(i) << std::endl;
			auto pivot = m(i,i);
			m.row(i) /= pivot;
//			std::cout << "After normalize\n" << m.row(i) << std::endl;
		};

		for(int i = 0; i < matrix.rows(); i++)
		{
			for(int j = i; j < matrix.rows(); j++)
			{
				if(matrix(i, j) != 0)
				{
					swap(matrix, i, j);
					normalize(matrix, i);
					break;
				}
			}
			for(int j = 0; j < matrix.rows(); j++)
			{
				if(j == i)
					continue;
				matrix.row(j) = matrix.row(j) * matrix(i, i) - (matrix.row(i) * matrix(j,i));
			}
		}

	}
};

int main(int argc, char** argv)
{
	size_t size = std::stoul(argv[1]);
	int maxVal = std::stoul(argv[2]);
	bool verbose = std::stoi(argv[3]);
	MatrixXd mat = MatrixXd::Random(size, size + 1);
	mat = mat % static_cast<double>(maxVal);
	auto rowEchelon = mat;

	if(verbose)
		std::cout << "Otiginal matrix:\n" << mat << std::endl;
	GuasJordanAlgs::toRowEchelon(mat);
	if(verbose)
		std::cout << "RowEchelon matrix:\n" << mat << std::endl;

	MatrixXd newMatr = MatrixXd::Random(size, size);
	newMatr = newMatr % static_cast<double>(maxVal);
	MatrixXd RJ(newMatr.rows(), 2 * newMatr.cols());
	RJ << newMatr, MatrixXd::Identity(newMatr.rows(), newMatr.cols());
	GuasJordanAlgs::toRowEchelon(RJ);
	auto inverse = RJ.block(0, newMatr.cols(), newMatr.rows(), newMatr.cols());
	std::cout << "Original Matrix\n" << newMatr << std::endl;
	std::cout << "J*[A|I]\n" << RJ << std::endl;
	std::cout << "Inverse of newMatr:\n" << inverse << std::endl;
	std::cout << "A*J:\n" << newMatr * inverse << std::endl;
	assert(1 - (newMatr * inverse).determinant() < 1e-6);

	return 0;

}
