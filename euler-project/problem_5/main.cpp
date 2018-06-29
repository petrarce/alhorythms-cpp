#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef struct{
    long long int prime_factor;
    long long int count;
} prime_factor_entire_t;

class Factor_db{
private:
    vector<prime_factor_entire_t> factor_db;
public:

    void update_factor_db(vector<prime_factor_entire_t> & factor_db){

        int i, j;
        
        for ( i = 0; i < factor_db.size(); i++){
            for (j = 0; j < this->factor_db.size(); j++){
                if(factor_db[i].prime_factor == this->factor_db[j].prime_factor){
                    if(factor_db[i].count > this->factor_db[j].count)
                        this->factor_db[j].count = factor_db[i].count;
                    break;
                }
            }

            //insert new element into back of the database if not faound
            if(j ==  this->factor_db.size())
                this->factor_db.push_back(factor_db[i]);
        }
    }

    void print_factor_db(){
        for (int i = 0; i < factor_db.size(); i++)
            cout << factor_db[i].prime_factor << " - " << factor_db[i].count << "\n";
    }

    void print_factor_db(vector<prime_factor_entire_t> & factor_db){
        for (int i = 0; i < factor_db.size(); i++)
            cout << factor_db[i].prime_factor << " - " << factor_db[i].count << "\n";
    }

    long long int print_minimum_factorised(){

        long long int val = 1;

        for (int i = 0; i < factor_db.size(); i++)
            val *= pow(factor_db[i].prime_factor, factor_db[i].count);

        return val;
    }


};


int get_prime_factors(long long int n, vector<prime_factor_entire_t> & local_factor_db)
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


int main(int argc, char** argv)
{
    Factor_db factor_db_obj;
    vector<prime_factor_entire_t> local_factor_db;
    string str = argv[1];

    for(int i = 2; i <= stoi(str); i++){
        cout << "iteration =======" << i << "\n"; 
        get_prime_factors(i, local_factor_db);
        factor_db_obj.update_factor_db(local_factor_db);
        factor_db_obj.print_factor_db();

    }
    cout << factor_db_obj.print_minimum_factorised();
    //cout << factor_db_obj.print_minimum_factorised();
}