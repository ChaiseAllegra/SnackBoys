#ifndef PLAYER_H
#define PLAYER_H

#include<GLModel.h>
#include<gl/gl.h>
#include<GLtexture.h>

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


        float scalesize[3]={1.0,1.0,1.0};
        vec verticies[4];

        int runspeed;
        int jumpspeed;
        int actionTrigger;
        int jump;
        float yex;
        float verticalVelocity;
        float prevXPos;
        bool dash;
        char lastKey;

        void playerUpdateHbox();//updates the hit box x and y to players current x and y
        void drawplayer();
        void playerInit();
        void actions(int, player*, Model*);

        double PZoom;
        double PXpos;
        double PYpos;


    protected:

    private:
};

#endif // PLAYER_H
