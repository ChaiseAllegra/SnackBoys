#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>

#include<circle.h>
#include<box.h>
using namespace std;


 bool box_collision(box rect1, box rect2){
    //cout<<rect1.x<<","<<rect1.y<<","<<rect1.width<<","<<rect1.height<<endl;
    //cout<<rect2.x<<","<<rect2.y<<","<<rect2.width<<","<<rect2.height<<endl;
	if (rect1.x <= rect2.x + (rect2.width/2) &&
	   rect1.x + (rect1.width/2) >= rect2.x &&
	   rect1.y < rect2.y + rect2.height &&
	   rect1.height + rect1.y > rect2.y)

	{
	   // cout<<"collision"<<endl;
	    return true;// collision detected!
	}
	else
	{

	    //cout<<"no collision"<<endl;
		return false;
	}
}
bool circle_collision(circle circle1, circle circle2)
{
  	int dx = circle1.x - circle2.x;
	int dy = circle1.y - circle2.y;
	int distance = sqrt(dx * dx + dy * dy);

	if (distance < circle1.radius + circle2.radius)
	{
	//	cout<<"circle collision"<<endl;
    return true;// collision detected!
	}
	else{
		return false;
	}
}
/*bool CR_collision(circle circle1, box rect)
{
    float x = abs(circle1.x - rect.x);
    float y = abs(circle1.y - rect.y);

    if (x > (rect.width/2 + circle1.radius)) { return false; }
    if (y > (rect.height/2 + circle1.radius)) { return false; }

    if (x <= (rect.width/2)) { return true; }
    if (y <= (rect.height/2)) { return true; }

    float cornerDistance_sq = pow((x - rect.width/2),2) +
                         pow((y - rect.height/2),2);
    if(cornerDistance_sq <= (circle1.radius^2))
    {
    	return true;
    }
}*/
