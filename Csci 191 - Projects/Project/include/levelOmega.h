#ifndef levelOmega_H
#define levelOmega_H
#include <player.h>
#include<time.h>
#include <GLModel.h>

class levelOmega
{
    public:
        levelOmega();
        virtual ~levelOmega();
        void update(float);
        bool playerOnTile(player* );
        void tileChange(Model* , Model* ,textureLoader* );
        bool topOfTile(player*, Model*);
        bool box_collision(Hbox, Hbox);

        int frameCount=0;
        int rightScore=0;
        int leftScore=0;
        float oneSecondTimer;
        float scale;

        float ballSpeed;
        float ballDirX;
        float ballDirY;
        float CurYpos;
        float CurXpos;
        float prevBallSpeed;

        float projAXdir;
        float projAYdir;
        float ProjACurX;
        float ProjACurY;
        float projBXdir;
        float projBYdir;
        float ProjBCurX;
        float ProjBCurY;

        bool setBallSpeed;

        Model* Ball = new Model();
        Model * projA = new Model();
        Model * projB = new Model();
        Model* leftWall = new Model(); // left wall
        Model* rightWall = new Model(); // right wall
        Model* topWall = new Model(); // top wall
        Model* killBox = new Model();
        Model* divide = new Model();

        //left side tiles
        Model* tile1 = new Model();
        Model* tile2 = new Model();
        Model* tile3 = new Model();
        Model* tile4 = new Model();
        Model* tile5 = new Model();
        Model* tile6 = new Model();
        Model* tile7 = new Model();
        //middle tile
        Model* tile8 = new Model();
        //right side tiles
        Model* tile9 = new Model();
        Model* tile10 = new Model();
        Model* tile22 = new Model();
        Model* tile12 = new Model();
        Model* tile13 = new Model();
        Model* tile14 = new Model();
        Model* tile15 = new Model();


        player* ply = new player();
        player* ply2 = new player();

        timer* BPA = new timer;//projectile A and ball collision timer
        timer* pCol = new timer;//ball and player collision timer
        timer* D = new timer;//tile and ball collision timer

        textureLoader* tileTex=new textureLoader();
        textureLoader* tileTex2=new textureLoader();
        textureLoader* tileTex3=new textureLoader();
        textureLoader* tileTex4=new textureLoader();
        textureLoader* tileTex5=new textureLoader();
        textureLoader* tileTex6=new textureLoader();
        textureLoader* tileTex7=new textureLoader();
        textureLoader* tileTex8=new textureLoader();
        textureLoader* tileTex9=new textureLoader();
        textureLoader* tileTex10=new textureLoader();
        textureLoader* tileTex11=new textureLoader();
        textureLoader* tileTex12=new textureLoader();
        textureLoader* tileTex13=new textureLoader();
        textureLoader* tileTex14=new textureLoader();
        textureLoader* tileTex15=new textureLoader();

    protected:

    private:
};

#endif // levelOmega_H
