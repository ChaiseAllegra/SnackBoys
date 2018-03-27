#include <iomanip>
#include <iostream>
#include <cmath>
#include <math.h>
#include<string>

#include<circle.h>


using namespace std;


 bool box_collision(Hbox rect1, Hbox rect2){
	if (rect1.y < (rect2.y + rect2.height) && rect1.y > (rect2.y - rect2.height) && rect1.x < (rect2.x + rect2.width) && rect1.x > (rect2.x - rect2.width))
        return true;
    else
        return false;
}
/*bool circle_collision(circle circle1, circle circle2)
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
bool CR_collision(circle circle1, box rect)
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
