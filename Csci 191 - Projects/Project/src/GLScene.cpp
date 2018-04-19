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

    D = new timer();
    PAT= new timer();
    BPA= new timer();
    pCol = new timer();
    ballCollTimer = new timer();

     modelTeapot = new Model();
     modelTeapot2 = new Model();

     KbMs = new Inputs();

     projA = new Model();
     projB= new Model();
     plx = new parallax();

     plx2 = new parallax();
     ply = new player();
     ply2 = new player();
     wallA = new Model(); // left wall
     wallB = new Model(); // right wall
     wallC = new Model(); // top wall
     killBox = new Model();
     divide = new Model();


     //platform tiles
     platTileBL = new Model();
     platTileBR = new Model();
     platTileTL = new Model();
     platTileTR = new Model();
     platTileM = new Model();

     //left side tiles
     tile1=new Model();
     floor=new Model();
     tile2=new Model();
     tile3=new Model();
     tile4=new Model();
     tile5=new Model();
     tile6=new Model();
     tile7=new Model();

    //middle tile
     tile8=new Model();

    //right side tiles
     tile9=new Model();
     tile10=new Model();
     tile22=new Model();
     tile12=new Model();
     tile13=new Model();
     tile14=new Model();
     tile15=new Model();

     //platform tiles
     platTileBL = new Model();
     platTileBR = new Model();
     platTileTL = new Model();
     platTileTR = new Model();
     platTileM = new Model();


     playMod= new Model();
     resetMod= new Model();
     exitMod= new Model();

     cross=new Model();

     wallAHbawks = new Model(); // left wall
     wallBHbawks = new Model(); // right wall
     wallCHbawks = new Model(); // top wall
      GoalL= new Model();
     GoalR= new Model();
     sky = new skyBox;
     Ball = new Model(); // the ball
     BallHbawks = new Model();
     texGL= new textureLoader();
     texGR= new textureLoader();

     playTex=new textureLoader();
     resetTex=new textureLoader();
     exitTex=new textureLoader();
     tex0 = new textureLoader();
     tex1 = new textureLoader();
     tex2 = new textureLoader();
     tex3 = new textureLoader();
     texD = new textureLoader();
     ballHBTex = new textureLoader();
     ballHBTex2 = new textureLoader();
     tileTexfloor = new textureLoader();
     texc = new textureLoader();
     texH = new textureLoader();
     texSky1 = new textureLoader();
     texSky2 = new textureLoader();

     tileTex=new textureLoader();
     tileTex2=new textureLoader();
     tileTex3=new textureLoader();
     tileTex4=new textureLoader();
     tileTex5=new textureLoader();
     tileTex6=new textureLoader();
     tileTex7=new textureLoader();
     tileTex8=new textureLoader();
     tileTex9=new textureLoader();
     tileTex10=new textureLoader();
     tileTex11=new textureLoader();
     tileTex12=new textureLoader();
     tileTex13=new textureLoader();
     tileTex14=new textureLoader();
     tileTex15=new textureLoader();

     crosshair=new textureLoader();
    }

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    ground=-1.38;
    dirXX = 1, dirYY = 1;
    directionX = -2;
    directionY = 1;
    CurXpos = 0, CurYpos = 0;//-1.3 ; // Current x position of the ball, current y position of the ball,
    ballSpeed = 0.001;
    lastTime = glfwGetTime();
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

    plx->parallaxInit("images/box/sky.png",texSky1);
    plx2->parallaxInit("images/box/city.png",texSky2);
    wallA->modelInit("images/box/girder.png", true, tex1);
    wallB->modelInit("images/box/girder.png", true, tex2);
    wallC->modelInit("images/box/girder2.png", true, tex3);
    divide->modelInit("images/box/nothing.png", true, texD);
    hud->modelInit("images/box/hud.png", true, texH);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    projA->modelInit("images/box/ball.png", true, ballHBTex);
    projB->modelInit("images/box/ball.png", true, ballHBTex);
    BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

    floor->modelInit("images/box/block.png",true, tileTexfloor);
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

    playMod->modelInit("images/box/pMPlay.png", true, playTex);
    resetMod->modelInit("images/box/pMReset.png", true, resetTex);
    exitMod->modelInit("images/box/pMExit.png", true, exitTex);


    cross->modelInit("images/box/crosshair.png", true, crosshair);

    ply->PXpos = -2;
    ply2->PXpos = 2;

    ply->isPlayer = 1;
    ply2->isPlayer = 2;

    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();

    ProjACurY=ply->PYpos, ProjACurX=ply->PXpos;
    ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos;
    projA->Xpos=999;
    projA->Ypos=999;
    projA->box.x = projA ->Xpos;
    projA->box.y = projA ->Ypos;
    projB->Xpos=999;
    projB->Ypos=999;
    projB->box.x = projB ->Xpos;
    projB->box.y = projB ->Ypos;
    ply2->health=5;
    ply->health=5;

    ply->frameRate->start();
    startTime = glfwGetTime();
    Ball->Xpos=-2;
    Ball->Ypos=-0.5;

    return true;
}

