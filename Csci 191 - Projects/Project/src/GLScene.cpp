#include "GLScene.h"
#include <GLLight.h>
#include <GLModel.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

float bound = 3;
float directionX = 1;
float directionY = 1;
float CurXpos, CurYpos; // Current x position of the ball, current y position of the ball,
float r = 0.3f, t = 0.007; // Size of the ball, speed of the ball
float xdir = bound, ydir = bound; // The direction the ball travels to in the x and y directions, set these to the maximum of the play area
bool RwHit = false, TwHit = false; // Right wall hit: if set to false the ball just hit the left wall if set true it just hit the right wall, TwHit the same but with top and bottom
float yex;

float ballSpeed = .02;

Model* modelTeapot = new Model();
Model* modelTeapot2 = new Model();

Inputs* KbMs = new Inputs();

parallax* plx = new parallax();
player* ply = new player();
player* ply2 = new player();
Model* wallA = new Model(); // left wall
Model* wallB = new Model(); // right wall
Model* wallC = new Model(); // top wall
Model* wallD = new Model(); // right wall// bottom wall
Model* divide = new Model();
Model* hud = new Model();

Model* tile1=new Model();
Model* tile2=new Model();
Model* tile3=new Model();
Model* tile4=new Model();
Model* tile5=new Model();
Model* tile6=new Model();
Model* tile7=new Model();
Model* tile8=new Model();



Model* wallAHbawks = new Model(); // left wall
Model* wallBHbawks = new Model(); // right wall
Model* wallCHbawks = new Model(); // top wall
Model* wallDHbawks = new Model(); // right wall// bottom wall
skyBox* sky = new skyBox;
Model* Ball = new Model(); // the ball
Model* BallHbawks = new Model();

textureLoader* tex0 = new textureLoader();
textureLoader* tex1 = new textureLoader();
textureLoader* tex2 = new textureLoader();
textureLoader* ballHBTex = new textureLoader();
textureLoader* ballHBTex2 = new textureLoader();
textureLoader* texa = new textureLoader();
textureLoader* texb = new textureLoader();
textureLoader* texc = new textureLoader();
textureLoader* texd = new textureLoader();
textureLoader* texD = new textureLoader();
textureLoader* texH = new textureLoader();

textureLoader* tileTex=new textureLoader();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
    modelTeapot->modelInit("images/player/player0.png", true, tex0);
    modelTeapot2->modelInit("images/player/player0.png", true, tex0);
   // plx->parallaxInit("images/box/band-BG2.png");
    ply->playerInit();
    ply2->playerInit();
    sky->loadTextures();
    //Ball->Ypos=-1;
    wallA->modelInit("images/box/vertical_hitbox.png", true, tex1);
    wallB->modelInit("images/box/vertical_hitbox.png", true, tex2);
    wallC->modelInit("images/box/nothing.png", true, texc);
    wallD->modelInit("images/box/nothing.png", true, texb);
    divide->modelInit("images/box/nothing.png", true, tex2);
    hud->modelInit("images/box/hud.png", true, texH);
    //wallAHbawks->modelInit("images/box/vertical_hitbox.png",true,texa);
    //wallBHbawks->modelInit("images/box/vertical_hitbox.png",true,texb);
    //wallCHbawks->modelInit("images/box/horizontal_hitbox.png",true,texc);
    //wallDHbawks->modelInit("images/box/horizontal_hitbox.png",true,texd);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

    tile1->modelInit("images/box/ball.png", true, tileTex);
     tile2->modelInit("images/box/ball.png", true, tileTex);
      tile3->modelInit("images/box/ball.png", true, tileTex);
       tile4->modelInit("images/box/ball.png", true, tileTex);
       tile5->modelInit("images/box/ball.png", true, tileTex);
        tile6->modelInit("images/box/ball.png", true, tileTex);
         tile7->modelInit("images/box/ball.png", true, tileTex);
          tile8->modelInit("images/box/ball.png", true, tileTex);

    return true;
}

bool b_collision(box rect1, box rect2)
{

    if (rect1.y < (rect2.y + rect2.height) && rect1.y > (rect2.y - rect2.height) && rect1.x < (rect2.x + rect2.width) && rect1.x > (rect2.x - rect2.width))
        return true;
    else
        return false;
}

