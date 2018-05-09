#ifndef PLAYER_H
#define PLAYER_H

#include<GLModel.h>
#include<gl/gl.h>
#include<GLtexture.h>
#include <timer.h>
#include <string>

using namespace std;

typedef struct
{
   float x;
   float y;
   float z;
}vec;

class player: public Model
{
    public:
        player();
        virtual ~player();

        string oneORtwo = "none";

        float scalesize[3]={1.0,1.0,1.0};
        vec verticies[4];

        float projAXdir;
        float projAYdir;
        float ProjACurX;
        float ProjACurY;
        bool pause;
        bool stunned;
        bool plyprojJump;

        Model * projA = new Model();

        int runspeed;
        int jumpspeed;
        int actionTrigger;
        int jump;
        float yex;
        bool hold;
        bool throwB;

        float verticalVelocity;
        float playerGrav;

        float aimX;
        float aimY;
        char lastKey;
        bool thrown;
        bool isDash;
        float prevx;

        char lastCase = 'R';

        float plyAccel;

        textureLoader runText[40];
        textureLoader runText_left[40];
        textureLoader swingText[40];
        textureLoader swingTextLeft[40];
        textureLoader stand[2];
        textureLoader jumpText[40];
        textureLoader jumpTextL[40];
        textureLoader dashL[40];
        textureLoader dash[40];


        void playerUpdateHbox();//updates the hit box x and y to players current x and y
        void drawplayer();
        void playerInit();
        void playerInit2();
        void actions();

        float ydir;
        float xdir;
        float x_direction;
        float startSpeed;

        double PZoom;
        double PXpos;
        double PYpos;

        float plyVel;

        bool jumpInitiated;
        bool startJump;
        bool endJump;
        bool onGround;
        float trueHeight;
        float dashVel;
        bool OnTile;

        bool swinging;
        timer* swingTimer = new timer();
        timer* swingDuration = new timer();
        timer *T = new timer();
        timer *T2 = new timer();
        timer* frameRate = new timer();
        timer* jumpTimer = new timer();
        timer* projJump;

        float delta;

        bool ballCollided;
        bool midCollision;
        bool leftWC;
        bool rightWC;
        bool topWC;

        int isPlayer;

        string playerDirection;

    protected:

    private:
};

#endif // PLAYER_H
