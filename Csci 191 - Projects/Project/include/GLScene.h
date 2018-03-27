#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>

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
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);



        WPARAM wParam;
        float screenHeight;
        float screenWidth;
    protected:

    private:
};

#endif // GLSCENE_H
