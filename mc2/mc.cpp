#include "mc.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>


#include <time.h>

using namespace std;

MC::MC(int p, int* brd, int s){
	size = s;
	sz = size - 2;
	player = p;
	boardpt = brd;
	winrates = new int[sz*sz*sz];
}

MC::~MC(){
	delete [] winrates;
}

void MC::selection(int *** brd, int &i, int &j, int &k){
	int *** internalboard = copyBoard(boardpt);
	randmove(brd,i,j,k);
	
	for(int x=0;x<size;x++){
		for(int y=0;y<size;y++){
			delete internalboard[x][y];
		}
		delete internalboard[x];
	}
	delete internalboard;
}

int MC::simulation(int *** brd, int i, int j, int k){
	srand(time(0));
	int bp = 0;
	int turn = player;
	bool winner = false;
	
	brd[i][j][k] = turn;
	if(win(player,brd,i,j,k))
		return 1;
		
	while(!fullboard(brd) && !winner){
		if(turn==2)
			turn=1;
		else 
			turn=2;
		
		int x,y,z;
		randmove(brd,x,y,z);
		brd[x][y][z] = turn;
		
		if(win(turn,brd,i,j,k)){
			winner = true;
			if(turn == player)
				bp = 1;
			else
				bp = -1;
		}
	}
	
	return 0;
}

void MC::getAIresponse(int &i, int &j, int &k, int sample){
	int max = numeric_limits<int>::min();
	
	while(sample-- > 0){
		int x,y,z;
		int *** internalboard = copyBoard(boardpt);
		selection(internalboard,x,y,z);
		int result = simulation(internalboard,x,y,z);
		int n = x*sz*sz+y*sz+z;
		winrates[n] += result;
		if(max < winrates[n]){
			max = winrates[n];
			i=x; j=y; k=z;
		}
		
		
		for(x=0;x<size;x++){
			for(y=0;y<size;y++){
				if(internalboard[x][y])
					delete internalboard[x][y];
			}
			if(internalboard[x])
				delete internalboard[x];
		}
		if(internalboard)
			delete internalboard;
	}
	
	for(int a=0; a<sz*sz*sz;a++)
		winrates[a] = 0;
}

//helpers

int*** MC::copyBoard(int *board)
{
	int*** array3D;
	array3D = new int**[size];
	for(int i=0;i<size;i++) {
		array3D[i] = new int*[size];
		for(int j=0;j<size;j++) {
			array3D[i][j] = new int[size];
			for(int k=0;k<size;k++) {
				int n = i*size*size + j*size + k;
				array3D[i][j][k] = *(board+n);
			}
		}
	}
	return array3D;
}

bool MC::fullboard(int ***brd){
	for(int i=1;i<sz+1;i++) {
		for(int j=1;j<sz+1;j++) {
			for(int k=1;k<sz+1;k++) {
				if(brd[i][j][k] == 0)
					return false;
			}
		}
	}
	return true;
}

void MC::randmove(int ***brd,int &i,int &j,int &k){
	do{
		i = rand()%sz + 1;
		j = rand()%sz + 1;
		k = rand()%sz + 1;
	}while( brd[i][j][k] != 0);
}

bool MC::win(int turn, int*** brd, int i, int j, int k){
	int sum = -1;
	for (int x=0;x<2;x++)
		for (int y=0;y<2;y++)
			for (int z=0;z<2;z++){
				if(!(x==0 && y==0 && z==0)){
					sum = -1;
					sum += checker(turn,brd,i,j,k,x,y,z);
					sum += checker(turn,brd,i,j,k,-x,-y,-z);
					if(sum == sz)
						return true;
				}
			}
	return false;
}

int MC::checker(int turn, int*** brd, int i, int j, int k, int id, int jd, int kd){
	
	if (brd[i][j][k] == 5 || brd[i][j][k] != turn)
		return 0;
		
	return 1 + checker(turn,brd,i+id,j+jd,k+kd,id,jd,kd);
}
