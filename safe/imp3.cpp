#include "imp3.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

void IMP3::selection(int*brd, int &i, int &j, int &k){
	int s = size -2;
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
	}
	
	int range = max-min;
	
	while(true){
		int x,y,z;
		MC::randmove(brd,x,y,z);
		if(arr[MC::addr(x,y,z)]>=range/16){
			i=x;
			j=y;
			k=z;
			return;
		}
	}
}
