#include <iostream>
#include <cmath>
#include "types.h"
#include "ball.h"

using namespace std;



struct CurPointLength{
	Coord_t pt;
	Coord_t dir;
	double length;
};
typedef struct CurPointLength CurPointLength_t;

#define EPS 0.0001

Coord_t decartStart{0,0};
Coord_t oxVect{0,1};
Coord_t oyVect{1,0};


Ball::Ball(Coord_t startPos, Coord_t startDir)
{

	curPos = startPos;
	speed  = sqrt(pow(startDir.x,2) + pow(startDir.y,2));
	curDir.x = startDir.x / speed;
	curDir.y = startDir.y / speed;
}

Coord_t Ball::GetPosition(Coord_t & box, double length)
{
	Shot(box);
	dbg_print("curPos:%f, %f", curPos.x, curPos.y);
	while(!CheckLength(length)){
		ChangeDir(box);
		dbg_print("curDir:%f, %f", curDir.x, curDir.y);
		Shot(box);
		dbg_print("curPos:%f, %f", curPos.x, curPos.y);
		dbg_print("nextIteration***");
	}

	FixEndpoint(length);
	dbg_print("Fixed length:%f, %f", curPos.x, curPos.y);

	return curPos;
}

bool Ball::CheckLength(double targLength)
{

	if (currLength < targLength)
		return 0;
	
	return 1;
}

void Ball::Shot(Coord_t & box)
{
	//for all walls do:
	CurPointLength_t points[4];
	
	//find all  crossig points
	points[0].pt = CrossPoint(decartStart,	curPos, oxVect, curDir);
	points[1].pt = CrossPoint(decartStart,	curPos, oyVect, curDir);
	points[2].pt = CrossPoint(box,			curPos, oxVect, curDir);
	points[3].pt = CrossPoint(box,			curPos, oyVect, curDir);

	//find all length from current to crossng point
	for(int i = 0; i < 4; i++){
		points[i].length = sqrt(
								pow(curPos.x - points[i].pt.x,2) +
								pow(curPos.y - points[i].pt.y,2)
							);
		points[i].dir.x = points[i].pt.x - curPos.x;
		points[i].dir.y = points[i].pt.y - curPos.y;
	}

	
	//sort all points by length from lowst to highest.
	//use boble for sorting
	for (int i = 0; i < 4; i++){
		for (int j = i+1; j < 4; j++){
			if (points[i].length > points[j].length){
				CurPointLength_t temp;
				temp = points[i];
				points[i] = points[j];
				points[j] = temp;
			}
		}
	}

	//Determine which vectors are semidirectional
	for (int i = 0; i < 4; i++){

		if(	points[i].dir.x*curDir.x < 0 ||  
			points[i].dir.y*curDir.y < 0 ||
			points[i].pt.x == curPos.x && points[i].pt.y == curPos.y)
				continue;

		curPos = points[i].pt;
		currLength += points[i].length;
		//cout << "new Position: " << curPos.x << "," << curPos.y << "\n";
		//cout << "currLength: " << currLength << "\n";
		return;
	}

}

void Ball::ChangeDir(Coord_t & box)
{
	// check situation of the corner
	// TODO: make overload of "==" for Coord_t structure
	if (curPos.x == box.x && curPos.y == box.y ||
		curPos.x == 0 && curPos.y == box.y ||
		curPos.x == box.x && curPos.y == 0 ||
		curPos.x == 0 && curPos.y == 0){
		curDir.x *= -1;
		curDir.y *= -1;

	}else if (curPos.x == box.x || curPos.x == 0)
		curDir.x *= -1;
	else
		curDir.y *= -1;

	//cout << "new Direction: " << curDir.x << "," << curDir.y << "\n";

}

void Ball::FixEndpoint(double targLength)
{

	double deltaLength = currLength - targLength;
	curPos.x = curPos.x - curDir.x*deltaLength;
	curPos.y = curPos.y - curDir.y*deltaLength;

	curPos.x = round(curPos.x);
	curPos.y = round(curPos.y);
	//cout << "Fixing endpoint: " << curPos.x << "," << curPos.y << "\n";

}

Coord_t Ball::CrossPoint(Coord_t & p1, Coord_t & p2, Coord_t & vp1, Coord_t & vp2)
{
	Coord_t res;

	//TODO: case: vectors are kolinear
	//TODO: 	case: points belongs to the same line 
	//TODO:		case: points belongs to paralel lines
	//TODO: case: points are the same

	res.y = -1*
			(
				vp2.y*(p1.x * vp1.y - p1.y*vp1.x)-
				vp1.y*(p2.x * vp2.y - p2.y*vp2.x)
			) /
			(
				vp1.x*vp2.y -
				vp2.x*vp1.y
			);
	res.x = -1*
			(
				vp2.x*(p1.x * vp1.y - p1.y*vp1.x)-
				vp1.x*(p2.x * vp2.y - p2.y*vp2.x)
			) /
			(
				vp1.x*vp2.y -
				vp2.x*vp1.y
			);

	/*result of calculation can have a deviation,
		in this case if calculated point is the same, as current position, 
		it will not be identified, and program will run in infinit cycle
		TODO: make more liable solution  
	*/
	res.x = custom_round(res.x, 100);
	res.y = custom_round(res.y, 100);

	return res;
}

double Ball::GetSpeed(){
	return speed;
}