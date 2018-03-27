#include "GLInputs.h"
#include <player.h>
#include<GLModel.h>
#include<collision.h>
#include<box.h>
Inputs::Inputs()
{
    //ctor
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
}

bool leftPRESSED = FALSE;
bool rightPRESSED = FALSE;

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
    ply->actionTrigger =1;

    switch(wParam)
    {
       default:break;
    }
}
void Inputs::keyPressed(player* ply)
{
    cout<<"jack "<<endl;
    return;
}

void Inputs::keyPressed(player* ply, Model* wallL,Model* wallR,Model* wallT)
{
    box tmp1;
    tmp1.x = ply->playerHBox.x - 0.2;
    tmp1.y = ply->playerHBox.y - 0.2;
    tmp1.width = ply->playerHBox.width;
    tmp1.height = ply->playerHBox.height;

    if(wParam==VK_LEFT)
    {

        ply->actionTrigger =0;
        ply->verticies[0].x-=0.2;
       ply->verticies[1].x-=0.2;
       ply->verticies[2].x-=0.2;

       ply->verticies[3].x-=0.2;
       ply->playerUpdateHbox();
    }

     if(wParam==VK_RIGHT)
        if(box_collision(ply->playerHBox,wallR->wallHBox)==false)
      {
       ply->actionTrigger =1;

       ply->verticies[0].x+=0.2;
       ply->verticies[1].x+=0.2;
       ply->verticies[2].x+=0.2;
       ply->verticies[3].x+=0.2;

        ply->playerUpdateHbox();
      }
      else{
             ply->actionTrigger =0;
      }
   /* switch(wParam)
    {
     case VK_LEFT:
      if(box_collision(tmp1,wallL->wallHBox)==false)
      {
           ply->actionTrigger = 1;

           if(!leftPRESSED)
           {

            float  temp1, temp2, temp3, temp4;
           temp1 = ply->verticies[0].x;
           ply->verticies[0].x = ply->verticies[1].x;
           ply->verticies[1].x = temp1;

           temp2 = ply->verticies[0].y;
           ply->verticies[0].y = ply->verticies[1].y;
           ply->verticies[1].y = temp1;

           temp3 = ply->verticies[2].x;
           ply->verticies[2].x = ply->verticies[3].x;
           ply->verticies[3].x = temp3;

           temp4 = ply->verticies[2].y;
           ply->verticies[2].y = ply->verticies[3].y;
           ply->verticies[3].y = temp4;
           leftPRESSED = TRUE;
            rightPRESSED = FALSE;
           }


           ply->verticies[0].x -= 0.2;
           ply->verticies[1].x -= 0.2;
           ply->verticies[2].x -= 0.2;
           ply->verticies[3].x -= 0.2;
           ply->playerUpdateHbox();
      }
        break;

      case VK_RIGHT:
        if(box_collision(ply->playerHBox,wallR->wallHBox)==false)
        {
           ply->actionTrigger = 1;
           if(!rightPRESSED){
           float  temp1, temp2, temp3, temp4;
           temp1 = ply->verticies[0].x;
           ply->verticies[0].x = ply->verticies[1].x;
           ply->verticies[1].x = temp1;

           temp2 = ply->verticies[0].y;
           ply->verticies[0].y = ply->verticies[1].y;
           ply->verticies[1].y = temp1;

           temp3 = ply->verticies[2].x;
           ply->verticies[2].x = ply->verticies[3].x;
           ply->verticies[3].x = temp3;

           temp4 = ply->verticies[2].y;
           ply->verticies[2].y = ply->verticies[3].y;
           ply->verticies[3].y = temp4;

           leftPRESSED = FALSE;
           rightPRESSED = TRUE;
           }

            ply->verticies[0].x += 0.2;
            ply->verticies[1].x += 0.2;
            ply->verticies[2].x += 0.2;
            ply->verticies[3].x += 0.2;
            ply->playerUpdateHbox();

        }
        break;

    case VK_DOWN:

        break;

    case VK_UP:

        break;

    case VK_ADD:

        break;

    case VK_SUBTRACT:

        break;
    }
   */
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
