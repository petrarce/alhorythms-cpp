#include <iostream>
#include <array>

using namespace std;

std::array<uint8_t, 12> mpd = {
	31/*Jan*/, 
	28/*Feb*/, 
	31/*Mar*/, 
	30/*Apr*/, 
	31/*Maj*/, 
	30/*Jun*/, 
	31/*Jul*/,
	31/*Aug*/,
	30/*Sep*/,
	31/*Oct*/,
	30/*Nov*/,
	31/*Dec*/ 
};

int main()
{
	int day = 366;
	int sundays = 0;
	for(int i = 1; i <= 100; i++)
	{

		std::cerr << "Januarry " 
			<< std::to_string(1900 + i) 
			<< ": " << ((day % 7 == 0) ? 
					7 : 
					day % 7) << std::endl;
		for(int j = 0; j < 12; j++)
		{
			if(day % 7 == 0)
				sundays ++;
			
			day += (j == 1 && (i % 4) == 0 && !(i%100 == 0 && !(i%400 == 0))) ? 					mpd[j] + 1 : 
				mpd[j];
		}

	}	
	std::cerr << "Number of sundayes: "<< sundays << std::endl;
	return 0;
}
