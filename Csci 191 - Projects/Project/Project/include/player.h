#ifndef PLAYER_H
#define PLAYER_H

#include<GLModel.h>
#include<gl/gl.h>
#include<GLtexture.h>
#include<box.h>
typedef struct
{
   float x;
   float y;
   float z;
}vec;

class player:box, Model
{
    public:
        player();
        virtual ~player();
        box playerHBox = box(0,0,1,1);//generates a hitbox for the player use player box to manipulate the players hit box values

        float scalesize[3]={1.0,1.0,1.0};
        vec verticies[4];

        int runspeed;
        int jumpspeed;
        int actionTrigger;

        void playerUpdateHbox();//updates the hit box x and y to players current x and y
        void drawplayer();
        void playerInit();
        void actions(int);
        WPARAM wParam;

    protected:

    private:
};

#endif // PLAYER_H
