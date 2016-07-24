#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "mc.h"
#include "imp2.h"
#include "imp5.h"
#include "imp6.h"
using namespace std;
const int sideLength = 4;
const int SampleN = 3000;
const int SIZE = sideLength + 2;
const int WALL = sideLength + 1;
const int WINCONDITION = 3;
int turn, adj[SIZE][SIZE][SIZE];

void display (int *brd);
void display (int ***brd);
bool displayWINNER (int turn);
void resetARRAY ();
bool checkWINNER (int turn, int g, int r, int c);
bool checkWINNERar (int turn, int g, int r, int c, int*** board);
int normalizeINPUT (string inp);
int*** copyBoard(int board[SIZE][SIZE][SIZE]);
int*** copyBoard(int ***board);
int* validOption(bool ***board,int len);
bool*** validBoard(int ***board, int &count);
int simulation(int ***board);
int* monteCarlo(int ***board);
int simulation(int ***board);
int whosturn(int turn);
//from above 10 needs hash function

bool is_Lcheckmate(int currentTurn, int ***board, int g, int r, int c);
bool is_Wcheckmate(int currentTurn, int ***board, int g, int r, int c);
bool is_Lcheckmate(int currentTurn, int ***board, int g, int r, int c)
{
  return checkWINNERar(currentTurn+1,g,r,c,board);
}
bool is_Wcheckmate(int currentTurn, int ***board, int g, int r, int c)
{
  return checkWINNERar(currentTurn,g,r,c,board);
}
int main(){
  srand (time(NULL));
  string inp;
  int g,r,c;
  resetARRAY();
  IMP5 AI2(2,&adj[0][0][0],6); 
  while(1) {
    turn++;
    display(&adj[0][0][0]);
        if(turn%2 == 1) //odd for player
      {
        AI2.getAIresponse(g,r,c,1000);
  // cout << "\nPlayer, it's your turn!\n\n";
  // cout<<"Enter grid number ('Q' to Quit) : ";
  // getline (cin,inp);
  // if ((inp[0]=='q')||(inp[0]=='Q')) break;
  // g=normalizeINPUT(inp);
  // if ((g<1)||(g>4)) {cout<<"\nInvalid selection.\n\n";            
  //   turn--;continue;}
                       
  // cout<<"Row number : ";
  // getline (cin,inp);
  // r=normalizeINPUT(inp);
  // if ((r<1)||(r>4)) {
  //   cout<<"\nInvalid selection.\n\n";            
  //   turn--;
  //   continue;
  // }    
  // cout<<"Column number : ";
  // getline (cin,inp);
  // c=normalizeINPUT(inp);
  // if ((c<1)||(c>4)) {
  //   cout<<"\nInvalid selection.\n\n";            
  //   turn--;
  //   continue;
  // }
      }
    else // even for ai
      {
	int*** board;
	board = copyBoard(adj);
	//monteCarlo
	int *grc;
	grc = monteCarlo(board);
	cout << grc[0] << grc[1] << grc[2] << endl;
	g = grc[0], r = grc[1], c = grc[2];
	for(int f=0;f<SIZE;f++) {
	  for(int g=0;g<SIZE;g++) {
	    delete [] board[f][g];
	  }
	  delete [] board[f];
	}
	delete [] board;
	delete [] grc;
      }
    //isOccupied()
    //cout << adj[g][r][c];
    
    if(adj[g][r][c]!=0){
      cout << "\nPlease select an unoccupied square!\n\n";
      turn--;
      continue;
    }
    
    if(turn%2==0){adj[g][r][c] = 2;} // 2 for AI
    else{adj[g][r][c] = 1;} // 1 for player
    //cout << adj[g][r][c];

    if(checkWINNER(turn,g,r,c)) {
      {if(displayWINNER(turn)) break;}
    }

    cout << "\n\n\n";
    
  }
  //display(&adj[0][0][0]);
  return 0;
}

