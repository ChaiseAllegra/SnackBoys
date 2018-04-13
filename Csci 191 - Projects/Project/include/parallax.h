#ifndef PARALLAX_H
#define PARALLAX_H

#include <iostream>
#include <string.h>
#include <gl/gl.h>
#include <windows.h>
#include <GLTexture.h>

using namespace std;

class parallax
{
    public:
        parallax();
        virtual ~parallax();
        void drawSquare(float,float,textureLoader*);
        void parallaxInit(char *, textureLoader*);
        void scroll(bool,string,float,float);

        float Xmax,Ymax,Xmin,Ymin;
    protected:

    private:
};

#endif // PARALLAX_H
