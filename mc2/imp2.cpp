#include "imp2.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

void IMP2::selection(int*** brd, int &i, int &j, int &k){
	int s = size -2;
	srand(time(NULL));
	int max = numeric_limits<int>::min();
	int min = numeric_limits<int>::max();
	
	
	for(int a=0;a<(size-2)*(size-2)*(size-2);a++){
		if(max < winrates[a]) max = winrates[a];
		if(min > winrates[a]) min = winrates[a];
	}
	
	if(rand()%2 ==1 || max-min<=0){
		return MC::selection(brd,i,j,k);
	}
	
	int * arr = new int[(size-2)*(size-2)*(size-2)];
	for(int a=0;a<(size-2)*(size-2)*(size-2);a++){
		arr[a] = winrates[a] - min;
		arr[a] = arr[a] * arr[a];
	}
	
	int range = max-min;
	range= range*range;
	
	int point = rand()%range;
	
	int distance = numeric_limits<int>::max();
	//~ for(int x=0; x<s;x++){
		//~ for(int y=0; y<s;y++){
			//~ for(int z=0; z<s;z++){
				//~ int a = x*s*s + y*s + z;
				//~ if(abs(point-arr[a]) < distance){
					//~ distance = abs(point-arr[a]);
					//~ i=x+1;
					//~ j=y+1;
					//~ k=z+1;
				//~ }
				//~ 
			//~ }
		//~ }
	//~ }
	
	for(int a=0;a<64*2;a++){
		int x,y,z;
		MC::randmove(brd,x,y,z);
		
		int n = (x-1)*s*s + (y-1)*s + (z-1);
		if(abs(point-arr[n]) < distance){
			distance = abs(point-arr[n]);
			i=x;
			j=y;
			k=z;
		}
	}
}
