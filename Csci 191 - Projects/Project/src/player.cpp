#include <player.h>
#include <timer.h>
#include <GLTexture.h>
#include <windows.h>
#include <iostream>

player::player()
{
    //verticalVelocity=0.005;
    playerGrav=-0.00001;

    jumpInitiated = false;
    PZoom = -4;
    PXpos = 0;
    PYpos = -1.181;
    aimX = 0;
    aimY = -1;

        verticies[0].x = -0.5; verticies[0].y = -0.5; verticies[0].z = -1.0;
        verticies[1].x =  0.5; verticies[1].y = -0.5; verticies[1].z = -1.0;
        verticies[2].x =  0.5; verticies[2].y =  0.5; verticies[2].z = -1.0;
        verticies[3].x = -0.5; verticies[3].y =  0.5; verticies[3].z = -1.0;

    runspeed  = 0;
    jumpspeed = 0;
    actionTrigger = 0;
    box.width = 0;
    box.height = 0;
    leftWC=false;
    rightWC=false;

    swinging = false;
    upPress=false;
    downPress=false;

    plyVel = 0.2;
    !ballCollided;
    !midCollision;
    freezeTimer = 0;
    swingDuration->start();

    playerDirection = "RIGHT";

    isPlayer = 1;
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //T2->start();
    //T->start();
    runText[0].bindTexture("images/player_right/player0.png");
    runText[1].bindTexture("images/player_right/player1.png");
    runText[2].bindTexture("images/player_right/player2.png");
    runText[3].bindTexture("images/player_right/player3.png");
    runText[4].bindTexture("images/player_right/player4.png");
    runText[5].bindTexture("images/player_right/player5.png");

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
}

void player::actions()
{
   switch(actionTrigger){
       case 0:
           plyVel = 0.002;
           glPushMatrix();
                glTranslated(PXpos, PYpos, PZoom);

                if(!ballCollided && swingDuration->getTicks() >= 400) // If player was swinging but not moving he still swings
                {
                    if(lastCase == 'L')
                        stand[1].binder();

                    if(lastCase == 'R')
                        stand[0].binder();
                }
                else
                    swingText[2].binder();
                drawplayer();

           glPopMatrix();
      break;

   case 1:
           glPushMatrix();
                glTranslated(PXpos, PYpos, PZoom);
                if(5==5)//T->getTicks() > 3)
                {
                    if ((PXpos >= -3.4 && PXpos <= 3.4 ) && !ballCollided && (swingDuration->getTicks() >= 400 || jumpInitiated))
                    {
                        plyVel *= plyAccel;

                        if (plyVel  > 0.004)
                            plyVel = 0.004;
                        if(lastCase == 'R'&& !rightWC)
                            PXpos += plyVel*3;
                        if(lastCase == 'L'&& !leftWC)
                            PXpos -= plyVel*3;

                    T->reset();
                    }
                }

                if (swingDuration->getTicks() >= 400 && !ballCollided)
                {
                    if(T2 ->getTicks()>80)
                    {
                        runspeed++;
                        runspeed %= 5;;
                        T2->reset();
                    }
                    if(lastCase == 'R')
                      runText[runspeed].binder();

                    if(lastCase == 'L')
                      runText_left[runspeed].binder();
                }

                else
                {
                    if(lastCase == 'R')
                        swingText[2].binder();
                    if(lastCase == 'L')
                        swingTextLeft[2].binder();
                }
                drawplayer();
           glPopMatrix();

    break;

    case 4:
           glPushMatrix();
              if(T2 ->getTicks()>80)
              {
                runspeed++;
                runspeed %= 8;
                T2->reset();
              }
            if (lastCase == 'R')
              swingText[runspeed].binder();
            if (lastCase == 'L')
                swingTextLeft[runspeed].binder();
              drawplayer();
           glPopMatrix();

    break;
   }
}
 void player::playerUpdateHbox() // updates the hit-box location to the players location
 {
    box.x = PXpos;
    box.y = PYpos;
    return;
 }
