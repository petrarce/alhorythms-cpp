#include <iostream>
#include <vector>

using namespace std;

enum Connect_alhors_e{
	QUICK_FIND = 1,
	QUICK_UNION,
	QUICK_UNION_WEIGHTED
};

class Connectivity{
private:
	vector<int> array;
	vector<int> veights;

private:
	void (Connectivity::*connect_alhor)(int, int);
	void quick_find(int, int);
	void quick_union(int, int){};
	void quick_union_weighted(int, int){};
	void init_array(int );

public:
	void print_conect_list();
	void process_connect_list();
};

void Connectivity::process_connect_list()
{
	vector<int> list1;
	vector<int> list2;
	unsigned int N;
	unsigned int M;
	unsigned char alh = 0;

	cout << "enter number of elements" << endl;
	cin >> N;

	cout << "enter number of connections" << endl;
	cin >> M;
	list1.resize(M);
	list2.resize(M);



	cout << "which algo should be used (1 - QUICK_FIND, 2 - QUICK_UNION, 3 - QUICK_UNION_WEIGHTED): ";
	cin >> alh;
	alh -= '0';
	switch(alh){
		case QUICK_FIND:
			connect_alhor = &Connectivity::quick_find;
			break;
		case QUICK_UNION:
			connect_alhor = &Connectivity::quick_union;
			break;
		case QUICK_UNION_WEIGHTED:
			connect_alhor = &Connectivity::quick_union_weighted;
			break;
		default:
			cout << "FALURE: 1, 2 or 3 values are valid only";
			return;
			break;
	}

	for (int i = 0; i < M; ++i){
		cout << "enter set " << i << "\n";
		cout << "element "; cin >> list1[i];
		cout << "is connected to "; cin >> list2[i];
	}

	for (int i = 0; i < M; ++i)
		cout << list1[i] << " is connected to " << list2[i] << "\n";


	init_array(N);

	for(int i = 0; i < M; i++){
		int el1 = list1[i];
		int el2 = list2[i];
		(this->*connect_alhor)(el1, el2);
	}
}

void Connectivity::quick_find(int el1, int el2){

	if(array[el1] == array[el2])
		return;

	for(int i = 0; i < array.size(); i++){
		if(array[i] == array[el1] && i != el1)
			array[i] = array[el2];
	}
	array[el1] = array[el2];

}

void Connectivity::print_conect_list(){
	for (int i = 0; i < array.size(); i++)
		cout << array[i];
}

void Connectivity::init_array(int size)
{
	int i;
	array.resize(size);
	for (i = 0; i < array.size(); ++i){
		array[i] = i;
	}
}
/*DEBUGGING
int main(){
	Connectivity obj1;

	obj1.process_connect_list();
	obj1.print_conect_list();
}
*/