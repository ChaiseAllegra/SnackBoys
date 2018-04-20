#ifndef LEVELALPHA_H
#define LEVELALPHA_H
#include <player.h>
#include<time.h>
#include <GLModel.h>

class levelAlpha
{
    public:
        levelAlpha();
        virtual ~levelAlpha();
        void update(float);
        bool playerOnTile(player* );
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
        bool shot;

        Model* Ball = new Model();
        Model * projA = new Model();
        Model * projB = new Model();
        Model * modelTeapot = new Model();
        Model * modelTeapot2 = new Model();
        Model* leftWall = new Model(); // left wall
        Model* rightWall = new Model(); // right wall
        Model* topWall = new Model(); // top wall
        Model* killBox = new Model();
        Model* GoalL = new Model();
        Model* GoalR = new Model();
        Model* cross = new Model();
        //left side tiles
        Model* floor = new Model();

        Model* platTileBL = new Model();//bottom left
        Model* platTileBR = new Model();//bottom right
        Model* platTileTL = new Model();//top left
        Model* platTileTR = new Model();//top right
        Model* platTileM = new Model();//middle

        player* ply = new player();
        player* ply2 = new player();

        timer* BPA = new timer;//projectile A and ball collision timer
        timer* pCol = new timer;//ball and player collision timer
        timer* D = new timer;//tile and ball collision timer

        textureLoader* tileTex=new textureLoader();
        textureLoader* tex0 = new textureLoader();
        textureLoader* tex1 = new textureLoader();
        textureLoader* tex2 = new textureLoader();
        textureLoader* tex3 = new textureLoader();
        textureLoader* texD = new textureLoader();
        textureLoader* ballHBTex = new textureLoader();
        textureLoader* texGL = new textureLoader();
        textureLoader* texGR = new textureLoader();
         textureLoader* crosshair = new textureLoader();

    protected:

    private:
};

#endif // LEVELALPHA_H
