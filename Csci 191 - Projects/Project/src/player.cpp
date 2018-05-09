#include <player.h>
#include <timer.h>
#include <GLTexture.h>
#include <windows.h>
#include <iostream>

player::player()
{
    verticalVelocity=0;
    playerGrav=-20;
    ydir=0;
    xdir=1;
    stunned=false;
    swingSpeed=0;
    fireTime= new timer();
    doReset=false;

    jumpInitiated = false;
    PZoom = -4;
    PXpos = 0;
    PYpos = -1.1;
    aimX = 0;
    aimY = -1;
    plyAccel = 0.000005;
    dashVel=7;//4;

        verticies[0].x=-0.3;verticies[0].y=-0.3;verticies[0].z=-1.0;
        verticies[1].x=0.3;verticies[1].y=-0.3;verticies[1].z=-1.0;
        verticies[2].x=0.3;verticies[2].y=0.3;verticies[2].z=-1.0;
        verticies[3].x=-0.3;verticies[3].y=0.3;verticies[3].z=-1.0;

    runspeed  = 0;
    jumpspeed = 0;
    actionTrigger = 0;
    box.width = 0;
    box.height = 0;
    leftWC=false;
    rightWC=false;
    health=5;
    rTime= new timer();

    thrown = false;
    isDash = false;
    pause = false;

    x_direction = 1;

    swinging = false;

    startSpeed=0.001;
    plyVel = startSpeed;//2;
   // plyVel = 0.002;
    !ballCollided;
    !midCollision;

    swingDuration->start();

    playerDirection = "RIGHT";
    plyprojJump=false;
    projJump= new timer();

    thrown=false;
    projA->Xpos=999;
    projA->Ypos=999;
    projA->box.x=999;
    projA->box.y=999;
    projA->box.width=0;
    projA->box.height=0;
    rInc=0;

}

player::~player()
{
    //dtor
}

void player::drawplayer()
{
    glTranslated(PXpos,PYpos,PZoom);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);
    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);
    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);
    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();
}

