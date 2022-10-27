#include <iostream>
#include <regex>
#include <iterator>
#include <fstream>
#include <sstream>

int main(int ac, char** av)
{
	std::ifstream file(av[1]);
	std::string password(av[2]);
	if(! file.is_open())
		throw std::runtime_error("Cannot open " + std::string(av[1]) + " for dectiption");
	std::regex lowerCaseCharsPassword("[a-z][a-z][a-z]");

	if(password.size() != 3)
		throw std::runtime_error("password should consist of 3 signs");

	std::stringstream ss;  ss << file.rdbuf();
	auto fileContent = ss.str();
	std::regex asciiChar("[0-9]+");
	std::sregex_iterator iter_begin(fileContent.begin(),fileContent.end(), asciiChar);
	auto iter_end = std::sregex_iterator();
	std::string coded;
	for(auto i = iter_begin; i != std::sregex_iterator(); i++)
	{
		coded.push_back(std::stoul(i->str()) & 0xff);
		std::cout << static_cast<int>(coded.back()) << std::endl;
	}
	return 0;
}
