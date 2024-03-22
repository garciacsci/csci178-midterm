#include "GLEnms.h"

GLEnms::GLEnms()
{
    //ctor

    pos.x =0;    // Default position settings
    pos.y =-0.5;
    pos.z =-2.0;

    eScale.x =0.12; // default scaling
    eScale.y =0.12;

    eRotate.x =0;  // default rotations
    eRotate.y =0;
    eRotate.z =0;

    framesX =7;   // number of columns in the sprite sheet
    framesY =1;   // number of rows in the spritesheet

    xMax =1.0/framesX;  // default image
    xMin=0;
    yMax=1.0/framesY;
    yMin=0.01;

    speed =0.03;  // moving speed
    action=STAND;     // set actions

    alive = true; // initialize as alive

    myTime->startTime = clock();
}

GLEnms::~GLEnms()
{
    //dtor

}

void GLEnms::drawEnemy()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(eRotate.x,1,0,0);
    glRotatef(eRotate.y,0,1,0);
    glRotatef(eRotate.z,0,0,1);

    
    glScalef(eScale.x,eScale.y,1.0);

     glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(-1,-1,0);

      glTexCoord2f(xMax,yMax);
      glVertex3f(1,-1,0);

      glTexCoord2f(xMax,yMin);
      glVertex3f(1,1,0);

      glTexCoord2f(xMin,yMin);
      glVertex3f(-1,1,0);

   glEnd();
   glPopMatrix();

}

void GLEnms::PlaceEnemy(vec3 p)
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;
}

void GLEnms::actions()
{
    switch(action) {
    case WALKRIGHT:
      if (clock() - myTime->startTime > 90)
      {
        xMin += 1.0 / framesX;
        xMax += 1.0 / framesX;

        pos.x += speed;
        myTime->startTime = clock();
      }
      break;

    case WALKLEFT:
      if (clock() - myTime->startTime > 90)
      {
        xMin += 1.0 / framesX;
        xMax += 1.0 / framesX;

        pos.x -= speed;

        myTime->startTime = clock();
      }
      break;

    case STAND:

      //if(clock() - myTime->startTime > 90) {

      xMax = 1.0 / framesX; // default image
      xMin = 0;
      yMax = 1.0 / framesY;
      yMin = 0;

      // myTime->startTime = clock();

      //}

      break;
  
    case DIE:

      if (clock() - myTime->startTime > 240) {

        if (xMin < 1.0) {
          xMin += 1.0 / framesX;
          xMax += 1.0 / framesX;
        } else {
          alive = false;
          break;
        }

        myTime->startTime = clock();

      }

      break;
  
  }

}
