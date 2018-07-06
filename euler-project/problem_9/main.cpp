#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Recursive function to return gcd of a and b
int gcd(int a, int b)
{
    // Everything divides 0 
	while(a != b && a*b)
		if (a > b)
			a-=b;
		else
			b-=a;

	return (a*b)?a:0;
}

int main(int argc, char** argv)
{
	int m,n;
	for(m = 1; m < sqrt(500); m++){
		for (n = (!(m%2))?1:2; n < m; n+=2){
			if ((pow(m,2)+ m * n) == 500){
				cout << "m=" << m << " n=" << n << endl;
				cout << (long long int)(pow(m,4)-pow(n,4))*2*m*n << endl;
			}
		}
	}

	return 0;
}