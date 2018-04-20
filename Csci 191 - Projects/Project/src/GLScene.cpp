#include <GLScene.h>
#include <GLLight.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <windows.h>
#include <mmsystem.h>
#include <cmath>
#include <timer.h>
#include <GLFW/glfw3.h>
#include<levelAlpha.h>
#include<levelOmega.h>

levelAlpha* alpha;
levelOmega* omega;

float tw=100,th=100;
float mX,mY,mXpos=0,mYpos=0;
float bY;
float resetV=0;
float velocity=resetV;
bool hit;
float maxHeight=1.5;
float vDecrement=0.001;
float endGoal;
float BallprevY;

using namespace std;

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);

    alpha= new levelAlpha();
    omega = new levelOmega();

     KbMs = new Inputs();

     plx = new parallax();
     plx2 = new parallax();
    sky = new skyBox;

     playMod= new Model();
     resetMod= new Model();
     exitMod= new Model();

     playTex=new textureLoader();
     resetTex=new textureLoader();
     exitTex=new textureLoader();

     texSky1 = new textureLoader();
     texSky2 = new textureLoader();
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    lastTime = glfwGetTime();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
    sky->loadTextures();

    plx->parallaxInit("images/box/sky.png",texSky1);
    plx2->parallaxInit("images/box/city.png",texSky2);

    playMod->modelInit("images/box/pMPlay.png", true, playTex);
    resetMod->modelInit("images/box/pMReset.png", true, resetTex);
    exitMod->modelInit("images/box/pMExit.png", true, exitTex);

    startTime= glfwGetTime();

    return true;
}

float manhattanDist(player* ply, player* ply2)
{
     mX=abs(ply->PXpos-ply2->PXpos);
     mY=abs(ply->PYpos-ply2->PYpos);
    return mX+mY;
}

void GLScene::makeModel(Model* mod,textureLoader* texture,float xspot,float yspot,float ZeroX,float ZeroY,float OneX, float OneY, float TwoX, float TwoY, float ThreX, float ThreY, float w, float h)
{
       glPushMatrix();

        mod->Xpos=xspot;
        mod->Ypos=yspot;
        mod->box.x = mod->Xpos; // wallA->Xpos;
        mod->box.y = mod->Ypos;
        mod->verticies[0].x = ZeroX; // -0.15;
        mod->verticies[1].x = OneX; // 0.15;
        mod->verticies[2].x = TwoX; // 0.15;
        mod->verticies[3].x = ThreX; // -0.15;
        mod->verticies[0].y = ZeroY; // -0.15;
        mod->verticies[1].y = OneY; // -0.15;
        mod->verticies[2].y = TwoY; // 0.15;
        mod->verticies[3].y = ThreY; // 0.15;

        mod->box.height = h;
        mod->box.width = w;
        mod->drawModel(texture);
    glPopMatrix();
    return;
}

