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
#include <sounds.h>
 //#include <SFML/Graphics.hpp>
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
sounds *snds = new sounds();
sounds *BtWsnds = new sounds();
sounds *gameSoundtrack = new sounds();
bool musicStarted = false;

bool cdown1 = false;
bool cdown2 = false;
bool cdown3 = false;
bool rumble = false;

bool wonSound = false;

timer* soundTimer = new timer();

timer* musicReset = new timer();

bool gameEntered = false;

using namespace std;

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    MMTex= new textureLoader();

    pauseMenu = false;
    mainParr= new parallax();

     KbMs = new Inputs();

     plx = new parallax();
     plx2 = new parallax();
     plx3 = new parallax();
     sky = new skyBox;

     playMod= new Model();
     controlsMod = new Model();
     resetMod= new Model();
     exitMod= new Model();

     playTex=new textureLoader();
     controlsTex=new textureLoader();
     resetTex=new textureLoader();
     exitTex=new textureLoader();

     texSky1 = new textureLoader();
     texSky2 = new textureLoader();
     plxSky2= new parallax();
     sky2Tex= new textureLoader();
     /*-----------------------------------------*/

    //--left side tiles
    tile1 = new Model();
    tile2 = new Model();
    tile3 = new Model();
    tile4 = new Model();
    tile5 = new Model();
    tile6 = new Model();
    tile7 = new Model();
    //--middle tile
    tile8 = new Model();
    //--right side tiles
    tile9 = new Model();
    tile10 = new Model();
    tile11 = new Model();
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
    leftWall = new Model(); //---Left wall
    rightWall = new Model(); //--Right wall
    topWall = new Model(); //----Top wall
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

    p1HP = new textureLoader();
    p1HPModel = new Model();
    p2HP = new textureLoader();
    p2HPModel = new Model();

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
    tile11->tag="right";
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

    menuModel = new Model();
    menuModel2 = new Model();
    menuModel3 = new Model();
    menuModel4 = new Model();

    playButton= new Model();
    infoButton = new Model();
    exitButton = new Model();
    infoPage= new Model();
    tex3 = new textureLoader();
    tex4 = new textureLoader();
    tex5 = new textureLoader();
    tex6 = new textureLoader();
    menu[0]=true;
    plyScoreLast = 0;
    score = 0;
    mainMenPos = 0;
    controlButton= new Model();
    controlTex= new textureLoader();
    controlButtonA= new Model();
    controlTexA= new textureLoader();
    infoButtonA= new Model();
    exitButtonA= new Model();
    playButtonA= new Model();
    pause_controls = new Model();
    infoTexA= new textureLoader();
    exitTexA= new textureLoader();
    playButtonTexA= new textureLoader();

    menuTex = new textureLoader();
    menuTex2 = new textureLoader();
    menuTex3 = new textureLoader();
    menuTex4 = new textureLoader();

    landingTex = new textureLoader();
    ply2->lastCase='L';
    /*------------------------------------------*/
      controlTexA= new textureLoader();
        infoButtonA= new Model();
     exitButtonA= new Model();
      playButtonA= new Model();
        infoTexA= new textureLoader();
      exitTexA= new textureLoader();
      playButtonTexA= new textureLoader();
      pauseCTex= new textureLoader();
//      mainMenuModel= new Model();
      //mainMenuTex= new textureLoader();
