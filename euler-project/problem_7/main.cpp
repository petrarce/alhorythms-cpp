#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

bool check_prime(long long int n){
    if(!(n%3))
        return 0;

    for(long long int prime = 5; prime < (long long int)sqrt(n); prime+=6)
        if(!(n%prime) || !(n%(prime+2)))
            return 0;
        
    return 1;
}

int main(int argc, char** argv)
{
    string str = argv[1];
    long long int n = 7;
    for(long long int count = 3; count < stoi(str);n+=2)
        if(check_prime(n))
            count++;
    cout << n-2;

    return 0;
}