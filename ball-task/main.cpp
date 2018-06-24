#include <iostream>
#include <fstream>
#include <vector>
#include "ball.h"

using namespace std;

//inpit data
Coord_t barierSize;
Coord_t startPos;
Coord_t startDir;
vector<int> timeLine;

//output data
Coord_t lastPont;

class test{
	int* a;
public:
	test(){
		cout << "Constructor test" << "\n";
		a = new int[20];
	};
	~test(){
		cout << "Destructor test" << "\n";
		delete [] a;

	};
};
class test1:public test{
	int* b;
public:
	void func(){return; };
	test1(){
		cout << "Constructor test1" << "\n";
		b = new int[20];
	};
	~test1(){
		cout << "Destructor test1" << "\n";
		delete [] b;
	};

};


void parse_file(char* path){
	ifstream f;
	f.open(path, ios::in);
	int strCount = 0;
	string data;

	while(!f.eof()){
		f >> data;

		switch(strCount){
			case 0:
				//set barier size
				barierSize.x = stoi(data.substr(0, data.find(",")));
				barierSize.y = stoi(data.substr(data.find(",")+1, data.length()));
				break;
			case 1:
				//set initial position of the ball
				startPos.x = stoi(data.substr(0, data.find(",")));
				startPos.y = stoi(data.substr(data.find(",")+1, data.length()));
				break;

			case 2:
				//set direction/speed vector
				startDir.x = stoi(data.substr(0, data.find(",")));
				startDir.y = stoi(data.substr(data.find(",")+1, data.length()));
				break;
			default:
				//set timeline parameters
				timeLine.push_back(stoi(data));
				break;
		}
		strCount++;
	}

	f.close();

}

int main(int argc, char** argv)
{

	Ball ball;

	test* a = new test1();

	delete a;
	return 0;

	if (argc < 2){
		cout << "please enter path to file!!!\n";
		return 1;
	}

	parse_file(argv[1]);



	for (int i = 0; i < timeLine.size()-1; i++){
		ball = Ball(startPos, startDir);
		lastPont = ball.GetPosition(barierSize, timeLine[i]*ball.GetSpeed());
		cout << lastPont.x << "," << lastPont.y << "\n";
	}

	return 0;
}

