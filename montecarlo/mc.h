#ifndef MC_H
#define MC_H
 
class MC
{
	
protected:
	int * winrates;
    int * boardpt;
    
    int innersize;
    int size;
    int player;
private:
	
public:
	MC(int player, int *brd, int s);
	~MC();
	
	virtual void selection(int &i, int &j, int &k);
	virtual int simulation(int *** brd, int i, int j, int k);
	virtual void getAIresponse(int &i, int &j, int &k, int sample);
	
	//helper functions
	void randmove(int *** brd, int &i, int &j, int &k);
	void randmove(int *brd, int &i, int &j, int &k);
    bool fullboard(int *** brd);
    int*** copyboard(int * brd);
    bool win(int turn, int *** brd, int i, int j, int k);
    int winchecker(int turn, int *** brd, int i, int j, int k, int idir, int jdir, int kdir);
	
};
 
#endif
