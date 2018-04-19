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

levelAlpha* alpha;

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

    // modelTeapot = new Model();
     //modelTeapot2 = new Model();
     alpha= new levelAlpha();

     KbMs = new Inputs();

     plx = new parallax();
     plx2 = new parallax();

     playMod= new Model();
     resetMod= new Model();
     exitMod= new Model();

     //cross=new Model();

     //wallAHbawks = new Model(); // left wall
    // wallBHbawks = new Model(); // right wall
     //wallCHbawks = new Model(); // top wall
     // GoalL= new Model();
    // GoalR= new Model();
     sky = new skyBox;
     //Ball = new Model(); // the ball
     //BallHbawks = new Model();
    // texGL= new textureLoader();
     //texGR= new textureLoader();

     playTex=new textureLoader();
     resetTex=new textureLoader();
     exitTex=new textureLoader();

     //tex0 = new textureLoader();
     //tex1 = new textureLoader();
     //tex2 = new textureLoader();
     //tex3 = new textureLoader();
     //texD = new textureLoader();
    // ballHBTex = new textureLoader();
    // ballHBTex2 = new textureLoader();
     //texc = new textureLoader();
     //texH = new textureLoader();
     texSky1 = new textureLoader();
     texSky2 = new textureLoader();
    }

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
   // ground=-1.38;
    //levelOne=true;
    //levelTwo=false;
    //dirXX = 1, dirYY = 1;
    //directionX = -2;
   // directionY = 1;
    //CurXpos = 0, CurYpos = 0;//-1.3 ; // Current x position of the ball, current y position of the ball,
    //ballSpeed = 0.001;
    lastTime = glfwGetTime();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
    //modelTeapot->modelInit("images/player/player0.png", true, tex0);
    //modelTeapot2->modelInit("images/player/player0.png", true, tex0);
    //plx->parallaxInit("images/box/band-BG2.png");
    //ply->playerInit();
    //ply2->playerInit();
    sky->loadTextures();

    plx->parallaxInit("images/box/sky.png",texSky1);
    plx2->parallaxInit("images/box/city.png",texSky2);
   /* wallA->modelInit("images/box/girder.png", true, tex1);
    wallB->modelInit("images/box/girder.png", true, tex2);
    wallC->modelInit("images/box/girder2.png", true, tex3);
    divide->modelInit("images/box/nothing.png", true, texD);
    hud->modelInit("images/box/hud.png", true, texH);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    projA->modelInit("images/box/ball.png", true, ballHBTex);
    projB->modelInit("images/box/ball.png", true, ballHBTex);
    BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

    tile1->modelInit("images/box/nothing2.png", true, tileTex);
    tile2->modelInit("images/box/block.png", true, tileTex2);
    tile3->modelInit("images/box/block.png", true, tileTex3);
    tile4->modelInit("images/box/block.png", true, tileTex4);
    tile5->modelInit("images/box/block.png", true, tileTex5);
    tile6->modelInit("images/box/block.png", true, tileTex6);
    tile7->modelInit("images/box/block.png", true, tileTex7);
    tile8->modelInit("images/box/block.png", true, tileTex8);
    tile9->modelInit("images/box/block.png", true, tileTex9);
    tile10->modelInit("images/box/block.png", true, tileTex10);
    tile22->modelInit("images/box/block.png", true, tileTex11);
    tile12->modelInit("images/box/block.png", true, tileTex12);
    tile13->modelInit("images/box/block.png", true, tileTex13);
    tile14->modelInit("images/box/block.png", true, tileTex14);
    tile15->modelInit("images/box/nothing2.png", true, tileTex15);
     GoalL->modelInit("images/box/hitbox.png",true,texGL);
    GoalR->modelInit("images/box/hitbox.png",true,texGR);
    platTileBL->modelInit("images/box/block.png", true, tileTex);
    platTileBR->modelInit("images/box/block.png", true, tileTex);
    platTileTL->modelInit("images/box/block.png", true, tileTex);
    platTileTR->modelInit("images/box/block.png", true, tileTex);
    platTileM->modelInit("images/box/block.png", true, tileTex);
    */
    playMod->modelInit("images/box/pMPlay.png", true, playTex);
    resetMod->modelInit("images/box/pMReset.png", true, resetTex);
    exitMod->modelInit("images/box/pMExit.png", true, exitTex);

    //cross->modelInit("images/box/crosshair.png", true, crosshair);

    //ply->frameRate->start();
    startTime = glfwGetTime();

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

      timeFromStart=glfwGetTime();

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
