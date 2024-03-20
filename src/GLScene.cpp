#include <GLScene.h>
#include<GLLight.h>
#include<GLTexture.h>
#include<GLModel.h>
#include<GLInputs.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>

// Create Objects
GLInputs* keyMouseInput     = new GLInputs(); // Keyboard and mouse inputs object
GLParallax* parallaxLayer1  = new GLParallax(); // Parallax background layer 1
GLParallax* parallaxLayer2  = new GLParallax(); // Parallax background layer 2
GLParallax* parallaxLayer3  = new GLParallax(); // Parallax background layer 3
GLParallax* parallaxLayer4  = new GLParallax(); // Parallax background layer 4
GLParallax* parallaxLayer5  = new GLParallax(); // Parallax background layer 5





GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    // Initialize Scene Settings //
    glShadeModel(GL_SMOOTH);            // for smooth render
    glClearColor(0.0f,0.0f,0.0f,0.0f);  // clear background to black
    glClearDepth(2.0f);                 // depth test for layers
    glEnable(GL_DEPTH_TEST);            // activate depth test
    glDepthFunc(GL_LEQUAL);             // depth function type

    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    glEnable(GL_BLEND);                 // Transparent effect of pngs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);  //enable textures



    // Load Textures //
    parallaxLayer1->parallaxInit("images/parallax1.png");       // load background texture
    parallaxLayer2->parallaxInit("images/parallax2.png");       // load foreground texture
    parallaxLayer3->parallaxInit("images/parallax3.png");       // load foreground texture
    parallaxLayer4->parallaxInit("images/parallax4.png");       // load foreground texture
    parallaxLayer5->parallaxInit("images/parallax5.png");       // load foreground texture


    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
                              // DO NOT ABUSE ME
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    // clear bits in each itterration
   glLoadIdentity();
   glColor3f(1.0,1.0,1.0);      //color the object red


   // Parallax Background Drawing
   glPushMatrix();                                              // save the current matrix on stack
    glScaled(3.33, 3.33, 1.0);                                  // scale the drawing
    glDisable(GL_LIGHTING);                                     // disable lighting for parallax

    // Draw parallax background layers //
    parallaxLayer1->parallaxDraw(screenWidth, screenHeight);
    parallaxLayer2->parallaxDraw(screenWidth, screenHeight);
    parallaxLayer3->parallaxDraw(screenWidth, screenHeight);
    parallaxLayer4->parallaxDraw(screenWidth, screenHeight);
    parallaxLayer5->parallaxDraw(screenWidth, screenHeight);

    glEnable(GL_LIGHTING);                                      // re-enable lighting for other objects
   glPopMatrix();                                               // restore the matrix from stack



    return true;
}

GLvoid GLScene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; // keep track of the ratio
    glViewport(0,0,width,height); // adjusting the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspectRatio,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN:
        keyMouseInput->wParam = wParam;                     // capture keystroke

        // move parallax backgrounds on keystroke increasingly faster on each new layer
        keyMouseInput->keyBackground(parallaxLayer1, 0.000);
        keyMouseInput->keyBackground(parallaxLayer2, 0.001);
        keyMouseInput->keyBackground(parallaxLayer3, 0.003);
        keyMouseInput->keyBackground(parallaxLayer4, 0.005);
        keyMouseInput->keyBackground(parallaxLayer5, 0.007);


         break;

    case WM_KEYUP:

         break;

    case WM_LBUTTONDOWN:

         break;

    case WM_RBUTTONDOWN:

         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;

    case WM_MOUSEMOVE:

         break;
    case WM_MOUSEWHEEL:


       break;
    }
}


