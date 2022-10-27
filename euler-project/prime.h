#pragma once
#include <math.h>

bool testPrime(const size_t val)
{

	if(val % 2 == 0 || val % 3 == 0)
		return false;

	for( int cv = 5; cv * cv <= val; cv += 6)
		if (val % cv == 0 || val % (cv + 2) == 0)
			return false;

	return true;
}
