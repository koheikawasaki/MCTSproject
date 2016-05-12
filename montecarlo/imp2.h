#ifndef IMP2_H
#define IMP2_H

#include "mc.h"
class IMP2 : public MC
{
protected:

private:
    
public:
	IMP2(int *brd, int player, int s):MC(brd,player,s){
		for(int a=0;a<(size-2)*(size-2)*(size-2);a++){
			winrates[a] = 0;
		}
	}
	

	bool selection(int &i, int &j, int &k);
};
 
#endif
