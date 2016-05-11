#ifndef IMP5V2_H
#define IMP5V2_H

#include "imp2.h"
class IMP5V2 : public IMP2
{
protected:

private:
    
public:
	IMP5V2(int *brd, int player, int s):IMP2(brd,player,s){}
	bool selection(int *brd, int &i, int &j, int &k);
};
 
#endif
