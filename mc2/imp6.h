#ifndef IMP6_H
#define IMP6_H

#include "imp2.h"
class IMP6 : public IMP2
{
protected:

private:
    
public:
	IMP6(int player,int *brd, int s):IMP2(player,brd,s){}
	

	void selection(int*brd, int &i, int &j, int &k);
};
 
#endif

