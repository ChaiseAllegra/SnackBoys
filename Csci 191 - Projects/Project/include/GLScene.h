#ifndef GLSCENE_H
#define GLSCENE_H
#include<time.h>
#include <GLInputs.h>
#include <windows.h>
#include <parallax.h>
#include <GLModel.h>
#include<gl/gl.h>
#include<iostream>
#include <player.h>


using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene(bool[256]);
        GLint drawGLScene2(bool[256]);
        GLvoid resizeGLScene(GLsizei, GLsizei);
         void update();
         void makeModel(Model* ,textureLoader* ,float ,float ,float ,float ,float , float , float , float , float, float, float, float);
        bool playerOnTile(player* );
         bool lol(player* );
        void tileChange(Model* , Model* ,textureLoader* );
        bool box_collision(Hbox, Hbox);
        void reset();
        int ballPosHit(Model* ,Model* );
        void updateHPBar();


        int windMsg(HWND,UINT,WPARAM,LPARAM,bool[256]);
        /*-----------------------------------------------------*/
        //int ballDirY;
        int hitCount;
        bool topOfTile(player* ,Model* );
         //left side tiles
        Model* tile1;
        Model* tile2 ;
        Model* tile3 ;
        Model* tile4 ;
        Model* tile5 ;
        Model* tile6 ;
        Model* tile7 ;
        //middle tile
        Model* tile8 ;
        //right side tiles
        Model* tile9 ;
        Model* tile10;
        Model* tile11 ;
        Model* tile12 ;
        Model* tile13 ;
        Model* tile14 ;
        Model* tile15 ;

        player* ply ;
        player* ply2 ;
           float ballDirX;
            float ballDirY;
                   void ballColl();
         timer* hitTimer;
        timer* hitTimer2;
        float speedInc;
        float speedDecr;
        textureLoader* ballTex;
        void wallColl();
        int ply2Score;
        Model* killBox;
        int plyScore;
        Model* leftWall; // left wall
        Model* rightWall; // right wall
        Model* topWall ; // top wall
        Model* divide;  //middle wall
        void projectileCol(player*,player*);
         float ballSpdBfrAcc;//ball speed before acceleration
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
          Model * playerModel;
            textureLoader* plyTex;
            Model * playerModel2;
              textureLoader* leftWallTex;
               textureLoader* rightWallTex;
                textureLoader* topWallTex;
                textureLoader* divWallTex;
                textureLoader* projTex;
                textureLoader* projTex2;
        Model* cross;
        textureLoader* crosshair;
         bool menu[6];
         Model* menuModel;
         Model* menuModel2;
         Model* menuModel3;
         Model* menuModel4;
        Model* playButton;
        Model *infoButton;
        Model *exitButton ;
        Model *infoPage;
        textureLoader *tex3 ;
        textureLoader *tex4;
        textureLoader *tex5;
        textureLoader *tex6;
        int plyScoreLast;
        int score;
        void setBallDir();
        int mainMenPos;
        Model* controlButton;
        textureLoader* controlTex;
        Model* controlButtonA;
        textureLoader* controlTexA;
         Model *infoButtonA;
         Model *exitButtonA;
        Model* playButtonA;
        Model* landing;
        textureLoader* landingTex;

        textureLoader* menuTex;
        textureLoader* menuTex2;
        textureLoader* menuTex3;
        textureLoader* menuTex4;

        textureLoader* infoTexA;
        textureLoader* exitTexA;
        textureLoader* playButtonTexA;
        Model playMenuModel;
        Model *winPlyModel;
        Model *winPly2Model;
        textureLoader* winPlyTex;
        textureLoader* winPly2Tex;

        textureLoader* p2HP;
        Model* p2HPModel;

        textureLoader* p1HP;
        Model* p1HPModel;
        parallax* mainParr;
        textureLoader* MMTex;
        //combine them all into one photo then load different versions of that phoito depending on where the menu pos is
        /*------------------------------------------------------*/
        WPARAM wParam;
        bool pauseMenu;
        int menuPos=3;
        float pauseChoice;
        float screenHeight;
        float screenWidth;
        float ground;
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
        bool firstpause=true;
        int tDirx=1;
         int tDiry=1;
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
        float level=1;

        timer* D;
        timer* PAT;//projectile A timer to stop multiple health decrements on a collision
        timer* BPA;//projectile A and ball collision timer
        timer* pCol;
        timer* ballCollTimer;
        timer* frameRate;

        Inputs* KbMs;

        parallax* plx;
        parallax* plx2;
        parallax* plx3;

        Model* playMod;
        Model* controlsMod;
        Model* resetMod;
        Model* exitMod;

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
        Model* pause_controls;

        textureLoader* texSky1;
        textureLoader* texSky2;

        textureLoader* playTex;
        textureLoader* controlsTex;
        textureLoader* resetTex;
        textureLoader* exitTex;
        textureLoader* pauseCTex;

        Model* threeMod;
        Model* twoMod;
        Model* oneMod;
        Model* zeroMod;

         textureLoader* threeTex;
          textureLoader* twoTex;
           textureLoader* oneTex;
            textureLoader* zeroTex;

    protected:

    private:
};

#endif // GLSCENE_H
/*timer* D = new timer();
    pCol = new timer();
    ballCollTimer = new timer();

     modelTeapot = new Model();
     modelTeapot2 = new Model();

     KbMs = new Inputs();

     plx = new parallax();
     ply = new player();
     ply2 = new player();
     wallA = new Model(); // left wall
    Model* wallB = new Model(); // right wall
    wallC = new Model(); // top wall
     killBox = new Model();
     divide = new Model();
     hud = new Model();

    //left side tiles
     tile1=new Model();
     tile2=new Model();
     tile3=new Model();
     tile4=new Model();
     tile5=new Model();
     tile6=new Model();
     tile7=new Model();

    //middle tile
     tile8=new Model();

    //right side tiles
     tile9=new Model();
     tile10=new Model();
     tile22=new Model();
     tile12=new Model();
     tile13=new Model();
     tile14=new Model();
      tile15=new Model();



     wallAHbawks = new Model(); // left wall
     wallBHbawks = new Model(); // right wall
     wallCHbawks = new Model(); // top wall
     sky = new skyBox;
     Ball = new Model(); // the ball
     BallHbawks = new Model();

     tex0 = new textureLoader();
     tex1 = new textureLoader();
     tex2 = new textureLoader();
     ballHBTex = new textureLoader();
     ballHBTex2 = new textureLoader();
     texc = new textureLoader();
     texH = new textureLoader();

     tileTex=new textureLoader();
     tileTex2=new textureLoader();
     tileTex3=new textureLoader();
     tileTex4=new textureLoader();
     tileTex5=new textureLoader();
     tileTex6=new textureLoader();
     tileTex7=new textureLoader();
     tileTex8=new textureLoader();
     tileTex9=new textureLoader();
     tileTex10=new textureLoader();
     tileTex11=new textureLoader();
     tileTex12=new textureLoader();
     tileTex13=new textureLoader();
     tileTex14=new textureLoader();
     tileTex15=new textureLoader();*/
