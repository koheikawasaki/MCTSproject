#ifndef IMP3_H
#define IMP3_H

#include "mc.h"
class IMP3 : public MC
{
protected:

private:
    
public:
	IMP3(int player,int *brd, int s):MC(player,brd,s){
		for(int a=0;a<(size-2)*(size-2)*(size-2);a++){
			winrates[a] = 0;
		}
	}
	

	void selection(int*brd, int &i, int &j, int &k);
};
 
#endif
