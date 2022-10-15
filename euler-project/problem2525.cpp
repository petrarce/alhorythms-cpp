#include <iostream>

using namespace std;

void fibonache(int cnt)
{
	std::cout << "fibonache avlues: ";
	size_t a0 = 1;
	size_t a1 = 1;
	std::cout << a0 << ", ";
	if(cnt == 1)
		return;
	std::cout << a1 << ", ";

	for(int i = 1; i < cnt; i++)
	{
		cout <<  a1 + a0<< ", ";
		size_t tmp = a0;
		a0 = a1;
		a1 = a1 + tmp;
	}

}

int main(int argc, char** argv)
{
	fibonache(stoi(argv[1]));
}
