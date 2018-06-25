#include <iostream>
#include <string>

using namespace std;

int get_sum_of(int divisor, int upper_bound)
{
	int n = upper_bound/divisor;
	int last = upper_bound - upper_bound%divisor;
	int first = divisor;

	return (last - first)*n/2;

}

int main(int argc, char** argv){

	int sum = 0;
	string inp_val = argv[1];
	int n = stoi(inp_val);

	sum = get_sum_of(3,n) + get_sum_of(5,n) - get_sum_of(15,n);
	cout << sum;
}