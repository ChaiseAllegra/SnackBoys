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
timer* J2= new timer();

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
}
void Inputs::keyPressed(player* ply)
{}

void Inputs::keyPressed(player* ply, player* ply2, Model *play, Model *play2, Model* wallL,Model* wallR,Model* wallT, bool pressed[256])
{

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
    J2->start();
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

    if(pressed['E']&&J->getTicks() >= 200)//200ms
        if(ply->jump<2)
        {
            J->reset();
            ply->verticalVelocity=0.008;
            ply->jump++;
        }

     if(pressed['F'])
     {
        ply->swinging=true;
        //ply->actionTrigger=4;
     }
     if(!pressed['F'])
        ply->swinging=false;

    if(pressed['T'])
    {

      if(ply->ydir<1)
        ply->ydir+=0.0025;

       if(ply->ydir>0&&ply->xdir>0)
         ply->xdir-=0.0025;

        if(ply->ydir<=0&&ply->xdir<1)
         ply->xdir+=0.0025;
    }
     if(pressed['G'])
    {
        if(ply->ydir>-1)
        ply->ydir-=0.0025;

       if(ply->ydir<=0&&ply->xdir>0)
         ply->xdir-=0.0025;

         if(ply->ydir>0&&ply->xdir<1)
         ply->xdir+=0.0025;

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

      if(pressed['O']&&J2->getTicks() >= 200)
    {
        if(ply2->jump<2)
        {
            J2->reset();
            ply2->verticalVelocity=0.005;
            ply2->jump++;
        }
    }

    if(pressed['H'])
    {
        //}
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


