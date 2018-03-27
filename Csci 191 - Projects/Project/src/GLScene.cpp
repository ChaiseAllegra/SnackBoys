#include "GLScene.h"
#include <GLLight.h>
#include <GLModel.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <windows.h>
#include <mmsystem.h>
#include <GLTexture.h>

using namespace std;

float ballSpeed = .005;

float bound = 3;
float directionX = 1;
float directionY = 1;
float CurXpos = 0, CurYpos=0; //current x position of the ball, current y position of the ball,
float r = 0.3f, t = 0.007; //size of the ball, speed of the ball
float xdir = bound, ydir = bound; //the direction the ball travels to in the x and y directions, set these to the maximum of the play area
bool RwHit = false, TwHit = false; //Right wall hit: if set to false the ball just hit the left wall if set true it just hit the right wall, TwHit the same but with top and bottom
float Bxvelocity, Byvelocity; //The x and y velocity of the ball

float q = bound - 0.1;

Model* modelTeapot = new Model();
Inputs* KbMs = new Inputs();
parallax* plx = new parallax();
player* ply = new player();
Model* wallA = new Model(); //left wall
Model* wallB = new Model(); //right wall
Model* wallC = new Model(); //top wall
Model* wallD = new Model(); //bottom wall
skyBox* sky = new skyBox;
Model* Ball = new Model(); //the ball
Model* BallHbawks = new Model();

//------------------PLANK MODELS----------------------//

Model* lPlank1 = new Model();
Model* lPlank2 = new Model();
Model* lPlank3 = new Model();
Model* lPlank4 = new Model();

//-----------------PLANK TEXTURES--------------------//

textureLoader* lPlank1_text1 = new textureLoader();
textureLoader* lPlank1_text2 = new textureLoader();
textureLoader* lPlank1_text3 = new textureLoader();
textureLoader* lPlank1_text4 = new textureLoader();
textureLoader* lPlank1_text5 = new textureLoader();

textureLoader* lPlank2_text1 = new textureLoader();
textureLoader* lPlank2_text2 = new textureLoader();
textureLoader* lPlank2_text3 = new textureLoader();
textureLoader* lPlank2_text4 = new textureLoader();
textureLoader* lPlank2_text5 = new textureLoader();

textureLoader* lPlank3_text1 = new textureLoader();
textureLoader* lPlank3_text2 = new textureLoader();
textureLoader* lPlank3_text3 = new textureLoader();
textureLoader* lPlank3_text4 = new textureLoader();
textureLoader* lPlank3_text5 = new textureLoader();

textureLoader* lPlank4_text1 = new textureLoader();
textureLoader* lPlank4_text2 = new textureLoader();
textureLoader* lPlank4_text3 = new textureLoader();
textureLoader* lPlank4_text4 = new textureLoader();
textureLoader* lPlank4_text5 = new textureLoader();





//--------------PLANK HIT COUNTERS------------------//

int l_plank1 = 0, l_plank2 = 0, l_plank3 = 0, l_plank4 = 0;
int r_plank1 = 0, r_plank2 = 0, r_plank3 = 0, r_plank4 = 0;




//-----------------OTHER TEXTURES-------------------//

