
#include "imp5.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

void IMP5::selection(int *brd, int &i, int &j, int &k){
    int s = size-2;
    int enemy = ((player-1)%2)+1;

    for(int x=1;x<size-1;x++){
        for(int y=1;y<size-1;y++){
            for(int z=1;z<size-1;z++){
                int n = x*size*size + y*size + z;
                if (brd[MC::addr(x,y,z)] == 0){
                    if(MC::win(enemy,brd,x,y,z)){
                        int n = (x-1)*s*s + (y-1)*s + (z-1);
                        winrates[n] += 100;
                        i=x;
                        j=y;
                        k=z;
                        return;
                    }
                }
            }
        }
    }
    MC::selection(brd,i,j,k);
    return;
}
