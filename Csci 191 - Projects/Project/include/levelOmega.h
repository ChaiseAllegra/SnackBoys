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

        timer* BPA = new timer;//projectile A and ball collision timer
        timer* pCol = new timer;//ball and player collision timer
        timer* D = new timer;//tile and ball collision timer

    protected:

    private:
};

#endif // levelOmega_H