float manhattanDist(player* ply, player* ply2)
{
     mX=abs(ply->PXpos-ply2->PXpos);
     mY=abs(ply->PYpos-ply2->PYpos);
    return mX+mY;
}


 bool GLScene::box_collision(Hbox rect1, Hbox rect2)
 {

 bool collisionX;
 bool collisionY;

collisionY = (((rect1.y-rect1.height) < (rect2.y + rect2.height) && (rect1.y+rect1.height) > (rect2.y - rect2.height))||((rect2.y-rect2.height) < (rect1.y + rect1.height) && (rect2.y+rect2.height) > (rect1.y - rect1.height)));
collisionX = (((rect1.x-rect1.width) < (rect2.x + rect2.width) && (rect1.x+rect1.width) > (rect2.x - rect2.width))||((rect2.x-rect2.width) < (rect1.x + rect1.width) && (rect2.x+rect2.width) > (rect1.x - rect1.width)));

    return collisionX && collisionY;
}


void GLScene::tileChange(Model* b, Model* t,textureLoader* TX)
{
    if(box_collision(b->box, t->box ) && D->getTicks() >= 200)
    {
                D->reset();
                directionY =  1;
                t->health-=1;
                t->isalive();
                ballSpeed=(0.125*8)/scale;

                if (t->health == 2)
                    t->modelInit("images/box/block2.png", true, TX);
                if (t->health == 1)
                    t->modelInit("images/box/block3.png", true, TX);
                    return;
    }

}


 bool topOfTile(player* ply,Model* tileT){
        if(
           (((ply->pl_pltfrm_box.x-ply->pl_pltfrm_box.width) < (tileT->box.x + tileT->box.width) && (ply->pl_pltfrm_box.x+ply->pl_pltfrm_box.width) > (tileT->box.x - tileT->box.width))
            ||((tileT->box.x-tileT->box.width) < (ply->pl_pltfrm_box.x + ply->pl_pltfrm_box.width) && (tileT->box.x+tileT->box.width) > (ply->pl_pltfrm_box.x - ply->pl_pltfrm_box.width)))
            &&(((ply->pl_pltfrm_box.y-ply->pl_pltfrm_box.height) < (tileT->box.y + tileT->box.height) ||
            (tileT->box.y+tileT->box.height) > (ply->pl_pltfrm_box.y - ply->pl_pltfrm_box.height))&&
            (ply->pl_pltfrm_box.y-ply->pl_pltfrm_box.height>tileT->box.y))
        )
        return true;
        else
        return false;



    }
bool GLScene::playerOnTile(player* ply)
{
             if((topOfTile(ply,tile1)||topOfTile(ply,tile2)||topOfTile(ply,tile3)||topOfTile(ply,tile4)||
                    topOfTile(ply,tile5)||topOfTile(ply,tile6)||topOfTile(ply,tile7)||topOfTile(ply,tile8)||
                    topOfTile(ply,tile9)||topOfTile(ply,tile10)||topOfTile(ply,tile22)||topOfTile(ply,tile12)||
                    topOfTile(ply,tile13)||topOfTile(ply,tile14)||topOfTile(ply,tile15)||topOfTile(ply,platTileBL)||
                    topOfTile(ply,platTileBR)||topOfTile(ply,platTileTL)||topOfTile(ply,platTileTR)||
                    topOfTile(ply,platTileM))||topOfTile(ply,floor))

               return true;
    else
        false;
}

