#include <iostream>
#include <vector>

using namespace std;

/*typedef struct {
    int val;
    int count;
} result_t;


class Solution {
public:

    vector<int> topKFrequent(vector<int>& nums, int k) {
        //get first val of elem
        int current = nums[0];
        int counter = 1;
        int resIndex = 0;
        result_t* result_arr = new result_t[nums.size()];
        
        
        for (int i = 1; i < nums.size(); i++){
            if (nums[i] == current){
                counter++;
            } else {
                result_arr[resIndex].val = current;
                result_arr[resIndex].count = counter;   
                current = nums[i];
                counter = 0;
            }
        }
        
        for (int i = 0; i < resIndex; i++){
            for (int j = i+1; j < resIndex; j++){
                if(result_arr[j].count > result_arr[i].count){
                    result_t temp = result_arr[i];
                    result_arr[i] = result_arr[j];
                    result_arr[j] = temp;    
                }   
            }
        }
        
        delete[] result_arr;
    }
};*/

int main()
{
	/*Solution obj;
    int temp_arr[6] = {5,5,5,3,1,2};
	vector<int> nums(temp_arr, temp_arr + sizeof(temp_arr));
	obj.topKFrequent(nums, 2);
    cout << "Hello World";*/

    int* array = new int[20];
    for (int i = 0; i < 20; i++){
        cout << array[i]; 
    }

    delete array;

    return 0;

}