bool checkWINNERar (int turn, int g, int r, int c, int*** board)
{
  int h=1;                   //sets 'h' to either
  if (turn%2==0) h=2;        //Xs or Os to check
     
  int x[sideLength],y[sideLength],z[sideLength];        //variables to store winning coordinates
  x[0]=g;y[0]=r;z[0]=c;      //sets 0 of each to last move
     
  int ct;
  for (int a=1;a<14;a++){    //iterates through all possible directions
    ct=1;                      //each time resetting counter to one 
    int g2=g; int r2=r; int c2=c;
    for (int i=0;board[g2][r2][c2]!=WALL;){
      switch (a) {
      case 1:g2--;break;                //////////////////////
      case 2:g2--;r2--;c2--;break;      //  increments
      case 3:g2--;r2--;break;           //  in each
      case 4:g2--;r2--;c2++;break;      //  possible
      case 5:g2--;c2--;break;           // direction
      case 6:g2--;c2++;break;           //  until 
      case 7:g2--;r2++;c2--;break;      // hitting
      case 8:g2--;r2++;break;           //  a '5'
      case 9:g2--;r2++;c2++;break;      //   
      case 10:c2--;break;               //
      case 11:r2--;c2--;break;          //   
      case 12:r2--;break;               //  
      case 13:r2--;c2++;break;          //////////////////////
      }
      if (adj[g2][r2][c2]==h) {
	x[ct]=g2;y[ct]=r2;z[ct]=c2;
	ct++;}
                 
    }
                 
                 
    g2=g;r2=r;c2=c;   //reset placeholder variables
         
         
    for (int i=0;board[g2][r2][c2]!=WALL;) { 
              
              
      switch (a) {
      case 1:g2++;break;                ///////////////////////
      case 2:g2++;r2++;c2++;break;      //
      case 3:g2++;r2++;break;           // and
      case 4:g2++;r2++;c2--;break;      // then back
      case 5:g2++;c2++;break;           //  in the
      case 6:g2++;c2--;break;           //  opposite 
      case 7:g2++;r2--;c2++;break;      //  direction
      case 8:g2++;r2--;break;           //
      case 9:g2++;r2--;c2--;break;      //
      case 10:c2++;break;               //
      case 11:r2++;c2++;break;          //
      case 12:r2++;break;               //
      case 13:r2++;c2--;break;          ///////////////////////
      }
                                   
      if (board[g2][r2][c2]==h) {
	x[ct]=g2;y[ct]=r2;z[ct]=c2;
	ct++;
      }
    }
    if (ct>=WINCONDITION) {return true;}
  }
  return false;
}