//     mainMenuModel= new Model();
//     mainMenuTex= new textureLoader();
    winPlyModel= new Model();
    winPly2Model= new Model();
    winPlyTex= new textureLoader();
    winPly2Tex= new textureLoader();
     /*------------------------------------------*/
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{

    cdown1 = false;
    cdown2 = false;
    cdown3 = false;
    rumble = false;
    // musicReset->start(); //not used
    soundTimer->start();
    snds->initSounds();
    BtWsnds->initSounds();
    gameSoundtrack->initSounds();

    gameSoundtrack->stopAllSounds();
    gameSoundtrack->adjustVolume(0.2);

    wonSound = false;

    if(!musicStarted)
    {
        gameSoundtrack->playMusic("sounds/bgmusic.mp3");
        musicStarted = true;
    }
    else
    {
        gameSoundtrack->stopAllSounds();
        gameSoundtrack->playMusic("sounds/Bloom_-_10_-_Temperance.mp3");
    }


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
    plx2->parallaxInit("images/box/landing.jpg",landingTex);
    plxSky2->parallaxInit("images/box/sky2.png",sky2Tex);
    mainParr->parallaxInit("images/box/MMBG.png",MMTex);

    plx2->parallaxInit("images/box/bak.jpg",landingTex);
    mainParr->parallaxInit("images/box/bakgrd.png",MMTex);

    playMod->modelInit("images/box/pMPlay.png", true, playTex);
    controlsMod->modelInit("images/box/pMcontrols.png", true, controlsTex);
    resetMod->modelInit("images/box/pMReset.png", true, resetTex);
    exitMod->modelInit("images/box/pmExit.png", true, exitTex);

    pause_controls->modelInit("images/box/pause_controls.png", true, pauseCTex);

    /* declare model init, player init in scene init*/
    playerModel->modelInit("images/player/player0.png", true, plyTex);
    ply->playerInit2();
    playerModel2->modelInit("images/player2_right/player0.png", true, plyTex);
    ply2->playerInit();

    p1HPModel->modelInit("images/box/p1_3.png", true, p1HP);
    p2HPModel->modelInit("images/box/p2_3.png", true, p2HP);


    //----------------player position variables---------------//
    ply->PXpos=-2;
    ply2->PXpos=2;
    ply->PYpos = -1.1;
    ply2->PYpos = -1.1;
    ply->thrown=false;
    ply2->thrown=false;
    ply->OnTile=true;
    ply2->OnTile=true;
    ply->actionTrigger=4;
    ply2->actionTrigger=4;
    ply->lastCase='R';
    ply2->lastCase='L';
    //--------------------------------------------------------//

    //-----------------------tile models--------------------------//
    tile1->modelInit("images/box/nothing2.png", true, tileTex);
    tile2->modelInit("images/box/block.png", true, tileTex2);
    tile3->modelInit("images/box/block.png", true, tileTex3);
    tile4->modelInit("images/box/block.png", true, tileTex4);
    tile5->modelInit("images/box/block.png", true, tileTex5);
    tile6->modelInit("images/box/block.png", true, tileTex6);
    tile7->modelInit("images/box/block.png", true, tileTex7);
    tile8->modelInit("images/box/nothing2.png", true, tileTex8);
    tile9->modelInit("images/box/block.png", true, tileTex9);
    tile10->modelInit("images/box/block.png", true, tileTex10);
    tile11->modelInit("images/box/block.png", true, tileTex11);
    tile12->modelInit("images/box/block.png", true, tileTex12);
    tile13->modelInit("images/box/block.png", true, tileTex13);
    tile14->modelInit("images/box/block.png", true, tileTex14);
    tile15->modelInit("images/box/nothing2.png", true, tileTex15);
    //-------------------------------------------------------------//

    //------------------------wall models--------------------------//
    leftWall->modelInit("images/box/girder.png", true, leftWallTex);
    rightWall->modelInit("images/box/girder.png", true, rightWallTex);
    topWall->modelInit("images/box/girder2.png", true, topWallTex);
    divide->modelInit("images/box/chain.png", true, divWallTex);
    //-------------------------------------------------------------//

    //----------------------projectile/ball--------------------------//
    cross->modelInit("images/box/crosshair.png", true, crosshair);
    ply->projA->modelInit("images/box/Fire.png", true, projTex);
    ply2->projA->modelInit("images/box/Fire2.png", true, projTex2);
    Ball->modelInit("images/box/ball.png", true, ballTex);
    //---------------------------------------------------------------//

    //-------------------player timers------------------------//
    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();
    //--------------------------------------------------------//

    //-------------------countdown models---------------------//
    threeMod->modelInit("images/box/three.png", true, threeTex);
    twoMod->modelInit("images/box/two.png", true, twoTex);
    oneMod->modelInit("images/box/one.png", true, oneTex);
    zeroMod->modelInit("images/box/zero.png", true, zeroTex);

    playButton->modelInit("images/box/playbutton.png",true,tex3);
    infoButton->modelInit("images/box/info.png",true,tex4);
    exitButton->modelInit("images/box/exit.png",true,tex5);
    infoPage->modelInit("images/box/rules_page.png",true,tex6);
    //setBallDir();

    menuModel->modelInit("images/box/background_play.png",true,menuTex);
    menuModel2->modelInit("images/box/rules_page.png",true,menuTex2);
    menuModel3->modelInit("images/box/controls_page.png",true,menuTex3);
    menuModel4->modelInit("images/box/background_exit.png",true,menuTex4);

    landing->modelInit("images/box/bak.png",true,landingTex);

    /*------------------------*/
     winPlyModel->modelInit("images/box/ply_wins.png",true,winPlyTex);
     winPly2Model->modelInit("images/box/ply2_wins.png",true,winPly2Tex);

    //--------------------------------------------------------//

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
                BtWsnds->playSound("sounds/aaj_1064_TbleHit04.mp3");
                D->reset();
                ballDirY =  1;
                if((b->tag=="one"&&t->tag=="right")||(b->tag=="two"&&t->tag=="left"))
                {
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
                if (t->health == 0)
                    t->modelInit("images/box/nothing2.png", true, TX);
                    return;
    }

}
bool GLScene::playerOnTile(player* ply)
{
             if((topOfTile(ply,tile1)||topOfTile(ply,tile2)||topOfTile(ply,tile3)||topOfTile(ply,tile4)||
                    topOfTile(ply,tile5)||topOfTile(ply,tile6)||topOfTile(ply,tile7)||topOfTile(ply,tile8)||
                    topOfTile(ply,tile9)||topOfTile(ply,tile10)||topOfTile(ply,tile11)||topOfTile(ply,tile12)||
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
        if(mod->isalive())
        {
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
        }
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
    tile11->health=3;
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
    ply->OnTile=true;
    ply2->OnTile=true;
    ply->health=4;
    ply2->health=4;
    ply->actionTrigger=0;
    ply2->actionTrigger=0;

    Ball->Xpos=0;
    Ball->Ypos=0;
    Ball->tag="";
    //ballDirX=-1;
    //ballDirY=-1;
    setBallDir();
    CurXpos=0;
    CurYpos=0;
    //reset the accel
   // updateHPBar();
    initGL();
}
void GLScene::ballColl()
{
    //----------------------PLAYER 1 --------------------------------------//
    if (box_collision(Ball->box, ply->box) && ply->swinging == true&& hitTimer->getTicks()>200)
    {
        hitTimer->reset();

        //cout << "swing hit" << endl;
        snds->playSound("sounds/swingHit.mp3");

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

        Ball->modelInit("images/box/ball3.png", true, ballTex);
        ply->swinging = false;
         hitCount++;
    }
     if (box_collision(Ball->box, ply->box) && ply->swinging == false&& hitTimer->getTicks()>200&&Ball->lethal==1)
    {
        //stun player1
        Ball->lethal=0;//now it is neutral and wont stun anyone
        ply->stunned=true;
    }

    if (!box_collision(Ball->box, ply->box) && ply->swinging == true && ply->swingTimer->getTicks() >=200 && hitTimer->getTicks()>200)
    {
        //cout << "swing" << endl;
        ply->swingTimer->reset();
        snds->playSound("sounds/swing.mp3");
    }

    //-----------------------PLAYER 2--------------------------------------//
    if (box_collision(Ball->box, ply2->box) && ply2->swinging == true&&hitTimer2->getTicks()>200)
    {
        //cout << "swing2 hit" << endl;
        snds->playSound("sounds/swingHit.mp3");
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
    if (!box_collision(Ball->box, ply2->box) && ply2->swinging == true && ply2->swingTimer->getTicks() >=200 && hitTimer->getTicks()>200)
    {
        //cout << "swing2" << endl;
        ply2->swingTimer->reset();
        snds->playSound("sounds/swing.mp3");
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
	double rando = rand() % 2+1;
	if(score<=0)
	{
	    //cout<<"in here"<<endl;
		if(rando>1)
        {
			ballDirX=1;
			ballDirY=1;
        }
		if(rando<=1)
        {
			ballDirX=-1;
			ballDirY=-1;
        }
	}
	else
	{
		if(rando>1)
			ballDirY=1;
		if(rando<=1)
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
        ply->doReset=false;

    }
    if(box_collision(ply2->box,killBox->box))
    {
        score++;
        reset();
        plyScoreLast=2;
        plyScore++;
        ply2->doReset=false;
    }
    if (box_collision(Ball->box, rightWall->box))
    {
        ballDirX = -1;
        BtWsnds->playSound("sounds/aaj_1064_TbleHit04.mp3");
    }


    if (box_collision(Ball->box, leftWall->box))
    {
        ballDirX = 1;
        BtWsnds->playSound("sounds/aaj_1064_TbleHit04.mp3");
    }


    if (box_collision(Ball->box, topWall->box))
    {
        ballDirY = -1;
        BtWsnds->playSound("sounds/aaj_1064_TbleHit04.mp3");
    }


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
        if(ply->oneORtwo=="one")
        {
            Ball->tag="one";
            Ball->modelInit("images/box/ball3.png", true, ballTex);
        }
        if(ply->oneORtwo=="two")
        {
            Ball->tag="two";
            Ball->modelInit("images/box/ball2.png", true, ballTex);
        }

        if(Ball->Xpos>0&&Ball->tag=="one")
            Ball->lethal=2;
        if(Ball->Xpos<0&&Ball->tag=="two")
            Ball->lethal=1;
        //ballDirY *= -1;
    }

    /*if(box_collision(Ball->box, ply2->projA->box)&&BPA->getTicks() >= 200&&manhattanD(ply2,Ball)>1)
    {
        BPA->reset();
        ballDirX*=-1;
        ply->projA->health=0;
        if(Ball->Xpos<0&&Ball->tag=="two")
            Ball->lethal=1;
        //ballDirY*=-1;
    }*/

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
    //tileChange(Ball, tile8,tileTex8);
    tileChange(Ball, tile9,tileTex9);
    tileChange(Ball, tile10,tileTex10);
    tileChange(Ball, tile11,tileTex11);
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

void GLScene::updateHPBar( )
{
    if (plyScore == 1)
    {
        p2HPModel->modelInit("images/box/p2_2.png", true, p2HP);
    }
    else if (plyScore == 2)
    {
        p2HPModel->modelInit("images/box/p2_1.png", true, p2HP);
    }
    else if (plyScore == 3)
    {
        p2HPModel->modelInit("images/box/emty.png", true, p2HP);
    }

    if (ply2Score == 1)
    {
        p1HPModel->modelInit("images/box/p1_2.png", true, p1HP);
    }
    else if (ply2Score == 2)
    {
        p1HPModel->modelInit("images/box/p1_1.png", true, p1HP);
    }
    else if (ply2Score == 3)
    {
        p1HPModel->modelInit("images/box/emty.png", true, p1HP);
    }
}


GLint GLScene::drawGLScene2(bool pressed[256])
{
    //updateHPBar();


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
         //if(timeFromStart-startTime>=2)//wait three seconds to start the game
            plx->scroll(true,"left",0.006,1);

        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            plxSky2->drawSquare(screenWidth, screenHeight, sky2Tex);
        glPopMatrix();
         //if(timeFromStart-startTime>=2)//wait three seconds to start the game
            plxSky2->scroll(true,"left",0.006,6);
          //-----------------------------------------------------------------------------------------------//
         //------------------------------- PARALLAX2 CREATION --------------------------------------------//
        //-----------------------------------------------------------------------------------------------//
        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            plx2->drawSquare(screenWidth, screenHeight, texSky2);
        glPopMatrix();

    if(menu[0])	// Not Time To Quit, Update Screen
    {
        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            plx3->drawSquare(screenWidth, screenHeight, landingTex);
        glPopMatrix();
         if(timeFromStart-startTime>=2)//wait three seconds to start the game
            plx->scroll(false,"left",1,scale);
    }

    if(menu[1] == true)
    {
        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            mainParr->drawSquare(screenWidth, screenHeight, MMTex);
        glPopMatrix();
        //          model,   texture, xpos,ypos, 0 X,  0 Y, 1 X,  1 Y, 2 X, 2 Y,  3 X, 3 Y, width,height
        //makeModel(menuModel, menuTex, 0.0, 0.0, -3.5, -1.0, 3.5, -1.0, 3.5, 1.0, -3.5, 1.0, 0.0, 0.0);
        //if(mainMenPos == 0) // play
          //  menuModel->modelInit("images/box/menu_play.png",true,menuTex);

        //makeModel(menuModel, menuTex, 0.0, 0.0, -3.5, -2.0, 3.5, -2.0, 3.5, 2.0, -3.5, 2.0, 0.0, 0.0);
        if(mainMenPos == 0) // play
            makeModel(menuModel, menuTex, 0.0, 0.0, -3.5, -2.0, 3.5, -2.0, 3.5, 2.0, -3.5, 2.0, 0.0, 0.0);
        if(mainMenPos == 1) // info
            makeModel(menuModel2, menuTex2, 0.0, 0.0, -3.5, -2.0, 3.5, -2.0, 3.5, 2.0, -3.5, 2.0, 0.0, 0.0);
        if(mainMenPos == 2) // controls
            makeModel(menuModel3, menuTex3, 0.0, 0.0, -3.5, -2.0, 3.5, -2.0, 3.5, 2.0, -3.5, 2.0, 0.0, 0.0);
        if(mainMenPos == 3) // exit
            //menuModel->modelInit("images/box/menu_exit.png",true,menuTex);
            makeModel(menuModel4, menuTex4, 0.0, 0.0, -3.5, -2.0, 3.5, -2.0, 3.5, 2.0, -3.5, 2.0, 0.0, 0.0);
    }
    if(this->menu[2]==true)
    {
        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            mainParr->drawSquare(screenWidth, screenHeight, MMTex);
        glPopMatrix();
        glPushMatrix();
        glScalef(2.00,1.00,1);
        menuModel2->Xpos=-0.0;
        menuModel2->Ypos=-0.0;
        menuModel2->drawModel(menuTex2);
        glPopMatrix();
    }
    if(this->menu[3]==true)
    {
        if(!gameEntered)
        {
            //gameSoundtrack->stopAllSounds();
            //gameSoundtrack->playMusic("sounds/Bloom_-_10_-_Temperance.mp3");
            gameEntered = true;
        }
        //updateHPBar();
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

        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            plxSky2->drawSquare(screenWidth, screenHeight, sky2Tex);
        glPopMatrix();
         if(timeFromStart-startTime>=2)//wait three seconds to start the game
            plxSky2->scroll(true,"left",1,scale);
          //-----------------------------------

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
            ply->pl_pltfrm_box.height = 0.55;
            ply->pl_pltfrm_box.width = 0.07;
            ply->box.height=0.1;
            ply->trueHeight=0.1;
            ply->box.width=0.2;
            ply->drawplayer();
            ply->oneORtwo = "one";
        glPopMatrix();
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
                ply2->box.width=0.2;
                ply2->drawplayer();
                ply2->oneORtwo = "two";
            glPopMatrix();
        }


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    //        model,texture, xpos, ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
    makeModel(tile1,tileTex,-3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile2,tileTex2,-2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile3,tileTex3,-2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile4,tileTex4,-1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile5,tileTex5,-1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile6,tileTex6,-0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile7,tileTex7,-0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile8,tileTex8, 0.00,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile9,tileTex9, 0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile10,tileTex10, 0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile11,tileTex11, 1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile12,tileTex12, 1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile13,tileTex13, 2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile14,tileTex14, 2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    makeModel(tile15,tileTex15, 3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);
    //left wall
    makeModel(leftWall,leftWallTex,-3.37,0,-0.2,-3.0,0.2,-3.0,0.2,3.0,-0.2,3.0,0.3,88);
    //right wall
    makeModel(rightWall,rightWallTex,3.37,0,-0.2,3.0,0.2,3.0,0.2,-3.0,-0.2,-3.0,0.3,88);
    //bottom wall
    makeModel(killBox,topWallTex,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,0.5);
    //dividing wall
    makeModel(divide,divWallTex,0,0, -3.5, -3, 3.5, -3, 3.5, 3, -3.5, 3, 0.25, 88);
    //top wall
    makeModel(topWall, topWallTex,0,1.8,-5.0,-0.2,5.0,-0.2,5.0,0.2,-5.0,0.2,88,0.17);

    //player 2 hp bar creation
   // makeModel(p1HPModel,p1HP,-2.40,1.20,-0.35,-0.00,0.35,-0.00,0.35,0.30,-0.35,0.30,0.2200005,.3);

    //makeModel(p1HPModel,p1HP,-2.40,1.20,-0.35,-0.00,0.35,-0.00,0.35,0.30,-0.35,0.30,0.2200005,.3);
    //makeModel(p2HPModel,p2HP,2.40,1.20,-0.35,-0.00,0.35,-0.00,0.35,0.30,-0.35,0.30,0.2200005,.3);
        //----------------Projectile creation------------------------------------------------//
        if(ply->thrown)
        {
              glPushMatrix();
                    ply->projA->box.height =  0.2;
                    ply->projA->box.width = 0.05;
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

        if(!menu[6])
        {
        if(lolTime-startTime>0.5&&lolTime-startTime<=1)
        {
             //draw the number 3
            if (!cdown3)
            {
                //snds->playSound("sounds/3.mp3");
                cdown3 = true;
            }
            glPushMatrix();
                threeMod->drawModel(threeTex);
            glPopMatrix();
        }
        if(lolTime-startTime>1&&lolTime-startTime<=2)
         {
              //drawmainMenChoice=false; the number 2
            if (!cdown2)
            {
              //  snds->playSound("sounds/2.mp3");
                cdown2 = true;
            }
            glPushMatrix();
                twoMod->drawModel(twoTex);
            glPopMatrix();
        }
        if(lolTime-startTime>2&&lolTime-startTime<=3)
         {
             //draw the number 1
            glPushMatrix();
            if (!cdown1)
            {
                //snds->playSound("sounds/1.mp3");
                cdown1 = true;
            }
                oneMod->drawModel(oneTex);
            glPopMatrix();
        }
        if(lolTime-startTime>3&&lolTime-startTime<=4)
         {
            //draw the number 0
            if (!rumble)
            {
                //snds->playSound("sounds/rumble.mp3");
                rumble = true;
            }
            glPushMatrix();
                zeroMod->drawModel(zeroTex);
            glPopMatrix();
         }

        if(lolTime-startTime>=4&&!menu[4])//wait two seconds to start the
            KbMs->idle(pressed,ply,ply2);
            //KbMs->keySound(pressed, snds);
        if(menu[6])//game is won
        {
            glPushMatrix();
             glScalef(1.00,1.00,1);
             playButton->Xpos=-2.0;
             playButton->Ypos=-0.0;
            playButton->drawModel(tex3);
            glPopMatrix();
        }
        update();
        }
        if(plyScore>=3||ply2Score>=3)
            menu[6]=true;

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
                if(menuPos==3)//resumed the game
                {
                    ballDirX=tDirx;
                    ballDirY=tDiry;
                    pauseMenu=false;
                    firstpause=true;
                    ply->pause=false;
                    ply2->pause=false;
                    menu[4]=false;
                }
                if(menuPos==2) // controls page
                {
                   // makeModel(pause_controls, pauseCTex, 0.0, 0.0, -0.09, -0.09, 0.09, -0.09, 0.09, 0.09, -0.09, 0.09, 0.0, 0.0);
                   pause_controls->drawModel(pauseCTex);
                }
                menuPos=3;
                pauseChoice=false;
            }
            else
            {
            glLoadIdentity();
                if(menuPos==3)
                {
                    glPushMatrix();
                    playMod->Xpos=0;
                    playMod->Ypos=0;
                    makeModel(playMod, playTex, 0.0, 0.0, -0.9, -1.0, 0.9, -1.0, 0.9, 1.0, -0.9, 1.0, 0.0, 0.0);
                    glPopMatrix();
                }
                if(menuPos==2)
                {
                    glPushMatrix();
                    controlsMod->Xpos=0;
                    controlsMod->Ypos=0;
                    makeModel(controlsMod, controlsTex, 0.0, 0.0, -0.9, -1.0, 0.9, -1.0, 0.9, 1.0, -0.9, 1.0, 0.0, 0.0);
                    makeModel(pause_controls, pauseCTex, 1.85, 0.0, -1.2, -1.0, 1.2, -1.0, 1.2, 1.0, -1.2, 1.0, 0.0, 0.0);
                    glPopMatrix();
                }
                if(menuPos==1)
                {
                    glPushMatrix();
                    resetMod->Xpos=0;
                    resetMod->Ypos=0;
                    makeModel(resetMod, resetTex, 0.0, 0.0, -0.9, -1.0, 0.9, -1.0, 0.9, 1.0, -0.9, 1.0, 0.0, 0.0);
                    glPopMatrix();
                }
                 if(menuPos==0)
                {
                    glPushMatrix();
                    exitMod->Xpos=0;
                    exitMod->Ypos=0;
                    makeModel(exitMod, exitTex, 0.0, 0.0, -0.9, -1.0, 0.9, -1.0, 0.9, 1.0, -0.9, 1.0, 0.0, 0.0);
                    glPopMatrix();
                }
            }
    }
    if(menu[5])//controls page
    {
        glPushMatrix();
            glScaled(3.33, 3.33, 1.0);
            mainParr->drawSquare(screenWidth, screenHeight, MMTex);
        glPopMatrix();
        glPushMatrix();
         glScalef(1.00,1.00,1);
         menuModel3->Xpos=0.0;
         menuModel3->Ypos=0.0;
         menuModel3->drawModel(menuTex3);
        glPopMatrix();
    }
    if(menu[6])
    {
        if(plyScore>=3)
        {
            if(!wonSound)
            {
                gameSoundtrack->stopAllSounds();
                gameSoundtrack->playSound("sounds/won.mp3");
                wonSound = true;
            }
            glPushMatrix();
             makeModel(winPlyModel, winPlyTex, 0.0, 0.0, -3.5, -0.5, 3.5, -0.5, 3.5, 0.5, -3.5, 0.5, 0.0, 0.0);
            glPopMatrix();
        }
        else if(ply2Score>=3)
        {
            if(!wonSound)
            {
                gameSoundtrack->stopAllSounds();
                gameSoundtrack->playSound("sounds/won.mp3");
                wonSound = true;
            }
            glPushMatrix();
             makeModel(winPly2Model, winPly2Tex, 0.0, 0.0, -3.5, -0.5, 3.5, -0.5, 3.5, 0.5, -3.5, 0.5, 0.0, 0.0);
            glPopMatrix();
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
    if(soundTimer->getTicks() >= 20)
    {
        KbMs->keySound(press, snds);
        soundTimer->reset();
    }
}
