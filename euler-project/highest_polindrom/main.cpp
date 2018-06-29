#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int arr[3];
long long int prog_counter = 0;

long long int get_polindr(int arr[3])
{

	long long int val = 0;
	prog_counter++;
	return val = 100001 * arr[0] + 10010 * arr[1] + 1100*arr[2];
}

bool has_two_factors(long long int n)
{
	for(int i = 100; i < 1000; i++, prog_counter+=2){
		prog_counter++;
		if(!(n%i)){
			prog_counter+=2;
			if(n/i < 1000 && n/i > 99)
				return 1;
		}
	}
	return 0;
}


int main(int argc, char** argv)
{
	int i,j,k;
	long long int polindrom;

	for ( i = 9, arr[0] = i; i >= 0; --i, arr[0] = i){
		for ( j = 9, arr[1] = j; j >= 0; j--, arr[1] = j){
			for ( k = 9, arr[2] = k; k >= 0; k--, arr[2] = k){
				polindrom = get_polindr(arr);
				prog_counter++;
				if ( polindrom > 998001){
					continue;
				}
				prog_counter++;
				if (has_two_factors(polindrom)){
					cout << polindrom << "\n" << prog_counter;
					return 0;
				}
			}
		}
	}
	return 0;
}