void player::playerInit()
{
    //rTime->start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    runText[0].bindTexture("images/player_right/player0.png");
    runText[1].bindTexture("images/player_right/player1.png");
    runText[2].bindTexture("images/player_right/player2.png");
    runText[3].bindTexture("images/player_right/player3.png");
    runText[4].bindTexture("images/player_right/player4.png");
    runText[5].bindTexture("images/player_right/player5.png");

    fireArr[0].bindTexture("images/player/respawn1.png");
    fireArr[1].bindTexture("images/player/respawn1.png");
    fireArr[2].bindTexture("images/player/respawn1.png");
    fireArr[3].bindTexture("images/player/respawn1.png");

    runText_left[0].bindTexture("images/player_left/player0.png");
    runText_left[1].bindTexture("images/player_left/player1.png");
    runText_left[2].bindTexture("images/player_left/player2.png");
    runText_left[3].bindTexture("images/player_left/player3.png");
    runText_left[4].bindTexture("images/player_left/player4.png");
    runText_left[5].bindTexture("images/player_left/player5.png");

    swingText[0].bindTexture("images/player/swing1.png");
    swingText[1].bindTexture("images/player/swing2.png");
    swingText[2].bindTexture("images/player/swing3.png");
    swingText[3].bindTexture("images/player/swing3.png");
    swingText[4].bindTexture("images/player/swing3.png");
    swingText[5].bindTexture("images/player/swing3.png");
    swingText[6].bindTexture("images/player/swing3.png");
    swingText[7].bindTexture("images/player/swing3.png");
    swingText[8].bindTexture("images/player/swing3.png");
    swingText[9].bindTexture("images/player/swing3.png");
    swingText[10].bindTexture("images/player/swing3.png");
    swingText[11].bindTexture("images/player/swing3.png");
    swingText[12].bindTexture("images/player/swing3.png");

    swingTextLeft[0].bindTexture("images/player_left/swing1.png");
    swingTextLeft[1].bindTexture("images/player_left/swing2.png");
    swingTextLeft[2].bindTexture("images/player_left/swing3.png");
    swingTextLeft[3].bindTexture("images/player_left/swing3.png");
    swingTextLeft[4].bindTexture("images/player_left/swing3.png");
    swingTextLeft[5].bindTexture("images/player_left/swing3.png");
    swingTextLeft[6].bindTexture("images/player_left/swing3.png");
    swingTextLeft[7].bindTexture("images/player_left/swing3.png");
    swingTextLeft[8].bindTexture("images/player_left/swing3.png");
    swingTextLeft[9].bindTexture("images/player_left/swing3.png");
    swingTextLeft[10].bindTexture("images/player_left/swing3.png");
    swingTextLeft[11].bindTexture("images/player_left/swing3.png");
    swingTextLeft[12].bindTexture("images/player_left/swing3.png");

    stand[0].bindTexture("images/player_right/play.png");
    stand[1].bindTexture("images/player_left/play.png");

    swingTextLeft[0].bindTexture("images/player_left/swing1.png");
    swingTextLeft[1].bindTexture("images/player_left/swing2.png");
    swingTextLeft[2].bindTexture("images/player_left/swing3.png");
    swingTextLeft[3].bindTexture("images/player_left/swing3.png");
    swingTextLeft[4].bindTexture("images/player_left/swing3.png");
    swingTextLeft[5].bindTexture("images/player_left/swing3.png");
    swingTextLeft[6].bindTexture("images/player_left/swing3.png");
    swingTextLeft[7].bindTexture("images/player_left/swing3.png");
    swingTextLeft[8].bindTexture("images/player_left/swing3.png");
    swingTextLeft[9].bindTexture("images/player_left/swing3.png");
    swingTextLeft[10].bindTexture("images/player_left/swing3.png");
    swingTextLeft[11].bindTexture("images/player_left/swing3.png");
    swingTextLeft[12].bindTexture("images/player_left/swing3.png");

    respawnArr[0].bindTexture("images/player/respawn1.png");
    respawnArr[1].bindTexture("images/player/respawn2.png");
    respawnArr[2].bindTexture("images/player/respawn3.png");
    respawnArr[3].bindTexture("images/player/respawn4.png");
    respawnArr[4].bindTexture("images/player/respawn5.png");


    fireArr[0].bindTexture("images/player/fire1.png");
    fireArr[1].bindTexture("images/player/fire2.png");
    fireArr[2].bindTexture("images/player/fire3.png");
    fireArr[3].bindTexture("images/player/fire4.png");

    stand[0].bindTexture("images/player_right/play.png");
    stand[1].bindTexture("images/player_left/play.png");

    jumpText[0].bindTexture("images/player_right/jump0.png");
    jumpText[1].bindTexture("images/player_right/jump1.png");
    jumpText[2].bindTexture("images/player_right/jump2.png");
    jumpText[3].bindTexture("images/player_right/jump3.png");
    jumpText[4].bindTexture("images/player_right/jump4.png");
    jumpText[5].bindTexture("images/player_right/jump5.png");

    jumpTextL[0].bindTexture("images/player_left/jump0.png");
    jumpTextL[1].bindTexture("images/player_left/jump1.png");
    jumpTextL[2].bindTexture("images/player_left/jump2.png");
    jumpTextL[3].bindTexture("images/player_left/jump3.png");
    jumpTextL[4].bindTexture("images/player_left/jump4.png");
    jumpTextL[5].bindTexture("images/player_left/jump5.png");

    dash[0].bindTexture("images/player_right/dash.png");
    dash[1].bindTexture("images/player_left/dashL.png");



    projA->Xpos=999;
    projA->Ypos=999;
    projA->box.x=999;
    projA->box.y=999;
    projA->box.width=0;
    projA->box.height=0;
}

