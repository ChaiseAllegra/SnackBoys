#ifndef MODEL_H
#define MODEL_H
#include<windows.h>
#include<GL/glut.h>
#include<wall.h>
#include<ball.h>
#include<GLTexture.h>
typedef struct{
 float x;
 float y;
 float z;
}vec1;
class Model:public ball, public wall
{
    public:
        Model();
        Model(float, float, float,float,float,float,float, float, float,float,float, float);
        virtual ~Model();
        void drawModel(float x, float y, float z,float a,float b,float c,float d, float e, float f,float q,float w, float r);
        void drawModel(textureLoader *tex);
        void modelInit(char *,bool,textureLoader* );
        void UpdateHbox(float , float );
        box HBox = box();//(0,0,0,0);
        //circle ballHBox = circle(0,0,0);
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
