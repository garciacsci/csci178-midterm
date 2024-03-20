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
GLInputs* KeyMouseInput     = new GLInputs(); // Keyboard and mouse inputs object
GLTimer*  Timer             = new GLTimer();  // Timer object


GLParallax* ParallaxLayer1  = new GLParallax(); // Parallax background layer 1
GLParallax* ParallaxLayer2  = new GLParallax(); // Parallax background layer 2
GLParallax* ParallaxLayer3  = new GLParallax(); // Parallax background layer 3
GLParallax* ParallaxLayer4  = new GLParallax(); // Parallax background layer 4
GLParallax* ParallaxLayer5  = new GLParallax(); // Parallax background layer 5

GLPlayer* Player            = new GLPlayer();   // Player object




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

    // Parallax Textures
    ParallaxLayer1->parallaxInit("images/parallax1.png");
    ParallaxLayer2->parallaxInit("images/parallax2.png");
    ParallaxLayer3->parallaxInit("images/parallax3.png");
    ParallaxLayer4->parallaxInit("images/parallax4.png");
    ParallaxLayer5->parallaxInit("images/parallax5.png");

    // Player Textures
    Player->initPlayer(6, 17, "images/warriorPlayer.png"); // columns, rows, spritesheet

    // Enemy Textures


    // Entity Initializations
    Player->actionTrigger = Player->STAND; // set Player to stand on start

    // Place Enemies //


    Timer->startTime = clock();                    // start the timer






    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
                              // DO NOT ABUSE ME
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    // clear bits in each itterration
   glLoadIdentity();
   glColor3f(1.0,1.0,1.0);      //color the object red


    //-- Parallax Background Drawing --//
    glPushMatrix();                                                 // save the current matrix on stack
        glScaled(3.33, 3.33, 1.0);                                  // scale the drawing
        glDisable(GL_LIGHTING);                                     // disable lighting for parallax

        // Draw parallax background layers //
        ParallaxLayer1->parallaxDraw(screenWidth, screenHeight);
        ParallaxLayer2->parallaxDraw(screenWidth, screenHeight);
        ParallaxLayer3->parallaxDraw(screenWidth, screenHeight);
        ParallaxLayer4->parallaxDraw(screenWidth, screenHeight);
        ParallaxLayer5->parallaxDraw(screenWidth, screenHeight);

        glEnable(GL_LIGHTING);                                      // re-enable lighting for other objects
    glPopMatrix();                                                  // restore the matrix from stack

    //-- Player Drawing --//
    glPushMatrix();                                                 // save the current matrix on stack
        glDisable(GL_LIGHTING);                                     // disable lighting for player
        
        Player->drawPlayer();                                       // draw player
        Player->actions();                                          // ensures player actions are updated each frame

        glEnable(GL_LIGHTING);                                      // re-enable lighting for other objects
    glPopMatrix();                                                  // restore the matrix from stack







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
        KeyMouseInput->wParam = wParam;                         // capture keystroke

        // move parallax backgrounds on keystroke increasingly faster on each new layer
        KeyMouseInput->keyBackground(ParallaxLayer1, 0.000);
        KeyMouseInput->keyBackground(ParallaxLayer2, 0.001);
        KeyMouseInput->keyBackground(ParallaxLayer3, 0.003);
        KeyMouseInput->keyBackground(ParallaxLayer4, 0.005);
        KeyMouseInput->keyBackground(ParallaxLayer5, 0.007);

        // Player Movement
        KeyMouseInput->keyPress(Player);               // move player on key press




         break;

    case WM_KEYUP:
        KeyMouseInput->wParam = wParam;                         // capture keystroke
        KeyMouseInput->keyUP(Player);                           // stop player movement on key release

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


