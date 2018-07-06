#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "lib_euler_project.h"

using namespace std;

//finds all prime factors with their power
//ARGS:
//  local_factor_db -   list of primes and their power represented in prime_factor_entire_t structure
//  n               -   value, from which prime values should be extracted 
void get_prime_factors(uint64_t n, vector<prime_factor_entire_t> & local_factor_db)
{

    local_factor_db.clear();

    if(!(n%2))
            local_factor_db.push_back({2,0});
    while(!(n%2)){
            local_factor_db.back().count++;
            n/=2;
    }



    for (int i = 3; n>1 ; i+=2){

        if(!(n%i)){
            local_factor_db.push_back({i,0});
        }
        while(!(n%i)){
            local_factor_db.back().count++;
            n/=i;
        }
    }
}