GLint GLScene::drawGLScene(bool pressed[256])
{



      //-----------------------------------------------------------------------------------------------//
     //------------------------------------------ TIMERS ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//

        alpha->projA->myTime->start();
        alpha->projB->myTime->start();
        alpha->ply->myTime->start();
        alpha->Ball->myTime->start();
        alpha->ply->swingTimer->start();
        alpha->ply2->swingTimer->start();
        alpha->D->start();
        alpha->BPA->start();
        alpha-> pCol->start();
      //-----------------------------------------------------------------------------------------------//
     //-------------------------------- SKYBOX CREATION ----------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
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

      //-----------------------------------------------------------------------------------------------//
     //------------------------------- PARALLAX CREATION ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);
        plx->drawSquare(screenWidth, screenHeight, texSky1);
    glPopMatrix();
     if(timeFromStart-startTime>=2)//wait three seconds to start the game
    plx->scroll(true,"left",1,scale);

      //-----------------------------------------------------------------------------------------------//
     //------------------------------- PARALLAX2 CREATION --------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);

             plx2->drawSquare(screenWidth, screenHeight, texSky2);


    glPopMatrix();
     if(timeFromStart-startTime>=2)//wait three seconds to start the game
    plx2->scroll(false,"left",0.0002,scale);

      //-------------------------------------------------------------------------------------------------//
     //------------------------------- PLAYER CREATION -------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if(alpha->ply->health>0)
    {
    glPushMatrix();
       alpha->ply->actions();
       alpha->ply->box.x=alpha->ply->PXpos;
        alpha->ply->box.y = alpha->ply->PYpos;
       alpha-> ply->pl_pltfrm_box.x = alpha->ply ->PXpos;
        alpha->ply->pl_pltfrm_box.y = alpha->ply -> PYpos;
        alpha->ply->pl_pltfrm_box.height = 0.6;
        alpha->ply->pl_pltfrm_box.width = 0.07;
        alpha->ply->box.height=0.1;
        alpha->ply->trueHeight=0.1;
        alpha->ply->box.width=0.3;
        alpha->update(scale);
        alpha->ply->drawplayer();
    glPopMatrix();
    }
     if(alpha->ply->health<=0)
    {
            alpha->ply->box.height=0;
            alpha->ply->box.width=0;
            alpha->ply->pl_pltfrm_box.height = 0;
            alpha->ply->pl_pltfrm_box.width = 0;
    }


    if(alpha->ply2->health>0)
    {
        glPushMatrix();
            alpha->ply2->actions();
            alpha->ply2->box.x =  alpha->ply2->PXpos;
            alpha->ply2->box.y =  alpha->ply2->PYpos;
            alpha->ply2->pl_pltfrm_box.x =  alpha->ply2 ->PXpos;
            alpha->ply2->pl_pltfrm_box.y =  alpha->ply2 -> PYpos;
            alpha->ply2->pl_pltfrm_box.height = 0.6;
            alpha->ply2->pl_pltfrm_box.width = 0.07;
            alpha->ply2->box.height=0.5;
           alpha-> ply2->box.width=0.2;
            alpha->update(scale);
            alpha->ply2->drawplayer();
        glPopMatrix();
    }
    if(alpha->ply2->health<=0)
    {
            alpha->ply2->box.height=0;
            alpha->ply2->box.width=0;
            alpha->ply2->box.x=999;
            alpha->ply2->box.y=999;
            alpha->ply2->pl_pltfrm_box.x =999;
            alpha->ply2->pl_pltfrm_box.y = 999;
            alpha->ply2->pl_pltfrm_box.height = 0;
            alpha->ply2->pl_pltfrm_box.width = 0;
            alpha->ply2->PXpos=999;
            alpha->ply2->PYpos=999;
            alpha->ply2->box.x=999;
            alpha->ply2->box.y=999;
    }
     //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//

    // model , texture, xpos,ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
   makeModel(alpha->floor,alpha->tileTex,0,-2.08,-3.5,-0.00,3.5,-0.00,3.5,0.40,-3.5,0.40,7,.3);

      //left wall
    makeModel(alpha->leftWall,alpha->tex1,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);

    //right wall
    makeModel(alpha->rightWall,alpha->tex2,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);

    //bottom wall
    makeModel(alpha->killBox,alpha->tex3,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);

     //top wall
    makeModel(alpha->topWall,alpha->tex3,0,2.1,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);

    makeModel(alpha->platTileBL, alpha->tileTex, -1.5, -1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
    makeModel(alpha->platTileBR, alpha->tileTex, 1.5, -1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
    makeModel(alpha->platTileTL, alpha->tileTex, -1.5, 1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
    makeModel(alpha->platTileTR, alpha->tileTex, 1.5, 1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
    makeModel(alpha->platTileM, alpha->tileTex, 0, 0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
    //left goal
    makeModel(alpha->GoalL,alpha->texGL,-3,0,-0.2,0.5,0.2,0.5,0.2,-0.5,-0.2,-0.5,0.5,1);
    //right goal
    makeModel(alpha->GoalR,alpha->texGL,3,0,-0.2,0.5,0.2,0.5,0.2,-0.5,-0.2,-0.5,0.5,1);

    if(alpha->ply->thrown)
        {
            glPushMatrix();
            alpha->projA->box.height =  .2;
            alpha->projA->box.width = .05;

           alpha-> projA->verticies[0].x = -0.15;
            alpha->projA->verticies[1].x = 0.15;
           alpha-> projA->verticies[2].x = 0.15;
           alpha-> projA->verticies[3].x = -0.15;
           alpha-> projA->verticies[0].y = -0.15;
           alpha-> projA->verticies[1].y = -0.15;
           alpha-> projA->verticies[2].y = 0.15;
           alpha-> projA->verticies[3].y = 0.15;
           alpha-> projA->box.x = alpha->projA ->Xpos;
            alpha->projA->box.y = alpha->projA ->Ypos;

            if(!alpha->shot)
            {
                if(alpha->ply->lastCase=='R')//lets player aim to his right
                {
                    alpha->projAXdir = alpha->ply->xdir;
                    alpha->projAYdir =  alpha->ply->ydir;
                }

                if(alpha->ply->lastCase=='L')//lets player aim to his left
                {

                    alpha->projAXdir = - alpha->ply->xdir;
                    alpha->projAYdir =  alpha->ply->ydir;
                }

                alpha->projA->health = 3;
                alpha->shot = true;
            }
            alpha->projA->drawModel(alpha->ballHBTex);
          glPopMatrix();
        }

    if(alpha->projA->health<=0)
    {
        alpha->ply->thrown=false;
        alpha->shot=false;
        alpha->projA->Xpos=999;
       alpha-> projA->Ypos=999;

        alpha->projA->box.x=999;
        alpha->projA->box.y=999;
        alpha->projA->box.width=0;
        alpha->projA->box.height=0;
    }


    if(alpha->ply->thrown==false&&alpha->ply->lastCase=='R')
        alpha->ProjACurY=alpha->ply->PYpos, alpha->ProjACurX=alpha->ply->PXpos+0.5;
     if(alpha->ply->thrown==false&&alpha->ply->lastCase=='L')
           alpha->ProjACurY=alpha->ply->PYpos, alpha->ProjACurX=alpha->ply->PXpos-0.5;

     if(alpha->ply2->thrown)
        {
            glPushMatrix();
            alpha->projA->box.height =  .2;
            alpha->projA->box.width = .05;

           alpha-> projA->verticies[0].x = -0.15;
            alpha->projA->verticies[1].x = 0.15;
           alpha-> projA->verticies[2].x = 0.15;
           alpha-> projA->verticies[3].x = -0.15;
           alpha-> projA->verticies[0].y = -0.15;
           alpha-> projA->verticies[1].y = -0.15;
           alpha-> projA->verticies[2].y = 0.15;
           alpha-> projA->verticies[3].y = 0.15;
           alpha-> projA->box.x = alpha->projA ->Xpos;
            alpha->projA->box.y = alpha->projA ->Ypos;

            if(!alpha->shot)
            {
                if(alpha->ply2->lastCase=='R')//lets player aim to his right
                {
                    alpha->projAXdir = alpha->ply2->xdir;
                    alpha->projAYdir =  alpha->ply2->ydir;
                }

                if(alpha->ply2->lastCase=='L')//lets player aim to his left
                {

                    alpha->projAXdir = - alpha->ply2->xdir;
                    alpha->projAYdir =  alpha->ply2->ydir;
                }

                alpha->projA->health = 3;
                alpha->shot = true;
            }
            alpha->projA->drawModel(alpha->ballHBTex);
          glPopMatrix();
        }

    if(alpha->projA->health<=0)
    {
        alpha->ply2->thrown=false;
        alpha->shot=false;
        alpha->projA->Xpos=999;
       alpha-> projA->Ypos=999;

        alpha->projA->box.x=999;
        alpha->projA->box.y=999;
        alpha->projA->box.width=0;
        alpha->projA->box.height=0;
    }


    if(alpha->ply2->thrown==false&&alpha->ply2->lastCase=='R')
        alpha->ProjACurY=alpha->ply2->PYpos, alpha->ProjACurX=alpha->ply2->PXpos+0.5;
     if(alpha->ply2->thrown==false&&alpha->ply2->lastCase=='L')
           alpha->ProjACurY=alpha->ply2->PYpos, alpha->ProjACurX=alpha->ply2->PXpos-0.5;

     glPushMatrix();
        alpha->Ball->box.height =  .2;
        alpha->Ball->box.width = .05;
        alpha->Ball->verticies[0].x = -0.15;
        alpha->Ball->verticies[1].x = 0.15;
        alpha->Ball->verticies[2].x = 0.15;
        alpha->Ball->verticies[3].x = -0.15;
        alpha->Ball->verticies[0].y = -0.15;
        alpha->Ball->verticies[1].y = -0.15;
        alpha->Ball->verticies[2].y = 0.15;
        alpha->Ball->verticies[3].y = 0.15;
        alpha->Ball->box.x = alpha->Ball ->Xpos;
        alpha->Ball->box.y = alpha->Ball ->Ypos;
       //alpha->update();
        alpha->Ball->drawModel(alpha->ballHBTex);
    glPopMatrix();

    //---------------------------Crosshair player 1 creation----------------------------------//
    float tmp1 = alpha->ply->PXpos - alpha->ply->xdir;
    float tmp2 = alpha->ply->PYpos + alpha->ply->ydir;
    float tmp3 = alpha->ply->PXpos + alpha->ply->xdir;

    if(alpha->ply->lastCase=='L')
        makeModel(alpha->cross, alpha->crosshair, tmp1, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(alpha->ply->lastCase=='R')
        makeModel(alpha->cross, alpha->crosshair, tmp3, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);


     if(pauseMenu)
    {
        if(pauseChoice)
        {
            if(menuPos==1)//reset the gameee
            {
                pauseMenu=false;
//                reset();
            }
            if(menuPos==2)//resumed the game
            {
                pauseMenu=false;

            }
            menuPos=2;
            pauseChoice=false;
        }
        else
        {
        glLoadIdentity();
            if(menuPos==2)
            {
                glPushMatrix();
                playMod->Xpos=0;
                 playMod->Ypos=0;
                 playMod->drawModel(playTex);
                glPopMatrix();
            }
            if(menuPos==1)
            {
                glPushMatrix();
                resetMod->Xpos=0;
                  resetMod->Ypos=0;
                 resetMod->drawModel(resetTex);
                glPopMatrix();
            }
             if(menuPos==0)
            {
                glPushMatrix();
                exitMod->Xpos=0;
                exitMod->Ypos=0;
                 exitMod->drawModel(exitTex);
                glPopMatrix();
            }
        }
    }

    alpha->ply->delta=20;
    alpha->ply2->delta=20;
    alpha->scale=20;
    //if(timeFromStart-startTime>=2&&!pauseMenu)//wait three seconds to start the game
     //KbMs->idle(pressed,alpha->ply,alpha->ply2);
}

GLint GLScene::drawGLScene2(bool pressed[256])
{
    double lolTime = glfwGetTime();
    cout<<lolTime<<endl;

      //-----------------------------------------------------------------------------------------------//
     //------------------------------------------ TIMERS ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
        omega->projA->myTime->start();
        omega->projB->myTime->start();
        omega->ply->myTime->start();
        omega->Ball->myTime->start();
        omega->ply->swingTimer->start();
        omega->ply2->swingTimer->start();
        omega->D->start();
        omega->BPA->start();
        omega-> pCol->start();
       //-----------------------------------------------------------------------------------------------//
     //-------------------------------- SKYBOX CREATION ----------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
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
      //-----------------------------------------------------------------------------------------------//
     //------------------------------- PARALLAX CREATION ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);
        plx->drawSquare(screenWidth, screenHeight, texSky1);
    glPopMatrix();
     if(timeFromStart-startTime>=2)//wait three seconds to start the game
        plx->scroll(true,"left",1,scale);
      //-----------------------------------------------------------------------------------------------//
     //------------------------------- PARALLAX2 CREATION --------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);
        plx2->drawSquare(screenWidth, screenHeight, texSky2);
    glPopMatrix();
    if(timeFromStart-startTime>=2)//wait three seconds to start the game
        plx2->scroll(false,"left",0.0002,scale);
      //-------------------------------------------------------------------------------------------------//
     //------------------------------- PLAYER CREATION -------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if(omega->ply->health>0)
    {
    glPushMatrix();
        omega->ply->actions();
        omega->ply->box.x=omega->ply->PXpos;
        omega->ply->box.y = omega->ply->PYpos;
        omega-> ply->pl_pltfrm_box.x = omega->ply ->PXpos;
        omega->ply->pl_pltfrm_box.y = omega->ply -> PYpos;
        omega->ply->pl_pltfrm_box.height = 0.6;
        omega->ply->pl_pltfrm_box.width = 0.07;
        omega->ply->box.height=0.1;
        omega->ply->trueHeight=0.1;
        omega->ply->box.width=0.3;
        //omega->update(20);
        omega->ply->drawplayer();
    glPopMatrix();
    }
     /*if(omega->ply->health<=0)
    {
            omega->ply->box.height=0;
            omega->ply->box.width=0;
            omega->ply->pl_pltfrm_box.height = 0;
            omega->ply->pl_pltfrm_box.width = 0;
    }*/
    if(omega->ply2->health>0)
    {
        glPushMatrix();
            omega->ply2->actions();
            omega->ply2->box.x =  omega->ply2->PXpos;
            omega->ply2->box.y =  omega->ply2->PYpos;
            omega->ply2->pl_pltfrm_box.x =  omega->ply2 ->PXpos;
            omega->ply2->pl_pltfrm_box.y =  omega->ply2 -> PYpos;
            omega->ply2->pl_pltfrm_box.height = 0.6;
            omega->ply2->pl_pltfrm_box.width = 0.07;
            omega->ply2->box.height=0.5;
            omega->ply2->box.width=0.2;
//          update();
            omega->ply2->drawplayer();
        glPopMatrix();
    }
    if(omega->ply2->health<=0)
    {
            omega->ply2->box.height=0;
            omega->ply2->box.width=0;
            omega->ply2->box.x=999;
            omega->ply2->box.y=999;
            omega->ply2->pl_pltfrm_box.x =999;
            omega->ply2->pl_pltfrm_box.y = 999;
            omega->ply2->pl_pltfrm_box.height = 0;
            omega->ply2->pl_pltfrm_box.width = 0;
            omega->ply2->PXpos=999;
            omega->ply2->PYpos=999;
            omega->ply2->box.x=999;
            omega->ply2->box.y=999;
    }
      //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    // model , texture, xpos,ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
    if(omega->tile1->isalive())
    makeModel(omega->tile1,omega->tileTex,-3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile2->isalive())
    makeModel(omega->tile2,omega->tileTex2,-2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile3->isalive())
    makeModel(omega->tile3,omega->tileTex3,-2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile4->isalive())
    makeModel(omega->tile4,omega->tileTex4,-1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile5->isalive())
    makeModel(omega->tile5,omega->tileTex5,-1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile6->isalive())
    makeModel(omega->tile6,omega->tileTex6,-0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile7->isalive())
    makeModel(omega->tile7,omega->tileTex7,-0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile8->isalive())
    makeModel(omega->tile8,omega->tileTex8, 0.00,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile9->isalive())
    makeModel(omega->tile9,omega->tileTex9, 0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile10->isalive())
    makeModel(omega->tile10,omega->tileTex10, 0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile22->isalive())
    makeModel(omega->tile22,omega->tileTex11, 1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile12->isalive())
    makeModel(omega->tile12,omega->tileTex12, 1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile13->isalive())
    makeModel(omega->tile13,omega->tileTex13, 2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile14->isalive())
    makeModel(omega->tile14,omega->tileTex14, 2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    if(omega->tile15->isalive())
    makeModel(omega->tile15,omega->tileTex15, 3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    //left wall
    makeModel(omega->leftWall,omega->tex1,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);
    //right wall
    makeModel(omega->rightWall,omega->tex2,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);
    //bottom wall
    makeModel(omega->killBox,omega->texc,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);
    //dividing wall
    makeModel(omega->divide,omega->divTex,0,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.1,88);

    //top wall
    makeModel(omega->topWall, omega->tex3,0,2.1,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);
    //ball creation
    //makeModel(Ball,ballHBTex,-0.5,-0.5,-0.15,-0.15,0.15,-0.15,0.15,0.15,-0.15,0.15,0.3,0.3);
    //----------------Projectile creation------------------------------------------------//
        if(omega->ply->thrown)
        {
            glPushMatrix();
                omega->projA->box.height =  .2;
                omega->projA->box.width = .05;
                omega->projA->verticies[0].x = -0.15;
                omega->projA->verticies[1].x = 0.15;
                omega->projA->verticies[2].x = 0.15;
                omega->projA->verticies[3].x = -0.15;
                omega->projA->verticies[0].y = -0.15;
                omega->projA->verticies[1].y = -0.15;
                omega->projA->verticies[2].y = 0.15;
                omega->projA->verticies[3].y = 0.15;
                omega->projA->box.x = omega->projA ->Xpos;
                omega->projA->box.y = omega->projA ->Ypos;
                omega->projA->drawModel(omega->ballHBTex);
          glPopMatrix();
        }

    //-------------------------projectile b-----------------------------------------//
    if(omega->ply2->thrown)
        {
            glPushMatrix();
                omega->projB->box.height =  .2;
                omega->projB->box.width = .05;
                omega->projB->verticies[0].x = -0.15;
                omega->projB->verticies[1].x = 0.15;
                omega->projB->verticies[2].x = 0.15;
                omega->projB->verticies[3].x = -0.15;
                omega->projB->verticies[0].y = -0.15;
                omega->projB->verticies[1].y = -0.15;
                omega->projB->verticies[2].y = 0.15;
                omega->projB->verticies[3].y = 0.15;
                omega->projB->box.x = omega->projB ->Xpos;
                omega->projB->box.y = omega->projB ->Ypos;
                if(!shot)
                {
                    if(omega->ply2->lastCase=='R')//lets player aim to his right
                    {
                        omega->projBXdir = omega->ply2->xdir;
                        omega->projBYdir = omega->ply2->ydir;
                    }
                    if(omega->ply2->lastCase=='L')//lets player aim to his left
                    {
                        omega->projBXdir = -omega->ply2->xdir;
                        omega->projBYdir = omega->ply2->ydir;
                    }
                    omega->projB->health = 3;
                    omega->shot = true;
                }
                omega->projB->drawModel(ballHBTex);
          glPopMatrix();
        }
    if(omega->projB->health<=0)
    {
        omega->ply2->thrown=false;
        omega->shot=false;
        omega->projB->Xpos=999;
        omega->projB->Ypos=999;
        omega->projB->box.x=999;
        omega->projB->box.y=999;
        omega->projB->box.width=0;
        omega->projB->box.height=0;
    }
    if(omega->ply2->thrown == false && omega->ply2->lastCase == 'R')
        omega->ProjBCurY = omega->ply2->PYpos, omega->ProjBCurX = omega->ply2->PXpos + 0.5;
    if(omega->ply2->thrown == false&&omega->ply2->lastCase=='L')
        omega->ProjBCurY = omega->ply2->PYpos, omega->ProjBCurX = omega->ply2->PXpos - 0.5;
    //----------------------------BALL CREATION------------------------------------//
    glPushMatrix();
        omega->Ball->box.height =  .2;
        omega->Ball->box.width = .05;
        omega->Ball->verticies[0].x = -0.15;
        omega->Ball->verticies[1].x = 0.15;
        omega->Ball->verticies[2].x = 0.15;
        omega->Ball->verticies[3].x = -0.15;
        omega->Ball->verticies[0].y = -0.15;
        omega->Ball->verticies[1].y = -0.15;
        omega->Ball->verticies[2].y = 0.15;
        omega->Ball->verticies[3].y = 0.15;
        omega->Ball->box.x = omega->Ball ->Xpos;
        omega->Ball->box.y = omega->Ball ->Ypos;
        omega->Ball->drawModel(omega->ballHBTex);
    glPopMatrix();
    //---------------------------Crosshair player 1 creation----------------------------------//
    float tmp1 = omega->ply->PXpos - omega->ply->xdir;
    float tmp2 = omega->ply->PYpos + omega->ply->ydir;
    float tmp3 = omega->ply->PXpos + omega->ply->xdir;
    if(omega->ply->lastCase=='L')
        makeModel(omega->cross, omega->crosshair, tmp1, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);
    if(omega->ply->lastCase=='R')
        makeModel(omega->cross, omega->crosshair, tmp3, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);


    //---------------------------Crosshair player 2 creation----------------------------------//
    float tmp4 = omega->ply2->PXpos - omega->ply2->xdir;
    float tmp5 = omega->ply2->PYpos + omega->ply2->ydir;
    float tmp6 = omega->ply2->PXpos + omega->ply2->xdir;
    if(omega->ply2->lastCase=='L')
        makeModel(omega->cross, omega->crosshair, tmp4, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);
    if(omega->ply2->lastCase=='R')
        makeModel(omega->cross, omega->crosshair, tmp6, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);


    if(lolTime-startTime>=2&&!pauseMenu)//wait three seconds to start the
    {
        KbMs->idle(pressed,omega->ply,omega->ply2);
    }

    omega->update();

}
GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    tw=width;
    th=height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,bool press[256])
{
}
