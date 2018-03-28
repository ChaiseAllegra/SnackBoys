#include "GLScene.h"
#include <GLLight.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <windows.h>
#include <mmsystem.h>
#include<timer.h>
#include<cmath>

using namespace std;

timer* tim;
float bound = 3;
float directionX = 1;
float directionY = 1;
float CurXpos, CurYpos; // Current x position of the ball, current y position of the ball,
float r = 0.3f, t = 0.007; // Size of the ball, speed of the ball
float xdir = bound, ydir = bound; // The direction the ball travels to in the x and y directions, set these to the maximum of the play area
bool RwHit = false, TwHit = false; // Right wall hit: if set to false the ball just hit the left wall if set true it just hit the right wall, TwHit the same but with top and bottom


float ballSpeed = .02;//.02

Model* modelTeapot = new Model();
Model* modelTeapot2 = new Model();

Inputs* KbMs = new Inputs();

parallax* plx = new parallax();
player* ply = new player();
player* ply2 = new player();
Model* wallA = new Model(); // left wall
Model* wallB = new Model(); // right wall
Model* wallC = new Model(); // top wall
Model* wallD = new Model(); // right wall// bottom wall
Model* divide = new Model();
Model* hud = new Model();

Model* tile1=new Model();
Model* tile2=new Model();
Model* tile3=new Model();
Model* tile4=new Model();
Model* tile5=new Model();
Model* tile6=new Model();
Model* tile7=new Model();
Model* tile8=new Model();

Model* tile9=new Model();
Model* tile10=new Model();
Model* tile11=new Model();
Model* tile12=new Model();
Model* tile13=new Model();
Model* tile14=new Model();
Model* tile15=new Model();
Model* tile16=new Model();



Model* wallAHbawks = new Model(); // left wall
Model* wallBHbawks = new Model(); // right wall
Model* wallCHbawks = new Model(); // top wall
Model* wallDHbawks = new Model(); // right wall// bottom wall
skyBox* sky = new skyBox;
Model* Ball = new Model(); // the ball
Model* BallHbawks = new Model();

textureLoader* tex0 = new textureLoader();
textureLoader* tex1 = new textureLoader();
textureLoader* tex2 = new textureLoader();
textureLoader* ballHBTex = new textureLoader();
textureLoader* ballHBTex2 = new textureLoader();
textureLoader* texa = new textureLoader();
textureLoader* texb = new textureLoader();
textureLoader* texc = new textureLoader();
textureLoader* texd = new textureLoader();
textureLoader* texD = new textureLoader();
textureLoader* texH = new textureLoader();

textureLoader* tileTex=new textureLoader();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
    modelTeapot->modelInit("images/player/player0.png", true, tex0);
    modelTeapot2->modelInit("images/player/player0.png", true, tex0);
   // plx->parallaxInit("images/box/band-BG2.png");
    ply->playerInit();
    ply2->playerInit();
    sky->loadTextures();

    wallA->modelInit("images/box/vertical_hitbox.png", true, tex1);
    wallB->modelInit("images/box/vertical_hitbox.png", true, tex2);
    wallC->modelInit("images/box/nothing.png", true, texc);
    wallD->modelInit("images/box/nothing.png", true, texb);
    divide->modelInit("images/box/nothing.png", true, tex2);
    hud->modelInit("images/box/hud.png", true, texH);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

    tile1->modelInit("images/box/ball.png", true, tileTex);
     tile2->modelInit("images/box/ball.png", true, tileTex);
      tile3->modelInit("images/box/ball.png", true, tileTex);
       tile4->modelInit("images/box/ball.png", true, tileTex);
       tile5->modelInit("images/box/ball.png", true, tileTex);
        tile6->modelInit("images/box/ball.png", true, tileTex);
         tile7->modelInit("images/box/ball.png", true, tileTex);
          tile8->modelInit("images/box/ball.png", true, tileTex);

          tile9->modelInit("images/box/ball.png", true, tileTex);
     tile10->modelInit("images/box/ball.png", true, tileTex);
      tile11->modelInit("images/box/ball.png", true, tileTex);
       tile12->modelInit("images/box/ball.png", true, tileTex);
       tile13->modelInit("images/box/ball.png", true, tileTex);
        tile14->modelInit("images/box/ball.png", true, tileTex);
         tile15->modelInit("images/box/ball.png", true, tileTex);
          tile16->modelInit("images/box/ball.png", true, tileTex);
    ply2->PXpos=-2.8;
    ply2->PYpos=-1.4;

    ply->PXpos=2.5;
    ply->PYpos=-1.4;

    return true;
}