bool checkWINNER (int turn,int g,int r,int c) {
  int h=1;                   //sets 'h' to either
  if (turn%2==0) h=2;        //Xs or Os to check
     
  int x[sideLength],y[sideLength],z[sideLength];        //variables to store winning coordinates
  x[0]=g;y[0]=r;z[0]=c;      //sets 0 of each to last move
     
  int ct;
     
  for (int a=1;a<14;a++){    //iterates through all possible directions
     
    ct=1;                      //each time resetting counter to one 
     
    int g2=g; int r2=r; int c2=c;
           
    for (int i=0;adj[g2][r2][c2]!=WALL;){

      switch (a) {
      case 1:g2--;break;                //////////////////////
      case 2:g2--;r2--;c2--;break;      //  increments
      case 3:g2--;r2--;break;           //  in each
      case 4:g2--;r2--;c2++;break;      //  possible
      case 5:g2--;c2--;break;           // direction
      case 6:g2--;c2++;break;           //  until 
      case 7:g2--;r2++;c2--;break;      // hitting
      case 8:g2--;r2++;break;           //  a '5'
      case 9:g2--;r2++;c2++;break;      //   
      case 10:c2--;break;               //
      case 11:r2--;c2--;break;          //   
      case 12:r2--;break;               //  
      case 13:r2--;c2++;break;          //////////////////////
      }
                        
      if (adj[g2][r2][c2]==h) {
	x[ct]=g2;y[ct]=r2;z[ct]=c2;
	ct++;}
                 
    }
                 
                 
    g2=g;r2=r;c2=c;   //reset placeholder variables
         
         
    for (int i=0;adj[g2][r2][c2]!=WALL;) { 
              
              
      switch (a) {
      case 1:g2++;break;                ///////////////////////
      case 2:g2++;r2++;c2++;break;      //
      case 3:g2++;r2++;break;           // and
      case 4:g2++;r2++;c2--;break;      // then back
      case 5:g2++;c2++;break;           //  in the
      case 6:g2++;c2--;break;           //  opposite 
      case 7:g2++;r2--;c2++;break;      //  direction
      case 8:g2++;r2--;break;           //
      case 9:g2++;r2--;c2--;break;      //
      case 10:c2++;break;               //
      case 11:r2++;c2++;break;          //
      case 12:r2++;break;               //
      case 13:r2++;c2--;break;          ///////////////////////
      }
                                   
      if (adj[g2][r2][c2]==h) {
	x[ct]=g2;y[ct]=r2;z[ct]=c2;
	ct++;
      }
    }
    if (ct>=WINCONDITION) {
      for (int b=0;b<sideLength;b++) {adj[x[b]][y[b]][z[b]]= -1;}
      return 1;
    }
  }
  return 0;
}


void display (int ***board)
{
  int range = sideLength * 2;
  for(int i = 1;i <= sideLength;i++)
    {
      cout << "#" << i << "\t\t";
      if (i == sideLength) cout <<"\n\n\n";
    }
  int n;
  for(int y=1;y<1+sideLength;y++) {
    for(int x=1;x<1+sideLength;x++){
      for(int z=1;z<1+sideLength;z++){
      	switch (board[x][y][z]) {
      	case 0: cout << " ";break;
      	case 1: cout << "X";break;
      	case 2: cout << "O";break;
      	case -1: cout << "t";break;
      	}
  
      	if(z<sideLength) {cout << "|";}
      }
      if(x<sideLength) cout << "\t\t";
    }
    if(y<sideLength) {
      cout << "\n";
      for(int m=1; m<sideLength * range;m++) {
	if(m%range == 0) {cout <<"\t\t";}
	else if(m%2==0) {cout << "+";}
	else cout << "-";
      }
      cout <<"\n";
    }
  }
  cout << "\n\n";
  return;
}
void display(int *brd)
{
  int range = sideLength * 2;
  for(int i = 1;i <= sideLength;i++)
    {
      cout << "#" << i << "\t\t";
      if (i == sideLength) cout <<"\n\n\n";
    }
  int n;
  for(int y=1;y<1+sideLength;y++) {
    for(int x=1;x<1+sideLength;x++){
      for(int z=1;z<1+sideLength;z++){
      	n=((x*SIZE*SIZE)+(y*SIZE)+z);
      	switch (*(brd+n)) {
      	case 0: cout << " ";break;
      	case 1: cout << "X";break;
      	case 2: cout << "O";break;
      	case -1: cout << "t";break;
      	}
  
      	if(z<sideLength) {cout << "|";}
      }
      if(x<sideLength) cout << "\t\t";
    }
    if(y<sideLength) {
      cout << "\n";
      for(int m=1; m<sideLength * range;m++) {
	if(m%range == 0) {cout <<"\t\t";}
	else if(m%2==0) {cout << "+";}
	else cout << "-";
      }
      cout <<"\n";
    }
  }
  cout << "\n\n";
  return;
}

