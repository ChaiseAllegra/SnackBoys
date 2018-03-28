#include "GLInputs.h"
#include <player.h>
#include<GLModel.h>
#include<collision.h>
#include<box.h>
#include <stdint.h>

char lastKey ;
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

void Inputs::keyUp(player* ply)
{
    //ply->actionTrigger =1;

    switch(wParam)
    {
       default:
                   if (lastKey == 'R')
                   {
                       ply->actionTrigger = 0;

                   }
                   else
                   {
                       ply->actionTrigger = 3;
                   }
                    ply->box.height = 0;
                    ply->box.width = 0;
           break;
    }
}
void Inputs::keyPressed(player* ply)
{
    switch(wParam)
    {
       default:break;
    }

    return;
}

void Inputs::keyPressed(player* ply, player* ply2,Model *play, Model* wallL,Model* wallR,Model* wallT, Model* divide)
{

    switch(wParam)
    {
     case VK_LEFT:
      // if(!ply->box_collision(divide->box,ply->box))
       ply->actionTrigger = 2;

        lastKey = 'L';
        break;

    case VK_RIGHT:
      // if(!ply->box_collision(ply->box,divide->box))
       ply->actionTrigger = 1;

        lastKey = 'R';
        break;

    case 'T':
      /*  if(ply2->jump<2)
        {
            ply2->jump++;
            ply2->verticalVelocity=0.15;
        }*/
        break;

    case VK_UP:
         if(ply->jump<2)
        {
            ply->jump++;
            ply->verticalVelocity=0.15;
        }
        if(ply2->jump<2)
        {
            ply2->jump++;
            ply2->verticalVelocity=0.15;
        }
        break;

    case VK_SPACE:

        ply->actionTrigger = 4;
        ply->box.height = .5;
        ply->box.width = .5;

         ply2->actionTrigger = 4;
        ply2->box.height = .5;
        ply2->box.width = .5;

        break;

    case VK_NUMPAD1:
         ply2->actionTrigger = 2;
    break;

    case VK_NUMPAD3:
        ply2->actionTrigger = 1;
    break;

    case VK_NUMPAD2:
        if(ply2->jump<2)
        {
            ply2->jump++;
            ply2->verticalVelocity=0.15;
        }
    break;
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
