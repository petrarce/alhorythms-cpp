#ifndef TYPES_H
#define TYPES_H
#include <cmath>

using namespace std;

//#define DEBUG

#ifdef DEBUG
#include "stdio.h"
#define dbg_print(str, args...) printf("%s:%d: " str "\n", __FILE__, __LINE__ , str, ##args)
#else
#define dbg_print(str, args...)
#endif

struct Coord{
	double x;
	double y;
};
typedef struct Coord Coord_t;

static double custom_round(double val, int exp)
{
	double temp = round(val*exp); 
	return temp/exp;
}

#endif //TYPES_H