#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <chrono>
using namespace std;

#include <iostream>
using namespace std;

bool is_prime(uint64_t n){

    if(!(n%2) || !(n%3))
        return 0;

    for (uint64_t i = 5; i*i <= n; i+=6)
        if(!(n%i) || !(n%(i+2)))
            return 0;

    return 1;
}

uint64_t get_sum(uint64_t n){
    uint64_t sum = 5;
    uint64_t pr, j, i;
    for( i = 0, pr = 5; pr < n ; pr+=2, i++){

        if(is_prime(pr))
            sum += pr;

#ifdef DEBUG
        if(!(i%1000)){
            cout << pr << endl;
            cout << sum << endl << endl;
        }
#endif

    }
    return sum;

}

uint64_t get_prime_erathosphen(vector<uint64_t> & v, uint64_t n){

    uint64_t sum = 0;

    for(uint64_t i = 0; i < v.size(); i++ ){
        if (v[i] == 0)
            continue;

        for(uint64_t j = 2; j * v[i] < n; j++)
            v[j*v[i]-2] = 0;
    }

    for (uint64_t i = 0; i < v.size(); i++)
        sum += v[i];

    return sum;
}



int main(int argc, char** argv)
{

    std::chrono::time_point<std::chrono::system_clock> start, end;

    string str = argv[1];
    uint64_t n = stoi(str);
    vector<uint64_t> primes(n-2, 0);
    for(uint64_t i = 0; i < primes.size(); i++)
        primes[i] = i + 2;
    start = std::chrono::system_clock::now();
    if(argv[2][0] == '1')
        cout << get_prime_erathosphen(primes, n) << endl;
    else
        cout << get_sum(n) << endl;
    end = std::chrono::system_clock::now();

    int msec = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    cout << "duration: " << msec << endl;



    return 0;
}