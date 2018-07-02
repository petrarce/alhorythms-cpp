#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

long long int square_sum(int n){
    long long int res = 0;
    for (int i = 0; i <= n; i++)
        res += (long long int)i*(long long int)i;

    return res;

}

int main(int argc, char** argv)
{
    string str;
    str = argv[1];
    long long int a=0, b=0;

    int n = stoi(str);
    a=square_sum(n);
    cout << a << endl;
    b=(((long long int)pow(n,2)*pow((n+1),2))/4.);
    cout << b << endl;
    cout << b-a << endl;
    return 0;
}