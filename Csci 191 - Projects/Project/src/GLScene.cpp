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
//#include<levelAlpha.h>
//#include<levelOmega.h>

//levelAlpha* alpha;
//levelOmega* omega;

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

    pauseMenu = false;

    //alpha= new levelAlpha();
    //omega = new levelOmega();

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
     /*------------------------------------------*/
      //left side tiles
         tile1 = new Model();
         tile2 = new Model();
         tile3 = new Model();
         tile4 = new Model();
         tile5 = new Model();
         tile6 = new Model();
         tile7 = new Model();
        //middle tile
         tile8 = new Model();
        //right side tiles
         tile9 = new Model();
        tile10 = new Model();
         tile22 = new Model();
         tile12 = new Model();
         tile13 = new Model();
         tile14 = new Model();
         tile15 = new Model();

        ply = new player();
        ply2 = new player();
         hitTimer=new timer();
      hitTimer2=new timer();
       speedInc=0.07;
        speedDecr=0.0045;
     ballTex = new textureLoader();
     killBox= new Model();
     ply2Score=0;
        leftWall = new Model(); // left wall
        rightWall = new Model(); // right wall
      topWall = new Model(); // top wall
     divide = new Model();
    ballSpdBfrAcc=0.5;
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
         leftWallTex= new textureLoader();
         rightWallTex= new textureLoader();
         topWallTex= new textureLoader();
         divWallTex= new textureLoader();
         D= new timer();
         BPA = new timer();
         pCol= new timer();
          playerModel = new Model();
          playerModel2 = new Model();
         plyTex = new textureLoader();
        projTex = new textureLoader();
        projTex2 = new textureLoader();
        cross = new Model();
        crosshair = new textureLoader();
        Ball = new Model();
        setBallSpeed=false;
        scale=1;
        ballDirX=-1;
        ballDirY=1;
     tile1->tag="left";
     tile2->tag="left";
     tile3->tag="left";
     tile4->tag="left";
     tile5->tag="left";
     tile6->tag="left";
     tile7->tag="left";

     tile8->tag="middle";
     tile9->tag="right";
     tile10->tag="right";
     tile12->tag="right";
     tile13->tag="right";
     tile14->tag="right";
     tile15->tag="right";
     threeMod= new Model();
     twoMod= new Model();
     oneMod= new Model();
     zeroMod= new Model();
     threeTex= new textureLoader();
     twoTex= new textureLoader();
     oneTex= new textureLoader();
     zeroTex= new textureLoader();
     playButton= new Model();
     infoButton = new Model();
     exitButton = new Model();
     infoPage= new Model();
     tex3 = new textureLoader();
    tex4 = new textureLoader();
    tex5 = new textureLoader();
    tex6 = new textureLoader();
    menu[0]=true;
    //menu[1]=false;
    //menu[2]=false;
    //menu[3]=false;
    //menu[4]=false;
    plyScoreLast=0;
    score=0;


     /*------------------------------------------*/
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

    /* declare model init, player init in scene init*/
    playerModel->modelInit("images/player/player0.png", true, plyTex);
    ply->playerInit();
    playerModel2->modelInit("images/player/player0.png", true, plyTex);
    ply2->playerInit();

    ply->PXpos=-2;
    ply->PYpos=-1;
    ply2->PXpos=2;
    ply2->PYpos=-1;
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
    leftWall->modelInit("images/box/girder.png", true, leftWallTex);
    rightWall->modelInit("images/box/girder.png", true, rightWallTex);
    topWall->modelInit("images/box/girder2.png", true, topWallTex);
    divide->modelInit("images/box/block.png", true, divWallTex);
    cross->modelInit("images/box/crosshair.png", true, crosshair);
    ply->projA->modelInit("images/box/Fire.png", true, projTex);
    ply2->projA->modelInit("images/box/Fire2.png", true, projTex2);
    Ball->modelInit("images/box/ball.png", true, ballTex);
    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();
    threeMod->modelInit("images/box/three.png", true, threeTex);
    twoMod->modelInit("images/box/two.png", true, twoTex);
    oneMod->modelInit("images/box/one.png", true, oneTex);
    zeroMod->modelInit("images/box/zero.png", true, zeroTex);
    playButton->modelInit("images/box/playbutton.png",true,tex3);
    infoButton->modelInit("images/box/info.png",true,tex4);
    exitButton->modelInit("images/box/exit.png",true,tex5);
    infoPage->modelInit("images/box/InfoPage.png",true,tex6);
    setBallDir();

    /*------------------------*/

    startTime = glfwGetTime();

    return true;
}
int GLScene::ballPosHit(Model* projA,Model* Ball)
{
    //if the projectile hits the ball on the TOP half of the ball   //if((Ball->Ypos-Ball->box.height)>(projA->Ypos+projA->box.height))
   if(
           (((projA->box.x-projA->box.width) < (Ball->box.x + Ball->box.width) &&
            (projA->box.x+projA->box.width) > (Ball->box.x - Ball->box.width)) ||
            ((Ball->box.x-Ball->box.width) < (projA->box.x + projA->box.width) &&
             (Ball->box.x+Ball->box.width) > (projA->box.x - projA->box.width)))&&

            (((projA->box.y-projA->box.height) < (Ball->box.y + Ball->box.height) ||
            (Ball->box.y+Ball->box.height) > (projA->box.y - projA->box.height))&&
            (projA->box.y-projA->box.height>Ball->box.y))
        )
    return 1;
    //if the projectile hits thte ball on the BOTTOM half of the ball //if((Ball->Ypos+Ball->box.height)<(projA->Ypos-projA->box.height))
    if(
                (((projA->box.x-projA->box.width) < (Ball->box.x + Ball->box.width) &&
            (projA->box.x+projA->box.width) > (Ball->box.x - Ball->box.width)) ||
            ((Ball->box.x-Ball->box.width) < (projA->box.x + projA->box.width) &&
             (Ball->box.x+Ball->box.width) > (projA->box.x - projA->box.width)))&&

            (((projA->box.y+projA->box.height) > (Ball->box.y - Ball->box.height) ||
            (Ball->box.y-Ball->box.height) < (projA->box.y + projA->box.height))&&
            (projA->box.y+projA->box.height<Ball->box.y))
        )
    return 2;
    else return 0;
}