void player::playerInit2()
{
     //rTime->start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    runText[0].bindTexture("images/player2_right/player0.png");
    runText[1].bindTexture("images/player2_right/player1.png");
    runText[2].bindTexture("images/player2_right/player2.png");
    runText[3].bindTexture("images/player2_right/player3.png");
    runText[4].bindTexture("images/player2_right/player4.png");
    runText[5].bindTexture("images/player2_right/player5.png");

    runText_left[0].bindTexture("images/player2_left/player0.png");
    runText_left[1].bindTexture("images/player2_left/player1.png");
    runText_left[2].bindTexture("images/player2_left/player2.png");
    runText_left[3].bindTexture("images/player2_left/player3.png");
    runText_left[4].bindTexture("images/player2_left/player4.png");
    runText_left[5].bindTexture("images/player2_left/player5.png");

    swingText[0].bindTexture("images/player2_right/swing1.png");
    swingText[1].bindTexture("images/player2_right/swing2.png");
    swingText[2].bindTexture("images/player2_right/swing3.png");
    swingText[3].bindTexture("images/player2_right/swing3.png");
    swingText[4].bindTexture("images/player2_right/swing3.png");
    swingText[5].bindTexture("images/player2_right/swing3.png");
    swingText[6].bindTexture("images/player2_right/swing3.png");
    swingText[7].bindTexture("images/player2_right/swing3.png");
    swingText[8].bindTexture("images/player2_right/swing3.png");
    swingText[9].bindTexture("images/player2_right/swing3.png");
    swingText[10].bindTexture("images/player2_right/swing3.png");
    swingText[11].bindTexture("images/player2_right/swing3.png");
    swingText[12].bindTexture("images/player2_right/swing3.png");

    swingTextLeft[0].bindTexture("images/player2_left/swing1.png");
    swingTextLeft[1].bindTexture("images/player2_left/swing2.png");
    swingTextLeft[2].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[3].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[4].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[5].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[6].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[7].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[8].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[9].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[10].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[11].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[12].bindTexture("images/player2_left/swing3.png");

    stand[0].bindTexture("images/player2_right/play.png");
    stand[1].bindTexture("images/player2_left/play.png");

    swingTextLeft[0].bindTexture("images/player2_left/swing1.png");
    swingTextLeft[1].bindTexture("images/player2_left/swing2.png");
    swingTextLeft[2].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[3].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[4].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[5].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[6].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[7].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[8].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[9].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[10].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[11].bindTexture("images/player2_left/swing3.png");
    swingTextLeft[12].bindTexture("images/player2_left/swing3.png");

    respawnArr[0].bindTexture("images/player/respawn1.png");
    respawnArr[1].bindTexture("images/player/respawn2.png");
    respawnArr[2].bindTexture("images/player/respawn3.png");
    respawnArr[3].bindTexture("images/player/respawn4.png");
    respawnArr[4].bindTexture("images/player/respawn5.png");

    fireArr[0].bindTexture("images/player/fire1.png");
    fireArr[1].bindTexture("images/player/fire2.png");
    fireArr[2].bindTexture("images/player/fire3.png");
    fireArr[3].bindTexture("images/player/fire4.png");

    stand[0].bindTexture("images/player2_right/play.png");
    stand[1].bindTexture("images/player2_left/play.png");
    stand[0].bindTexture("images/player2_right/play.png");

    jumpText[0].bindTexture("images/player2_right/jump0.png");
    jumpText[1].bindTexture("images/player2_right/jump1.png");
    jumpText[2].bindTexture("images/player2_right/jump2.png");
    jumpText[3].bindTexture("images/player2_right/jump3.png");
    jumpText[4].bindTexture("images/player2_right/jump4.png");
    jumpText[5].bindTexture("images/player2_right/jump5.png");

    jumpTextL[0].bindTexture("images/player2_left/jump0.png");
    jumpTextL[1].bindTexture("images/player2_left/jump1.png");
    jumpTextL[2].bindTexture("images/player2_left/jump2.png");
    jumpTextL[3].bindTexture("images/player2_left/jump3.png");
    jumpTextL[4].bindTexture("images/player2_left/jump4.png");
    jumpTextL[5].bindTexture("images/player2_left/jump5.png");

    dash[0].bindTexture("images/player2_right/dash.png");
    dash[1].bindTexture("images/player2_left/dashL.png");

    projA->Xpos=999;
    projA->Ypos=999;
    projA->box.x=999;
    projA->box.y=999;
    projA->box.width=0;
    projA->box.height=0;
}


