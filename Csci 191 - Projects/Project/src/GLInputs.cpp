#include "GLInputs.h"
#include <player.h>
#include <GLModel.h>
#include <collision.h>
#include <box.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <sounds.h>

sounds* jumpSound = new sounds();
using namespace std;
timer* stunTimer= new timer();

Inputs::Inputs()
{
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
   dashTimer= new timer();
   dashTimer2= new timer();
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
    //cout << "Inputs!!" << endl;
    ply->jumpTimer->start();
    ply2->jumpTimer->start();
    dashTimer->start();
    dashTimer2->start();

    if(ply->stunned)
    {
        stunTimer->start();
        ply->actionTrigger=0;
    }
    if(ply->stunned&&stunTimer->getTicks()>900)
    {
    stunTimer->reset();
    ply->stunned=false;
    }
    if(!ply->stunned)
    {

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

    if(!pressed['D']&&!pressed['A']||ply->isDash)
        ply->actionTrigger=0;
    if(pressed['S'])//ducking
        ply->box.height=ply->trueHeight/2;
    if(!pressed['S'])
        ply->box.height=ply->trueHeight;

    if(pressed['E']&&ply->jumpTimer->getTicks() >= 200)//200ms
        if(ply->jump<2)
        {
            //jumpSound->playSound("sounds/jump.mp3");
            ply->jumpTimer->reset();
            ply->verticalVelocity=6;//0.008;
            ply->jump++;
        }

     if(pressed['F'])
     {
        ply->swinging=true;
     }

     if(!pressed['F'])
        ply->swinging=false;

    if(pressed['T'])
    {

      if(ply->ydir<1)
        ply->ydir+=(0.0050*700)/ply->delta;

       if(ply->ydir>0&&ply->xdir>0)
         ply->xdir-=(0.0050*700)/ply->delta;

        if(ply->ydir<=0&&ply->xdir<1)
         ply->xdir+=(0.0050*700)/ply->delta;
    }
     if(pressed['G'])
    {
        if(ply->ydir>-1)
        ply->ydir-=(0.0050*700)/ply->delta;

       if(ply->ydir<=0&&ply->xdir>0)
         ply->xdir-=(0.005*700)/ply->delta;

         if(ply->ydir>0&&ply->xdir<1)
         ply->xdir+=(0.005*700)/ply->delta;

    }
    if(pressed['R']&&dashTimer->getTicks()>1200)
    {
        ply->isDash=true;
        ply->prevx=ply->PXpos;
        dashTimer->reset();
    }
    if(pressed['Q'])
    {
        ply->thrown=true;
        ply->swinging=true;
    }

    if(pressed['C'])
        ply->hold=true;
    else
        ply->hold=false;
}


    //------------------------------player 2---------------------------//
    if(ply2->stunned)
    {
        stunTimer->start();
        ply2->actionTrigger=0;
    }
    if(ply2->stunned&&stunTimer->getTicks()>900)
    {
    stunTimer->reset();
    ply2->stunned=false;
    }
    if(!ply2->stunned)
    {
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
    if(pressed['K'])//ducking
        ply2->box.height=ply2->trueHeight/2;
    if(!pressed['K'])
        ply2->box.height=ply2->trueHeight;

    if(pressed['O']&&ply2->jumpTimer->getTicks() >= 200)//200ms
        if(ply2->jump<2)
        {
            //asjumpSound->playSound("sounds/jump.mp3");
            ply2->jumpTimer->reset();
            ply2->verticalVelocity=6;//0.008;
            ply2->jump++;
        }

     if(pressed['P'])
        ply2->swinging=true;

     if(!pressed['P'])
        ply2->swinging=false;

    if(pressed['Y'])
    {

      if(ply2->ydir<1)
        ply2->ydir+=(0.0025*700)/ply2->delta;

       if(ply2->ydir>0&&ply2->xdir>0)
         ply2->xdir-=(0.0025*700)/ply2->delta;

        if(ply2->ydir<=0&&ply2->xdir<1)
         ply2->xdir+=(0.0025*700)/ply2->delta;
    }
     if(pressed['H'])
    {
        if(ply2->ydir>-1)
        ply2->ydir-=(0.0025*700)/ply2->delta;

       if(ply2->ydir<=0&&ply2->xdir>0)
         ply2->xdir-=(0.0025*700)/ply2->delta;

         if(ply2->ydir>0&&ply2->xdir<1)
         ply2->xdir+=(0.0025*700)/ply2->delta;

    }
    if(pressed['U']&&dashTimer2->getTicks()>1200)
    {
        dashTimer2->reset();
        ply2->isDash=true;
        ply2->prevx=ply2->PXpos;
    }
    if(pressed['M'])
    {
        ply2->thrown=true;
        ply2->swinging=true;
    }

    if(pressed['N'])
        ply2->hold=true;
    else
        ply2->hold=false;
    }
   /*if(pressed['Z'])
    {
        ply2->actionTrigger=5;
        ply->actionTrigger=5;
    }*/


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

void Inputs::keySound(bool pressed[256], sounds* snds)
{
        if (pressed['F'])
        {
            //snds->playSound("sounds/swing.mp3");
        }




}