textureLoader* tex0 = new textureLoader();
textureLoader* tex1 = new textureLoader();
textureLoader* tex2 = new textureLoader();
textureLoader* ballHBTex = new textureLoader();
textureLoader* ballHBTex2 = new textureLoader();
textureLoader* texa = new textureLoader();
textureLoader* texb = new textureLoader();
textureLoader* texc = new textureLoader();
textureLoader* texd = new textureLoader();

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
    plx->parallaxInit("images/box/band-BG.png");
    ply->playerInit();
    sky->loadTextures();
    wallA->modelInit("images/box/invisible_wall.png", true, tex1);
    wallB->modelInit("images/box/invisible_wall.png", true, tex2);
    wallC->modelInit("images/box/horizontal_hitbox.png", true, texc);
    wallD->modelInit("images/box/horizontal_hitbox.png", true, texb);

    //--------------------------------PLANK INITS------------------------------//
    lPlank1->modelInit("images/box/invisible_wall.png", true, lPlank1_text1);
    lPlank2->modelInit("images/box/invisible_wall.png", true, lPlank2_text1);
    lPlank3->modelInit("images/box/invisible_wall.png", true, lPlank3_text1);
    lPlank4->modelInit("images/box/invisible_wall.png", true, lPlank4_text1);




    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    //BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

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
    }
    if (b_collision(Ball->HBox, wallA->HBox))
    {
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //CurXpos = -3.1999;
        directionX = 1;
    }
    if (b_collision(Ball->HBox, wallC->HBox))
    {
        //CurYpos = 1.8199;
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        directionY = -1;
    }
    if (b_collision(Ball->HBox, wallD->HBox))
    {
        //CurYpos = -1.8799;
        //PlaySound(TEXT("sounds/wall_bounce.wav"), NULL, SND_FILENAME | SND_ASYNC);
        directionY = 1;
    }

    if (b_collision(Ball->HBox, ply->playerHBox))
    {
        if(Ball->Xpos < ply->playerHBox.x)
        {
            //ballSpeed = ballSpeed + .000005;
            directionX = -1;
            directionY =  1;
        }
        if(Ball->Xpos >= ply->playerHBox.x)
        {
            //ballSpeed = ballSpeed + .000005;

            directionX =  1;
            directionY =  1;
        }

    }

    //------------------------------- LEFT SIDE PLANK 1 COLLISION -----------------------------------------//
    if (b_collision(Ball->HBox, lPlank1->HBox))
    {
        directionY = 1;
        cout << " plank collision " << endl;

        if(l_plank1 == 0 || l_plank1 == 1 || l_plank1 == 2)
        {
            lPlank1->modelInit("images/box/plank_textures/left_1_1.png", true, lPlank1_text1);
            //lPlank1->drawModel(lPlank1_text2);
            l_plank1++;
        }
        if(l_plank1 == 3 || l_plank1 == 4 || l_plank1 == 5)
        {
            lPlank1->modelInit("images/box/plank_textures/left_1_2.png", true, lPlank1_text1);
            l_plank1++;
        }
        if(l_plank1 == 6 || l_plank1 == 7 || l_plank1 == 8)
        {
            lPlank1->modelInit("images/box/plank_textures/left_1_3.png", true, lPlank1_text1);
            l_plank1++;
        }
        if(l_plank1 == 9 || l_plank1 == 10 || l_plank1 == 11)
        {
            lPlank1->modelInit("images/box/plank_textures/left_1_4.png", true, lPlank1_text1);
        }    cout << l_plank1 << endl;
    }

    //------------------------------- LEFT SIDE PLANK 2 COLLISION -----------------------------------------//
    if (b_collision(Ball->HBox, lPlank2->HBox))
        {
            directionY = 1;
            cout << " plank collision " << endl;

            if(l_plank2 == 0 || l_plank2 == 1 || l_plank2 == 2)
            {
                lPlank2->modelInit("images/box/plank_textures/left_2_1.png", true, lPlank2_text1);
                //lPlank1->drawModel(lPlank1_text2);
                l_plank2++;
            }
            if(l_plank2 == 3 || l_plank2 == 4 || l_plank2 == 5)
            {
                lPlank2->modelInit("images/box/plank_textures/left_2_2.png", true, lPlank2_text1);
                l_plank2++;
            }
            if(l_plank2 == 6 || l_plank2 == 7 || l_plank2 == 8)
            {
                lPlank2->modelInit("images/box/plank_textures/left_2_3.png", true, lPlank2_text1);
                l_plank2++;
            }
            if(l_plank2 == 9 || l_plank2 == 10 || l_plank2 == 11)
            {
                lPlank2->modelInit("images/box/plank_textures/left_2_4.png", true, lPlank2_text1);
            }    cout << l_plank2 << endl;
        }
    //------------------------------- LEFT SIDE PLANK 3 COLLISION -----------------------------------------//
    if (b_collision(Ball->HBox, lPlank3->HBox))
        {
            directionY = 1;
            cout << " plank collision " << endl;

            if(l_plank3 == 0 || l_plank3 == 1 || l_plank3 == 2)
            {
                lPlank3->modelInit("images/box/plank_textures/left_3_1.png", true, lPlank3_text1);
                //lPlank1->drawModel(lPlank1_text2);
                l_plank3++;
            }
            if(l_plank3 == 3 || l_plank3 == 4 || l_plank3 == 5)
            {
                lPlank3->modelInit("images/box/plank_textures/left_3_2.png", true, lPlank3_text1);
                l_plank3++;
            }
            if(l_plank3 == 6 || l_plank3 == 7 || l_plank3 == 8)
            {
                lPlank3->modelInit("images/box/plank_textures/left_3_3.png", true, lPlank3_text1);
                l_plank3++;
            }
            if(l_plank3 == 9 || l_plank3 == 10 || l_plank3 == 11)
            {
                lPlank3->modelInit("images/box/plank_textures/left_3_4.png", true, lPlank3_text1);
            }    cout << lPlank3 << endl;
        }
    //------------------------------- LEFT SIDE PLANK 4 COLLISION -----------------------------------------//
    if (b_collision(Ball->HBox, lPlank4->HBox))
        {
            directionY = 1;
            cout << " plank collision " << endl;

            if(l_plank4 == 0 || l_plank4 == 1 || l_plank4 == 2)
            {
                lPlank4->modelInit("images/box/plank_textures/left_4_1.png", true, lPlank4_text1);
                //lPlank1->drawModel(lPlank1_text2);
                l_plank4++;
            }
            if(l_plank4 == 3 || l_plank4 == 4 || l_plank4 == 5)
            {
                lPlank4->modelInit("images/box/plank_textures/left_4_1.png", true, lPlank4_text1);
                l_plank4++;
            }
            if(l_plank4 == 6 || l_plank4 == 7 || l_plank4 == 8)
            {
                lPlank4->modelInit("images/box/plank_textures/left_4_3.png", true, lPlank4_text1);
                l_plank4++;
            }
            if(l_plank4 == 9 || l_plank4 == 10 || l_plank4 == 11)
            {
                lPlank4->modelInit("images/box/plank_textures/left_4_4.png", true, lPlank4_text1);
            }    cout << lPlank3 << endl;
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
        //glTranslated(0, -1.5, ply->Zoom);

        ply->actions(ply->actionTrigger, ply, modelTeapot);
        ply->playerHBox.x = ply->PXpos;
        ply->playerHBox.y = ply->PYpos;
        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value
        ply->drawplayer();

    glPopMatrix();

    //------------------------- PLANK CREATIONS --------------------------------//
        //--------------------- PLANK 1 --------------------------//
        glPushMatrix();
            lPlank1->Ypos = -2.09;
            lPlank1->Xpos = -3.155;
            lPlank1->verticies[0].x = -.85; //bottom left x -- Shrink it horizontally
            lPlank1->verticies[1].x = .55; //bottom right x
            lPlank1->verticies[2].x = .7; //top right x
            lPlank1->verticies[3].x = -.75; //top left x
            lPlank1->verticies[0].y = -.0; //bottom left y -- Stretch it vertically
            lPlank1->verticies[1].y = -.0; //bottom right y
            lPlank1->verticies[2].y = .49; //top right y
            lPlank1->verticies[3].y = .49; // top left y
            lPlank1->HBox.x = lPlank1->Xpos;
            lPlank1->HBox.y = lPlank1->Ypos;
            lPlank1->HBox.width = .356;
            lPlank1->HBox.height = 0.2;
            lPlank1->drawModel(lPlank1_text1);
        glPopMatrix();

        //--------------------- PLANK 2 --------------------------//
        glPushMatrix();
            lPlank2->Ypos = -2.09;
            lPlank2->Xpos = -2.355;
            lPlank2->verticies[0].x = -.8; //bottom left x -- Shrink it horizontally
            lPlank2->verticies[1].x = .8; //bottom right x
            lPlank2->verticies[2].x = .85; //top right x
            lPlank2->verticies[3].x = -.7; //top left x
            lPlank2->verticies[0].y = -.0; //bottom left y -- Stretch it vertically
            lPlank2->verticies[1].y = -.0; //bottom right y
            lPlank2->verticies[2].y = 0.75; //top right y
            lPlank2->verticies[3].y = 0.75; // top left y
            lPlank2->HBox.x = lPlank2->Xpos;
            lPlank2->HBox.y = lPlank2->Ypos;
            lPlank2->HBox.width = .445;
            lPlank2->HBox.height = 0.2;
            lPlank2->drawModel(lPlank2_text1);
        glPopMatrix();

        //--------------------- PLANK 3 --------------------------//
        glPushMatrix();
            lPlank3->Ypos = -2.09;
            lPlank3->Xpos = -1.555;
            lPlank3->verticies[0].x = -.7; //bottom left x -- Shrink it horizontally
            lPlank3->verticies[1].x = .47; //bottom right x
            lPlank3->verticies[2].x = .52; //top right x
            lPlank3->verticies[3].x = -0.6; //top left x
            lPlank3->verticies[0].y = -.0; //bottom left y -- Stretch it vertically
            lPlank3->verticies[1].y = -.0; //bottom right y
            lPlank3->verticies[2].y = 0.4; //top right y
            lPlank3->verticies[3].y = 0.4; // top left y
            lPlank3->HBox.x = lPlank3->Xpos;
            lPlank3->HBox.y = lPlank3->Ypos;
            lPlank3->HBox.width = .345;
            lPlank3->HBox.height = 0.2;
            lPlank3->drawModel(lPlank3_text1);
        glPopMatrix();

        //--------------------- PLANK 4 --------------------------//
        glPushMatrix();
            lPlank4->Ypos = -2.09;
            lPlank4->Xpos = -.8;
            lPlank4->verticies[0].x = -.55; //bottom left x -- Shrink it horizontally
            lPlank4->verticies[1].x = .55; //bottom right x
            lPlank4->verticies[2].x = .55; //top right x
            lPlank4->verticies[3].x = -.5; //top left x
            lPlank4->verticies[0].y = -.0; //bottom left y -- Stretch it vertically
            lPlank4->verticies[1].y = -.0; //bottom right y
            lPlank4->verticies[2].y = .71; //top right y
            lPlank4->verticies[3].y = .71; // top left y
            lPlank4->HBox.x = lPlank4->Xpos;
            lPlank4->HBox.y = lPlank4->Ypos;
            lPlank4->HBox.width = .4;
            lPlank4->HBox.height = 0.2;
            lPlank4->drawModel(lPlank4_text1);
        glPopMatrix();



    //--------------------------LEFT WALL CREATION-----------------------------//
    glPushMatrix();
        wallA->Xpos = -3.8;
        wallA->Ypos = 0;

        // --------- REMODEL --------------- //
        wallA->verticies[0].x = -0.2; //bottom left x -- Shrink it horizontally
        wallA->verticies[1].x = 0.2; //bottom right x
        wallA->verticies[2].x = 0.2; //top right x
        wallA->verticies[3].x = -0.2; //top left x
        wallA->verticies[0].y = -2; //bottom left y -- Stretch it vertically
        wallA->verticies[1].y = -2; //bottom right y
        wallA->verticies[2].y = 2; //top right y
        wallA->verticies[3].y = 2; // top left y

        //add the hitbox for the wall we created on the next four line
        wallA->HBox.x = wallA->Xpos;
        wallA->HBox.y = wallA->Ypos;

        wallA->HBox.width = .3;
        wallA->HBox.height = 88;
        wallA->tag = "L";
        wallA->drawModel(tex1); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();

    //--------------------------RIGHT WALL CREATION-----------------------------//
    glPushMatrix();
        //add the hitbox for the wall we created on the next four line
        wallB->Xpos = 3.8;
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

    //--------------------------BALL CREATION-----------------------------//
    glPushMatrix();
        //glTranslated(1,0,(Ball->Zoom));
        //glScalef(0.3,0.03,1);
        Ball->Ypos = 0;

        Ball->verticies[0].x = -0.1;
        Ball->verticies[1].x = 0.1;
        Ball->verticies[2].x = 0.1;
        Ball->verticies[3].x = -0.1;
        Ball->verticies[0].y = -0.1;
        Ball->verticies[1].y = -0.1;
        Ball->verticies[2].y = 0.1;
        Ball->verticies[3].y = 0.1;

        Ball->HBox.height = 0.3;
        Ball->HBox.width = 0.3;
        idle();
        Ball->UpdateHbox(Ball->Xpos, Ball->Ypos);
        Ball->drawModel(ballHBTex);
    glPopMatrix();

    //cout << "Ball y Pos @ " << Ball->Xpos << endl;
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
        KbMs->keyPressed(modelTeapot);
        KbMs->keyEnv(plx, 0.005);
        KbMs->keyPressed(ply, modelTeapot, wallA, wallB, wallC); //TEMPORARY!!!!!!!!11!!!

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
