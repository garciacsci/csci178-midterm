#ifndef GLINPUTS_H
#define GLINPUTS_H

#include<GLModel.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<common.h>

class GLInputs
{
    public:
        GLInputs();
        virtual ~GLInputs();

        void keyPress(GLPlayer*);  // when key pressed
        void keyUP(GLPlayer*);               // when key released
        void keyBackground(GLParallax *, float);//parallax model & speed
        void keyEnemy(GLEnms *);


        void mouseEventDown(GLModel*, double, double); // mouse btn pressed
        void mouseEventUp();                                // mouse btn released
        void mouseWheel(GLModel*,double);              // mouse wheel rolled
        void mouseMove(GLModel*, double,double);       // mouse moved

        double prev_MouseX;      // current mouse location X before action
        double prev_MouseY;      // current mouse location Y before action

        bool mouse_Translate;    // if mouse moved
        bool mouse_Rotate;       // if mouse moved for rotation

        WPARAM wParam;           // catching input interrupts

    protected:

    private:
};

#endif // GLINPUTS_H
