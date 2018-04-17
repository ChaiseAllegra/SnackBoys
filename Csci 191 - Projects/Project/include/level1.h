#ifndef LEVEL1_H
#define LEVEL1_H
#include<time.h>
#include <GLInputs.h>
#include <windows.h>
#include <parallax.h>
#include <GLModel.h>
#include<gl/gl.h>
#include<iostream>
#include <player.h>

class level1
{
    public:
        level1();
        virtual ~level1();
        GLint initGL();
        GLint drawGLScene(bool[256]);
        GLvoid resizeGLScene(GLsizei, GLsizei);
         void update();
         void makeModel(Model* ,textureLoader* ,float ,float ,float ,float ,float , float , float , float , float, float, float, float);
        bool playerOnTile(player* );
         bool lol(player* );
        void tileChange(Model* , Model* ,textureLoader* );
        bool box_collision(Hbox, Hbox);
        bool topOfTile(player*,Model*);

        int windMsg(HWND,UINT,WPARAM,LPARAM,bool[256]);


        WPARAM wParam;
        float screenHeight;
        float screenWidth;
        float ground;
        bool levelOne;
        bool levelTwo;
        float TBscore=0;
        float TRscore=0;
        float prevBallSpeed;
        timer* goalscore=new timer();

        float xx, yy;
        int dirXX,dirYY;
        float max_xx_yy;
        float directionX;
        float directionY;
        float CurXpos, CurYpos; // Current x position of the ball, current y position of the ball,
        float ballSpeed;
        float yDirA;
        float xDirA;
        float ProjACurY;
        float ProjACurX;
         float ProjBCurY;
        float ProjBCurX;
        float projAXdir;
        float projAYdir;
         float projBXdir;
        float projBYdir;
        bool projAdrawn;
        float dashVel;
        bool shot;
        float dashChange=0.00001;

        float curFrame = 0;
        float prevFrame = 0;
        float dashDec=1.5;
        double currentTime;
        double timeFromStart;
        double lastTime;
        double deltaTime;
        int frameCount=0;
        float scale=1;
        bool setBallSpeed;
        double startTime;

        timer* D;
        timer* PAT;//projectile A timer to stop multiple health decrements on a collision
        timer* BPA;//projectile A and ball collision timer
        timer* pCol;
        timer* ballCollTimer;
        timer* frameRate;

        Model * projA;
        Model * projB;
        Model* modelTeapot;
        Model* modelTeapot2;

        Inputs* KbMs;

        parallax* plx;

        parallax* plx2;


        player* ply;
        player* ply2;
        Model* wallA; // left wall
        Model* wallB; // right wall
        Model* wallC; // top wall
        Model* killBox;
        Model* divide;
        Model* hud;
        Model* GoalL;
        Model* GoalR;

        //left side tiles
        Model* tile1;
        Model* tile2;
        Model* tile3;
        Model* tile4;
        Model* tile5;
        Model* tile6;
        Model* tile7;

        //middle tile
        Model* tile8;

        //right side tiles
        Model* tile9;
        Model* tile10;
        Model* tile22;
        Model* tile12;
        Model* tile13;
        Model* tile14;
        Model* tile15;

        Model* cross;

        Model* wallAHbawks; // left wall
        Model* wallBHbawks; // right wall
        Model* wallCHbawks; // top wall
        skyBox* sky;
        Model* Ball; // the ball
        Model* BallHbawks;

        Model* platTileBL;
        Model* platTileBR;
        Model* platTileTL;
        Model* platTileTR;
        Model* platTileM;

        textureLoader* tex0;
        textureLoader* texGL;
        textureLoader* texGR;
        textureLoader* tex1;
        textureLoader* tex2;
        textureLoader* tex3;
        textureLoader* texD;
        textureLoader* ballHBTex;
        textureLoader* ballHBTex2;
        textureLoader* texc;
        textureLoader* texH;

        textureLoader* texSky1;
        textureLoader* texSky2;

        textureLoader* tileTex;
        textureLoader* tileTex2;
        textureLoader* tileTex3;
        textureLoader* tileTex4;
        textureLoader* tileTex5;
        textureLoader* tileTex6;
        textureLoader* tileTex7;
        textureLoader* tileTex8;
        textureLoader* tileTex9;
        textureLoader* tileTex10;
        textureLoader* tileTex11;
        textureLoader* tileTex12;
        textureLoader* tileTex13;
        textureLoader* tileTex14;
        textureLoader* tileTex15;

        textureLoader* crosshair;

    protected:

    private:
};

#endif // LEVEL1_H
