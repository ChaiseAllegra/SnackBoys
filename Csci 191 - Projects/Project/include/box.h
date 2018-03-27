#ifndef BOX_H
#define BOX_H


#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>




using namespace std;
class box
{
    public:
	float x;
	float y;
	float width;
	float height;
	box() { x = 0.0; y = 0.0; width = 0.0; height = 0.0; }
	//box(float a,float b,float w,float h) { x = a; y = b; width = w; height = h;}
};

#endif // BOX_H
