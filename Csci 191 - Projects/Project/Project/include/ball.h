#ifndef BALL_H
#define BALL_H

#include<circle.h>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>
#include<circle.h>
//#include "collisioncode.h"


using namespace std;



class ball:public circle
{
public:
	int weight=10;
	int damage=1;
	string color="white";
	circle *p;
	circle c;
//	c.x = 0;
	//c.y = 0;
	//c.r = 1;
	int x,y,a,b;
	ball(){weight=10;damage=1;color="white";}
	ball(int ex, int why, int r, int w, int d, string c){x=ex;y=why; a=r; weight=w;damage=d;color=c;}
};

#endif // BALL_H
