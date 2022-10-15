#include <iostream>
#include <vector>
#include <cassert>

std::vector<std::string> once =
{
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

std::vector<std::string> tens = {
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety"
};

std::vector<std::string> ten_nineteen = {
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen"
};

std::string generateNumber(int i)
{
	assert(i < 1000 && i >= 1);
	std::string num;
	if(i >= 100)
	{
		num += once[i/100 - 1] + "hundred";
		i %= 100;
		if(i != 0)
			num += "and";
	}

	if(i >= 20)
	{
		num += tens[i/10 - 2];
		i %= 10;
	}
	else if(i >= 10)
	{
		num += ten_nineteen[i%10];
		return num;
	}

	if(i >= 1)
	{
		num +=  once[i - 1];
	}
	return num;


}



int main()
{
	std::string fullString;
	for(int i = 1; i < 1000; i++)
		fullString += generateNumber(i);
	fullString += "onethousand";
	std::cout << fullString << " fullString.size: " << fullString.size();
	return 0;
}