void GLScene:: update()
{
    double currentTime = glfwGetTime();

    frameCount++;
    if(currentTime-lastTime>=1.0)
    {
        scale=(frameCount)/2;
        if(!setBallSpeed)
        {
             ballSpeed=(0.125*8)/scale;
             setBallSpeed=true;
        }
        frameCount=0;
        lastTime+=1.0;

        if(scale>0)
        {
            ply->delta=scale;
            ply2->delta=scale;
        }
    }

    if (!glfwInit())
    exit(EXIT_FAILURE);

    //-------------------------------------------------------------------------------------------------//
    //-------------------------------WALL COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if (box_collision(Ball->box, wallB->box))
    {
        directionX = -1;
        //hit=false;
        //velocity=resetV;
    }

    if (box_collision(Ball->box, wallA->box))
    {
        directionX = 1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, wallC->box))
    {
        directionY = -1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, killBox->box))
    {
       CurYpos=2;
       directionY=-1;
       //hit=false;
       //velocity=resetV;

        if(directionX==-1)
        CurXpos+=2;

        if(directionX==1)
        CurXpos-=2;
    }

    if(box_collision(ply->box,wallA->box))//player has hit the left wall
        ply->leftWC=true;//set to true so the player cannot move left
    else
        ply->leftWC=false;


    if(box_collision(ply->box,divide->box))//player has hit the right wall
        ply->rightWC=true;//set to true so the player cannot move right
    else
        ply->rightWC=false;




     if(box_collision(ply->box,wallC->box))//player has hit the top wall
        ply->topWC=true;//set to true so the player cannot move up
    else
        ply->topWC=false;


    if(box_collision(ply2->box,divide->box))//player has hit the left wall
        ply2->leftWC=true;//set to true so the player cannot move left
        else
        ply2->leftWC=false;



    if(box_collision(ply2->box,wallB->box))//player has hit the right wall
        ply2->rightWC=true;//set to true so the player cannot move right
    else
        ply2->rightWC=false;

    if(box_collision(projA->box,wallA->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,wallB->box)&& projA->myTime->getTicks() >= 200)
    {
       projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,wallC->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(projA->box,killBox->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(Ball->box,projA->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        directionX*=-1;
        directionY*=-1;
    }

    //-----------------PROJECTILE 2 WALL COLLISIONS---------------------------------------------//
      if(box_collision(projB->box,wallA->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,wallB->box)&& projB->myTime->getTicks() >= 200)
    {
       projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,wallC->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(projB->box,killBox->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(Ball->box,projB->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        directionX*=-1;
        directionY*=-1;
    }

    //---------------------------------------------------------------------------------------------------//
    //------------------------------- BALL -----------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    //----------------------PLAYER 1 --------------------------------------//
     if (box_collision(Ball->box, ply->box) && ply->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply->lastCase=='R')//lets player aim to his right
        {
            directionX = ply->xdir;
            directionY = ply->ydir;
        }

        if(ply->lastCase=='L')//lets player aim to his left
        {
            directionX = -ply->xdir;
            directionY = ply->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply->swinging=false;

    }

    //Set a bool if player is on tile
    ply->OnTile=playerOnTile(ply);

    //-----------------------PLAYER 2--------------------------------------//
     if (box_collision(Ball->box, ply2->box) && ply2->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply2->lastCase=='R')//lets player aim to his right
        {
            directionX = ply2->xdir;
            directionY = ply2->ydir;
        }

        if(ply2->lastCase=='L')//lets player aim to his left
        {
            directionX = -ply2->xdir;
            directionY = ply2->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply2->swinging=false;

    }
    if(box_collision(ply2->box,Ball->box)&&ply2->isalive()&&Ball->myTime->getTicks()>200)
    {
           Ball->myTime->reset();
           ply2->health--;
    }
    //Set a bool if player is on tile
    ply2->OnTile=playerOnTile(ply2);


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- BALL VS TILE COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//


    tileChange(Ball, tile1,tileTex);
    tileChange(Ball, tile2,tileTex2);
    tileChange(Ball, tile3,tileTex3);
    tileChange(Ball, tile4,tileTex4);
    tileChange(Ball, tile5,tileTex5);
    tileChange(Ball, tile6,tileTex6);
    tileChange(Ball, tile7,tileTex7);
    tileChange(Ball, tile8,tileTex8);
    tileChange(Ball, tile9,tileTex9);
    tileChange(Ball, tile10,tileTex10);
    tileChange(Ball, tile22,tileTex11);
    tileChange(Ball, tile12,tileTex12);
    tileChange(Ball, tile13,tileTex13);
    tileChange(Ball, tile14,tileTex14);
    tileChange(Ball, tile15,tileTex15);

    //----------------------------------
    //holding the ball or moving the ball
    //---------------------------------
    if(timeFromStart-startTime>=2)
     CurYpos = CurYpos + directionY * ballSpeed;
     if(timeFromStart-startTime>=2)
      CurXpos = CurXpos + directionX * ballSpeed;

     if(box_collision(Ball->box, ply->box)&&ply->hold)//lets the player hold the ball
    {
        Ball->Xpos=ply->PXpos;
        Ball->Ypos=ply->PYpos;
        if(ply->lastCase=='R')
        {
             directionY=ply->ydir;
             directionX=ply->xdir;
        }
        if(ply->lastCase=='L')
        {
             directionY=ply->ydir;
             directionX=-ply->xdir;
        }
             CurYpos=ply->PYpos;
             CurXpos=ply->PXpos;
             Ball->prevHeld=true;
    }
    //MOVING THE BALL
    else if(!hit)
    {
        Ball->Xpos = CurXpos;
        Ball->Ypos = CurYpos;
    }
     if(Ball->prevHeld&&!ply->hold)
     {
         prevBallSpeed=ballSpeed;
        ballSpeed += (0.010*200)/scale;
        Ball->prevHeld=false;
     }

     //-------------------------------------------------------------------
     //-----------------------Projectile----------------------------------
     //-------------------------------------------------------------------
     //------------------------Projectile A----------------------------------//
    if(box_collision(projA->box,ply2->box)&&ply2->isalive()&&projA->myTime->getTicks()>200)//ball from player one hits player 2
    {
           projA->myTime->reset();
           projA->health=0;
           ply2->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projA->box,ply->box)&&ply->swinging==true)//player one can hit his own wall
       {
           //projA->health--;
            projAXdir=ply->xdir;
            projAYdir=ply->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projA->box,ply->box)&&ply->swinging==false)//player one can hit his own ball
         ply->verticalVelocity=6;


    if(ply->thrown)
    {
        ProjACurY += (projAYdir * 3)/scale;
        ProjACurX += (projAXdir * 3)/scale;

        projA->Xpos = ProjACurX;
        projA->Ypos = ProjACurY;
    }

    //-------------------------projectile B-----------------------------------//

      if(box_collision(projB->box,ply->box)&&ply->isalive()&&projB->myTime->getTicks()>200)//ball from player one hits player
    {
           projB->myTime->reset();
           projB->health=0;
           ply->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projB->box,ply2->box)&&ply2->swinging==true)//player one can hit his own wall
       {
           //projB->health--;
            projBXdir=ply2->xdir;
            projBYdir=ply2->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projB->box,ply2->box)&&ply2->swinging==false)//player one can hit his own ball
         ply2->verticalVelocity=6;


    if(ply2->thrown)
    {
        ProjBCurY += (projBYdir * 3)/scale;
        ProjBCurX += (projBXdir * 3)/scale;

        projB->Xpos = ProjBCurX;
        projB->Ypos = ProjBCurY;
    }

}

