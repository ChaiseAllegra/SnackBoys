#include "GLInputs.h"
#include <player.h>
#include <GLModel.h>
#include <collision.h>
#include <box.h>
#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;

Inputs::Inputs()
{
    //ctor
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
}
Inputs::~Inputs()
{
    //dtor
}
void Inputs::keyEnv(parallax* plx, float speed)
{
    switch(wParam)
    {
        case VK_LEFT:
            //plx->Xmin -=speed;
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
                   //-----------------------------------PLAYER 1----------------------------------------------//
                   if ((pressed['A'] ||wParam=='A')&& !ply->rightReleased && !ply->midCollision)
                   {
                       ply->leftReleased = true;
                       ply->plyVel = 0.002;
                       ply->actionTrigger = 1;
                       ply->lastKey = 'R';
                   }
                   if ((pressed['D']||wParam=='D') && !ply->leftReleased && !ply->midCollision)
                   {
                       ply->rightReleased = true;
                       ply->plyVel = 0.002;
                       ply->actionTrigger = 2;
                       ply->lastKey = 'L';
                   }

                   if (pressed['A']||wParam=='A')
                       ply->leftReleased = true;
                   if(pressed['D']||wParam=='D')
                       ply->rightReleased = true;
                   if (ply->rightReleased && ply->leftReleased && !ply->midCollision)
                   {
                      // if (ply->lastKey == 'L')
                        //   ply->actionTrigger = 3;
                       //if (ply->lastKey == 'R')
                           //ply->actionTrigger = 0;
                   }
                   ply->swinging = false;
                   //-----------------------------------PLAYER 2----------------------------------------------//
                   if ((pressed['J']||wParam=='J') && !ply2->rightReleased && !ply2->midCollision)
                   {
                       ply2->leftReleased = true;
                       ply2->plyVel = 0.002;
                       ply2->actionTrigger = 1;
                       ply2->lastKey = 'R';
                   }
                   if ((pressed['L']||wParam=='L') && !ply2->leftReleased && !ply2->midCollision)
                   {
                       ply2->rightReleased = true;
                       ply2->plyVel = 0.002;
                       ply2->actionTrigger = 2;
                       ply2->lastKey = 'L';
                   }

                   if (pressed['J']||wParam=='J')
                       ply2->leftReleased = true;
                   if(pressed['L']||wParam=='L')
                       ply2->rightReleased = true;
                   if (ply2->rightReleased && ply2->leftReleased && !ply2->midCollision)//problem boolean not set correctly
                   {
                      // if (ply2->lastKey == 'L')
                        //   ply2->actionTrigger = 3;
                       //if (ply2->lastKey == 'R')
                           //ply2->actionTrigger = 0;
                   }
                   ply2->swinging = false;
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
    // --------------------------------------------------------- PLAYER 1 ---------------------------------------------------------//
     if(pressed['A']||wParam=='A')
     {
         cout << "A on" << endl;
         ply->leftReleased = false;
         if(ply->leftReleased == false && ply->midCollision == false)
         ply->actionTrigger = 2;
        // ply->actions(ply->actionTrigger, ply, play);
         ply->lastKey = 'L';
     }

    if(pressed['D']||wParam=='D')
    {

        ply->rightReleased = false;
        if(ply->rightReleased == false && ply->midCollision == false)
        ply->actionTrigger = 1;
         //     ply->actions(ply->actionTrigger, ply, play);
        ply->lastKey = 'R';
    }


    if(pressed['W'])
        ply->upPressed = true;
    if(pressed['F']||wParam=='F')
    {
        ply->swingPressed = true;
        if(ply->swingReleased == true && ply->swingPressed == true && ply->swingTimer->getTicks()>= 500)
        {
            ply->swingReleased = false;
            //cout << "Swung" << endl;
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
         if(ply2->leftReleased == false && ply2->midCollision == false)
         ply2->actionTrigger = 2;
        //ply2->actions(ply2->actionTrigger, ply2, play2);
         ply2->lastKey = 'L';
     }
    if(pressed['L']||wParam=='L')
    {
        cout<<"L on"<<endl;
        ply2->rightReleased = false;
        if(ply2->rightReleased == false && ply2->midCollision == false)
        ply2->actionTrigger = 1;
        //ply2->actions(ply2->actionTrigger, ply2, play2);
        ply2->lastKey = 'R';
    }
     if(!pressed['L'])
        cout<<"L off"<<endl;
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
}
void Inputs::keyUP()
{
  switch (wParam)
            {
                default:
                break;
            }
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


