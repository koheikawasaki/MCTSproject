#include "mc.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>


#include <time.h>

using namespace std;


MC::MC(int p, int * brd, int s){
	srand(time(0));
	player = p;
	size = s;
	innersize = s-2;
	boardpt = brd;
	winrates = new int[innersize*innersize*innersize];
	for(int a=0;a<innersize*innersize*innersize;a++){
		winrates[a] = 0;
	}
}
MC::~MC(){
	delete [] winrates;
}

void MC::selection(int &i, int &j, int &k){
	randmove(boardpt,i,j,k);
}
int MC::simulation(int  *** brd, int i, int j, int k){
	
	int bp = 0;
	int turn = player;
	brd[i][j][k] = turn;
	if(win(player,brd,i,j,k)){
		return 1;
	}
	
	bool winner = false;
	int x,y,z;
	while(!(fullboard(brd) || winner)){
		if (turn==2) 
			turn=1;
		else
			turn=2;
		
				
		randmove(brd,x,y,z);
		brd[x][y][z] = turn;
		
		
		if(win(turn,brd,x,y,z)){
			winner = true;
			if(turn == player) 
				bp = 1;
			else
				bp = -1;
		}
	}
	
	return bp;
}
void MC::getAIresponse(int &i, int &j, int &k, int sample){
	
	int *** tempboard;
	while(sample-- >= 0){
		//~ cout << "sampling" << endl;
		int x,y,z;
		tempboard = copyboard(boardpt);
		selection(x,y,z);
		int result = simulation(tempboard,x,y,z);
		winrates[x*innersize*innersize + y*innersize + z] += result;
		
		for(int x=0; x<size; x++){
			for(int y=0; y<size; y++){
				delete[] tempboard[x][y]; 
			}
			delete[] tempboard[x];
		}
		delete[] tempboard;
		
	}
	
	
	
	int max = numeric_limits<int>::min();
	for(int x=0;x<innersize;x++){
		for(int y=0;y<innersize;y++){
			for(int z=0;z<innersize;z++){
				int a = x*innersize*innersize + y*innersize + z;
				if(max < winrates[a]){
					max = winrates[a];
					i=x+1; j=y+1; k=z+1;
				}
			}
		}
	}
	
	for(int a=0;a<innersize*innersize*innersize;a++){
		winrates[a] = 0;
	}
	
}

// Helper Functions

void MC::randmove(int *** brd, int &i, int &j, int &k){
	int x,y,z;
	do{
		x = rand()% (innersize) + 1;
		y = rand()% (innersize) + 1;
		z = rand()% (innersize) + 1;
	}while(brd[x][y][z] != 0);
	i=x; j=y; k=z;
}

void MC::randmove(int * brd, int &i, int &j, int &k){
	int x,y,z,n;
	do{
		x = (rand()% innersize) + 1;
		y = (rand()% innersize) + 1;
		z = (rand()% innersize) + 1;
		n = x*size*size + y*size + z;
	}while(*(brd+n) != 0);
	i=x; j=y; k=z;
}


bool MC::fullboard(int *** brd){
	for(int x=1;x<size-1;x++)
		for(int y=1;y<size-1;y++)
			for(int z=1;z<size-1;z++)
				if(brd[x][y][z] == 0)
					return false;
	return true;
}
int *** MC::copyboard(int *board){
	int ***  array3D;
	array3D = new int**[size];
	for(int i=0;i<size;i++) {
		array3D[i] = new int*[size];
		for(int j=0;j<size;j++) {
			array3D[i][j] = new int[size];
			for(int k=0;k<size;k++) {
				int a = i*size*size + j*size + k;
				array3D[i][j][k] = *(board+a);
			}
		}
	}
	return array3D;
}
bool MC::win(int turn, int *** brd, int i, int j, int k){
	int sum;
	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
			for(int z=0;z<2;z++)
				if(!(x==0 && y==0 && z==0)){
					sum = -1;
					sum += winchecker(turn,brd,i,j,k,x,y,z);
					sum += winchecker(turn,brd,i,j,k,-x,-y,-z);
					if(sum >= innersize)
						return true;
				}
	return false;			
}
int MC::winchecker(int turn, int *** brd, int i, int j, int k, int idir, int jdir, int kdir){
	if(brd[i][j][k] == 5 || brd[i][j][k] != turn)
		return 0;
	return 1 + winchecker(turn,brd,i+idir,j+jdir,k+kdir,idir,jdir,kdir);
}
