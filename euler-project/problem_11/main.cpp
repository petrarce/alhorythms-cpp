#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "lib_euler_project.h"

using namespace std;

int count_factors(vector<prime_factor_entire_t> & local_primes_db){

    uint64_t sum1 = 0, sum2 = 0;

    for (int i = 0; i < local_primes_db.size(); i++)
        sum1 += local_primes_db[i].count;

    for (int i = 0; i < local_primes_db.size() - 1; i++){

        uint64_t sum3 = 0, mult1;

        for (int j = i+1; j < local_primes_db.size(); j++)
            sum3+=local_primes_db[j].count;

        mult1=local_primes_db[0].count;
        for (int k = 1; k < i; k++)
            mult1*=local_primes_db[k].count;

        sum2+=(i+1)*sum3*mult1;

    }

    return sum1+sum2+1;


}

int main(int argc, char** argv)
{
    vector<prime_factor_entire_t> primes_db;
    uint64_t max_factors = 0, count = 0;
    uint64_t triangle = 28;

    for (uint64_t i = 8; ; i++){

        triangle += i;
        cout << "triangle " << i << ":" << triangle << endl;
        get_prime_factors(triangle, primes_db);      
        count = count_factors(primes_db); 

        cout << "divisors:" << count;

    }

    return 0;

}