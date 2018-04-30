#ifndef INPUTS_H
#define INPUTS_H
#include <windows.h>
#include <iostream>
#include <GLModel.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <timer.h>
#include <sounds.h>
class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();
        void keyPressed(Model *);
        void keyPressed(player *);
        void keyPressed(player *, player *, Model *, Model *, Model *, Model *, Model *, bool[256]);
        void keyUp(player *, player *, bool[256]);
        void keyUP();
        void idle(bool[256],player*,player*);
        void keyEnv(parallax *, float); // movements of my background
        void mouseEventDown(Model *,double ,double);
        void mouseEventUp();
        void mouseWheel(Model *,double);
        void mouseMove(Model *,double ,double );
        double prev_Mouse_X;
        double prev_Mouse_Y;
        bool Mouse_Translate;
        bool Mouse_Roatate;
        timer* dashTimer;
        timer* dashTimer2;
        WPARAM wParam;
        void keySound(bool[256], sounds *);
    protected:
    private:
};
#endif // INPUTS_H


