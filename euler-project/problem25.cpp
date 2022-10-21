#include <list>
#include <cassert>
#include <vector>
#include <set>
#include <iostream>
#include <numeric>
#include <sstream>
#include <cmath>

class LargeInt {
public:
	static constexpr int MAX_POW = 7;
	LargeInt() = default;
	LargeInt(const std::string& val)
	{
		int curVal = 0;
		for(auto it = val.rbegin(); 
			it != val.rend(); 
			it++)
		{
			int pow = std::distance(val.rbegin(), it) % (MAX_POW);
			if(!pow)
				mValue.push_front(0);
			
			mValue.front() += std::pow(10, pow) * (*it - '0');
		}
	}
	LargeInt& operator=(const LargeInt& val) = default;
	LargeInt& operator=(const std::string& val)
	{
		LargeInt lval(val);
		*this = lval;
		return *this;
	}
	
	LargeInt operator+(const LargeInt& val) const 
	{
		LargeInt newVal;
		auto v1 = this->mValue;
		auto v2 = val.mValue;
		if(v1.size() > v2.size())
			v2.insert(v2.begin(), v1.size() - v2.size(), 0);
		else if(v2.size() > v1.size())
			v1.insert(v1.begin(), v2.size() - v1.size(), 0);
		
		assert(v1.size() == v2.size());

		int left = 0;

		for(auto itv1 = v1.rbegin(), itv2 = v2.rbegin();
			itv1 != v1.rend() && itv2 != v2.rend();
			itv1++, itv2++)
		{
			int currentValue = (*itv1 + *itv2) % static_cast<int>(std::pow(10, MAX_POW));
			newVal.mValue.push_front(currentValue + left);
			left = ((*itv1 + *itv2) - currentValue) / std::pow(10, MAX_POW);
		}
		if(left)
			newVal.mValue.push_front(left);
		return newVal;
	}
	const std::list<int>& value() const
	{
		return mValue;
	}
private:
	std::list<int> mValue;
};

namespace std 
{

template<class T, class R>
std::basic_ostream<T, R>& operator<<(std::basic_ostream<T, R>& stream, const LargeInt& val)
{
	auto it = val.value().begin();
	if(it != val.value().end())
	{
		stream << std::to_string(*it);
		it++;
	}
	
	for(; it != val.value().end(); it++)
	{
		auto stringVal = std::to_string(*it);
		stream << std::string(std::max(static_cast<int>(LargeInt::MAX_POW - stringVal.length()), 0), '0') + stringVal;
	}

	return stream;
}

}

int findFirstFibonacheIndex(int size)
{
	LargeInt fn_2("1");
	LargeInt fn_1("1");
	int index = 2;
	std::string currentVal;
	do
	{
		index++;
		LargeInt fn = fn_1 + fn_2;
		std::stringstream ss; ss << fn;
		currentVal = ss.str();
		fn_2 = fn_1;
		fn_1 = fn;
//		std::cout << fn << std::endl;
	} while(currentVal.size() < size);
	return index;
}
int main(int ac, char** av)
{

//	std::string initVal = std::string(av[1]);
//	LargeInt val(initVal);
//	std::stringstream ss;
//	ss << val;
//	std::cout << "\"" << ss.str() << "\"vs\"" << initVal << "\"" << std::endl;
////	assert(ss.str() == initVal);
//	std::cout << val + val << std::endl;
	int maxDigits = std::stoi(av[1]);
	auto v = findFirstFibonacheIndex(maxDigits);
	std::cout << "index of first fibonache with " << maxDigits << " digits: " << v << std::endl;
	return 0;
	
}
