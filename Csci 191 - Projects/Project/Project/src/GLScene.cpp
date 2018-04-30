#include "GLScene.h"
#include <GLLight.h>
#include <GLModel.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
//#include<collision.h>


float bound = 3;

float CurXpos,CurYpos;//current x position of the ball, current y position of the ball,
float r = 0.3f, t = 0.007;//size of the ball, speed of the ball
float xdir=bound,ydir=bound;//the direction the ball travels to in the x and y directions, set these to the maximum of the play area
bool RwHit=false,TwHit=false;//Right wall hit: if set to false the ball just hit the left wall if set true it just hit the right wall, TwHit the same but with top and bottom
float Bxvelocity,Byvelocity;//The x and y velocity of the ball

float q=bound-0.1;

Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
Model *wallA= new Model();//left wall
Model *wallB= new Model();//top wall
Model *wallC= new Model();//right wall
skyBox *sky = new skyBox;
Model *Ball = new Model();//the ball

textureLoader *tex0 = new textureLoader();

<<<<<<< HEAD
textureLoader *tex1 = new textureLoader();
=======
float CurXpos,CurYpos;//current x position of the ball, current y position of the ball,
float r = 0.3f, t = 0.7;//size of the ball, speed of the ball
float xdir=bound,ydir=bound;//the direction the ball travels to in the x and y directions, set these to the maximum of the play area
bool RwHit=false,TwHit=false;//Right wall hit: if set to false the ball just hit the left wall if set true it just hit the right wall, TwHit the same but with top and bottom
float Bxvelocity,Byvelocity;//The x and y velocity of the ball
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys

textureLoader *tex2 = new textureLoader();

GLScene::GLScene()
{
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}
GLScene::~GLScene()
{
    //dtor
}
GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    modelTeapot->modelInit("images/player/player0.png",true,tex0);
    plx->parallaxInit("images/box/bandBg.png");
=======
    modelTeapot->modelInit("images/player/player0.png",true);
    plx->parallaxInit("images/box/back.jpg");
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
    ply->playerInit();
    sky->loadTextures();
    //Ball->Ypos=-1;
    wallA->modelInit("images/box/WallLeft.png",true,tex1);
    wallB->modelInit("images/box/WallLeft.png",true,tex1);
    wallC->modelInit("images/box/WallLeft.png",true,tex1);
    Ball->modelInit("images/box/ball.png",true,tex2);
    return true;
}

bool b_collision(box rect1, box rect2){
	if (rect1.x <= rect2.x + (rect2.width/2) && rect1.x + (rect1.width/2) >= rect2.x &&
	   rect1.y < rect2.y + rect2.height && rect1.height + rect1.y > rect2.y)
	    return true;
	else
		return false;
}
static void idle()
=======
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
    modelTeapot->modelInit("images/player/player0.png",true);
    plx->parallaxInit("images/box/back.jpg");
    ply->playerInit();
    sky->loadTextures();
    Ball->modelInit("images/box/ball.png",true);
    wallA->modelInit("images/box/WallLeft.png",true);
      wallB->modelInit("images/box/WallLeft.png",true);
          wallC->modelInit("images/box/WallLeft.png",true);
    //Ball->modelInit("images/box/ball.png",true);
    return true;
}
bool collision(circle circle1, box rect)
{
    //cout<<"collision function"<<endl;

    float x = abs(circle1.x - rect.x);
    float y = abs(circle1.y - rect.y);

    if (x > (rect.width/2 + circle1.radius)) { return false; }
    if (y > (rect.height/2 + circle1.radius)) { return false; }
    //cout<<"circle.x "<<circle1.x<<", "<<"rect.x "<<rect.x<<endl;
    //cout<<"<<(rect.width/2 + circle1.radius) "<<(rect.width/2 + circle1.radius)<<endl;
    //cout<<"x "<<x<<endl;
   // cout<<""<<endl;
    if (x >= (rect.width/2)) { cout<<" x rect if collision"<<endl;
    return true; }

   // if (y <= (rect.height/2)) { //cout<<"collision"<<endl;
   // return true; }

    float cornerDistance_sq = pow((x - rect.width/2),2) +
                         pow((y - rect.height/2),2);
    /*if(cornerDistance_sq <= (pow(circle1.radius,2)))
    {
        cout<<" corner distance collision"<<endl;
        exit(0);
    	return true;
    }*/
}
static void idle(void)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
{
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/q);
    float p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/q);

     Bxvelocity=t * (xdir);//XVelocity: Multiply the speed by the x direction you want to travel in
     CurXpos = CurXpos +  Bxvelocity;//Add the velocity calcualtion to he current x position
     Byvelocity = t * (ydir);////YVelocity: Multiply the speed by the y direction you want to travel in
     CurYpos = CurYpos + Byvelocity;//Add the velocity calcualtion to he current Y position