void player::actions()
{
   switch(actionTrigger){
       case 0:
           cout<<"case 0"<<endl;
           //plyVel = startSpeed;
           plyVel = 0.002;
           glPushMatrix();
                glTranslated(PXpos, PYpos, PZoom);

                if(!ballCollided && swingDuration->getTicks() >= 400 && OnTile) // If player was swinging but not moving he still swings
                {
                    if(lastCase == 'L')
                        stand[1].binder();

                    if(lastCase == 'R')
                        stand[0].binder();
                }
                else if (!ballCollided && swingDuration->getTicks() >= 400 && !OnTile)
                {
                    if(lastCase == 'L')
                        jumpTextL[4].binder();

                    if(lastCase == 'R')
                        jumpText[4].binder();
                }
                else
                    swingText[2].binder();
                drawplayer();

           glPopMatrix();
      break;

   case 1:
       cout << "Case 1 " << endl;
           glPushMatrix();
                glTranslated(PXpos, PYpos, PZoom);
                if(5==5)//T->getTicks() > 3)
                {
                    if (!ballCollided && (swingDuration->getTicks() >= 400 || jumpInitiated)&&!pause)
                    {
                        if (plyVel  >  0.002)
                        {
                            plyVel = 0.002;
                            //cout << "IN te if " << endl;
                            plyAccel = 0.000005;
                        }
                        else
                        {
                            //cout<<"else"<<endl;
                            plyVel += plyAccel;
                            plyAccel += 0.0000015;
                        }


                        if(lastCase == 'R'&& !rightWC&&OnTile)//running on the ground and not colliding with the wall
                            PXpos += (plyVel*1200.5)/delta;//10;//(plyVel*1800.5)/delta;//10;
                        else if(lastCase == 'R'&& !rightWC&&!OnTile)
                            PXpos += (plyVel*800)/delta;//10;
                        if(lastCase == 'L'&& !leftWC&&OnTile)
                            PXpos -= (plyVel*1200.5)/delta;//10
                        else if(lastCase == 'L'&& !leftWC&&!OnTile)//move slower in the air
                            PXpos -= (plyVel*800)/delta;//10;

                    T->reset();
                    }
                }

                if (swingDuration->getTicks() >= 400 && !ballCollided&&!pause && OnTile)
                {
                    if(T2 ->getTicks()>80)
                    {
                        runspeed++;
                        runspeed %= 5;
                        T2->reset();
                    }
                    if(lastCase == 'R')
                      runText[runspeed].binder();

                    if(lastCase == 'L')
                      runText_left[runspeed].binder();
                }

                else if(swingDuration->getTicks() >= 400 && !ballCollided && !pause && !OnTile && isDash)
                {

                    cout << "in dash" << endl;
                    if(lastCase == 'R')
                      dash[0].binder();

                    if(lastCase == 'L')
                      dash[1].binder();
                }

                else if(swingDuration->getTicks() >= 400 && !ballCollided && !pause && !OnTile && !isDash)
                {

                    if(lastCase == 'R')
                      jumpText[5].binder();

                    if(lastCase == 'L')
                      jumpTextL[5].binder();
                }


                /*else
                {
                    if(lastCase == 'R')
                        swingText[2].binder();
                    if(lastCase == 'L')
                        swingTextLeft[2].binder();
                }*/
                drawplayer();
           glPopMatrix();

    break;
   case 4:
       glPushMatrix();
        glTranslated(PXpos, PYpos, PZoom);;
       rTime->start();
       if(rTime->getTicks()<=300)
       respawnArr[0].binder();
       if(rTime->getTicks()<=500&&rTime->getTicks()>300)
       respawnArr[1].binder();
       if(rTime->getTicks()<=600&&rTime->getTicks()>500)
       respawnArr[2].binder();
       if(rTime->getTicks()<=700&&rTime->getTicks()>600)
        respawnArr[3].binder();
        if(rTime->getTicks()<=800&&rTime->getTicks()>700)
        respawnArr[4].binder();
        if(rTime->getTicks()<=900&&rTime->getTicks()>800)
        {
            actionTrigger=0;
            rTime->stop();
            rTime->reset();
        }
       drawplayer();
       glPopMatrix();
    break;
   case 5://death animation
      /* glPushMatrix();
        glTranslated(PXpos, PYpos, PZoom);;
       fireTime->start();
       if(fireTime->getTicks()<=100)
       fireArr[0].binder();
       if(fireTime->getTicks()<=200 && fireTime->getTicks()>100)
       fireArr[1].binder();
       if(fireTime->getTicks()<=300 && fireTime->getTicks()>200)
       fireArr[2].binder();
       if(fireTime->getTicks()<=400 && fireTime->getTicks()>300)
       fireArr[3].binder();
       if(fireTime->getTicks()<=500 && fireTime->getTicks()>400)
       fireArr[0].binder();
       if(fireTime->getTicks()<=600 && fireTime->getTicks()>500)
       fireArr[1].binder();
       if(fireTime->getTicks()<=700 && fireTime->getTicks()>600)
       fireArr[2].binder();
       if(fireTime->getTicks()<=800 && fireTime->getTicks()>700)
       fireArr[3].binder();
       if(fireTime->getTicks()>=900)
        {
            actionTrigger=0;
            fireTime->stop();
            fireTime->reset();
        }
       drawplayer();
       glPopMatrix();*/
    break;
   }
   if(swinging&&!pause)
   {
           glPushMatrix();
              if(T2 ->getTicks()>80)
              {
                swingSpeed++;
                swingSpeed %= 8;
                T2->reset();
              }
            if (lastCase == 'R')
              swingText[swingSpeed].binder();
            if (lastCase == 'L')
                swingTextLeft[swingSpeed].binder();
              drawplayer();
           glPopMatrix();
   }
    if(isDash&&!pause)
    {
        if(!OnTile)
            verticalVelocity=-0.5;

        if(lastCase=='R'&&rightWC)
        {

                    isDash=false;
                    dashVel=7;
        }
        if(lastCase=='R'&&!rightWC)
        {
            dash[0].binder();
            PXpos += (dashVel)/delta;
            if(dashVel<=0||rightWC)
            {
                isDash=false;
                dashVel=7;
            }
            dashVel-=(11.5)/delta;//dashDec;//5.5
        }

        if(lastCase=='L'&&leftWC)
        {
                    isDash=false;
                    dashVel=7;
        }
         if(lastCase=='L'&&!leftWC)
        {
            dash[1].binder();
            PXpos -= (dashVel)/delta;
            if(dashVel<=0||leftWC)
            {
                isDash=false;
                dashVel=7;
            }
            dashVel-=(11.5)/delta;//5.5
        }

    }
    if(delta>0&&!pause)
    {
        if(!isDash)
        PYpos+=(verticalVelocity)/delta;

        if(OnTile&&verticalVelocity<0)
        {
            jump=0;
            verticalVelocity=0;
            PYpos=-1.38;
        }

        if(topWC)
            verticalVelocity=-0.5;

        if(!OnTile&&!isDash)
           verticalVelocity+=(playerGrav)/delta;//decrement the vertical velocity by the gravity as long as the player is not touching a tile


    }
}
 void player::playerUpdateHbox() // updates the hit-box location to the players location
 {
    box.x = PXpos;
    box.y = PYpos;
    return;
 }
