#include "levelAlpha.h"
#include <GLFW/glfw3.h>

levelAlpha::levelAlpha()
{
    modelTeapot->modelInit("images/player/player0.png", true, tex0);
    modelTeapot2->modelInit("images/player/player0.png", true, tex0);

    ply->playerInit();
    ply2->playerInit();

    leftWall->modelInit("images/box/girder.png", true, tex1);
    rightWall->modelInit("images/box/girder.png", true, tex2);
    topWall->modelInit("images/box/girder2.png", true, tex3);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    projA->modelInit("images/box/ball.png", true, ballHBTex);
    projB->modelInit("images/box/ball.png", true, ballHBTex);

    GoalL->modelInit("images/box/hitbox.png",true,texGL);
    GoalR->modelInit("images/box/hitbox.png",true,texGR);
    platTileBL->modelInit("images/box/block.png", true, tileTex);
    platTileBR->modelInit("images/box/block.png", true, tileTex);
    platTileTL->modelInit("images/box/block.png", true, tileTex);
    platTileTR->modelInit("images/box/block.png", true, tileTex);
    platTileM->modelInit("images/box/block.png", true, tileTex);

    cross->modelInit("images/box/crosshair.png", true, crosshair);

    ply->PXpos = -2;
    ply2->PXpos = 2;

    ply->isPlayer = 1;
    ply2->isPlayer = 2;

    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();

    ProjACurY=ply->PYpos, ProjACurX=ply->PXpos;
    ProjBCurY=ply2->PYpos, ProjBCurX=ply2->PXpos;
    projA->Xpos=999;
    projA->Ypos=999;
    projA->box.x = projA ->Xpos;
    projA->box.y = projA ->Ypos;
    projB->Xpos=999;
    projB->Ypos=999;
    projB->box.x = projB ->Xpos;
    projB->box.y = projB ->Ypos;
    ply2->health=5;
    ply->health=5;

}

levelAlpha::~levelAlpha()
{
    //dtor
}
bool levelAlpha::topOfTile(player* ply,Model* tileT){
        if(
           (((ply->pl_pltfrm_box.x-ply->pl_pltfrm_box.width) < (tileT->box.x + tileT->box.width) && (ply->pl_pltfrm_box.x+ply->pl_pltfrm_box.width) > (tileT->box.x - tileT->box.width))
            ||((tileT->box.x-tileT->box.width) < (ply->pl_pltfrm_box.x + ply->pl_pltfrm_box.width) && (tileT->box.x+tileT->box.width) > (ply->pl_pltfrm_box.x - ply->pl_pltfrm_box.width)))
            &&(((ply->pl_pltfrm_box.y-ply->pl_pltfrm_box.height) < (tileT->box.y + tileT->box.height) ||
            (tileT->box.y+tileT->box.height) > (ply->pl_pltfrm_box.y - ply->pl_pltfrm_box.height))&&
            (ply->pl_pltfrm_box.y-ply->pl_pltfrm_box.height>tileT->box.y))
        )
        return true;
        else
        return false;



    }