static void idle()
{
    CurXpos = CurXpos + (directionX * ballSpeed);
    CurYpos = CurYpos + (directionY * ballSpeed);

    if (b_collision(Ball->HBox, wallB->HBox))
    {
        //CurXpos = 3.1999;
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        directionX = -1;
        //cout << " Right Collision " << endl;
    }
    if (b_collision(Ball->HBox, wallA->HBox))
    {
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //CurXpos = -3.1999;
        directionX = 1;
        //cout << " Left Collision " << endl;
    }
    if (b_collision(Ball->HBox, wallC->HBox))
    {
        //CurYpos = 1.8199;
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        directionY = -1;
        //cout << " Top Collision " << endl;
        hud->modelInit("images/box/hud1.png", true, texH);
    }
    if (b_collision(Ball->HBox, wallD->HBox))
    {
        //CurYpos = -1.8799;
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        directionY = 1;
        //cout << " Bottom Collision " << endl;
        hud->modelInit("images/box/hud2.png", true, texH);
    }

    if (b_collision(Ball->HBox, ply->playerHBox))
    {
        if(Ball->Xpos < ply->playerHBox.x)
        {
            ballSpeed = ballSpeed + 0.002;
            directionX =  -1;
            directionY =  1;
        }
        if(Ball->Xpos >= ply->playerHBox.x)
        {
            ballSpeed = ballSpeed + 0.002;

            directionX =  1;
            directionY =  1;
        }
        Ball->modelInit("images/box/ball2P.png", true, ballHBTex);
        hud->modelInit("images/box/hud3.png", true, texH);
    }
    Ball->Xpos = CurXpos;
    Ball->Ypos = CurYpos;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
    // Reset The Current Modelview Matrix
    glPushMatrix();
        glTranslated(0, 0, 1);
        glDisable(GL_LIGHTING);
        glScaled(10, 10, 10);
        sky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    //--------------------------PARALLAX CREATION-----------------------------//
    glPushMatrix();
        glScaled(3.33, 3.33, 1.0);
        plx->drawSquare(screenWidth, screenHeight);
    glPopMatrix();
    //plx->scroll(true,"up",0.005);

    //--------------------------PLAYER CREATION-----------------------------//
    glPushMatrix();
        ply->actions(ply->actionTrigger, ply, modelTeapot);
        ply->playerHBox.x = ply->PXpos;
        ply->playerHBox.y = ply->PYpos;
        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value
        ply->drawplayer();
    glPopMatrix();

    if(ply->jump > 0)
   {
       yex = 0.60*sin(ply->verticalVelocity);
       ply->verticalVelocity -= 0.0048;
       ply->PYpos += yex;
        if(ply->PYpos <= -1.4)
        {

            yex = 0;
            ply->PYpos = -1.4;
            ply->jump = 0;
        }
  }

    glPushMatrix();
        ply2->actions(ply2->actionTrigger, ply2, modelTeapot2);
        ply2->playerHBox.x = ply2->PXpos;
        ply2->playerHBox.y = ply2->PYpos;
        //ply2->Xpos = 1.0;
        ply2->PYpos = 1;
        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value
        ply2->drawplayer();
    glPopMatrix();

    glPushMatrix();
        tile1->Xpos=0;
        tile1->Ypos=0;
        tile1->HBox.x = tile1->Xpos; //wallA->Xpos;
        tile1->HBox.y = tile1->Ypos;
        tile1->drawModel();
    glPopMatrix();

    //--------------------------LEFT WALL CREATION-----------------------------//
    glPushMatrix();
        //glTranslated(wallA->Xpos, wallA->Ypos, (wallA->Zoom));
        wallA->Xpos = -3.9;
        wallA->Ypos = 0;

        // --------- REMODEL --------------- //
        wallA->verticies[0].x = -0.2; //bottom left x
        wallA->verticies[1].x = 0.2; //bottom right x
        wallA->verticies[2].x = 0.2; //top right x
        wallA->verticies[3].x = -0.2; //top left x
        wallA->verticies[0].y = -2; //bottom left y
        wallA->verticies[1].y = -2; //bottom right y
        wallA->verticies[2].y = 2; //top right y
        wallA->verticies[3].y = 2; // top left y

        //add the hitbox for the wall we created on the next four line
        wallA->HBox.x = wallA->Xpos; //wallA->Xpos;
        wallA->HBox.y = wallA->Ypos;

        wallA->HBox.width = .3;
        wallA->HBox.height = 88;
        wallA->tag = "L";
        wallA->drawModel(tex1); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------RIGHT WALL CREATION-----------------------------//
    glPushMatrix();
        //add the hitbox for the wall we created on the next four line
        wallB->Xpos = 3.9;
        wallB->Ypos = 0;

        // --------- REMODEL --------------- //
        wallB->verticies[0].x = -0.2; //bottom left x
        wallB->verticies[1].x = 0.2; //bottom right x
        wallB->verticies[2].x = 0.2; //top right x
        wallB->verticies[3].x = -0.2; //top left x
        wallB->verticies[0].y = -2; //bottom left y
        wallB->verticies[1].y = -2; //bottom right y
        wallB->verticies[2].y = 2; //top right y
        wallB->verticies[3].y = 2; // top left y

        wallB->HBox.x = wallB->Xpos;
        wallB->HBox.y = wallB->Ypos;
        wallB->HBox.width = .3;
        wallB->HBox.height = 88;
        wallB->tag = "R";
        wallB->drawModel(tex2); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------TOP WALL CREATION-----------------------------//
    glPushMatrix();
        wallC->Xpos = 0;
        wallC->Ypos = 2.02;
        //add the hitbox for the wall we created on the next four line
        wallC->HBox.x = wallC->Xpos;
        wallC->HBox.y = wallC->Ypos;
        wallC->HBox.width = 66;
        wallC->HBox.height = .2;
        wallC->tag = "T";
        wallC->drawModel(texc); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------BOTTOM WALL CREATION-----------------------------//
    glPushMatrix();
        wallD->Xpos = 0;
        wallD->Ypos = -2.09;
        //add the hitbox for the wall we created on the next four line
        wallD->HBox.x = wallD->Xpos;
        wallD->HBox.y = wallD->Ypos;
        wallD->HBox.width = 88;
        wallD->HBox.height = 0.2;
        wallD->tag = "B";
        wallD->drawModel(texb); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------Dividing WALL CREATION-----------------------------//
    glPushMatrix();
        //add the hitbox for the wall we created on the next four line
        divide->Xpos = 0;
        divide->Ypos = 0;

        // --------- REMODEL --------------- //
        divide->verticies[0].x = -0.2; //bottom left x
        divide->verticies[1].x = 0.2; //bottom right x
        divide->verticies[2].x = 0.2; //top right x
        divide->verticies[3].x = -0.2; //top left x
        divide->verticies[0].y = -2; //bottom left y
        divide->verticies[1].y = -2; //bottom right y
        divide->verticies[2].y = 2; //top right y
        divide->verticies[3].y = 2; // top left y

        divide->HBox.x = divide->Xpos;
        divide->HBox.y = divide->Ypos;
        divide->HBox.width = .3;
        divide->HBox.height = 88;
        divide->tag = "R";
        divide->drawModel(tex2); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------BALL CREATION-----------------------------//
    glPushMatrix();
        //glTranslated(1,0,(Ball->Zoom));
        //glScalef(0.3,0.03,1);
        Ball->Ypos = 0;
        Ball->Ypos = -0.5;

        Ball->verticies[0].x = -0.15;
        Ball->verticies[1].x = 0.15;
        Ball->verticies[2].x = 0.15;
        Ball->verticies[3].x = -0.15;
        Ball->verticies[0].y = -0.15;
        Ball->verticies[1].y = -0.15;
        Ball->verticies[2].y = 0.15;
        Ball->verticies[3].y = 0.15;

        Ball->HBox.height = 0.3;
        Ball->HBox.width = 0.3;
        idle();
        Ball->UpdateHbox(Ball->Xpos, Ball->Ypos);
        Ball->drawModel(ballHBTex);
    glPopMatrix();

    glPushMatrix();
        hud->verticies[0].x = -1; //bottom left x
        hud->verticies[1].x = 1; //bottom right x
        hud->verticies[2].x = 1; //top right x
        hud->verticies[3].x = -1; //top left x
        hud->verticies[0].y = -1; //bottom left y
        hud->verticies[1].y = -1; //bottom right y
        hud->verticies[2].y = 1; //top right y
        hud->verticies[3].y = 1; // top left y
        hud->Xpos = -2.69;
        hud->Ypos = 1.15;
        //hud->Zoom = 0;
        hud->drawModel(texH); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();
}
GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) // Check For Windows Messages
    {
    case WM_KEYDOWN:
        KbMs->wParam = wParam;
        //KbMs->keyPressed(modelTeapot);
        KbMs->keyEnv(plx, 0.005);
        KbMs->keyPressed(ply, modelTeapot, wallA, wallB, wallC);


        break;
    case WM_KEYUP: // Has A Key Been Released?
    {
        KbMs->wParam = wParam;
        KbMs->keyUP();
        KbMs->keyUp(ply);
        break; // Jump Back
    }
    case WM_LBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_RBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_MBUTTONDOWN: {
        KbMs->wParam = wParam;
        KbMs->mouseEventDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP: {
        KbMs->mouseEventUp();
        break; // Jump Back
    }
    case WM_MOUSEMOVE: {
        KbMs->mouseMove(modelTeapot, LOWORD(lParam), HIWORD(lParam));
        break; // Jump Back
    }
    case WM_MOUSEWHEEL: {
        KbMs->mouseWheel(modelTeapot, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break; // Jump Back
    }
    }
}
