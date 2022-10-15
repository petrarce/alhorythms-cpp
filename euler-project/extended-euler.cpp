#include <iostream>
#include <vector>

template<typename T>
struct bezier_set{
	T r;
	T s;
	T t;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, bezier_set<T> b)
{
	return stream << b.r << " " << b.s << " " << b.t;
}

template<typename T>
bezier_set<T> gcd(T a, T b)
{
	bezier_set<T> b0 = {a, 1, 0};
	bezier_set<T> b1 = {b, 0, 1};

	while(b1.r != 0 )
	{
		auto tmp = b1;
		auto q = b0.r / b1.r;
		b1.r = b0.r % b1.r;
		b1.s = b0.s - q*b1.s;
		b1.t = b0.t - q*b1.t;
		b0 = tmp;
	}
	return b0;
}

struct a {
	long long val;
};

int main(int argc, char** argv)
{
	long long val1 = std::stoll(argv[1]);
	long long val2 = std::stoll(argv[2]);

	std::cout << "gcd(val1, val2) = " << gcd(val1, val2) << std::endl;
}
