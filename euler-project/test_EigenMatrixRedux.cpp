#include <Eigen/Dense>
#include <iostream>
#include <chrono>
template<typename T>
T CalcMinHeightAboveZero(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& matr)
{
		T min = std::numeric_limits<T>::max();

		const int samplesX = matr.cols();
		const int samplesY = matr.rows();

		for(int y = 0; y < samplesY; ++y)
		{
			for(int x = 0; x < samplesX; ++x)
			{
				const T height = matr(x, y);
				if(std::fabs(height) > 0.0001)
					min = std::min(min, height);
			}
		}
	return min;
}



int main(int ac, char** av)
{
	int size = std::stoi(av[1]);
	Eigen::MatrixXf mat = Eigen::MatrixXf::Random(size, size);
//	std::cout << mat << std::endl;
	const auto& constMat = mat;
	std::chrono::system_clock clock;
	std::cout << "start calculations" << std::endl;
	auto start = std::chrono::system_clock::now();
	auto min = constMat.redux([](float a, float b) 
		{
		auto tmpA =  std::fabs(a) > 0.0001 ? a : std::numeric_limits<float>::max();
		auto tmpB = std::fabs(b) > 0.0001 ? b : std::numeric_limits<float>::max();
		return std::min(tmpA, tmpB);
		});
	auto end = std::chrono::system_clock::now();
	std::cout << "redux time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	start = std::chrono::system_clock::now();
	auto newMin = CalcMinHeightAboveZero(mat);
	end = std::chrono::system_clock::now();
	std::cout << "CalcMinHeightAboveZero time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "newMin: " << newMin << ", min: " << min << std::endl;
	if( newMin != min ) throw std::runtime_error("invalid calculations somewhere");
	return 0;

}