float manhattanD(player* ply, Model* Ball)
{
      float mX=fabs(ply->PXpos-Ball->Xpos);
     float mY=fabs(ply->PYpos-Ball->Ypos);
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
                ballDirY =  1;
                if((b->tag=="one"&&t->tag=="right")||(b->tag=="two"&&t->tag=="left"))
                {
                    cout<<t->health<<endl;
                    t->health-=1;
                    ballSpeed=(0.3*8)/scale;//(0.125*8)/scale;
                    hitCount=0;
                }
                t->isalive();


                if(t->health>2)
                    t->modelInit("images/box/block.png", true, TX);
                if (t->health == 2)
                    t->modelInit("images/box/block2.png", true, TX);
                if (t->health == 1)
                    t->modelInit("images/box/block3.png", true, TX);
                    return;
    }

}
bool GLScene::playerOnTile(player* ply)
{
             if((topOfTile(ply,tile1)||topOfTile(ply,tile2)||topOfTile(ply,tile3)||topOfTile(ply,tile4)||
                    topOfTile(ply,tile5)||topOfTile(ply,tile6)||topOfTile(ply,tile7)||topOfTile(ply,tile8)||
                    topOfTile(ply,tile9)||topOfTile(ply,tile10)||topOfTile(ply,tile22)||topOfTile(ply,tile12)||
                    topOfTile(ply,tile13)||topOfTile(ply,tile14)||topOfTile(ply,tile15)))
               return true;
    else
        false;
}
bool GLScene::topOfTile(player* ply,Model* tileT){
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
void GLScene::reset()
{
    tile1->health=3;
    tile2->health=3;
    tile3->health=3;
    tile4->health=3;
    tile5->health=3;
    tile6->health=3;
    tile7->health=3;
    tile8->health=3;
    tile9->health=3;
    tile10->health=3;
    tile22->health=3;
    tile12->health=3;
    tile13->health=3;
    tile14->health=3;
    tile15->health=3;

    ply->PXpos=-2;
    ply2->PXpos=2;
    ply->PYpos = -1.1;
    ply2->PYpos = -1.1;
    ply->thrown=false;
    ply2->thrown=false;

    Ball->Xpos=0;
    Ball->Ypos=0;
    Ball->tag="";
    ballDirX=-1;
    ballDirY=1;
    CurXpos=0;
    CurYpos=0;
    //reset the accel
    initGL();
}
void GLScene::ballColl()
{
    //----------------------PLAYER 1 --------------------------------------//
    if (box_collision(Ball->box, ply->box) && ply->swinging == true&& hitTimer->getTicks()>200)
    {
        hitTimer->reset();

        pCol->reset();
        Ball->tag="one";
        Ball->lethal=0;
        if(ply->lastCase == 'R') // lets player aim to his right
        {
            ballDirX = ply->xdir;
            ballDirY = ply->ydir;
        }
        if(ply->lastCase == 'L') // lets player aim to his left
        {
            ballDirX = -ply->xdir;
            ballDirY = ply->ydir;
        }
        if(ballSpeed<0.17)
            ballSpeed+=speedInc*(60/scale);

        Ball->modelInit("images/box/ball.png", true, ballTex);
        ply->swinging = false;
         hitCount++;
    }
     if (box_collision(Ball->box, ply->box) && ply->swinging == false&& hitTimer->getTicks()>200&&Ball->lethal==1)
    {
        //stun player1
        Ball->lethal=0;//now it is neutral and wont stun anyone
        ply->stunned=true;
    }

    //-----------------------PLAYER 2--------------------------------------//
    if (box_collision(Ball->box, ply2->box) && ply2->swinging == true&&hitTimer2->getTicks()>200)
    {
        hitTimer2->reset();
         Ball->tag="two";
         Ball->lethal=0;
        pCol->reset();
        if(ply2->lastCase == 'R')//lets player aim to his right
        {
            ballDirX = ply2->xdir;
            ballDirY = ply2->ydir;
        }

        if(ply2->lastCase == 'L')//lets player aim to his left
        {
            ballDirX = -ply2->xdir;
            ballDirY = ply2->ydir;
        }
        if(ballSpeed<0.17)
            ballSpeed+=speedInc*(60/scale);

        Ball->modelInit("images/box/ball2.png", true, ballTex);
        ply2->swinging = false;
        hitCount++;
    }
      if (box_collision(Ball->box, ply2->box) && ply2->swinging == false&& hitTimer2->getTicks()>200&&Ball->lethal==2)
    {
        //stun player2
        Ball->lethal=0;//now it is neutral and wont stun anyone
        ply2->stunned=true;
    }

    if(box_collision(ply2->box,Ball->box) && ply2->isalive() && Ball->myTime->getTicks() > 200)
    {
           Ball->myTime->reset();
           //ply2->health--;
    }
}
void GLScene::setBallDir()
{
    srand (time(NULL));
	double rando = rand() % 10+1;
	if(score<0)
	{
		if(rando>5)
			ballDirX=1;
			ballDirY=1;
		if(rando<=5)
			ballDirX=-1;
			ballDirY=-1;
	}
	else
	{
		if(rando>5)
			ballDirY=1;
		if(rando<=5)
			ballDirY=-1;
		if(plyScoreLast==1)
			ballDirX=-1;
		if(plyScoreLast==2)
			ballDirX=1;
	}
}
void GLScene::wallColl()
{
    if(box_collision(ply->box,killBox->box))
    {
        reset();
        score++;
        plyScoreLast=1;
        ply2Score++;
    }
    if(box_collision(ply2->box,killBox->box))
    {
        score++;
        reset();
        plyScoreLast=2;
        plyScore++;
    }
    if (box_collision(Ball->box, rightWall->box))
        ballDirX = -1;

    if (box_collision(Ball->box, leftWall->box))
        ballDirX = 1;

    if (box_collision(Ball->box, topWall->box))
        ballDirY = -1;

    if (box_collision(Ball->box, killBox->box))
    {
        CurYpos=2;
        ballDirY=-1;

        if(ballDirX==-1)
            CurXpos+=2;

        if(ballDirX==1)
            CurXpos-=2;
    }

    if(box_collision(ply->box,leftWall->box)) // player has hit the left wall
        ply->leftWC=true; // set to true so the player cannot move left
    else
        ply->leftWC=false;

    if(box_collision(ply->box,divide->box)) // player has hit the right wall
        ply->rightWC=true; // set to true so the player cannot move right
    else
        ply->rightWC=false;

    if(box_collision(ply->box,topWall->box))//player has hit the top wall
        ply->topWC=true;//set to true so the player cannot move up
    else
        ply->topWC=false;

    if(box_collision(ply2->box,divide->box)) // player has hit the left wall
        ply2->leftWC=true; // set to true so the player cannot move left
    else
        ply2->leftWC=false;


    if(box_collision(ply2->box,rightWall->box)) // player has hit the right wall
        ply2->rightWC=true; // set to true so the player cannot move right
    else
        ply2->rightWC=false;

    if(box_collision(ply2->box,topWall->box))//player has hit the top wall
        ply2->topWC=true;//set to true so the player cannot move up
    else
        ply2->topWC=false;


    if(box_collision(ply->projA->box,leftWall->box) && ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAXdir *= -1;
    }

    if(box_collision(ply->projA->box,rightWall->box) && ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAXdir *= -1;
    }

    if(box_collision(ply->projA->box,topWall->box)&& ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAYdir *= -1;
    }

    if(box_collision(ply->projA->box,killBox->box)&& ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAYdir *= -1;
    }


    //-----------------PROJECTILE 2 WALL COLLISIONS---------------------------------------------//
      if(box_collision(ply2->projA->box,leftWall->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAXdir*=-1;
    }

    if(box_collision(ply2->projA->box, rightWall->box) && ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAXdir*=-1;
    }

    if(box_collision(ply2->projA->box,topWall->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAYdir*=-1;
    }

    if(box_collision(ply2->projA->box,killBox->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAYdir*=-1;
    }
}
void GLScene::projectileCol(player* ply, player* ply2)
{
    if(box_collision(ply->projA->box, ply2->box) && ply2->isalive() && ply->projA->myTime->getTicks() > 200) // ball from player one hits player 2
    {
           //ply->projA->myTime->reset();
           //if(ply2->lastCase=='R')
            //make him dash in the oppposit direction he is facing
           //ply->projA->health = 0;
           //ply2->health--;
    }
    if(box_collision(ply->projA->box, ply->box) && ply->swinging == true)//player one can hit his own wall
    {
        ply->projAXdir=ply->xdir;
        ply->projAYdir=ply->ydir;
    }

    if(box_collision(ply->projA->box,ply->box) && ply->swinging==false)//player one can hit his own ball
    {
         ply->verticalVelocity=6;
         ply->projJump->start();
         ply->plyprojJump=true;
    }
    if(ply->projJump->getTicks()<500&&ply->plyprojJump)
        ply->playerGrav=-20/2;

    else if(ply->projJump->getTicks()>500&&ply->plyprojJump)
    {
        ply->plyprojJump=false;
        ply->projJump->reset();
        ply->playerGrav=-20;
    }

    if(box_collision(Ball->box, ply->projA->box)&&BPA->getTicks() >= 200&&manhattanD(ply,Ball)>1)
    {
        BPA->reset();
        //cout<<ballPosHit(ply->projA,Ball)<<endl;

        if(ballPosHit(ply->projA,Ball)==1)//hit the top half of the ball
            ballDirY=-1;
        if(ballPosHit(ply->projA,Ball)==2)//hit the bottom half of the ball
            ballDirY=1;
        ballDirX *= -1;
        //cout<<manhattanDist(ply,Ball)<<endl;
        ply->projA->health=0;
        if(Ball->Xpos>0&&Ball->tag=="one")
            Ball->lethal=2;
        //ballDirY *= -1;
    }

    if(box_collision(Ball->box, ply2->projA->box)&&BPA->getTicks() >= 200&&manhattanD(ply2,Ball)>1)
    {
        BPA->reset();
        ballDirX*=-1;
        ply->projA->health=0;
        if(Ball->Xpos<0&&Ball->tag=="two")
            Ball->lethal=1;
        //ballDirY*=-1;
    }

    if(ply->thrown)
    {
        ply->ProjACurY += ply->projAYdir * (10/scale);
        ply->ProjACurX += ply->projAXdir * (10/scale);

        ply->projA->Xpos = ply->ProjACurX;
        ply->projA->Ypos = ply->ProjACurY;
    }

}
void GLScene:: update()
{
    hitTimer2->start();
    hitTimer->start();
    double currentTime = glfwGetTime();

    frameCount++;
    if(currentTime-lastTime>=1.0)
    {
        if(frameCount>0)
            scale=(frameCount);
        if(!setBallSpeed&&scale>0)
        {
             ballSpeed=(3.4)/scale;//(0.125*8)/scale;
             ballSpdBfrAcc=ballSpeed;
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

    wallColl();
    ballColl();
     //Set a bool if player is on tile
    ply->OnTile=playerOnTile(ply);
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




    //MOVING THE BALL
    if(currentTime-startTime>4)
    {
     if(ballSpeed>ballSpdBfrAcc)
        ballSpeed-=speedDecr*(10/scale);
     //cout<<ballSpeed<<endl;
     CurYpos = CurYpos + ballDirY * ballSpeed;
     CurXpos = CurXpos + ballDirX * ballSpeed;
     //cout<<scale<<endl;
     Ball->Xpos =CurXpos;
     Ball->Ypos =CurYpos;
    // cout<<""<<endl;
     //cout<<CurXpos<<endl;
    // cout<<ballSpeed<<endl;
    // cout<<ballDirX<<endl;
    }


     projectileCol(ply, ply2);
     projectileCol(ply2, ply);
    if(!ply->thrown)
    {
        if(ply->lastCase=='R')//lets player aim to his right
        {
            ply->projAXdir = ply->xdir;
            ply->projAYdir = ply->ydir;
        }
        if(ply->lastCase=='L')//lets player aim to his left
        {
            ply->projAXdir = -ply->xdir;
            ply->projAYdir = ply->ydir;
        }
        ply->projA->health = 3;
    }
     if(ply->projA->health<=0)
    {
        ply->thrown=false;
        ply->projA->box.width=0;
        ply->projA->box.height=0;
        ply->projA->box.x=999;
        ply->projA->box.y=999;

    }
    if(ply->thrown==false&&ply->lastCase=='R')
        ply->ProjACurY=ply->PYpos, ply->ProjACurX=ply->PXpos+0.5;
    if(ply->thrown==false&&ply->lastCase=='L')
        ply->ProjACurY=ply->PYpos, ply->ProjACurX=ply->PXpos-0.5;

     if(!ply2->thrown)
    {
        if(ply2->lastCase=='R')//lets player aim to his right
        {
            ply2->projAXdir = ply2->xdir;
            ply2->projAYdir = ply2->ydir;
        }
        if(ply2->lastCase=='L')//lets player aim to his left
        {
            ply2->projAXdir = -ply2->xdir;
            ply2->projAYdir = ply2->ydir;
        }
        ply2->projA->health = 3;
    }
     if(ply2->projA->health<=0)
    {
        ply2->thrown=false;
        ply2->projA->box.width=0;
        ply2->projA->box.height=0;
        ply2->projA->box.x=999;
        ply2->projA->box.y=999;

    }
    if(ply2->thrown==false&&ply2->lastCase=='R')
        ply2->ProjACurY=ply2->PYpos, ply2->ProjACurX=ply2->PXpos+0.5;
    if(ply2->thrown==false&&ply2->lastCase=='L')
        ply2->ProjACurY=ply2->PYpos, ply2->ProjACurX=ply2->PXpos-0.5;
}

GLint GLScene::drawGLScene2(bool pressed[256])
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
                                     // Reset The Current Modelview Matrix
    glPushMatrix();
        glTranslated(0, 0, 1);
        glDisable(GL_LIGHTING);
        glScaled(10,10,10);
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

    if(menu[0])									// Not Time To Quit, Update Screen
    {
			    					// Swap Buffers (Double Buffering)
    }
     if(menu[1]==true)
    {
        glPushMatrix();
         glScalef(2.00,1.00,1);
         playButton->Xpos=-1;
         playButton->Ypos=-0.0;
        playButton->drawModel(tex3);
        glPopMatrix();

        glPushMatrix();
         glScalef(2.00,1.00,1);
         infoButton->Xpos=0.0;
         infoButton->Ypos=0.0;
        infoButton->drawModel(tex4);
        glPopMatrix();

        glPushMatrix();
         glScalef(2.00,1.00,1);
         exitButton->Xpos=1;
         exitButton->Ypos=0.0;
        exitButton->drawModel(tex5);
        glPopMatrix();
    }
    if(this->menu[2]==true)
    {
          glPushMatrix();
         glScalef(2.00,1.00,1);
         infoPage->Xpos=-0.0;
         infoPage->Ypos=-0.0;
        infoPage->drawModel(tex6);
        glPopMatrix();
    }
    if(this->menu[3]==true)
    {
        double lolTime = glfwGetTime();


          //-----------------------------------------------------------------------------------------------//
         //------------------------------------------ TIMERS ---------------------------------------------//
        //-----------------------------------------------------------------------------------------------//
            ply->projA->myTime->start();
            ply2->projA->myTime->start();
            ply->myTime->start();
            Ball->myTime->start();
            ply->swingTimer->start();
            ply2->swingTimer->start();
            D->start();
            BPA->start();
            pCol->start();
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
            ply->box.x=ply->PXpos;
            ply->box.y = ply->PYpos;
            ply->pl_pltfrm_box.x = ply ->PXpos;
            ply->pl_pltfrm_box.y = ply -> PYpos;
            ply->pl_pltfrm_box.height = 0.6;
            ply->pl_pltfrm_box.width = 0.07;
            ply->box.height=0.1;
            ply->trueHeight=0.1;
            ply->box.width=0.3;
            //update(20);
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
                ply2->box.x =  ply2->PXpos;
                ply2->box.y =  ply2->PYpos;
                ply2->pl_pltfrm_box.x =  ply2 ->PXpos;
                ply2->pl_pltfrm_box.y =  ply2 -> PYpos;
                ply2->pl_pltfrm_box.height = 0.6;
                ply2->pl_pltfrm_box.width = 0.07;
                ply2->trueHeight=0.1;
                ply2->box.height=0.1;
                ply2->box.width=0.3;
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
        makeModel(leftWall,leftWallTex,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);
        //right wall
        makeModel(rightWall,rightWallTex,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);
        //bottom wall
        makeModel(killBox,topWallTex,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,0.5);
        //dividing wall
        makeModel(divide,divWallTex,0,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.1,88);

        //top wall
        makeModel(topWall, topWallTex,0,1.8,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);

        //----------------Projectile creation------------------------------------------------//
            if(ply->thrown)
            {
                glPushMatrix();
                    ply->projA->box.height =  .2;
                    ply->projA->box.width = .05;
                    ply->projA->verticies[0].x = -0.15;
                    ply->projA->verticies[1].x = 0.15;
                    ply->projA->verticies[2].x = 0.15;
                    ply->projA->verticies[3].x = -0.15;
                    ply->projA->verticies[0].y = -0.15;
                    ply->projA->verticies[1].y = -0.15;
                    ply->projA->verticies[2].y = 0.15;
                    ply->projA->verticies[3].y = 0.15;
                    ply->projA->box.x = ply->projA ->Xpos;
                    ply->projA->box.y = ply->projA ->Ypos;
                    ply->projA->drawModel(projTex);
              glPopMatrix();
            }
            if(ply->projA->health<=0)
        {
            ply->thrown=false;
            shot=false;
            ply->projA->Xpos=999;
            ply->projA->Ypos=999;
            ply->projA->box.x=999;
            ply->projA->box.y=999;
            ply->projA->box.width=0;
            ply->projA->box.height=0;
        }

        //-------------------------projectile b-----------------------------------------//
        if(ply2->thrown)
            {
                glPushMatrix();
                    ply2->projA->box.height =  .2;
                    ply2->projA->box.width = .05;
                    ply2->projA->verticies[0].x = -0.15;
                    ply2->projA->verticies[1].x = 0.15;
                    ply2->projA->verticies[2].x = 0.15;
                    ply2->projA->verticies[3].x = -0.15;
                    ply2->projA->verticies[0].y = -0.15;
                    ply2->projA->verticies[1].y = -0.15;
                    ply2->projA->verticies[2].y = 0.15;
                    ply2->projA->verticies[3].y = 0.15;
                    ply2->projA->box.x = ply2->projA ->Xpos;
                    ply2->projA->box.y = ply2->projA ->Ypos;
                    ply2->projA->drawModel(projTex2);
              glPopMatrix();
            }
        if(ply2->projA->health<=0)
        {
            ply2->thrown=false;
            shot=false;
            ply2->projA->Xpos=999;
            ply2->projA->Ypos=999;
            ply2->projA->box.x=999;
            ply2->projA->box.y=999;
            ply2->projA->box.width=0;
            ply2->projA->box.height=0;
        }

        //----------------------------BALL CREATION------------------------------------//
        glPushMatrix();
            Ball->box.height = 0.2;
            Ball->box.width = 0.05;
            Ball->verticies[0].x = -0.15;
            Ball->verticies[1].x = 0.15;
            Ball->verticies[2].x = 0.15;
            Ball->verticies[3].x = -0.15;
            Ball->verticies[0].y = -0.15;
            Ball->verticies[1].y = -0.15;
            Ball->verticies[2].y = 0.15;
            Ball->verticies[3].y = 0.15;
            Ball->box.x = Ball->Xpos;
            Ball->box.y = Ball->Ypos;
            Ball->drawModel(ballTex);
        glPopMatrix();

        //---------------------------Crosshair player 1 creation----------------------------------//
        float tmp1 = ply->PXpos - ply->xdir;
        float tmp2 = ply->PYpos + ply->ydir;
        float tmp3 = ply->PXpos + ply->xdir;
        if(ply->lastCase=='L')
            makeModel(cross, crosshair, tmp1, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);
        if(ply->lastCase=='R')
            makeModel(cross, crosshair, tmp3, tmp2, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);


        //---------------------------Crosshair player 2 creation----------------------------------//
        float tmp4 = ply2->PXpos - ply2->xdir;
        float tmp5 = ply2->PYpos + ply2->ydir;
        float tmp6 = ply2->PXpos + ply2->xdir;
        if(ply2->lastCase=='L')
            makeModel(cross, crosshair, tmp4, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);
        if(ply2->lastCase=='R')
            makeModel(cross, crosshair, tmp6, tmp5, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);


        if(lolTime-startTime>0.5&&lolTime-startTime<=1)
        {
             //draw the number 3
            glPushMatrix();
                threeMod->drawModel(threeTex);
            glPopMatrix();
        }
        if(lolTime-startTime>1&&lolTime-startTime<=2)
         {
              //draw the number 2
            glPushMatrix();
                twoMod->drawModel(twoTex);
            glPopMatrix();
        }
        if(lolTime-startTime>2&&lolTime-startTime<=3)
         {
             //draw the number 1
            glPushMatrix();
                oneMod->drawModel(oneTex);
            glPopMatrix();
        }
        if(lolTime-startTime>3&&lolTime-startTime<=4)
         {
            //draw the number 0
            glPushMatrix();
                zeroMod->drawModel(zeroTex);
            glPopMatrix();
         }
        if(lolTime-startTime>=4&&!menu[4])//wait two seconds to start the
            KbMs->idle(pressed,ply,ply2);

        update();
    }
     if(this->menu[4]==true)
    {
            ply->pause=true;
            ply2->pause=true;
            if(firstpause)
            {
              tDirx=ballDirX;
              tDiry=ballDirY;
             firstpause=false;
            }
            ballDirX=0;
            ballDirY=0;
            if(pauseChoice)
            {
                if(menuPos==1)//reset the gameee
                {
                    pauseMenu=false;
                    reset();
                    firstpause=true;
                    ply->pause=false;
                    ply2->pause=false;
                    menu[4]=false;
                }
                if(menuPos==2)//resumed the game
                {
                    ballDirX=tDirx;
                    ballDirY=tDiry;
                    pauseMenu=false;
                    firstpause=true;
                    ply->pause=false;
                    ply2->pause=false;
                    menu[4]=false;
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
