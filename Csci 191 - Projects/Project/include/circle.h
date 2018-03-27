#ifndef CIRCLE_H
#define CIRCLE_H


#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>

//#include "collisioncode.h"


using namespace std;


class circle
{
	public:
	float x;
	float y;
	float radius;
	circle() { x = 0; y = 0; radius = 0; }
	circle(float a,float b,float r) { x = a; y = b; radius = r;}
};
#endif // CIRCLE_H
