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
                    ply->playerHBox.height = 0;
                    ply->playerHBox.width = 0;
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

void Inputs::keyPressed(player* ply, Model *play, Model* wallL,Model* wallR,Model* wallT)
{
    box tmp1;
    tmp1.x = ply->playerHBox.x - 0.2;
    tmp1.y = ply->playerHBox.y - 0.2;
    tmp1.width = ply->playerHBox.width;
    tmp1.height = ply->playerHBox.height;
    switch(wParam)
    {
     case VK_LEFT:

       ply->actionTrigger = 2;

        lastKey = 'L';
        break;

    case VK_RIGHT:

       ply->actionTrigger = 1;

        lastKey = 'R';
        break;

    case 'T':

        break;

    case VK_UP:

        break;

    case VK_SPACE:

        ply->actionTrigger = 4;
        ply->playerHBox.height = .5;
        ply->playerHBox.width = .5;

        break;

    case VK_SUBTRACT:

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
