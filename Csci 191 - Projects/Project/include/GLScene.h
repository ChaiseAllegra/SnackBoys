#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
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
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT,WPARAM,LPARAM,bool[256]);


        WPARAM wParam;
        float screenHeight;
        float screenWidth;

    protected:

    private:
};

#endif // GLSCENE_H
