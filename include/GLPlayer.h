#ifndef GLPLAYER_H
#define GLPLAYER_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class GLPlayer
{
    public:
        GLPlayer();
        virtual ~GLPlayer();

        enum {STAND, WALKLEFT, WALKRIGHT, RUN, JUMPRIGHT, JUMPLEFT, FALLRIGHT, FALLLEFT, ATTACK};
        enum {LEFT, RIGHT, DOWN, UP};

        int facing;


        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void initPlayer(int,int,char* fileName); // number of x, y frames
        void drawPlayer();
        void actions();

        vec3 plPosition;
        vec3 plScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;

        int actionTrigger;  // for load actions

        int v;   // velocity
        float t; // projectile timer
        float theta;// angle of projectile


    protected:

    private:
};

#endif // GLPLAYER_H