bool displayWINNER (int tn) {
     char yn[100];
     display (&adj[0][0][0]);
     if (tn%2==0) {cout<<"\n\nAI is the winner!!\n\n";}
        else cout<<"\n\nPlayer is the winner!!\n\n";
     return 1;
}
void resetARRAY()
{
  for(int x=0;x<SIZE;x++){
    for(int y=0;y<SIZE;y++){
      for(int z=0;z<SIZE;z++){
	adj[x][y][z] = 0;
      }
    }
  }

  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      adj[0][i][j]=WALL; adj[WALL][i][j]=WALL;
      adj[i][j][0]=WALL; adj[i][j][WALL]=WALL;
      adj[i][0][j]=WALL; adj[i][WALL][j]=WALL;
    }
  }
}

int normalizeINPUT (string inp) {
  int i, q; 
  string n;
  for (int i=0;inp[i] != ' ';i++) n=n+inp[i];
  q=atoi(n.c_str());
  return q;
}

int*** copyBoard(int board[SIZE][SIZE][SIZE])
{
  int*** array3D;
  array3D = new int**[SIZE];
  for(int i=0;i<SIZE;i++) {
    array3D[i] = new int*[SIZE];
    for(int j=0;j<SIZE;j++) {
      array3D[i][j] = new int[SIZE];
      for(int k=0;k<SIZE;k++) {
	array3D[i][j][k] = board[i][j][k];
	}
      }
    }
  return array3D;
}
int*** copyBoard(int ***board)
{
  int*** array3D;
  array3D = new int**[SIZE];
  for(int i=0;i<SIZE;i++) {
    array3D[i] = new int*[SIZE];
    for(int j=0;j<SIZE;j++) {
      array3D[i][j] = new int[SIZE];
      for(int k=0;k<SIZE;k++) {
	array3D[i][j][k] = board[i][j][k];
	}
      }
    }
  return array3D;
}
bool*** validBoard(int ***board, int &count)
{
  bool*** array3D;
  array3D = new bool**[SIZE];
  for(int i=0;i<SIZE;i++) {
    array3D[i] = new bool*[SIZE];
    for(int j=0;j<SIZE;j++) {
      array3D[i][j] = new bool[SIZE];
      for(int k=0;k<SIZE;k++) {
	if(board[i][j][k] ==0) {
	  array3D[i][j][k] = true;
	  count++;
	}
	else array3D[i][j][k] = false;
      }
    }
  }
  return array3D;
}
int* validOption(bool ***board,int len)
{
  int *arr;
  int c = 0;
  arr = new int[len];
  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      for(int k=0;k<SIZE;k++) {
	if(c >=len) break;
	if(board[i][j][k] == true){
	  arr[c] = i*100 + j*10 + k;
	  //cout << arr[c] << endl;
	  c++;
	} 
      }
    }
  }
  return arr;
}
//monte carlo いったんコピーを作ってからいれる
int whosturn(int turn)
{
  if(turn%2==0) return 2;
  else return 1;
}
int simulation(int ***board)
{
  int simTurn=0;
  int gs, rs, cs;
  while(true){

    simTurn++;
    bool ***valid;
    int len = 0;
    int self = whosturn(simTurn);
    valid = validBoard(board,len);
    //cout << "len: " << len << endl;
    if(len==0){
      //cout << "No choice" << endl;
      //cout << "break" << endl;
      break;
    }
    int *option;
    option = validOption(valid, len);
    int pick = rand() % len;
    //cout << "pick " << pick << endl;
    //cout << "option " << option[pick] << endl;
    
    gs = option[pick]/ 100;
    rs = (option[pick] %100) /10;
    cs = option[pick] %10;
    //cout << gs << rs << cs << endl;
    if(adj[gs][rs][cs]!=0){
      cout << "\nPlease select an unoccupied square!\n\n";
      turn--;
      continue;
    }
    if(simTurn%2==0){board[gs][rs][cs] = 2;}
    else{board[gs][rs][cs] = 1;}
    
    if(checkWINNERar(simTurn, gs, rs, cs, board)){break;}
    //display(board);
    //delete zone
    for(int i=0;i<SIZE;i++) {
      for(int j=0;j<SIZE;j++) {
	delete [] valid[i][j];
      }
      delete [] valid[i];
    }
    delete [] valid;
    delete [] option;
  }
  if(!checkWINNERar(simTurn, gs, rs, cs, board)) return 0;
  else if(simTurn % 2 == 0){
    //cout << 1 << endl;
    return 1;
  }
  else {
    //cout << -1 << endl;
    return -1;
  }
  
}
int* monteCarlo(int ***board)
{
  int *grc;
  grc = new int[3];
  bool ***firstvalid;
  int hashlen = 0;
  //definitely hashlen must be initialized!!!
  firstvalid = validBoard(board, hashlen);
  cout << "hashlen: " << hashlen;
  int *hash;
  hash = validOption(firstvalid, hashlen);
  //delete 3d array;
  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      delete [] firstvalid[i][j];
    }
    delete [] firstvalid[i];
  }
  delete [] firstvalid;
  
  int *probarray;
  bool Lmarker = false, Wmarker = false;
  probarray = new int[hashlen];
  for(int i=0; i<hashlen; i++){
    //cout << i << "_______________ New _____________ \n\n\n\n\n" << endl; 
    //tempboardをもう一回つくる
    int ***temp;
    temp = copyBoard(adj);
    probarray[i] = 0;
    int sum =0;
    int fg, fr, fc;
    fg = hash[i]/ 100;
    fr = (hash[i] %100) /10;
    fc = hash[i] %10;
    int Lfg, Lfr, Lfc, Wfg, Wfr, Wfc;
    //tempboardに上３っつを反映して勝ち負けチェック
    if(is_Lcheckmate(turn, temp, fg, fr, fc))
      {
	Lmarker = true;
	Lfg = fg, Lfr = fr, Lfc = fc;
      }
    if(is_Wcheckmate(turn, temp, fg, fr, fc))
      {
	Wmarker = true;
	Wfg = fg, Wfr = fr, Wfc = fc;
	i+=hashlen;
      }
    if(i==hashlen-1){
      if(Lmarker){
	grc[0] = Lfg;
	grc[1] = Lfr;
	grc[2] = Lfc;
      }
      if(Wmarker){
	grc[0] = Wfg;
	grc[1] = Wfr;
	grc[2] = Wfc;
      }
      if(Wmarker||Lmarker){
      //deletepart
	for(int a=0;a<SIZE;a++) {
	  for(int b=0;b<SIZE;b++) {
	    delete [] temp[a][b];
	  }
	  delete [] temp[a];
	}
	delete [] temp;
	//deletepart
	return grc;
      }
    }
	
    //cout << i << ": " <<fg << fr << fc << endl;
    temp[fg][fr][fc] = 2;
    for(int j=0; j<SampleN; j++) {
      int ***newtemp;
      newtemp = copyBoard(temp);
      sum += simulation(newtemp);
      for(int a=0;a<SIZE;a++) {
	for(int b=0;b<SIZE;b++) {
	  delete [] newtemp[a][b];
	}
	delete [] newtemp[a];
      }
      delete [] newtemp;
      //deletepart
    }
    probarray[i] = sum;
    cout << setw(3)<< i << "sum: " << setw(4) << probarray[i] << setw(6) <<hash[i] << endl;
    for(int a=0;a<SIZE;a++) {
      for(int b=0;b<SIZE;b++) {
	delete [] temp[a][b];
      }
      delete [] temp[a];
    }
    delete [] temp;
  }
  int maxp = -(SampleN);
  int maxi = 0;
  for(int i=0; i<hashlen; i++) {
    if(maxp < probarray[i]) {
      maxp = probarray[i];
      maxi = i;
    }
  }
  cout << maxi << endl;
  cout << hash[maxi] << endl;
  delete [] hash;
  delete [] probarray;
  grc[0] = hash[maxi]/ 100;
  grc[1] = (hash[maxi] %100) /10;
  grc[2] = hash[maxi] %10;

  return grc;
 
}



    