<<<<<<< HEAD
         if(b_collision(Ball->wallHBox,wallB->wallHBox))
         {
               xdir=-r;
=======
        /*if(collision(Ball->ballHBox,wallA->wallHBox))
            xdir=-r;
        if(collision(Ball->ballHBox,wallA->wallHBox))
            xdir=r;
        if(collision(Ball->ballHBox,wallA->wallHBox))
            ydir=-p;
        if(collision(Ball->ballHBox,wallA->wallHBox))
            ydir=p;*/

         if(collision(Ball->ballHBox,wallB->wallHBox))
         {
               xdir=-r;
               //xdir=xdir*-1;
               cout<<"right wall collision, "<<xdir<<endl;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys

         }
        if(collision(Ball->ballHBox,wallA->wallHBox))
         {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
            xdir=r;
         }

            Ball->Xpos=CurXpos;
           // Ball->Ypos=CurYpos;

=======
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
               xdir=r;
               //xdir=xdir*-1;
         }
        /*if(collision(Ball->ballHBox,wallB->wallHBox))
            xdir=r;
        if(collision(Ball->ballHBox,wallB->wallHBox))
            ydir=-p;
        if(collision(Ball->ballHBox,wallB->wallHBox))
            ydir=p;*/
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
}


GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();

    glPushMatrix();
        glTranslated(0, 0, 1);
        glDisable(GL_LIGHTING);
        glScaled(10,10,10);
        sky->drawBox();
        glEnable(GL_LIGHTING);
     glPopMatrix();

    glPushMatrix();
        glScaled(3.33,3.33,1.0);
        plx->drawSquare(screenWidth,screenHeight);
    glPopMatrix();

    //player is created
     glPushMatrix();
         glTranslated(0,0,(modelTeapot->Zoom));
         ply->actions(ply->actionTrigger);
          ply->playerHBox.width=0.5;
         ply->playerHBox.height=1;
     glPopMatrix();

     //ball is created
     glPushMatrix();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        glScalef(0.3,0.3,1);
        Ball->wallHBox.height=0.8;
        Ball->wallHBox.width=0.8;

        idle();
        Ball->Ypos=0;
        Ball->UpdateHbox(Ball->Xpos,Ball->Ypos);
        Ball->drawModel(tex2);
     glPopMatrix();

=======
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
         glTranslated(0,0,(Ball->Zoom));
          Ball->ballHBox.radius=1;
          idle();
          //cout<<CurXpos<<", "<<xdir<<endl;
           glTranslated(CurXpos, 0, 1);//move the ball to these x and y and z coordinates
           Ball->ballUpdateHbox(CurXpos,CurYpos);
          Ball->drawModel(-1,1,2,0,1,2,-1,0,2,0,1,2);
     glPopMatrix();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys

     //left wasll is created
     glPushMatrix();
         glTranslated(0,0,(wallA->Zoom));
         //add the hitbox for the wall we created on the next four line
         wallA->wallHBox.x=-3.5;
         wallA->wallHBox.y=0;
         wallA->wallHBox.width=1;
         wallA->wallHBox.height=4;
         wallA->tag="L";
          wallA->drawModel(tex1);

     glPopMatrix();

    //right wall
     glPushMatrix();
         glTranslated(0,0,(wallB->Zoom));
         //add the hitbox for the wall we created on the next four line
         wallB->wallHBox.x=4.5;
         wallB->wallHBox.y=0;
         wallB->wallHBox.width=1;
         wallB->wallHBox.height=4;
          wallB->tag="R";
          wallB->drawModel(tex1);

     glPopMatrix();

    //top wall is created
      glPushMatrix();
         glTranslated(0,0,(wallC->Zoom));
         //add the hitbox for the wall we created on the next four line
         wallC->wallHBox.x=3.5;
         wallC->wallHBox.y=2.5;
         wallC->wallHBox.width=9;
         wallC->wallHBox.height=1;
          wallC->tag="T";
<<<<<<< HEAD
          wallC->drawModel(tex1);

     glPopMatrix();

=======
        //top left, top right, lower left, lower right
         //wallC->drawModel(-4,3,2,0,3,2,-4,2,2,-3,2,2);//made the z equal to 2 so the pillar is in front of the player
     glPopMatrix();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
=======
>>>>>>> parent of 4db99ef... Merge branch 'master' of https://github.com/RAGE778/SnackBoys
}
GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
   GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0,aspectRatio,0.1,1000);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)                                   // Check For Windows Messages
    {
        case WM_KEYDOWN:
            KbMs->wParam = wParam;
            KbMs->keyPressed(modelTeapot);
            KbMs->keyEnv(plx, 0.005);
            KbMs->keyPressed(ply,wallA,wallB,wallC);//TEMPORARY!!!!!!!!11!!!

        break;
        case WM_KEYUP:                              // Has A Key Been Released?
        {
            KbMs->wParam = wParam;
            KbMs->keyUP();
            KbMs->keyUp(ply);
        break;                              // Jump Back
        }
        case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;                              // Jump Back
        }
        case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;                              // Jump Back
        }
          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;                              // Jump Back
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            KbMs->mouseEventUp();
        break;                              // Jump Back
        }
        case WM_MOUSEMOVE:
        {
             KbMs->mouseMove(modelTeapot, LOWORD(lParam),HIWORD(lParam));
        break;                              // Jump Back
        }
        case WM_MOUSEWHEEL:
        {
            KbMs->mouseWheel(modelTeapot,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;                              // Jump Back
        }
}
}
