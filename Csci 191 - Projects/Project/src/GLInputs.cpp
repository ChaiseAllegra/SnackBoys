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

}

void Inputs::keyPressed(Model* Mdl)
{

}

void Inputs::keyUp(player* ply, player* ply2, bool pressed[256])
{
}
void Inputs::keyPressed(player* ply)
{}

void Inputs::keyPressed(player* ply, player* ply2, Model *play, Model *play2, Model* wallL,Model* wallR,Model* wallT, bool pressed[256])
{

}
void Inputs::keyUP()
{

}
void Inputs::idle(bool pressed[256],player* ply, player * ply2)
{
    ply->jumpTimer->start();

    if(pressed['A']&&!ply->isDash)
     {
        ply->actionTrigger = 1;
        ply->lastKey = 'L';
        ply->lastCase = 'L';
     }

    if(pressed['D']&&!ply->isDash)
    {
        ply->actionTrigger = 1;
        ply->lastKey = 'R';
        ply->lastCase = 'R';
    }

    if(!pressed['D']&&!pressed['A'])
        ply->actionTrigger=0;
    if(pressed['S'])//ducking
        ply->box.height=ply->trueHeight/2;
    if(!pressed['S'])
        ply->box.height=ply->trueHeight;

    if(pressed['E']&&ply->jumpTimer->getTicks() >= 200)//200ms
        if(ply->jump<2)
        {
            ply->jumpTimer->reset();
            ply->verticalVelocity=0.008;
            ply->jump++;
        }

     if(pressed['F'])
        ply->swinging=true;

     if(!pressed['F'])
        ply->swinging=false;

    if(pressed['T'])
    {

      if(ply->ydir<1)
        ply->ydir+=(0.0025*600)/ply->delta;

       if(ply->ydir>0&&ply->xdir>0)
         ply->xdir-=(0.0025*600)/ply->delta;

        if(ply->ydir<=0&&ply->xdir<1)
         ply->xdir+=(0.0025*600)/ply->delta;
    }
     if(pressed['G'])
    {
        if(ply->ydir>-1)
        ply->ydir-=(0.0025*600)/ply->delta;

       if(ply->ydir<=0&&ply->xdir>0)
         ply->xdir-=(0.0025*600)/ply->delta;

         if(ply->ydir>0&&ply->xdir<1)
         ply->xdir+=(0.0025*600)/ply->delta;

    }
    if(pressed['R'])
    {
        ply->isDash=true;
        ply->prevx=ply->PXpos;
    }
    if(pressed['Q'])
        ply->thrown=true;

    if(pressed['C'])
        ply->hold=true;


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


