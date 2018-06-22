#include <iostream>
#include <vector>

using namespace std;



class A{
public:
	void ((A::*fnction_A))(void);
	virtual void method(){ cout << "~A";};
};

class B:public A{
public:
	int var;
	void method(){ cout << "~B";};
	void method1();
	void method2();

};


int main(){

	A* aptr;
	B* bptr;
	A a;
	B b;

	cout << sizeof(a) << "\n";
	cout << sizeof(b);



	return 0;
}