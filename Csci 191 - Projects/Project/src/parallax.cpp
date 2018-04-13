#include "parallax.h"
#include <textureLoader.h>

parallax::parallax()
{
    //ctor
    Xmax= 1.0f;
    Ymax= 0.0f;
    Xmin= 0.0f;
    Ymin= 1.0f;
}

parallax::~parallax()
{
    //dtor
}

void parallax::drawSquare(float width, float height, textureLoader* bTex)
{
    glColor3f(1.0,1.0,1.0);
    bTex->binder();
    glBegin(GL_POLYGON);
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(-width/height,-1,-8.0f);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(width/height,-1,-8.0f);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(width/height,1,-8.0f);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(-width/height,1,-8.0f);
     glEnd();
}

void parallax::parallaxInit(char *FileName, textureLoader* bTex)
{
    bTex->binder();
    bTex->bindTexture(FileName);
}

void parallax::scroll(bool Auto, string dir, float speed,float scale)
{
    if(Auto){

        if(dir == "up")
        {
           Ymin -=(speed*200)/scale;
           Ymax -=(speed*200)/scale;
        }
        if(dir == "down")
        {
           Ymin +=(speed*200)/scale;
           Ymax +=(speed*200)/scale;
        }
        if(dir == "left")
        {

           Xmin -=(speed*0.05)/scale;
           Xmax -=(speed*0.05)/scale;
        }
        if(dir == "right")
        {
           Xmin +=(speed*200)/scale;
           Xmax +=(speed*200)/scale;
        }
    }
}
