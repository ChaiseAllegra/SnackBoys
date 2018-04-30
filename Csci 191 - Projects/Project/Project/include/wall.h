#ifndef WALL_H
#define WALL_H
#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>
#include<box.h>
//#include "collisioncode.h"


using namespace std;


class wall:public box
{
public:
	string tag;//tells the kill box from the other walls
	int x,y,a,b;
	wall(){tag="white";}
	wall(int ex, int why, int w, int h, string t){x = ex; y = why; a = w; b = h; tag = t;}
	//box berx(x,y,a,b);
};

#endif // WALL_H
