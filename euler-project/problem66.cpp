#undef NDEBUG
#include <iostream>
#include <algorithm>
#include <ranges>
#include <cmath>
#include <optional>
#include <tuple>
#include <vector>
#include <execution>
#include <cassert>
#include <mutex>

#include <boost/multiprecision/cpp_int.hpp>
template<typename T, typename std::enable_if_t<!std::is_floating_point_v<T>, bool> = true>
std::optional<T> minDiophantinXSolution(T D)
{
	T yyP = 0, xxP= 0;
	for(T yy = 1
		, y = 1
		, xx = D + 1; ;
		yyP = yy
		,  yy = (y * y + 2 * y + 1)
		, y++
		, xxP = xx
		, xx = D * yy + 1)
	{
		assert(yyP < yy);
		if(xxP >= xx)
			return ~static_cast<T>(0);
		T x = std::sqrt(xx);
		if( x * x == xx )
		{
			assert( xx - D * yy == 1);
			return x;
		}
	}
	return std::nullopt;
}

int main(int ac, char** av)
{
	using T = uint64_t;
	size_t dBound(std::stoull(av[1]));
	std::optional<T> mLimit = std::nullopt;
	if( ac == 3 )
		std::stoull(av[2]);

	std::vector<std::tuple<T, std::optional<T>>> dFactors(dBound-1);
	T i = 2;
	std::generate(dFactors.begin(), dFactors.end(), [&i]()
		{
			auto r = i;
			i++;
			return std::tuple(r, std::nullopt);
		});

	std::atomic_uint64_t progress = 0;
	std::mutex mut;
	std::transform(std::execution::par,
		dFactors.begin(),
		dFactors.end(),
		dFactors.begin(),
		[&progress, &mut, dFactorsSize=dFactors.size()](const std::tuple<T, std::optional<T>>& item) {
					auto [D, minXSol] = item;
					T dSqrt = std::sqrt(D);
					if (dSqrt * dSqrt == D)
						return std::make_tuple(D, minXSol);

					minXSol = minDiophantinXSolution(D);
					progress++;
					{
						std::lock_guard<std::mutex> lock(mut);
						std::cout << "\r" << progress.load() << "/" << dFactorsSize;
						std::cout.flush();
					}
					return std::make_tuple(D, minXSol);
		});

	std::remove_if(dFactors.rbegin(), dFactors.rend(), [](const auto& item)
		{
			const auto [D, minXSol] = item;
			return !minXSol.has_value();
		});

	std::sort(dFactors.begin(), dFactors.end(), [](auto& v1, auto& v2)
			{
						auto [D1, minXSol1] = v1;
						auto [D2, minXSol2] = v2;
						return *minXSol1 > *minXSol2;
			});
	std::for_each(dFactors.begin(), dFactors.end(), [](const auto& item){
									const auto& [D, minXSol] = item;
									std::cout << "D: " << D << " => " << *minXSol << std::endl;
									return;
						});
	auto [DMin, solXMinMin] = dFactors.front();
	auto [DMax, solXMinMax] = dFactors.back();
	std::cout << "minMinSolX: " << DMin << ":" << *solXMinMin << std::endl;
	std::cout << "minMinSolX: " << DMax<< ":" << *solXMinMax << std::endl;
	return 0;
}
