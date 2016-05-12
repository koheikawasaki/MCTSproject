#ifndef MC_H
#define MC_H
 
class MC
{
	
protected:
	int * winrates;
    int * boardpt;
    
    int sz;
    int size;
    int player;
private:
	
public:
	MC(int player, int *brd, int s);
	~MC();
	
	virtual void selection(int *** brd, int &i, int &j, int &k);
	virtual int simulation(int *** brd, int i, int j, int k);
	virtual void getAIresponse(int &i, int &j, int &k, int sample);
	
	//helper functions
	int*** copyBoard(int *board);
	void randmove(int***,int&,int&,int&);
	int* addr(int* brd,int i,int j,int k);
	bool win(int turn, int*** brd, int i, int j, int k);
	int checker(int turn, int*** brd, int i, int j, int k, int id, int kd, int jd);
	bool fullboard(int ***brd);
};
 
#endif