void GLScene:: update2()
{
    double currentTime = glfwGetTime();

    frameCount++;
    if(currentTime-lastTime>=1.0)
    {
        scale=(frameCount)/2;
        if(!setBallSpeed)
        {
             ballSpeed=(0.125*8)/scale;
             setBallSpeed=true;
        }
        frameCount=0;
        lastTime+=1.0;

        if(scale>0)
        {
            ply->delta=scale;
            ply2->delta=scale;
        }
    }

    if (!glfwInit())
    exit(EXIT_FAILURE);

    //-------------------------------------------------------------------------------------------------//
    //-------------------------------WALL COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if (box_collision(Ball->box, wallB->box))
    {
        directionX = -1;
        //hit=false;
        //velocity=resetV;
    }

    if (box_collision(Ball->box, wallA->box))
    {
        directionX = 1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, wallC->box))
    {
        directionY = -1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, killBox->box))
    {
       CurYpos=2;
       directionY=-1;
       //hit=false;
       //velocity=resetV;

        if(directionX==-1)
        CurXpos+=2;

        if(directionX==1)
        CurXpos-=2;
    }

    if(box_collision(ply->box,wallA->box))//player has hit the left wall
        ply->leftWC=true;//set to true so the player cannot move left
    else
        ply->leftWC=false;



    if(box_collision(ply->box,wallB->box))//player has hit the right wall
        ply->rightWC=true;//set to true so the player cannot move right
    else
        ply->rightWC=false;



     if(box_collision(ply->box,wallC->box))//player has hit the top wall
        ply->topWC=true;//set to true so the player cannot move up
    else
        ply->topWC=false;



    if(box_collision(ply2->box,wallA->box))//player has hit the left wall
        ply2->leftWC=true;//set to true so the player cannot move left
    else
        ply2->leftWC=false;


    if(box_collision(ply2->box,wallB->box))//player has hit the right wall
        ply2->rightWC=true;//set to true so the player cannot move right
    else
        ply2->rightWC=false;

    if(box_collision(projA->box,wallA->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,wallB->box)&& projA->myTime->getTicks() >= 200)
    {
       projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,wallC->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(projA->box,killBox->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(Ball->box,projA->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        directionX*=-1;
        directionY*=-1;
    }

    //-----------------PROJECTILE 2 WALL COLLISIONS---------------------------------------------//
      if(box_collision(projB->box,wallA->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,wallB->box)&& projB->myTime->getTicks() >= 200)
    {
       projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,wallC->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(projB->box,killBox->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(Ball->box,projB->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        directionX*=-1;
        directionY*=-1;
    }

    //---------------------------------------------------------------------------------------------------//
    //------------------------------- BALL -----------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    //----------------------PLAYER 1 --------------------------------------//
     if (box_collision(Ball->box, ply->box) && ply->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply->lastCase=='R')//lets player aim to his right
        {
            directionX = ply->xdir;
            directionY = ply->ydir;
        }

        if(ply->lastCase=='L')//lets player aim to his left
        {
            directionX = -ply->xdir;
            directionY = ply->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply->swinging=false;

    }

    //Set a bool if player is on tile
    ply->OnTile=playerOnTile(ply);

    //-----------------------PLAYER 2--------------------------------------//
     if (box_collision(Ball->box, ply2->box) && ply2->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply2->lastCase=='R')//lets player aim to his right
        {
            directionX = ply2->xdir;
            directionY = ply2->ydir;
        }

        if(ply2->lastCase=='L')//lets player aim to his left
        {
            directionX = -ply2->xdir;
            directionY = ply2->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply2->swinging=false;

    }
    if(box_collision(ply2->box,Ball->box)&&ply2->isalive()&&Ball->myTime->getTicks()>200)
    {
           Ball->myTime->reset();
           ply2->health--;
    }
    //Set a bool if player is on tile
    ply2->OnTile=playerOnTile(ply2);


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- BALL VS TILE COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//


   if(box_collision(floor->box,Ball->box))
    directionY=1;

    //----------------------------------
    //holding the ball or moving the ball
    //---------------------------------
    if(timeFromStart-startTime>=2)
     CurYpos = CurYpos + directionY * ballSpeed;
     if(timeFromStart-startTime>=2)
      CurXpos = CurXpos + directionX * ballSpeed;

     if(box_collision(Ball->box, ply->box)&&ply->hold)//lets the player hold the ball
    {
        Ball->Xpos=ply->PXpos;
        Ball->Ypos=ply->PYpos;
        if(ply->lastCase=='R')
        {
             directionY=ply->ydir;
             directionX=ply->xdir;
        }
        if(ply->lastCase=='L')
        {
             directionY=ply->ydir;
             directionX=-ply->xdir;
        }
             CurYpos=ply->PYpos;
             CurXpos=ply->PXpos;
             Ball->prevHeld=true;
    }
    //MOVING THE BALL
    /*else if(!hit)
    {
        Ball->Xpos = CurXpos;
        Ball->Ypos = CurYpos;
    }*/
     if(Ball->prevHeld&&!ply->hold)
     {
         prevBallSpeed=ballSpeed;
        ballSpeed += (0.010*200)/scale;
        Ball->prevHeld=false;
     }

     //-------------------------------------------------------------------
     //-----------------------Projectile----------------------------------
     //-------------------------------------------------------------------
     //------------------------Projectile A----------------------------------//
    if(box_collision(projA->box,ply2->box)&&ply2->isalive()&&projA->myTime->getTicks()>200)//ball from player one hits player 2
    {
           projA->myTime->reset();
           projA->health=0;
           ply2->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projA->box,ply->box)&&ply->swinging==true)//player one can hit his own wall
       {
           //projA->health--;
            projAXdir=ply->xdir;
            projAYdir=ply->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projA->box,ply->box)&&ply->swinging==false)//player one can hit his own ball
         ply->verticalVelocity=6;


    if(ply->thrown)
    {
        ProjACurY += (projAYdir * 3)/scale;
        ProjACurX += (projAXdir * 3)/scale;

        projA->Xpos = ProjACurX;
        projA->Ypos = ProjACurY;
    }

    //-------------------------projectile B-----------------------------------//

      if(box_collision(projB->box,ply->box)&&ply->isalive()&&projB->myTime->getTicks()>200)//ball from player one hits player
    {
           projB->myTime->reset();
           projB->health=0;
           ply->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projB->box,ply2->box)&&ply2->swinging==true)//player one can hit his own wall
       {
           //projB->health--;
            projBXdir=ply2->xdir;
            projBYdir=ply2->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projB->box,ply2->box)&&ply2->swinging==false)//player one can hit his own ball
         ply2->verticalVelocity=6;


    if(ply2->thrown)
    {
        ProjBCurY += (projBYdir * 3)/scale;
        ProjBCurX += (projBXdir * 3)/scale;

        projB->Xpos = ProjBCurX;
        projB->Ypos = ProjBCurY;
    }

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
        D->start();
        projA->myTime->start();
        projB->myTime->start();
        BPA->start();
        pCol->start();
        ply->myTime->start();
        Ball->myTime->start();
        ply->swingTimer->start();
        ply2->swingTimer->start();
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
    if(ply->health>0)
    {
    glPushMatrix();
        ply->actions();
        ply->box.x = ply->PXpos;
        ply->box.y = ply->PYpos;
        ply->pl_pltfrm_box.x = ply ->PXpos;
        ply->pl_pltfrm_box.y = ply -> PYpos;
        ply->pl_pltfrm_box.height = 0.6;
        ply->pl_pltfrm_box.width = 0.07;
        ply->box.height=0.1;
        ply->trueHeight=0.1;
        ply->box.width=0.3;
        update();
        ply->drawplayer();
    glPopMatrix();
    }
     if(ply->health<=0)
    {
            ply->box.height=0;
            ply->box.width=0;
            ply->box.x=999;
            ply->box.y=999;
            ply->pl_pltfrm_box.x =999;
            ply->pl_pltfrm_box.y = 999;
            ply->pl_pltfrm_box.height = 0;
            ply->pl_pltfrm_box.width = 0;
            ply->PXpos=999;
            ply->PYpos=999;
            ply->box.x=999;
            ply->box.y=999;
    }


    if(ply2->health>0)
    {
        glPushMatrix();
            ply2->actions();
            ply2->box.x = ply2->PXpos;
            ply2->box.y = ply2->PYpos;
            ply2->pl_pltfrm_box.x = ply2 ->PXpos;
            ply2->pl_pltfrm_box.y = ply2 -> PYpos;
            ply2->pl_pltfrm_box.height = 0.6;
            ply2->pl_pltfrm_box.width = 0.07;
            ply2->box.height=0.5;
            ply2->box.width=0.2;
            update();
            ply2->drawplayer();
        glPopMatrix();
    }
    if(ply2->health<=0)
    {
            ply2->box.height=0;
            ply2->box.width=0;
            ply2->box.x=999;
            ply2->box.y=999;
            ply2->pl_pltfrm_box.x =999;
            ply2->pl_pltfrm_box.y = 999;
            ply2->pl_pltfrm_box.height = 0;
            ply2->pl_pltfrm_box.width = 0;
            ply2->PXpos=999;
            ply2->PYpos=999;
            ply2->box.x=999;
            ply2->box.y=999;
    }

      //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//

    // model , texture, xpos,ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
    if(tile1->isalive())
    makeModel(tile1,tileTex,-3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile2->isalive())
    makeModel(tile2,tileTex2,-2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile3->isalive())
    makeModel(tile3,tileTex3,-2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile4->isalive())
    makeModel(tile4,tileTex4,-1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile5->isalive())
    makeModel(tile5,tileTex5,-1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile6->isalive())
    makeModel(tile6,tileTex6,-0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile7->isalive())
    makeModel(tile7,tileTex7,-0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile8->isalive())
    makeModel(tile8,tileTex8, 0.00,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile9->isalive())
    makeModel(tile9,tileTex9, 0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile10->isalive())
    makeModel(tile10,tileTex10, 0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile22->isalive())
    makeModel(tile22,tileTex11, 1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile12->isalive())
    makeModel(tile12,tileTex12, 1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile13->isalive())
    makeModel(tile13,tileTex13, 2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile14->isalive())
    makeModel(tile14,tileTex14, 2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile15->isalive())
    makeModel(tile15,tileTex15, 3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);


    //left wall
    makeModel(wallA,tex1,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);

    //right wall
    makeModel(wallB,tex2,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);

    //bottom wall
    makeModel(killBox,texc,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);

    //dividing wall
    makeModel(divide,texD,0,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.1,88);

    //top wall
    makeModel(wallC,tex3,0,2.1,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);




    //ball creation
    //makeModel(Ball,ballHBTex,-0.5,-0.5,-0.15,-0.15,0.15,-0.15,0.15,0.15,-0.15,0.15,0.3,0.3);
    //----------------Projectile creation------------------------------------------------//
        if(ply->thrown)
        {
              glPushMatrix();
            projA->box.height =  .2;
            projA->box.width = .05;

            projA->verticies[0].x = -0.15;
            projA->verticies[1].x = 0.15;
            projA->verticies[2].x = 0.15;
            projA->verticies[3].x = -0.15;
            projA->verticies[0].y = -0.15;
            projA->verticies[1].y = -0.15;
            projA->verticies[2].y = 0.15;
            projA->verticies[3].y = 0.15;
            projA->box.x = projA ->Xpos;
            projA->box.y = projA ->Ypos;

            if(!shot)
            {
                if(ply->lastCase=='R')//lets player aim to his right
                {
                    projAXdir = ply->xdir;
                    projAYdir = ply->ydir;
                }

                if(ply->lastCase=='L')//lets player aim to his left
                {

                    projAXdir = -ply->xdir;
                    projAYdir = ply->ydir;
                }

                projA->health = 3;
                shot = true;
            }
            projA->drawModel(ballHBTex);
          glPopMatrix();
        }

    if(projA->health<=0)
    {
        ply->thrown=false;
        shot=false;
        projA->Xpos=999;
        projA->Ypos=999;

        projA->box.x=999;
        projA->box.y=999;
        projA->box.width=0;
        projA->box.height=0;
    }


    if(ply->thrown==false&&ply->lastCase=='R')
        ProjACurY=ply->PYpos, ProjACurX=ply->PXpos+0.5;
     if(ply->thrown==false&&ply->lastCase=='L')
           ProjACurY=ply->PYpos, ProjACurX=ply->PXpos-0.5;

    //-------------------------projectile b-----------------------------------------//
    if(ply2->thrown)
        {
              glPushMatrix();
            projB->box.height =  .2;
            projB->box.width = .05;

            projB->verticies[0].x = -0.15;
            projB->verticies[1].x = 0.15;
            projB->verticies[2].x = 0.15;
            projB->verticies[3].x = -0.15;
            projB->verticies[0].y = -0.15;
            projB->verticies[1].y = -0.15;
            projB->verticies[2].y = 0.15;
            projB->verticies[3].y = 0.15;
            projB->box.x = projB ->Xpos;
            projB->box.y = projB ->Ypos;

            if(!shot)
            {
                if(ply2->lastCase=='R')//lets player aim to his right
                {
                    projBXdir = ply2->xdir;
                    projBYdir = ply2->ydir;
                }

                if(ply2->lastCase=='L')//lets player aim to his left
                {

                    projBXdir = -ply2->xdir;
                    projBYdir = ply2->ydir;
                }

                projB->health = 3;
                shot = true;
            }
            projB->drawModel(ballHBTex);
          glPopMatrix();
        }

    if(projB->health<=0)
    {
        ply2->thrown=false;
        shot=false;
        projB->Xpos=999;
        projB->Ypos=999;

        projB->box.x=999;
        projB->box.y=999;
        projB->box.width=0;
        projB->box.height=0;
    }


    if(ply2->thrown==false&&ply2->lastCase=='R')
        ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos+0.5;
     if(ply2->thrown==false&&ply2->lastCase=='L')
           ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos-0.5;


    //----------------------------BALL CREATION------------------------------------//
    glPushMatrix();
        Ball->box.height =  .2;
        Ball->box.width = .05;
        Ball->verticies[0].x = -0.15;
        Ball->verticies[1].x = 0.15;
        Ball->verticies[2].x = 0.15;
        Ball->verticies[3].x = -0.15;
        Ball->verticies[0].y = -0.15;
        Ball->verticies[1].y = -0.15;
        Ball->verticies[2].y = 0.15;
        Ball->verticies[3].y = 0.15;
        Ball->box.x = Ball ->Xpos;
        Ball->box.y = Ball ->Ypos;
       update();
        Ball->drawModel(ballHBTex);
    glPopMatrix();


    glPushMatrix();

    //---------------------------Crosshair player 1 creation----------------------------------//
    float tmp1 = ply->PXpos - ply->xdir;
    float tmp2 = ply->PYpos + ply->ydir;
    float tmp3 = ply->PXpos + ply->xdir;

    if(ply->lastCase=='L')
        makeModel(cross, crosshair, tmp1, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(ply->lastCase=='R')
        makeModel(cross, crosshair, tmp3, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(timeFromStart-startTime>=2&&!pauseMenu)//wait three seconds to start the game
    KbMs->idle(pressed,ply,ply2);

    //---------------------------Crosshair player 2 creation----------------------------------//
    float tmp4 = ply2->PXpos - ply2->xdir;
    float tmp5 = ply2->PYpos + ply2->ydir;
    float tmp6 = ply2->PXpos + ply2->xdir;

    if(ply2->lastCase=='L')
        makeModel(cross, crosshair, tmp4, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(ply2->lastCase=='R')
        makeModel(cross, crosshair, tmp6, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

     if(pauseMenu)
    {
        if(pauseChoice)
        {
            if(menuPos==1)//reset the gameee
            {
                pauseMenu=false;
               // reset();
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

    if(pressed['1'])
    {
        tw+=10;
        th+=5;
    }

    if(pressed['2'])
    {
        tw-=10;
        th-=5;
    }
     if(pressed['3'])
    {
        mXpos+=10;
        //mYpos+=5;
    }

    if(pressed['4'])
    {
        mXpos-=10;
        //mYpos-=5;
    }
      if(pressed['5'])
    {
        //mXpos+=10;
        mYpos+=5;
    }

    if(pressed['6'])
    {
        //mXpos-=10;
        mYpos-=5;
    }
    /*if(pressed['D']&&!ply->rightWC&&mX>1)
    {
        mXpos-=1/mX;
        tw+=2/mX;
        th+=1/mX;
    }
    if(pressed['A']&&!ply->leftWC&&mX>1)
    {
        mXpos+=1/mX;
        tw-=2/mX;
        th-=1/mX;
    }*/

    //mXpos-=mX;
   // cout<<mXpos<<endl;
   /*manhattanDist(ply,ply2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
      gluOrtho2D(ply->PXpos-600/2,ply->PXpos+600/2,ply->PYpos-600/2,ply->PYpos+600/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/



    //cout<<mX<<" , "<<mY<<endl;
    //cout<<tw<<","<<th<<endl;
    //cout<<mXpos<<", "<<mYpos<<endl;
    //if(level==2)
    //glViewport(mXpos, mYpos, tw, th);
    //if(mX<2)
      //   glViewport((-1*(ply2->PXpos + ply->PXpos)/2)*63, mYpos, tw*1.5, th*1.25);
   /* if(tw*mX>=tw&&tw*mX<2500)
    glViewport((-1*(ply2->PXpos + ply->PXpos)/2)*63, mYpos, tw*mX, th*mX);
    if(tw*mX<=tw)
    glViewport((-1*(ply2->PXpos + ply->PXpos)/2)*63, mYpos, tw/mX, th/mX);*/
    //cout<<tile1->health<<endl;
}

GLint GLScene::drawGLScene2(bool pressed[256])
{

  timeFromStart=glfwGetTime();

      //-----------------------------------------------------------------------------------------------//
     //------------------------------------------ TIMERS ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
        D->start();
        projA->myTime->start();
        projB->myTime->start();
        BPA->start();
        pCol->start();
        ply->myTime->start();
        Ball->myTime->start();
        ply->swingTimer->start();
        ply2->swingTimer->start();
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
    if(ply->health>0)
    {
    glPushMatrix();
        ply->actions();
        ply->box.x = ply->PXpos;
        ply->box.y = ply->PYpos;
        ply->pl_pltfrm_box.x = ply ->PXpos;
        ply->pl_pltfrm_box.y = ply -> PYpos;
        ply->pl_pltfrm_box.height = 0.6;
        ply->pl_pltfrm_box.width = 0.07;
        ply->box.height=0.1;
        ply->trueHeight=0.1;
        ply->box.width=0.3;
        update2();
        ply->drawplayer();
    glPopMatrix();
    }
     if(ply->health<=0)
    {
            ply->box.height=0;
            ply->box.width=0;
            ply->box.x=999;
            ply->box.y=999;
            ply->pl_pltfrm_box.x =999;
            ply->pl_pltfrm_box.y = 999;
            ply->pl_pltfrm_box.height = 0;
            ply->pl_pltfrm_box.width = 0;
            ply->PXpos=999;
            ply->PYpos=999;
            ply->box.x=999;
            ply->box.y=999;
    }


    if(ply2->health>0)
    {
        glPushMatrix();
            ply2->actions();
            ply2->box.x = ply2->PXpos;
            ply2->box.y = ply2->PYpos;
            ply2->pl_pltfrm_box.x = ply2 ->PXpos;
            ply2->pl_pltfrm_box.y = ply2 -> PYpos;
            ply2->pl_pltfrm_box.height = 0.6;
            ply2->pl_pltfrm_box.width = 0.07;
            ply2->box.height=0.5;
            ply2->box.width=0.2;
            update();
            ply2->drawplayer();
        glPopMatrix();
    }
    if(ply2->health<=0)
    {
            ply2->box.height=0;
            ply2->box.width=0;
            ply2->box.x=999;
            ply2->box.y=999;
            ply2->pl_pltfrm_box.x =999;
            ply2->pl_pltfrm_box.y = 999;
            ply2->pl_pltfrm_box.height = 0;
            ply2->pl_pltfrm_box.width = 0;
            ply2->PXpos=999;
            ply2->PYpos=999;
            ply2->box.x=999;
            ply2->box.y=999;
            tile6->health=3;
    }

      //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//

    // model , texture, xpos,ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
    makeModel(floor,tileTex,0,-2.08,-3.5,-0.00,3.5,-0.00,3.5,0.40,-3.5,0.40,7,.3);

    //left wall
    makeModel(wallA,tex1,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);

    //right wall
    makeModel(wallB,tex2,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);

    //bottom wall
    makeModel(killBox,texc,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);

    //dividing wall
        divide->box.width=0;
        divide->box.height=0;



    //top wall
    makeModel(wallC,tex3,0,2.1,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);
        makeModel(platTileBL, tileTex, -1.5, -1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
        makeModel(platTileBR, tileTex, 1.5, -1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
        makeModel(platTileTL, tileTex, -1.5, 1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
        makeModel(platTileTR, tileTex, 1.5, 1.0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);
        makeModel(platTileM, tileTex, 0, 0, -0.5, -0.00, 0.5, -0.00, 0.5, 0.10, -0.5, 0.10, 0.3, 0.3);

           //left goal
        makeModel(GoalL,texGL,-3,0,-0.2,0.5,0.2,0.5,0.2,-0.5,-0.2,-0.5,0.5,1);

        //right goal
        makeModel(GoalR,texGL,3,0,-0.2,0.5,0.2,0.5,0.2,-0.5,-0.2,-0.5,0.5,1);



    //ball creation
    //makeModel(Ball,ballHBTex,-0.5,-0.5,-0.15,-0.15,0.15,-0.15,0.15,0.15,-0.15,0.15,0.3,0.3);
    //----------------Projectile creation------------------------------------------------//
        if(ply->thrown)
        {
              glPushMatrix();
            projA->box.height =  .2;
            projA->box.width = .05;

            projA->verticies[0].x = -0.15;
            projA->verticies[1].x = 0.15;
            projA->verticies[2].x = 0.15;
            projA->verticies[3].x = -0.15;
            projA->verticies[0].y = -0.15;
            projA->verticies[1].y = -0.15;
            projA->verticies[2].y = 0.15;
            projA->verticies[3].y = 0.15;
            projA->box.x = projA ->Xpos;
            projA->box.y = projA ->Ypos;

            if(!shot)
            {
                if(ply->lastCase=='R')//lets player aim to his right
                {
                    projAXdir = ply->xdir;
                    projAYdir = ply->ydir;
                }

                if(ply->lastCase=='L')//lets player aim to his left
                {

                    projAXdir = -ply->xdir;
                    projAYdir = ply->ydir;
                }

                projA->health = 3;
                shot = true;
            }
            projA->drawModel(ballHBTex);
          glPopMatrix();
        }

    if(projA->health<=0)
    {
        ply->thrown=false;
        shot=false;
        projA->Xpos=999;
        projA->Ypos=999;

        projA->box.x=999;
        projA->box.y=999;
        projA->box.width=0;
        projA->box.height=0;
    }


    if(ply->thrown==false&&ply->lastCase=='R')
        ProjACurY=ply->PYpos, ProjACurX=ply->PXpos+0.5;
     if(ply->thrown==false&&ply->lastCase=='L')
           ProjACurY=ply->PYpos, ProjACurX=ply->PXpos-0.5;

    //-------------------------projectile b-----------------------------------------//
    if(ply2->thrown)
        {
              glPushMatrix();
            projB->box.height =  .2;
            projB->box.width = .05;

            projB->verticies[0].x = -0.15;
            projB->verticies[1].x = 0.15;
            projB->verticies[2].x = 0.15;
            projB->verticies[3].x = -0.15;
            projB->verticies[0].y = -0.15;
            projB->verticies[1].y = -0.15;
            projB->verticies[2].y = 0.15;
            projB->verticies[3].y = 0.15;
            projB->box.x = projB ->Xpos;
            projB->box.y = projB ->Ypos;

            if(!shot)
            {
                if(ply2->lastCase=='R')//lets player aim to his right
                {
                    projBXdir = ply2->xdir;
                    projBYdir = ply2->ydir;
                }

                if(ply2->lastCase=='L')//lets player aim to his left
                {

                    projBXdir = -ply2->xdir;
                    projBYdir = ply2->ydir;
                }

                projB->health = 3;
                shot = true;
            }
            projB->drawModel(ballHBTex);
          glPopMatrix();
        }

    if(projB->health<=0)
    {
        ply2->thrown=false;
        shot=false;
        projB->Xpos=999;
        projB->Ypos=999;

        projB->box.x=999;
        projB->box.y=999;
        projB->box.width=0;
        projB->box.height=0;
    }


    if(ply2->thrown==false&&ply2->lastCase=='R')
        ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos+0.5;
     if(ply2->thrown==false&&ply2->lastCase=='L')
           ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos-0.5;


    //----------------------------BALL CREATION------------------------------------//
    glPushMatrix();
        Ball->box.height =  .2;
        Ball->box.width = .05;
        Ball->verticies[0].x = -0.15;
        Ball->verticies[1].x = 0.15;
        Ball->verticies[2].x = 0.15;
        Ball->verticies[3].x = -0.15;
        Ball->verticies[0].y = -0.15;
        Ball->verticies[1].y = -0.15;
        Ball->verticies[2].y = 0.15;
        Ball->verticies[3].y = 0.15;
        Ball->box.x = Ball ->Xpos;
        Ball->box.y = Ball ->Ypos;
       update();
        Ball->drawModel(ballHBTex);
    glPopMatrix();


    glPushMatrix();

    //---------------------------Crosshair player 1 creation----------------------------------//
    float tmp1 = ply->PXpos - ply->xdir;
    float tmp2 = ply->PYpos + ply->ydir;
    float tmp3 = ply->PXpos + ply->xdir;

    if(ply->lastCase=='L')
        makeModel(cross, crosshair, tmp1, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(ply->lastCase=='R')
        makeModel(cross, crosshair, tmp3, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(timeFromStart-startTime>=2&&!pauseMenu)//wait three seconds to start the game
    KbMs->idle(pressed,ply,ply2);

    //---------------------------Crosshair player 2 creation----------------------------------//
    float tmp4 = ply2->PXpos - ply2->xdir;
    float tmp5 = ply2->PYpos + ply2->ydir;
    float tmp6 = ply2->PXpos + ply2->xdir;

    if(ply2->lastCase=='L')
        makeModel(cross, crosshair, tmp4, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

    if(ply2->lastCase=='R')
        makeModel(cross, crosshair, tmp6, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);

     if(pauseMenu)
    {
        if(pauseChoice)
        {
            if(menuPos==1)//reset the gameee
            {
                pauseMenu=false;
                //reset();
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
