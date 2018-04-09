#ifndef MODEL_H
#define MODEL_H
#include<windows.h>
#include <string>
#include<GL/glut.h>
#include<GLTexture.h>
#include<timer.h>
<<<<<<< HEAD

=======
>>>>>>> f782b2eaa50c01dabdd579d09581c90b7b94edda
typedef struct{
 float x;
 float y;
 float z;
}vec1;

typedef struct
{
        float x;
        float y;
        float width;
        float height;
}Hbox;

class Model
{
    public:
        Model();
        Model(float, float, float,float,float,float,float, float, float,float,float, float);
        virtual ~Model();
        void drawModel(float x, float y, float z,float a,float b,float c,float d, float e, float f,float q,float w, float r);
        void drawModel(textureLoader *tex);
        void modelInit(char *,bool,textureLoader* );
        void UpdateHbox(float , float );
        bool isalive();

        Hbox box;
        Hbox pl_pltfrm_box;
        float health;
        std::string tag;
        timer* myTime;

        timer* myTime;

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