static void update()
{
    //ballSpeed+=(1/tim->GetCounter());
    //cout<<tim->GetCounter()<<endl;
    CurXpos = CurXpos + (directionX * ballSpeed);
    CurYpos = CurYpos + (directionY * ballSpeed);

    if (Ball->box_collision(Ball->box, wallB->box))
        directionX = -1;

    if (Ball->box_collision(Ball->box, wallA->box))
        directionX = 1;

    if (Ball->box_collision(Ball->box, wallC->box))
    {
        directionY = -1;
        hud->modelInit("images/box/hud1.png", true, texH);
    }

    if (Ball->box_collision(Ball->box, ply->box))
    {
        Ball->tag="P1";//the ball will remember who hit it last
        if(Ball->Xpos < ply->box.x)
        {
            ballSpeed = ballSpeed + 0.002;//0.002;
            directionX =  -1;
            directionY =  1;
        }
        if(Ball->Xpos >= ply->box.x)
        {
            ballSpeed = ballSpeed + 0.002;//0.002;

            directionX =  1;
            directionY =  1;
        }
        Ball->modelInit("images/box/ball.png", true, ballHBTex);
        hud->modelInit("images/box/hud3.png", true, texH);
    }
    if(CurYpos<-1.8)//makes the ball come in from the top of the map when it falls through the bottom
    {
        CurYpos=2;
        directionY=-1;
        if(directionX==-1)
        CurXpos+=2;

        if(directionX==1)
        CurXpos-=2;

    }
    if(ply->jump > 0)
       {
           ply->yex = 1.5*sin(ply->verticalVelocity);

           if(ply->verticalVelocity>0)
                ply->verticalVelocity -= 0.0070;

            ply->PYpos += ply->yex;

            if(ply->PYpos <= -1.4)
            {
                ply->yex = 0;
                ply->PYpos = -1.4;
                ply->jump = 0;
            }
       }

       if(ply2->jump > 0)
       {
           ply2->yex = 1.5*sin(ply->verticalVelocity);

           if(ply2->verticalVelocity>0)
                ply2->verticalVelocity -= 0.0070;

            ply2->PYpos += ply2->yex;

            if(ply2->PYpos <= -1.4)
            {
                ply2->yex = 0;
                ply2->PYpos = -1.4;
                ply2->jump = 0;
            }
       }


     if(!(ply->box_collision(ply->box,tile1->box)||ply->box_collision(ply->box,tile2->box)||ply->box_collision(ply->box,tile3->box)||ply->box_collision(ply->box,tile4->box)||
    ply->box_collision(ply->box,tile5->box)||ply->box_collision(ply->box,tile6->box)||ply->box_collision(ply->box,tile7->box)||ply->box_collision(ply->box,tile8->box))||ply->PYpos>-1.4)
            ply->PYpos-=0.005;//0.05;
      if(!(ply2->box_collision(ply2->box,tile1->box)||ply2->box_collision(ply2->box,tile2->box)||ply2->box_collision(ply2->box,tile3->box)||ply2->box_collision(ply2->box,tile4->box)||
    ply2->box_collision(ply2->box,tile5->box)||ply2->box_collision(ply2->box,tile6->box)||ply2->box_collision(ply2->box,tile7->box)||ply2->box_collision(ply2->box,tile8->box))||ply2->PYpos>-1.4)
            ply2->PYpos-=0.005;//0.05;

    if (ply->box_collision(ply->box, wallD->box))//if the player hits the killbox end the game
    {
        //exit(0);
    }

    if (ply2->box_collision(ply2->box, wallD->box))//if the player hits the killbox end the game
    {
        //exit(0);
    }


    if(Ball->box_collision(Ball->box, tile1->box ))
    {
        directionY = 1;
        ballSpeed=0.004;//0.002;
        tile1->health-=1;
        tile1->isalive();
    }
    if(Ball->box_collision(Ball->box, tile2->box))
     {
         directionY = 1;
           ballSpeed=0.004;
        tile2->health-=1;
        tile2->isalive();
    }
    if(Ball->box_collision(Ball->box, tile3->box))
       {
           directionY = 1;
             ballSpeed=0.004;;
        tile3->health-=1;
        tile3->isalive();
    }
    if(Ball->box_collision(Ball->box, tile4->box))
     {
         directionY = 1;
           ballSpeed=0.004;
        tile4->health-=1;
        tile4->isalive();
    }
    if(Ball->box_collision(Ball->box, tile5->box))
        {
            directionY = 1;
              ballSpeed=0.004;
        tile5->health-=1;
        tile5->isalive();
    }
    if(Ball->box_collision(Ball->box, tile6->box))
     {
         directionY = 1;
           ballSpeed=0.004;
        tile6->health-=1;
        tile6->isalive();
    }
    if(Ball->box_collision(Ball->box, tile7->box))
        {
            directionY = 1;
              ballSpeed=0.004;
        tile7->health-=1;
        tile7->isalive();
    }
    if(Ball->box_collision(Ball->box, tile8->box))
        {
            directionY = 1;
              ballSpeed=0.004;
        tile8->health-=1;
        tile8->isalive();
    }


     if(Ball->box_collision(Ball->box, tile9->box ))
    {
        directionY = -1;
        ballSpeed=0.004;
        tile9->health-=1;
        tile9->isalive();
    }
    if(Ball->box_collision(Ball->box, tile10->box))
     {
         directionY = -1;
           ballSpeed=0.004;
        tile10->health-=1;
        tile10->isalive();
    }
    if(Ball->box_collision(Ball->box, tile11->box))
       {
           directionY = -1;
             ballSpeed=0.004;
        tile11->health-=1;
        tile11->isalive();
    }
    if(Ball->box_collision(Ball->box, tile12->box))
     {
         directionY = -1;
           ballSpeed=0.004;
        tile12->health-=1;
        tile12->isalive();
    }
    if(Ball->box_collision(Ball->box, tile13->box))
        {
            directionY = -1;
              ballSpeed=0.004;
        tile13->health-=1;
        tile13->isalive();
    }
    if(Ball->box_collision(Ball->box, tile14->box))
     {
         directionY = -1;
           ballSpeed=0.004;
        tile14->health-=1;
        tile14->isalive();
    }
    if(Ball->box_collision(Ball->box, tile15->box))
        {
            directionY = -1;
              ballSpeed=0.004;
        tile15->health-=1;
        tile15->isalive();
    }
    if(Ball->box_collision(Ball->box, tile16->box))
        {
            directionY = -1;
              ballSpeed=0.004;
        tile16->health-=1;
        tile16->isalive();
    }


    Ball->Xpos = CurXpos;
    Ball->Ypos = CurYpos;
}