bool levelAlpha::playerOnTile(player* ply)
{
             if((topOfTile(ply,floor)||topOfTile(ply,platTileBL)||
                    topOfTile(ply,platTileBR)||topOfTile(ply,platTileTL)||topOfTile(ply,platTileTR)||
                    topOfTile(ply,platTileM)))

               return true;
    else
        false;
}
 bool levelAlpha::box_collision(Hbox rect1, Hbox rect2)
 {

 bool collisionX;
 bool collisionY;

collisionY = (((rect1.y-rect1.height) < (rect2.y + rect2.height) && (rect1.y+rect1.height) > (rect2.y - rect2.height))||((rect2.y-rect2.height) < (rect1.y + rect1.height) && (rect2.y+rect2.height) > (rect1.y - rect1.height)));
collisionX = (((rect1.x-rect1.width) < (rect2.x + rect2.width) && (rect1.x+rect1.width) > (rect2.x - rect2.width))||((rect2.x-rect2.width) < (rect1.x + rect1.width) && (rect2.x+rect2.width) > (rect1.x - rect1.width)));

    return collisionX && collisionY;
}
void levelAlpha:: update(float scale)
{
    //-------------------------------------------------------------------------------------------------//
    //-------------------------------WALL COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if (box_collision(Ball->box, rightWall->box))
    {
        ballDirX = -1;
        //hit=false;
        //velocity=resetV;
    }

    if (box_collision(Ball->box, leftWall->box))
    {
        ballDirX = 1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, topWall->box))
    {
        ballDirY = -1;
        //hit=false;
          //velocity=resetV;
    }

    if (box_collision(Ball->box, killBox->box))
    {
       CurYpos=2;
       ballDirY=-1;
       //hit=false;
       //velocity=resetV;

        if(ballDirX==-1)
        CurXpos+=2;

        if(ballDirX==1)
        CurXpos-=2;
    }
    if(box_collision(Ball->box,GoalR->box))
    {
        rightScore++;
    }
     if(box_collision(Ball->box,GoalL->box))
    {
        leftScore++;
    }

    if(box_collision(ply->box,leftWall->box))//player has hit the left wall
        ply->leftWC=true;//set to true so the player cannot move left
    else
        ply->leftWC=false;


    if(box_collision(ply->box,rightWall->box))//player has hit the right wall
        ply->rightWC=true;//set to true so the player cannot move right
    else
        ply->rightWC=false;


    if(box_collision(ply->box,rightWall->box))//player has hit the right wall
        ply->rightWC=true;//set to true so the player cannot move right
    else
        ply->rightWC=false;



     if(box_collision(ply->box,topWall->box))//player has hit the top wall
        ply->topWC=true;//set to true so the player cannot move up
    else
        ply->topWC=false;


    if(box_collision(ply2->box,leftWall->box))//player has hit the left wall
        ply2->leftWC=true;//set to true so the player cannot move left
        else
        ply2->leftWC=false;

    if(box_collision(ply2->box,leftWall->box))//player has hit the left wall
        ply2->leftWC=true;//set to true so the player cannot move left
    else
        ply2->leftWC=false;


    if(box_collision(ply2->box,rightWall->box))//player has hit the right wall
        ply2->rightWC=true;//set to true so the player cannot move right
    else
        ply2->rightWC=false;

    if(box_collision(projA->box,leftWall->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,rightWall->box)&& projA->myTime->getTicks() >= 200)
    {
       projA->myTime->reset();
        projA->health--;
        projAXdir*=-1;
    }

    if(box_collision(projA->box,topWall->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(projA->box,killBox->box)&& projA->myTime->getTicks() >= 200)
    {
         projA->myTime->reset();
        projA->health--;
        projAYdir*=-1;
    }

    if(box_collision(Ball->box,projA->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        ballDirX*=-1;
        ballDirY*=-1;
    }

    //-----------------PROJECTILE 2 WALL COLLISIONS---------------------------------------------//
      if(box_collision(projB->box,leftWall->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,rightWall->box)&& projB->myTime->getTicks() >= 200)
    {
       projB->myTime->reset();
        projB->health--;
        projBXdir*=-1;
    }

    if(box_collision(projB->box,topWall->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(projB->box,killBox->box)&& projB->myTime->getTicks() >= 200)
    {
         projB->myTime->reset();
        projB->health--;
        projBYdir*=-1;
    }

    if(box_collision(Ball->box,projB->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        ballDirX*=-1;
        ballDirY*=-1;
    }

    //---------------------------------------------------------------------------------------------------//
    //------------------------------- BALL -----------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    //----------------------PLAYER 1 --------------------------------------//
     if (box_collision(Ball->box, ply->box) && ply->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply->lastCase=='R')//lets player aim to his right
        {
            ballDirX = ply->xdir;
            ballDirY = ply->ydir;
        }

        if(ply->lastCase=='L')//lets player aim to his left
        {
            ballDirX = -ply->xdir;
            ballDirY = ply->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply->swinging=false;

    }

    //Set a bool if player is on tile
    ply->OnTile=playerOnTile(ply);

    //-----------------------PLAYER 2--------------------------------------//
     if (box_collision(Ball->box, ply2->box) && ply2->swinging == true )//&& pCol->getTicks() >= 350)
    {
        pCol->reset();
        if(ply2->lastCase=='R')//lets player aim to his right
        {
            ballDirX = ply2->xdir;
            ballDirY = ply2->ydir;
        }

        if(ply2->lastCase=='L')//lets player aim to his left
        {
            ballDirX = -ply2->xdir;
            ballDirY = ply2->ydir;
        }
        ballSpeed += (0.0010*200)/scale;
        ply2->swinging=false;

    }
    if(box_collision(ply2->box,Ball->box)&&ply2->isalive()&&Ball->myTime->getTicks()>200)
    {
           Ball->myTime->reset();
           ply2->health--;
    }
    //Set a bool if player is on tile
    ply2->OnTile=playerOnTile(ply2);


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- BALL VS TILE COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//




    //----------------------------------
    //holding the ball or moving the ball
    //---------------------------------

     CurYpos = CurYpos + ballDirY * ballSpeed;

      CurXpos = CurXpos + ballDirX * ballSpeed;

     if(box_collision(Ball->box, ply->box)&&ply->hold)//lets the player hold the ball
    {
        Ball->Xpos=ply->PXpos;
        Ball->Ypos=ply->PYpos;
        if(ply->lastCase=='R')
        {
             ballDirY=ply->ydir;
             ballDirX=ply->xdir;
        }
        if(ply->lastCase=='L')
        {
             ballDirY=ply->ydir;
             ballDirX=-ply->xdir;
        }
             CurYpos=ply->PYpos;
             CurXpos=ply->PXpos;
             Ball->prevHeld=true;
    }
    //MOVING THE BALL
    /*else if(!hit)
    {
        Ball->Xpos = CurXpos;
        Ball->Ypos = CurYpos;
    }*/
     if(Ball->prevHeld&&!ply->hold)
     {
        prevBallSpeed=ballSpeed;
        ballSpeed += (0.010*200)/scale;
        Ball->prevHeld=false;
     }

     //-------------------------------------------------------------------
     //-----------------------Projectile----------------------------------
     //-------------------------------------------------------------------
     //------------------------Projectile A----------------------------------//
    if(box_collision(projA->box,ply2->box)&&ply2->isalive()&&projA->myTime->getTicks()>200)//ball from player one hits player 2
    {
           projA->myTime->reset();
           projA->health=0;
           ply2->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projA->box,ply->box)&&ply->swinging==true)//player one can hit his own wall
       {
           //projA->health--;
            projAXdir=ply->xdir;
            projAYdir=ply->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projA->box,ply->box)&&ply->swinging==false)//player one can hit his own ball
         ply->verticalVelocity=6;


    if(ply->thrown)
    {
        ProjACurY += (projAYdir * 3)/scale;
        ProjACurX += (projAXdir * 3)/scale;

        projA->Xpos = ProjACurX;
        projA->Ypos = ProjACurY;
    }

    //-------------------------projectile B-----------------------------------//

      if(box_collision(projB->box,ply->box)&&ply->isalive()&&projB->myTime->getTicks()>200)//ball from player one hits player
    {
           projB->myTime->reset();
           projB->health=0;
           ply->health--;
           //cout<<"p2 collisions"<<endl;
           //player 2 is deleted or stunned
    }
    if(box_collision(projB->box,ply2->box)&&ply2->swinging==true)//player one can hit his own wall
       {
           //projB->health--;
            projBXdir=ply2->xdir;
            projBYdir=ply2->ydir;
           //player 2 is deleted or stunned
       }

    if(box_collision(projB->box,ply2->box)&&ply2->swinging==false)//player one can hit his own ball
         ply2->verticalVelocity=6;


    if(ply2->thrown)
    {
        ProjBCurY += (projBYdir * 3)/scale;
        ProjBCurX += (projBXdir * 3)/scale;

        projB->Xpos = ProjBCurX;
        projB->Ypos = ProjBCurY;
    }

}
