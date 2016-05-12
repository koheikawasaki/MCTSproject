#ifndef IMP5_H
#define IMP5_H

#include "mc.h"
class IMP5 : public MC
{
protected:

private:
    
public:
	IMP5(int *brd, int player, int s):MC(brd,player,s){}
	bool selection(int *brd, int &i, int &j, int &k);
};
 
#endif
