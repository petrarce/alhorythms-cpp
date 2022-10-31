#pragma once
#include <iostream>
#include <map>
namespace std
{

template<class T, class P, class T1, class T2>
std::basic_ostream<T, P>& operator<<(std::basic_ostream<T, P>& stream, const std::map<T1, T2>& mapVal)
{
	for(auto [key, val] : mapVal )
		stream << "[" << key << "," << val << "]" << std::endl;
	return stream;
}

template<class T, class P, class Iteratable>
std::basic_ostream<T, P>& operator<<(std::basic_ostream<T, P>& stream, const Iteratable& iteratable)
{
	stream << "[ ";
	for(const auto& v : iteratable)
		stream << v << ", ";
	stream << " ]";
	return stream;
}

}
