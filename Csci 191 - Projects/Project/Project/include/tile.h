#ifndef TILE_H
#define TILE_H
#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>

//#include "collisioncode.h"


using namespace std;




class tile
{
public:
	int health;
	string tag;
	int x,y,a,b;
	tile() { health = 1; tag = "white"; }
	tile(int ex, int why, int r,int h, string t) { x=ex;y=why;a=r;b=h; health = h; tag = t; }
	//box berx(x,y,a,b);

};

#endif // TILE_H
