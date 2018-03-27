#include "skyBox.h"

 textureLoader tLoad[6];

skyBox::skyBox()
{
    //ctor

    RotateX =0;
    RotateY =0;
    RotateZ =0;

    translateX =0;
    translateY =0;
    translateZ =0;
}

skyBox::~skyBox()
{
    //dtor
}
void skyBox::loadTextures()
{

   glEnable(GL_TEXTURE_2D);
 //  glGenTextures(6,tex);
   //tLoad[1].bindTexture("images/Box/street.jpg");
   tLoad[0].bindTexture("images/Box/front.jpg");
   tLoad[5].bindTexture("images/Box/back.jpg");
   tLoad[2].bindTexture("images/Box/top.jpg");
   tLoad[3].bindTexture("images/Box/bottom.jpg");
   tLoad[4].bindTexture("images/Box/left.jpg");
   tLoad[1].bindTexture("images/Box/right.jpg");

}

void skyBox::drawBox()
{

   // glBindTexture(GL_TEXTURE_2D,tex[0]);
    //Front Face
    tLoad[0].binder();
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0);glVertex3f(-1.0,1.0,1.0);
    glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(1.0,1.0);glVertex3f(1.0, -1.0,1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(-1.0,-1.0,1.0);

    glEnd();

    //Back wall
    tLoad[1].binder();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0,1.0,-1.0);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0,-1.0,-1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(1.0, -1.0,-1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,-1.0);
    glEnd();

    //Top Face
    tLoad[2].binder();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0);glVertex3f(11.0,1.0,-1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0, 1.0,1.0);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0,1.0,-1.0);
    glEnd();
    //Bottom
    tLoad[3].binder();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0,-1.0,1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(1.0,-1.0,1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(1.0, -1.0,-1.0);
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0,-1.0,-1.0);
    glEnd();

    //Left Face
     tLoad[4].binder();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);glVertex3f(-1.0,1.0,-1.0);
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0,1.0,1.0);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0, -1.0,1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(-1.0,-1.0,-1.0);
    glEnd();

    //Right Face
    tLoad[5].binder();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.0,-1.0);
    glTexCoord2f(1.0,1.0);glVertex3f(1.0,-1.0,-1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(1.0, -1.0,1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,1.0);
    glEnd();
}