void makeModel(Model* mod,textureLoader* texture,float xspot,float yspot,float ZeroX,float ZeroY,float OneX, float OneY, float TwoX, float TwoY, float ThreX, float ThreY, float w, float h)
{
       glPushMatrix();

        mod->Xpos=xspot;
        mod->Ypos=yspot;
        mod->box.x = mod->Xpos; //wallA->Xpos;
        mod->box.y = mod->Ypos;
        mod->verticies[0].x = ZeroX;//-0.15;
        mod->verticies[1].x = OneX;//0.15;
        mod->verticies[2].x = TwoX;//0.15;
        mod->verticies[3].x = ThreX;//-0.15;
        mod->verticies[0].y = ZeroY;//-0.15;
        mod->verticies[1].y = OneY;//-0.15;
        mod->verticies[2].y = TwoY;//0.15;
        mod->verticies[3].y = ThreY;//0.15;

        mod->box.height = h;
        mod->box.width = w;
        mod->drawModel(texture);
    glPopMatrix();
    return;
}
GLint GLScene::drawGLScene()
{
    tim->StartCounter();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
    // Reset The Current Modelview Matrix
    glPushMatrix();
        glTranslated(0, 0, 1);
        glDisable(GL_LIGHTING);
        glScaled(10, 10, 10);
        sky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    //--------------------------PARALLAX CREATION-----------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);
        plx->drawSquare(screenWidth, screenHeight);
    glPopMatrix();
    //plx->scroll(true,"up",0.005);

    //--------------------------PLAYER CREATION-----------------------------//
    glPushMatrix();
        ply->actions(ply->actionTrigger, ply, modelTeapot);
        ply->box.x = ply->PXpos;
        ply->box.y = ply->PYpos;
        ply->box.height=0.3;
        ply->box.width=0.3;
        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value
        ply->drawplayer();
    glPopMatrix();


     //--------------------------PLAYER DOS CREATION-----------------------------//
    /*glPushMatrix();
        ply2->actions(ply2->actionTrigger, ply2, modelTeapot2);
        ply2->box.x = ply2->PXpos;
        ply2->box.y = ply2->PYpos;
        //ply2->Xpos = 1.0;

        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value
        ply2->drawplayer();
    glPopMatrix();*/

    // model*, tecture*, xpos, ypos, zerox, zeroy, etc,  width height
    if(tile1->health>0)
    makeModel(tile1,tileTex,-3.5,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile2->health>0)
    makeModel(tile2,tileTex,-3.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile3->health>0)
    makeModel(tile3,tileTex,-2.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile4->health>0)
    makeModel(tile4,tileTex,-1.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile5->health>0)
    makeModel(tile5,tileTex,0.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile6->health>0)
    makeModel(tile6,tileTex,1.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile7->health>0)
    makeModel(tile7,tileTex,2.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile8->health>0)
    makeModel(tile8,tileTex,3.0,-2.1,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    //top tiles
    if(tile9->health>0)
    makeModel(tile9,tileTex,-3.5,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile10->health>0)
    makeModel(tile10,tileTex,-3.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile11->health>0)
    makeModel(tile11,tileTex,-2.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile12->health>0)
    makeModel(tile12,tileTex,-1.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile13->health>0)
    makeModel(tile13,tileTex,0.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile14->health>0)
    makeModel(tile14,tileTex,1.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile15->health>0)
    makeModel(tile15,tileTex,2.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    if(tile16->health>0)
    makeModel(tile16,tileTex,3.0,2.0,-0.70,-0.15,0.70,-0.15,0.70,0.15,-0.70,0.15,0.7,0.7);

    //left wall
    makeModel(wallA,tex1,-4.0,0,-0.2,-2.0,0.2,-2.0,0.2,2.0,-0.2,2,.3,88);

    //right wall
    makeModel(wallB,tex2,3.9,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.3,88);

    //top wall
    makeModel(wallC,texc,0,2.02,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,.2);

    //kill box
    makeModel(wallD,texb,0,-3.09,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,88,0.2);

    //dividing wall
    makeModel(divide,tex2,0,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.3,88);

    //ball creation
    //makeModel(Ball,ballHBTex,-0.5,-0.5,-0.15,-0.15,0.15,-0.15,0.15,0.15,-0.15,0.15,0.3,0.3);

   // tim->GetCounter();

    //--------------------------BALL CREATION-----------------------------//
    glPushMatrix();
        Ball->Ypos = 0;
        Ball->Ypos = -0.5;
        Ball->box.height = 0.3;
        Ball->box.width = 0.3;

        Ball->verticies[0].x = -0.15;
        Ball->verticies[1].x = 0.15;
        Ball->verticies[2].x = 0.15;
        Ball->verticies[3].x = -0.15;
        Ball->verticies[0].y = -0.15;
        Ball->verticies[1].y = -0.15;
        Ball->verticies[2].y = 0.15;
        Ball->verticies[3].y = 0.15;

        update();

        Ball->UpdateHbox(Ball->Xpos, Ball->Ypos);
        Ball->drawModel(ballHBTex);
    glPopMatrix();

//---------------HUD IS DRAWN-----------------
    /*glPushMatrix();
        hud->verticies[0].x = -1; //bottom left x
        hud->verticies[1].x = 1; //bottom right x
        hud->verticies[2].x = 1; //top right x
        hud->verticies[3].x = -1; //top left x
        hud->verticies[0].y = -1; //bottom left y
        hud->verticies[1].y = -1; //bottom right y
        hud->verticies[2].y = 1; //top right y
        hud->verticies[3].y = 1; // top left y
        hud->Xpos = -2.69;
        hud->Ypos = 1.15;
        //hud->Zoom = 0;
        hud->drawModel(texH); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();*/
}
GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) // Check For Windows Messages
    {
    case WM_KEYDOWN:
        KbMs->wParam = wParam;
        //KbMs->keyPressed(modelTeapot);
        KbMs->keyEnv(plx, 0.005);
        KbMs->keyPressed(ply,ply2,modelTeapot, wallA, wallB, wallC,divide);


        break;
    case WM_KEYUP: // Has A Key Been Released?
    {
        KbMs->wParam = wParam;
        KbMs->keyUP();
        KbMs->keyUp(ply);
        break; // Jump Back
    }
    case WM_LBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_RBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_MBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP: {
        KbMs->mouseEventUp();
        break; // Jump Back
    }
    case WM_MOUSEMOVE: {
        KbMs->mouseMove(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_MOUSEWHEEL: {
        KbMs->mouseWheel(modelTeapot, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break; // Jump Back
    }
    }
}
