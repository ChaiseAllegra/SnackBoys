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
/*

#include "levelOmega.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
levelOmega::levelOmega()
{
    modelTeapot->modelInit("images/player/player0.png", true, tex0);
    modelTeapot2->modelInit("images/player/player0.png", true, tex0);
    ply->playerInit();
    ply2->playerInit();

    ply->playerInit();
    ply2->playerInit();

    leftWall->modelInit("images/box/girder.png", true, tex1);
    rightWall->modelInit("images/box/girder.png", true, tex2);
    topWall->modelInit("images/box/girder2.png", true, tex3);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    ply->projA->modelInit("images/box/ball.png", true, ballHBTex);
    ply2->projA->modelInit("images/box/ball.png", true, ballHBTex);

    cross->modelInit("images/box/crosshair.png", true, crosshair);

    ply->PXpos = -2;
    ply2->PXpos = 2;

    ply->isPlayer = 1;
    ply2->isPlayer = 2;

    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();

    ply->ProjACurY=ply->PYpos, ply->ProjACurX=ply->PXpos;
    ply2->ProjACurY=ply2->PYpos, ply2->ProjACurX=ply2->PXpos;
    ply->projA->Xpos=999;
    ply->projA->Ypos=999;
    ply->projA->box.x = ply->projA ->Xpos;
    ply->projA->box.y = ply->projA ->Ypos;
    ply2->projA->Xpos=999;
    ply2->projA->Ypos=999;
    ply2->projA->box.x = ply2->projA ->Xpos;
    ply2->projA->box.y = ply2->projA ->Ypos;
    ply2->health=5;
    ply->health=5;

    tile1->modelInit("images/box/nothing2.png", true, tileTex);
    tile2->modelInit("images/box/block.png", true, tileTex2);
    tile3->modelInit("images/box/block.png", true, tileTex3);
    tile4->modelInit("images/box/block.png", true, tileTex4);
    tile5->modelInit("images/box/block.png", true, tileTex5);
    tile6->modelInit("images/box/block.png", true, tileTex6);
    tile7->modelInit("images/box/block.png", true, tileTex7);
    tile8->modelInit("images/box/block.png", true, tileTex8);
    tile9->modelInit("images/box/block.png", true, tileTex9);
    tile10->modelInit("images/box/block.png", true, tileTex10);
    tile22->modelInit("images/box/block.png", true, tileTex11);
    tile12->modelInit("images/box/block.png", true, tileTex12);
    tile13->modelInit("images/box/block.png", true, tileTex13);
    tile14->modelInit("images/box/block.png", true, tileTex14);
    tile15->modelInit("images/box/nothing2.png", true, tileTex15);
    divide->modelInit("images/box/block.png", true, divTex);



    cross->modelInit("images/box/crosshair.png", true, crosshair);
}

levelOmega::~levelOmega()
{
    //dtor
}
void levelOmega::tileChange(Model* b, Model* t,textureLoader* TX)
{
    if(box_collision(b->box, t->box ) && D->getTicks() >= 200)
    {
                D->reset();
                ballDirY =  1;
                t->health-=1;
                t->isalive();
                ballSpeed=(0.3*8)/scale;//(0.125*8)/scale;

                if (t->health == 2)
                    t->modelInit("images/box/block2.png", true, TX);
                if (t->health == 1)
                    t->modelInit("images/box/block3.png", true, TX);
                    return;
    }

}
bool levelOmega::topOfTile(player* ply,Model* tileT){
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
bool levelOmega::playerOnTile(player* ply)
{
             if((topOfTile(ply,tile1)||topOfTile(ply,tile2)||topOfTile(ply,tile3)||topOfTile(ply,tile4)||
                    topOfTile(ply,tile5)||topOfTile(ply,tile6)||topOfTile(ply,tile7)||topOfTile(ply,tile8)||
                    topOfTile(ply,tile9)||topOfTile(ply,tile10)||topOfTile(ply,tile22)||topOfTile(ply,tile12)||
                    topOfTile(ply,tile13)||topOfTile(ply,tile14)||topOfTile(ply,tile15)))
               return true;
    else
        false;
}
 bool levelOmega::box_collision(Hbox rect1, Hbox rect2)
 {

 bool collisionX;
 bool collisionY;

collisionY = (((rect1.y-rect1.height) < (rect2.y + rect2.height) && (rect1.y+rect1.height) > (rect2.y - rect2.height))||((rect2.y-rect2.height) < (rect1.y + rect1.height) && (rect2.y+rect2.height) > (rect1.y - rect1.height)));
collisionX = (((rect1.x-rect1.width) < (rect2.x + rect2.width) && (rect1.x+rect1.width) > (rect2.x - rect2.width))||((rect2.x-rect2.width) < (rect1.x + rect1.width) && (rect2.x+rect2.width) > (rect1.x - rect1.width)));

    return collisionX && collisionY;
}
void levelOmega::ballColl()
{
    //----------------------PLAYER 1 --------------------------------------//
    if (box_collision(Ball->box, ply->box) && ply->swinging == true)
    {
        pCol->reset();
        if(ply->lastCase == 'R') // lets player aim to his right
        {
            ballDirX = ply->xdir;
            ballDirY = ply->ydir;
        }
        if(ply->lastCase == 'L') // lets player aim to his left
        {
            ballDirX = -ply->xdir;
            ballDirY = ply->ydir;
        }
        ballSpeed += 0.1 / scale;//0.2 / scale;
        ply->swinging = false;
    }

    //-----------------------PLAYER 2--------------------------------------//
    if (box_collision(Ball->box, ply2->box) && ply2->swinging == true)
    {
        pCol->reset();
        if(ply2->lastCase == 'R')//lets player aim to his right
        {
            ballDirX = ply2->xdir;
            ballDirY = ply2->ydir;
        }

        if(ply2->lastCase == 'L')//lets player aim to his left
        {
            ballDirX = -ply2->xdir;
            ballDirY = ply2->ydir;
        }
        ballSpeed += 0.1 / scale;
        ply2->swinging = false;
    }
    if(box_collision(ply2->box,Ball->box) && ply2->isalive() && Ball->myTime->getTicks() > 200)
    {
           Ball->myTime->reset();
           ply2->health--;
    }
}
void levelOmega::wallColl()
{
    if (box_collision(Ball->box, rightWall->box))
        ballDirX = -1;

    if (box_collision(Ball->box, leftWall->box))
        ballDirX = 1;

    if (box_collision(Ball->box, topWall->box))
        ballDirY = -1;

    if (box_collision(Ball->box, killBox->box))
    {
        CurYpos=2;
        ballDirY=-1;

        if(ballDirX==-1)
            CurXpos+=2;

        if(ballDirX==1)
            CurXpos-=2;
    }

    if(box_collision(ply->box,leftWall->box)) // player has hit the left wall
        ply->leftWC=true; // set to true so the player cannot move left
    else
        ply->leftWC=false;

    if(box_collision(ply->box,divide->box)) // player has hit the right wall
        ply->rightWC=true; // set to true so the player cannot move right
    else
        ply->rightWC=false;

    if(box_collision(ply->box,topWall->box))//player has hit the top wall
        ply->topWC=true;//set to true so the player cannot move up
    else
        ply->topWC=false;

    if(box_collision(ply2->box,divide->box)) // player has hit the left wall
        ply2->leftWC=true; // set to true so the player cannot move left
    else
        ply2->leftWC=false;


    if(box_collision(ply2->box,rightWall->box)) // player has hit the right wall
        ply2->rightWC=true; // set to true so the player cannot move right
    else
        ply2->rightWC=false;

    if(box_collision(ply2->box,topWall->box))//player has hit the top wall
        ply2->topWC=true;//set to true so the player cannot move up
    else
        ply2->topWC=false;


    if(box_collision(ply->projA->box,leftWall->box) && ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAXdir *= -1;
    }

    if(box_collision(ply->projA->box,rightWall->box) && ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAXdir *= -1;
    }

    if(box_collision(ply->projA->box,topWall->box)&& ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAYdir *= -1;
    }

    if(box_collision(ply->projA->box,killBox->box)&& ply->projA->myTime->getTicks() >= 200)
    {
        ply->projA->myTime->reset();
        ply->projA->health--;
        ply->projAYdir *= -1;
    }

    if(box_collision(Ball->box, ply->projA->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        ballDirX *= -1;
        ply->projA->health=0;
        //ballDirY *= -1;
    }

    //-----------------PROJECTILE 2 WALL COLLISIONS---------------------------------------------//
      if(box_collision(ply2->projA->box,leftWall->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAXdir*=-1;
    }

    if(box_collision(ply2->projA->box, rightWall->box) && ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAXdir*=-1;
    }

    if(box_collision(ply2->projA->box,topWall->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAYdir*=-1;
    }

    if(box_collision(ply2->projA->box,killBox->box)&& ply2->projA->myTime->getTicks() >= 200)
    {
        ply2->projA->myTime->reset();
        ply2->projA->health--;
        ply2->projAYdir*=-1;
    }

    if(box_collision(Ball->box, ply2->projA->box)&&BPA->getTicks() >= 200)
    {
        BPA->reset();
        ballDirX*=-1;
        ballDirY*=-1;
    }
}
void levelOmega::projectileCol(player* ply, player* ply2)
{
    if(box_collision(ply->projA->box, ply2->box) && ply2->isalive() && ply->projA->myTime->getTicks() > 200) // ball from player one hits player 2
    {
           ply->projA->myTime->reset();
           //if(ply2->lastCase=='R')
            //make him dash in the oppposit direction he is facing
           ply->projA->health = 0;
           ply2->health--;
    }
    if(box_collision(ply->projA->box, ply->box) && ply->swinging == true)//player one can hit his own wall
    {
        ply->projAXdir=ply->xdir;
        ply->projAYdir=ply->ydir;
        //player 2 is deleted or stunned
    }

    if(box_collision(ply->projA->box,ply->box) && ply->swinging==false)//player one can hit his own ball
         ply->verticalVelocity=6;

    if(ply->thrown)
    {
        ply->ProjACurY += (ply->projAYdir * 6)/scale;
        ply->ProjACurX += (ply->projAXdir * 6)/scale;

        ply->projA->Xpos = ply->ProjACurX;
        ply->projA->Ypos = ply->ProjACurY;
    }

}

void levelOmega:: update()
{
    double currentTime = glfwGetTime();

    frameCount++;
    if(currentTime-lastTime>=1.0)
    {
        if(frameCount>0)
            scale=(frameCount);
        if(!setBallSpeed)
        {
             ballSpeed=(0.3*8)/scale;//(0.125*8)/scale;
             setBallSpeed=true;
        }
        frameCount=0;
        lastTime+=1.0;

        if(scale>0)
        {
            ply->delta=scale;
            ply2->delta=scale;
        }
    }
    //cout<<scale<<endl;
    if (!glfwInit())
    exit(EXIT_FAILURE);

    wallColl();
    ballColl();
     //Set a bool if player is on tile
    ply->OnTile=playerOnTile(ply);
    //Set a bool if player is on tile
    ply2->OnTile=playerOnTile(ply2);


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- BALL VS TILE COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//


    tileChange(Ball, tile1,tileTex);
    tileChange(Ball, tile2,tileTex2);
    tileChange(Ball, tile3,tileTex3);
    tileChange(Ball, tile4,tileTex4);
    tileChange(Ball, tile5,tileTex5);
    tileChange(Ball, tile6,tileTex6);
    tileChange(Ball, tile7,tileTex7);
    tileChange(Ball, tile8,tileTex8);
    tileChange(Ball, tile9,tileTex9);
    tileChange(Ball, tile10,tileTex10);
    tileChange(Ball, tile22,tileTex11);
    tileChange(Ball, tile12,tileTex12);
    tileChange(Ball, tile13,tileTex13);
    tileChange(Ball, tile14,tileTex14);
    tileChange(Ball, tile15,tileTex15);

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
    else
    {
        Ball->Xpos = CurXpos;
        Ball->Ypos = CurYpos;
    }
     if(Ball->prevHeld&&!ply->hold)
     {
        prevBallSpeed=ballSpeed;
        ballSpeed += (0.010*200)/scale;
        Ball->prevHeld=false;
     }

     projectileCol(ply, ply2);
     projectileCol(ply2, ply);
    if(!ply->thrown)
    {
        if(ply->lastCase=='R')//lets player aim to his right
        {
            ply->projAXdir = ply->xdir;
            ply->projAYdir = ply->ydir;
        }
        if(ply->lastCase=='L')//lets player aim to his left
        {
            ply->projAXdir = -ply->xdir;
            ply->projAYdir = ply->ydir;
        }
        ply->projA->health = 3;
    }
     if(ply->projA->health<=0)
    {
        ply->thrown=false;
        ply->projA->box.width=0;
        ply->projA->box.height=0;
        ply->projA->box.x=999;
        ply->projA->box.y=999;

    }
    if(ply->thrown==false&&ply->lastCase=='R')
        ply->ProjACurY=ply->PYpos, ply->ProjACurX=ply->PXpos+0.5;
    if(ply->thrown==false&&ply->lastCase=='L')
        ply->ProjACurY=ply->PYpos, ply->ProjACurX=ply->PXpos-0.5;

     if(!ply2->thrown)
    {
        if(ply2->lastCase=='R')//lets player aim to his right
        {
            ply2->projAXdir = ply2->xdir;
            ply2->projAYdir = ply2->ydir;
        }
        if(ply2->lastCase=='L')//lets player aim to his left
        {
            ply2->projAXdir = -ply2->xdir;
            ply2->projAYdir = ply2->ydir;
        }
        ply2->projA->health = 3;
    }
     if(ply2->projA->health<=0)
    {
        ply2->thrown=false;
        ply2->projA->box.width=0;
        ply2->projA->box.height=0;
        ply2->projA->box.x=999;
        ply2->projA->box.y=999;

    }
    if(ply2->thrown==false&&ply2->lastCase=='R')
        ply2->ProjACurY=ply2->PYpos, ply2->ProjACurX=ply2->PXpos+0.5;
    if(ply2->thrown==false&&ply2->lastCase=='L')
        ply2->ProjACurY=ply2->PYpos, ply2->ProjACurX=ply2->PXpos-0.5;
}

*/
