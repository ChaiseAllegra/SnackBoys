#include "GLInputs.h"
#include <player.h>
#include <GLModel.h>
#include <collision.h>
#include <box.h>
#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;

timer* J = new timer();

Inputs::Inputs()
{
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
}

Inputs::~Inputs()
{

}

void Inputs::keyEnv(parallax* plx, float speed)
{
    switch(wParam)
    {
        case VK_LEFT:
            // plx->Xmin -=speed;
            // plx->Xmax -=speed;
            break;
        case VK_RIGHT:
            // plx->Xmin +=speed;
            // plx->Xmax +=speed;
            break;
         case VK_UP:
            // plx->Ymin -=speed;
            // plx->Ymax -=speed;
            break;
        case VK_DOWN:
            //  plx->Ymin +=speed;
            //  plx->Ymax +=speed;
            break;
    }
}

void Inputs::keyPressed(Model* Mdl)
{
    switch(wParam)
    {
    case VK_LEFT:
        Mdl->RotateX +=1.0;
        break;
    case VK_RIGHT:
        Mdl->RotateX -=1.0;
        break;
    case VK_DOWN:
        Mdl->RotateY -=1.0;
        break;
    case VK_UP:
        Mdl->RotateY +=1.0;
        break;
    case VK_ADD:
        Mdl->Zoom +=1.0;
        break;
    case VK_SUBTRACT:
        Mdl->Zoom -=1.0;
        break;
    }
}

void Inputs::keyUp(player* ply, player* ply2, bool pressed[256])
{
    if(pressed['D']==true)
    {
        cout<<"should work"<<endl;
        pressed['D']=false;
        pressed['A']=false;
        ply->actionTrigger = 0;
    }
   /* if(!pressed['D'])
        cout<<"d false"<<endl;

    if(!pressed['A'])
        cout<<"a false"<<endl;

        if(!pressed['J'])
        cout<<"j false"<<endl;

        if(!pressed['L'])
        cout<<"l false"<<endl;*/
    //-----------------------------------PLAYER 1----------------------------------------------//
    /*if ((pressed['D'] || wParam == 'D') || (pressed['A'] || wParam == 'A') && !ply->midCollision)
    {
            ply->actionTrigger = 0;
    }
    ply->swinging = false;

    //-----------------------------------PLAYER 2----------------------------------------------//

    if ((pressed['J'] || wParam == 'J') || (pressed['L'] || wParam == 'L') && !ply2->midCollision)
    {
            ply2->actionTrigger = 0;
    }
    ply2->swinging = false;*/
}
void Inputs::keyPressed(player* ply)
{
    switch(wParam)
    {
       default:break;
    }
    return;
}

