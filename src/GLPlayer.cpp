#include "GLPlayer.h"
#include <common.h>


GLPlayer::GLPlayer()
{
    //ctor
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;


    theta = 30*PI/180.0;
    v =100.0;
    t=0;

    int facing = RIGHT; // facing right by default

}

GLPlayer::~GLPlayer()
{
    //dtor
}
void GLPlayer::initPlayer(int x, int y, char* fileName) // cols, rows, spritesheet file
{
    plPosition.x =-1.0;         // initialize positions
    plPosition.y =-0.35;
    plPosition.z = -1.0;

    plScale.x = 0.5;           // initialize scale
    plScale.y = 0.5;
    plScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    texture->loadTexture(fileName); // load spritesheet

    xMin =0;
    yMax =2.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

    actionTrigger=0;
    myTime->startTime = clock();
}

void GLPlayer::drawPlayer()
{

    glTranslatef(plPosition.x,plPosition.y,plPosition.z);
    glScalef(plScale.x,plScale.y,plScale.z);

    glColor3f(1.0,1.0,1.0);    //white rectangle
    texture->bindTexture();    //binding my background


    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      glTexCoord2f(xMax,yMax);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      glTexCoord2f(xMax,yMin);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      glTexCoord2f(xMin,yMin);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
}

void GLPlayer::actions()
{
    switch(actionTrigger)
    {
        case STAND:

            if(clock() -myTime->startTime > 90) { // change frame every x ms

                // Set yMin and yMax to display the first row
                yMin = 0;
                yMax = 1.0 / (float)framesY;

                if(xMax < 1) { // if not at the end of the row
                
                // advance to next frame in row
                xMin += 1.0 / (float)framesX;
                xMax += 1.0 / (float)framesX;

                } else { // Reset to the first frame in the row
                  facing == LEFT ? (xMax = 0, xMin = 1.0 / (float)framesX)
                                  : (xMin = 0, xMax = 1.0 / (float)framesX);
                }

                myTime->startTime = clock();

            }
            break;


        case WALKLEFT:
            if(clock() - myTime->startTime>60) 
            {

                // Select second row
                yMin = 1.0 / (float)framesY;
                yMax = 2.0 / (float)framesY;

                if(xMax <1) // if not at end of row
                { // advance to next frame in row
                    xMax += 1.0/(float)framesX;
                    xMin += 1.0/(float)framesX;
                
                } else { // Reset to the first frame in the row
                    xMax = 0;
                    xMin = 1.0/(float)framesX;
                }
                
                myTime->startTime =clock();
            }

            break;


        case WALKRIGHT:
            if(clock() - myTime->startTime>60)
            {
                // Select second row
                yMin = 1.0 / (float)framesY;
                yMax = 2.0 / (float)framesY;

                if(xMax <1) 
                {
                    xMin += 1.0/(float)framesX;
                    xMax += 1.0/(float)framesX;
                }
                else
                {
                    xMin = 0;
                    xMax = 1.0/(float)framesX;

                }

                myTime->startTime =clock();
            }

            break;

        case JUMPRIGHT: 

            if(clock() - myTime->startTime > 120) { // change frame every x ms

                if(xMax < 1) { // if not at the end of the row
                
                    // advance to next frame in row
                    xMin += 1.0 / (float)framesX;
                    xMax += 1.0 / (float)framesX;


                    // Move the player up
                        plPosition.y += 0.15;
                        plPosition.x += 0.15; // move right



                } else { // advance next row

                        actionTrigger = FALLRIGHT;
                        xMin = 0;
                        xMax = 1.0 / (float)framesX;
                        yMin += 1.0 / (float)framesY;
                        yMax += 1.0 / (float)framesY;

                        break;

                    }

                    myTime->startTime = clock();


            }      

            break;

        case FALLRIGHT:
            if(clock() - myTime->startTime > 120) { // change frame every x ms

                if(xMax < 4 / (float)framesX) { // if not at the end of the row
                
                    // advance to next frame in row
                    xMin += 1.0 / (float)framesX;
                    xMax += 1.0 / (float)framesX;


                    // Move the player down
                    plPosition.y -= 0.15;
                      plPosition.x += 0.15; // move right

                } else {

                    actionTrigger = STAND;
                    plPosition.y = -0.35;
                        
                    break;

                } 

                    myTime->startTime = clock();

                }

                
            break;

        
        case JUMPLEFT: 

            if(clock() - myTime->startTime > 120) { // change frame every x ms

                if(xMin < 1) { // if not at the end of the row
                
                    // advance to next frame in row
                    xMin += 1.0 / (float)framesX;
                    xMax += 1.0 / (float)framesX;


                    // Move the player up
                        plPosition.y += 0.15;
                        plPosition.x -= 0.15; // move left



                } else { // advance next row

                        actionTrigger = FALLLEFT;
                        xMax = 0;
                        xMin = 1.0 / (float)framesX;
                        yMin += 1.0 / (float)framesY;
                        yMax += 1.0 / (float)framesY;

                        break;

                    }

                    myTime->startTime = clock();


            }      

            break;

        case FALLLEFT:
            if(clock() - myTime->startTime > 120) { // change frame every x ms

                if(xMin < 4 / (float)framesX) { // if not at the end of the row
                
                    // advance to next frame in row
                    xMin += 1.0 / (float)framesX;
                    xMax += 1.0 / (float)framesX;


                    // Move the player down
                    plPosition.y -= 0.15;
                    plPosition.x -= 0.15; // move left
                    
                

                } else {

                    actionTrigger = STAND;
                    plPosition.y = -0.35;
                        
                    break;

                } 

                    myTime->startTime = clock();

                }

                
            break;

        


    }

}
