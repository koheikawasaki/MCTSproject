#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h> 

using namespace std;
int flagmaker(int svx, int svy);
int * modmaker(int flag);
bool is_checked(int cX, int cY, int x, int y);
bool is_div1(int cX, int cY, int x, int y);
bool is_div2(int cX, int cY, int x, int y);
int * diff(int x1, int y1, int x2, int y2);
int distance(int x1, int y1, int x2, int y2);
// int diff(int x1, int x2, int 
int * direction(int x1, int y1, int x2, int y2, double angl, int r);
int * diff(int vx1, int vy1, int vx2, int vy2) {
    int big = distance(vx1, vx1, vx2, vy2);
    if(big > 300) {
        
}
bool is_div1(int cX, int cY, int x, int y) {
    return (x - cX) * (x - cX) + (y - cY) * (y - cY) < 16000000;
}
bool is_div2(int cX, int cY, int x, int y) {
    return (x - cX) * (x - cX) + (y - cY) * (y - cY) < 4900000;
}
bool is_checked(int cX, int cY, int x, int y) {
    int r = ((x - cX) * (x - cX) + (y - cY) * (y - cY));
    // cerr << r << endl;
    return  r <  360000;
}
int distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x1- y1), 2) + pow((x2- y2), 2));
}
int * direction(int x1, int y1, int x2, int y2, double angl, int r) {
    static int dirrec[2];
    double slope = (double)(y1 - y2) / (double)(x1 - x2);
    dirrec[0] = x1 + (int)(r * sin(slope + angl));
    dirrec[1] = y1 + (int)(r * sin(slope + angl));
    return dirrec;
}
    
int flagmaker(int svx, int svy) {
    int flag2 = 0;
    if(svx >0 && svy > 0) {
        flag2 = 1;
    }else if(svy < 0 && svx >0) {
        flag2 = 2;
    }else if(svy < 0 && svx <0) {
        flag2 = 3;
    }else if(svy > 0 && svx <0) {
        flag2 = 4;
    }
    return flag2;
}
int * modmaker(int flag) {
    static int mod[2];
    if(flag == 1) {
        mod[0] = 141;
        mod[1] = 141;
    }
    else if(flag == 2) {
        mod[0] = 141;
        mod[1] = -141;
    }
    else if(flag == 3) {
        mod[0] = -141;
        mod[1] = -141;
    }else if(flag == 4) {
        mod[0] = 141;
        mod[1] = -141;
    }else{
        mod[0] = 0;
        mod[1] = 0;
    }
    return mod;
}

int main()
{

    int laps;
    cin >> laps; cin.ignore();
    int checkpointCount;
    cin >> checkpointCount; cin.ignore();
    // cerr<< checkpointCount<<endl;
    int cX[checkpointCount], cY[checkpointCount];
    for (int i = 0; i < checkpointCount; i++) {
        int checkpointX;
        int checkpointY;
        cin >> checkpointX >> checkpointY; cin.ignore();
        cX[i] = checkpointX, cY[i] = checkpointY;
    }
    int turn = 1;
    int * foo;
    foo = new int [5];
    
    int * fvy;
    int * fvx;
    fvy = new int [1000];
    fvx = new int [1000];
    // cerr << cX[1] << " " <<cY[1] << endl;
    // game loop
    while (1) {

        int fx, fy, fA, fNC;
        for (int i = 0; i < 2; i++) {
            int x;
            int y;
            int vx;
            int vy;
            int angle;
            int nextCheckPointId;
            cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
            fx = x, fy = y, fvx[turn] = vx, fvy[turn] = vy, fA = angle, fNC = nextCheckPointId;
        }
        int sx, sy, svx, svy, sA, sNC;
        for (int i = 0; i < 2; i++) {
            int x;
            int y;
            int vx;
            int vy;
            int angle;
            int nextCheckPointId;
            cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
            sx = x, sy = y, svx = vx, svy = vy, sA = angle, sNC = nextCheckPointId;
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;sqrt(fvx* fvx + fvy* fvy)
        // cout << x << " " << y << " " << vx << " " << vy << " " << angle << " " << nextcheckPointId;
        cerr << fx << " " <<  fy << " " << fvx[turn] << " " <<  fvy[turn] << " " << fA<< " " <<  fNC << endl;
        cerr << sx << " " <<  sy << " " << svx << " " <<  svy << " " << sA<< " " <<  sNC << endl;
        int currentfId = fNC, currentsId = sNC;
        // int midstate1 = sqrt(fvx* fvx + fvy* fvy);
        // int midstate2 = sqrt(svx* svx + svy* svy);
        // cerr << midstate1 << " " << midstate2 << endl;
        // int flag1, flag2;
        // flag1 = flagmaker(fvx, fvy);
        // flag2 = flagmaker(svx, svy);
        // int *mod1,*mod2;
        // mod1 = modmaker(flag1);
        // mod2 = modmaker(flag2);
        //if(fNc
        int accf = 90, accs = 85;
        
        turn+= 2;
        cerr << turn << endl;

        if(is_div1(cX[fNC], cY[fNC], fx, fy)) {
            accs = 60;
            int *d;
            d = direction(cX[fNC], cY[fNC], fx, fy, -45, 490000); 
            cout << d[0] << " " << d[1]  << " "<< accs << endl;
        } else if(is_div2(cX[fNC], cY[fNC], fx, fy)) {
            accs = 30;
            cout << cX[fNC] << " " << cY[fNC]  << " "<< accs << endl;
        }else {
            cout << cX[fNC] << " " << cY[fNC]  << " "<< accs << endl;
        }
        if(is_div1(cX[sNC], cY[sNC], sx, sy)) {
            accs = 55;
            int *d;
            d = direction(cX[sNC], cY[sNC], sx, sy, -45, 490000); 
            cout << d[0] << " " << d[1]  << " "<< accs << endl;
        } else if(is_div2(cX[sNC], cY[sNC], sx, sy)) {
            accs = 30;
            cout << cX[sNC] << " " << cY[sNC]  << " "<< accs << endl;
        }else {
            cout << cX[sNC] << " " << cY[sNC]  << " "<< accs << endl;
        }


        

        
  

    }
}