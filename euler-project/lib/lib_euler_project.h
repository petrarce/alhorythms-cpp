#ifndef LIB_EULER_PROJECT_H
#define LIB_EULER_PROJECT_H
#include <vector>

using namespace std;

typedef struct{
    uint64_t prime_factor;
    uint64_t count;
} prime_factor_entire_t;


void get_prime_factors(long long int n, vector<prime_factor_entire_t> & local_factor_db);
#endif //LIB_EULER_PROJECT_H