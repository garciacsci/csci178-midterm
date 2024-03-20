#include "GLInputs.h"


GLInputs::GLInputs()
{
    //ctor

    prev_MouseX =0;     // init mouse values
    prev_MouseY =0;

    mouse_Translate =0;
    mouse_Rotate =0;
}

GLInputs::~GLInputs()
{
    //dtor
}
void GLInputs::keyPress(GLPlayer* pl)
{
    switch(wParam)
    {
    case VK_LEFT:
        pl->actionTrigger= pl->WALKLEFT;
        break;

    case VK_RIGHT:
        pl->actionTrigger = pl->WALKRIGHT;
        break;

    case VK_DOWN:
        break;

    case VK_UP:
        pl->actionTrigger = pl->JUMP;
        break;

    case VK_ADD:

        break;

    case VK_SUBTRACT:
        break;
    }
}

void GLInputs::keyUP(GLPlayer* pl) // no longer interrupts jump action
{
    switch (wParam)
    {
        default:
           if(pl->actionTrigger == pl->JUMP) { // if not jumping
                pl->actionTrigger = pl->JUMP;
           } else {
                pl->actionTrigger= pl->STAND;
           }
        break;
    }
}

void GLInputs::mouseEventDown(GLModel* model, double x, double y)
{
       prev_MouseX =x;   //keep previous x val
       prev_MouseY =y;   // keep previous y val

    switch (wParam)
    {
        case MK_LBUTTON:
               mouse_Rotate =true;  // set rotation flag
              break;
        case MK_RBUTTON:
               mouse_Translate = true;  // set translation flag
            break;

        case MK_MBUTTON:
               // something you like to add
            break;

        default:
        break;
    }
}

void GLInputs::mouseEventUp()
{
       mouse_Rotate =false;    // reset rotation flag
       mouse_Translate =false; //reset translation flag
}

void GLInputs::mouseWheel(GLModel*mdl, double delta)
{
   mdl->zPos +=delta/100.0;   // mouse wheel movement
}

void GLInputs::mouseMove(GLModel* mdl, double x, double y)
{
      if(mouse_Translate)
      {
          mdl->xPos += (x-prev_MouseX)/100.0;  // move model in x direction
          mdl->yPos -= (y-prev_MouseY)/100.0;  // move model in y direction

          prev_MouseX =x;                      // update previous mouse x
          prev_MouseY =y;                      // update previous mouse y
      }

      if(mouse_Rotate)
      {
          mdl->RotateY += (x-prev_MouseX)/3.0; // model rotation on X direction
          mdl->RotateX += (y-prev_MouseY)/3.0; // model rotation on y direction

          prev_MouseX =x;                      // update previous mouse x
          prev_MouseY =y;                      // update previous mouse y
      }
}


void GLInputs::keyBackground(GLParallax* prlx, float speed) // parallax only goes left and right
{
   //  if(clock() - myTime->startTime>15)
       switch(wParam)
        {
       case VK_UP:               // move parallax up
        //    prlx->yMin -=speed;
        //    prlx->yMax -=speed;
        break;

        // Disabling parallax down since we won't go underground
        case VK_DOWN:           // move parallax down
        //    prlx->yMin +=speed;
        //    prlx->yMax +=speed;
        break;

        case VK_LEFT:            // move parallax left

           prlx->xMin -=speed;
           prlx->xMax -=speed;
        break;

        case VK_RIGHT:         // move parallax right

           prlx->xMin +=speed;
           prlx->xMax +=speed;
       break;
    //    myTime->startTime =clock();
    }
}
