#ifndef MODEL_H
#define MODEL_H

#include<windows.h>
#include<GL/glut.h>
#include<wall.h>
#include<ball.h>
#include<textureLoader.h>
typedef struct{
 float x;
 float y;
 float z;
}vec1;

class Model:public wall, public ball
{

    public:
        Model();
        virtual ~Model();
        Model(float, float, float,float,float,float,float, float, float,float,float, float);
        void drawModel(textureLoader *);
        void modelInit(char *,bool, textureLoader *);
        void UpdateHbox(float,float);

        void drawModel(float x, float y, float z,float a,float b,float c,float d, float e, float f,float q,float w, float r);
        void modelInit(char *,bool);
        void ballUpdateHbox(float,float);

        box wallHBox = box(0,0,0,0);
        circle ballHBox = circle(0,0,0);

        double RotateX;
        double RotateY;
        double RotateZ;

        double Zoom;
        double Xpos;
        double Ypos;

        vec1 verticies[4];

    protected:

    private:
};

#endif // MODEL_H
