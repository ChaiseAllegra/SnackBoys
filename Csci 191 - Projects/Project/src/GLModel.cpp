#include "GLModel.h"
#include <textureLoader.h>


Model::Model()
{
    //ctor
        RotateX =0.0; // Rotations
        RotateY =0.0;
        RotateZ =0.0;

        Zoom = -4.0;  //translations
        Xpos = -0.5;
        Ypos = 0;

        verticies[0].x=-0.5;verticies[0].y=-0.5;verticies[0].z=-1.0;
        verticies[1].x=0.5;verticies[1].y=-0.5;verticies[1].z=-1.0;
        verticies[2].x=0.5;verticies[2].y=0.5;verticies[2].z=-1.0;
        verticies[3].x=-0.5;verticies[3].y=0.5;verticies[3].z=-1.0;

        health=1;
}

Model::Model(float x, float y, float z,float a,float b,float c,float d, float e, float f,float q,float w, float r)
{
        Xpos = -0.5;
        Ypos = -0;

        verticies[0].x=0.0;verticies[0].y=0.0;verticies[0].z=1.0;
        verticies[1].x=1.0;verticies[1].y=0.0;verticies[1].z=1.0;
        verticies[2].x=1.0;verticies[2].y=1.0;verticies[2].z=1.0;
        verticies[3].x=0.0;verticies[3].y=1.0;verticies[3].z=1.0;
}

Model::~Model()
{
    //dtor
}
void Model::modelInit(char *fileName, bool trans, textureLoader *tex)
{
   if(trans)
   {
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }

    tex->binder();
    tex->bindTexture(fileName);
}

void Model::drawModel(textureLoader *tex)
{
    glColor3f(0.8,0.5,0.0);
    tex->binder();
    glTranslated(Xpos,Ypos,Zoom);
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);
    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);
    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);
    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();
}
 bool Model::box_collision(Hbox rect1, Hbox rect2){
	if (rect1.y < (rect2.y + rect2.height) && rect1.y > (rect2.y - rect2.height) && rect1.x < (rect2.x + rect2.width) && rect1.x > (rect2.x - rect2.width))
        return true;
    else
        return false;
}
void Model::UpdateHbox(float CurXpos, float CurYpos)//updates the hitbox location to the players location
{
   this->box.x=CurXpos;
   this->box.y=CurYpos;

     return;
}
void Model::isalive()
{
    if(this->health<1)
    {
      this->box.width=0;
      this->box.height=0;
    }
    return;
}
