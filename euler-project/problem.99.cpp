#include <iostream>
#include <gcd.hpp>
#include <InfInt.h>
#include <fstream>
#include <cmath>
#include <absl/strings/str_format.h>
#include <absl/strings/str_split.h>

struct ExpNumber {
    uint64_t base{0};
    uint64_t exp{1};
    InfInt value(bool vbs = false) const;
    bool operator>(const ExpNumber& b) const
    {
        return this->exp > b.exp * std::log2(b.base) / std::log2(this->base);
    }
};

std::ostream& operator<<(std::ostream& ostr, const ExpNumber& val)
{
    ostr << "{" << val.base << "^" << val.exp << "}";
    return ostr;
}

InfInt ExpNumber::value(bool vbs) const
{
    InfInt v = base;
    for(int i = 0; i < exp; i++)
    {
        v *= base;
        if(vbs)
            std::cout << *this << ": " << v.toString() << std::endl;
    }
    return v;
}

std::pair<ExpNumber, ExpNumber> stripCommonBase(const ExpNumber& a, const ExpNumber& b, bool vbs = false)
{
    const auto baseGcd = libcore::math::gcd(a.base, b.base);
    const auto expGcd = libcore::math::gcd(a.exp, b.exp);
    if (vbs)
        std::cout << "baseGfc, expGcd:" << baseGcd << "," << expGcd << std::endl;
    return {
        ExpNumber{ a.base / baseGcd, a.exp / expGcd },
        ExpNumber{b.base / baseGcd, b.exp / expGcd }
    };
}

int main(int argc, char** argv)
{

    std::ifstream f(argv[1]);
    if(!f.is_open())
        throw std::runtime_error(absl::StrFormat("cannot open file %s",  argv[1]));
    std::stringstream ss;
    ss << f.rdbuf();
    std::vector<std::string> items = absl::StrSplit(ss.str().c_str(), '\n');
    if(items.empty())
        throw std::runtime_error("empty input values");
    ExpNumber largest;
    int largestLN = -1;
    int traversedLines = 0;
    std::for_each(items.begin(), items.end(), [&](const std::string& item) {
        const std::vector<std::string> expVal = absl::StrSplit(item.c_str(), ",");
        if(expVal.size() != 2)
            return;

        try {
            ExpNumber n{std::stoull(expVal[0]), std::stoull(expVal[1])};
            if(n > largest)
            {
                largest = n;
                largestLN = traversedLines;
            }
            traversedLines++;
        }
        catch(const std::exception& e)
        {
            std::cout << "Failed to access value:" << expVal[0] << "," << expVal[1];
            return;
        }
    });
    std::cout << "LargestItem/LineNumber: " << largest << "/" << largestLN << std::endl;
    return 0;
}