void Inputs::keyPressed(player* ply, player* ply2, Model *play, Model *play2, Model* wallL,Model* wallR,Model* wallT, bool pressed[256])
{
    /*// --------------------------------------------------------- PLAYER 1 ---------------------------------------------------------//
   // if(pressed['A']==false)
   //     cout<<"A not pressed"<<endl;
     if(pressed['A'])
     {
         cout<<"A pressed"<<endl;
         //ply->leftReleased = false;
         //if(ply->leftReleased == false && ply->midCollision == false)
            ply->actionTrigger = 1;
         ply->lastKey = 'L';
         ply->lastCase = 'L';
     }

    if(pressed['D'])
    {
        cout<<"D pressed"<<endl;
        //ply->rightReleased = false;
       // if(ply->rightReleased == false && ply->midCollision == false)
        ply->actionTrigger = 1;
        // ply->actions(ply->actionTrigger, ply, play);
        ply->lastKey = 'R';
        ply->lastCase = 'R';
    }
    if(!pressed['D']&&!pressed['A'])
    {
        cout<<"not pressed"<<endl;
        ply->actionTrigger=0;
    }

    if(pressed['W'])
        ply->upPressed = true;

    if(pressed['F']||wParam=='F')
    {
        ply->swingPressed = true;
        if(ply->swingReleased == true && ply->swingPressed == true && ply->swingTimer->getTicks()>= 500)
        {
            ply->swingReleased = false;
            ply->swingDuration->reset();
            ply->swingDuration->start();
            ply->swingTimer->reset();
            if (ply->upPressed == true && ply->downPressed == false)
            {
                if(ply->lastKey == 'R')
                    ply->swingDirection = "TOPRIGHT";

                if(ply->lastKey == 'L')
                    ply->swingDirection = "TOPLEFT";
            }
            else if (ply->upPressed == false && ply->downPressed == true)
            {
                if(ply->lastKey == 'R')
                    ply->swingDirection = "BOTTOMRIGHT";

                if(ply->lastKey == 'L')
                    ply->swingDirection = "BOTTOMLEFT";
            }
            else
            {
                if(ply->lastKey == 'R')
                    ply->swingDirection = "RIGHT";

                if(ply->lastKey == 'L')
                    ply->swingDirection = "LEFT";
            }
            ply->swinging = true;
        }
        else
            ply->swinging = false;
    }
    if(pressed['S'])
        ply->downPressed = true;
    if(pressed['E']||wParam=='E')
    {
        ply->jumpReleased = false;

        if(ply->jumpReleased == false)
            ply->jumpInitiated = true;
    }
    //------------------------------------------------------------PLAYER 2---------------------------------------------------------------//
     if(pressed['J']||wParam=='J')
     {
         ply2->leftReleased = false;
        // if(ply2->leftReleased == false && ply2->midCollision == false)
         ply2->actionTrigger = 1;
         ply2->lastKey = 'L';
         ply2->lastCase = 'L';
     }
   if(pressed['L']||wParam=='L')
    {
        ply2->rightReleased = false;
       // if(ply2->rightReleased == false && ply2->midCollision == false)
        ply2->actionTrigger = 1;
        ply2->lastKey = 'R';
        ply2->lastCase = 'R';
    }


    if(pressed['I'])
        ply2->upPressed = true;

    if(pressed['H'])
    {
        ply2->swingPressed = true;
        if(ply2->swingReleased == true && ply2->swingPressed == true && ply2->swingTimer->getTicks()>= 500)
        {
            ply2->swingReleased = false;
            ply2->swingDuration->reset();
            ply2->swingDuration->start();
            ply2->swingTimer->reset();
            if (ply2->upPressed == true && ply2->downPressed == false)
            {
                if(ply2->lastKey == 'R')
                    ply2->swingDirection = "TOPRIGHT";

                if(ply2->lastKey == 'L')
                    ply2->swingDirection = "TOPLEFT";
            }
            else if (ply2->upPressed == false && ply2->downPressed == true)
            {
                if(ply2->lastKey == 'R')
                    ply2->swingDirection = "BOTTOMRIGHT";

                if(ply2->lastKey == 'L')
                    ply2->swingDirection = "BOTTOMLEFT";
            }
            else
            {
                if(ply2->lastKey == 'R')
                    ply2->swingDirection = "RIGHT";

                if(ply2->lastKey == 'L')
                    ply2->swingDirection = "LEFT";
            }
            ply2->swinging = true;
        }
        else
            ply2->swinging = false;
    }
    if(pressed['K'])
        ply2->downPressed = true;
    if(pressed['U'])
    {
        ply2->jumpReleased = false;

        if(ply2->jumpReleased == false)
            ply2->jumpInitiated = true;
    }

    /*if ((!pressed['D'] || wParam != 'D') && (!pressed['A'] || wParam != 'A') && !ply->midCollision)
    {
            ply->actionTrigger = 0;
    }
   // ply->swinging = false;

    //-----------------------------------PLAYER 2----------------------------------------------//

    if ((!pressed['J'] || wParam != 'J') && (!pressed['L'] || wParam != 'L') && !ply2->midCollision)
    {
            ply2->actionTrigger = 0;
    }
    //ply2->swinging = false;*/
}
void Inputs::keyUP()
{
  switch (wParam)
            {
                default:
                break;
            }
}
void Inputs::idle(bool pressed[256],player* ply, player * ply2)
{
    J->start();
    if(pressed['A'])
     {
            ply->actionTrigger = 1;
         ply->lastKey = 'L';
         ply->lastCase = 'L';
     }

    if(pressed['D'])
    {
        ply->actionTrigger = 1;
        ply->lastKey = 'R';
        ply->lastCase = 'R';
    }

    if(!pressed['D']&&!pressed['A'])
        ply->actionTrigger=0;

    if(pressed['E']&&J->getTicks() >= 200)
            if(ply->jump<2)
            {
            J->reset();
            ply->verticalVelocity=0.005;
            ply->jump++;
            cout<<ply->jump<<endl;
            }



    if(pressed['W'])
    {
        ply->upPress = true;
        ply->downPress=false;
        }

    if(pressed['S'])
    {
        ply->upPress = false;
        ply->downPress=true;
    }
    if(!pressed['S']&&!pressed['W'])
    {
           ply->upPress = false;
        ply->downPress=false;
    }

     if(pressed['F'])
    {
       // if( ply->swingTimer->getTicks()>= 500)
       // {
            ply->swingDuration->reset();
            ply->swingDuration->start();
            ply->swingTimer->reset();

              if (ply->upPress)
              {

                if(ply->lastCase == 'R')
                    ply->swingDirection = "TOPRIGHT";

                if(ply->lastCase == 'L')
                    ply->swingDirection = "TOPLEFT";
              }
              else if (ply->downPress)
              {
                if(ply->lastCase == 'R')
                    ply->swingDirection = "BOTTOMRIGHT";

                if(ply->lastCase == 'L')
                    ply->swingDirection = "BOTTOMLEFT";

              }

              else
                {
                if(ply->lastCase == 'R')
                    ply->swingDirection = "RIGHT";

                if(ply->lastCase == 'L')
                    ply->swingDirection = "LEFT";
              }
            ply->swinging = true;
        //}
    }
        else
            ply->swinging = false;

    if(pressed['J'])
     {
        ply2->actionTrigger = 1;
         ply2->lastKey = 'L';
         ply2->lastCase = 'L';
     }

    if(pressed['L'])
    {
        ply2->actionTrigger = 1;
        ply2->lastKey = 'R';
        ply2->lastCase = 'R';
    }
    if(!pressed['J']&&!pressed['L'])
        ply2->actionTrigger=0;

      if(pressed['O'])
            ply2->jumpInitiated = true;
}
void Inputs::mouseEventDown(Model *Model, double x,double y)
{
        prev_Mouse_X =x;
        prev_Mouse_Y =y;
   switch (wParam)
            {
                case MK_LBUTTON:
                        Mouse_Roatate = true;
                    break;
                case MK_RBUTTON:
                     Mouse_Translate =true;
                    break;
                case MK_MBUTTON:
                    break;
                default:
                    break;
            }
}
 void Inputs::mouseEventUp()
 {
    Mouse_Translate =false;
    Mouse_Roatate =false;
 }
void Inputs::mouseWheel(Model *Model,double Delta)
{
    Model->Zoom += Delta/100;
}
void Inputs::mouseMove(Model *Model,double x,double y)
{
      if(Mouse_Translate)
      {
       Model->Xpos += (x-prev_Mouse_X)/100;
       Model->Ypos -= (y-prev_Mouse_Y)/100;
       prev_Mouse_X =x;
       prev_Mouse_Y =y;
      }
      if(Mouse_Roatate)
      {
        Model->RotateY += (x-prev_Mouse_X)/3;
        Model->RotateX += (y-prev_Mouse_Y)/3;
        prev_Mouse_X =x;
        prev_Mouse_Y =y;
      }
}


