#include <player.h>
#include <timer.h>
#include <GLTexture.h>
//#include<gameclasses.h>
timer *T = new timer();
textureLoader runText[40];
textureLoader stand[2];
player::player()
{
    //ctor
    verticies[0].x = 0.0;verticies[0].y = 0.0;verticies[0].z = -1.0;
    verticies[1].x = 1.0;verticies[1].y = 0.0;verticies[1].z = -1.0;
    verticies[2].x = 1.0;verticies[2].y = 1.0;verticies[2].z = -1.0;
    verticies[3].x = 0.0;verticies[3].y = 1.0;verticies[3].z = -1.0;
    runspeed  = 0;
    jumpspeed = 0;
    actionTrigger = 0;
}
player::~player()
{
    //dtor
}
void player::drawplayer()
{
  //  glColor3f(1.0,0.0,0.0);
   // glPushMatrix();
    glTranslated(0, -1.5, 0);
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
 //   glPopMatrix();
}
void player::playerInit()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    T->start();
    stand[0].bindTexture("images/player/play.png");
    runText[0].bindTexture("images/player/player0.png");
    runText[1].bindTexture("images/player/player0 - Copy.png");
    runText[2].bindTexture("images/player/player1.png");
    runText[3].bindTexture("images/player/player1 - Copy.png");
    runText[4].bindTexture("images/player/player2.png");
    runText[5].bindTexture("images/player/player2 - Copy.png");
    runText[6].bindTexture("images/player/player3.png");
    runText[7].bindTexture("images/player/player3 - Copy.png");
    runText[8].bindTexture("images/player/player4.png");
    runText[9].bindTexture("images/player/player4 - Copy.png");
    runText[10].bindTexture("images/player/player5.png");
    runText[11].bindTexture("images/player/player5 - Copy.png");
    runText[12].bindTexture("images/player/player6.png");
    runText[13].bindTexture("images/player/player6 - Copy.png");
    runText[14].bindTexture("images/player/player7.png");
    runText[15].bindTexture("images/player/player7 - Copy.png");
    runText[16].bindTexture("images/player/player8.png");
    runText[17].bindTexture("images/player/player8 - Copy.png");
    runText[18].bindTexture("images/player/player9.png");
    runText[19].bindTexture("images/player/player9 - Copy.png");
    runText[20].bindTexture("images/player/player10.png");
    runText[21].bindTexture("images/player/player10 - Copy.png");
    runText[22].bindTexture("images/player/player11.png");
    runText[23].bindTexture("images/player/player11 - Copy.png");
    runText[24].bindTexture("images/player/player12.png");
    runText[25].bindTexture("images/player/player12 - Copy.png");
    runText[26].bindTexture("images/player/player13.png");
    runText[27].bindTexture("images/player/player13 - Copy.png");
    runText[28].bindTexture("images/player/player14.png");
    runText[29].bindTexture("images/player/player14 - Copy.png");
    runText[30].bindTexture("images/player/player15.png");
    runText[31].bindTexture("images/player/player15 - Copy.png");
    runText[32].bindTexture("images/player/player16.png");
    runText[33].bindTexture("images/player/player16 - Copy.png");
    runText[34].bindTexture("images/player/player17.png");
    runText[35].bindTexture("images/player/player17 - Copy.png");
    runText[36].bindTexture("images/player/player18.png");
    runText[37].bindTexture("images/player/player18 - Copy.png");
    runText[38].bindTexture("images/player/player19.png");
    runText[39].bindTexture("images/player/player19 - Copy.png");
}
void player::actions(int action)
{
   switch(action){
   case 0:
       glPushMatrix();
           glTranslated(-0.8,-0.75,-1.0);
           stand[0].binder();
           //glutSolidTeapot(1.5);
           drawplayer();
       glPopMatrix();
       break;
   case 1:
       glPushMatrix();
           glTranslated(-0.8,-0.75,-1.0);
           if(T->getTicks()>30){
            runspeed++;
            runspeed = runspeed %10;
            T->reset();
           }
           runText[runspeed].binder();
           drawplayer();
       glPopMatrix();
       break;
   }
}
 void player::playerUpdateHbox()//updates the hitbox location to the players location
 {

    this->playerHBox.x=(this->verticies[0].x+this->verticies[1].x)/2;
    this->playerHBox.y=(this->verticies[1].y+this->verticies[2].y)/2;
    cout<<this->playerHBox.x<<", "<<this->playerHBox.y<<endl;

      return;
 }
