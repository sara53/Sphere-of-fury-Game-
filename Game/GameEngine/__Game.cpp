#include <Windows.h>
#include <GL\glut.h>
#include "__Game.h"
#include <iostream>
#include <time.h>
#include "_Room.h"
#include "RmLevel1.h"
#include "RmLevel2.h"
#include "RmLevel3.h"
#include "Keyboard.h"
#include "Camera.h"
#include "G.h"
#include "Light.h"
#include "Player.h"
using namespace std;


// static variables definition (possibly giving them initial value)
int __Game::currentFPS;
long double __Game::oldTime;
long double __Game::currentTime;
long double __Game::deltaTime;
long double __Game::totalTimeMillis;
long double __Game::millisPerFrame;
long double __Game::ticks;
int __Game::windowWidth = 640;
int __Game::windowHeight = 480;
Player* __Game::player;
bool __Game::isGameOver;
bool __Game::isWinner;


// start: This function starts the game. It should be called once in the main function.
void __Game::start(){
    __Game::currentFPS = 0;
    __Game::player = nullptr;
    __Game::millisPerFrame = 1000.0/__Game::FPS;
    __Game::currentTime = clock();
    __Game::totalTimeMillis = 0;
    __Game::ticks = 0;
    __Game::deltaTime = 0;
    __Game::isGameOver = false;
    G::loadTextures();
    Camera::init(45, 200, 100, 100, 0);
    Light::init();
    _Room::gotoRoom(new RmLevel1());
}


// idle: This is the IdleFunc for openGL. It's called so many times as long the game is running.
// In this function we calculate deltaTime in order to call the step() and draw() function at a fixed FPS rate
void __Game::idle(){
    __Game::oldTime = __Game::currentTime;
    __Game::currentTime = clock();
    __Game::totalTimeMillis += (__Game::currentTime - __Game::oldTime)/CLOCKS_PER_SEC*1000.0;
    __Game::deltaTime += (__Game::currentTime - __Game::oldTime)/CLOCKS_PER_SEC*1000.0/__Game::millisPerFrame;
    if(__Game::deltaTime >= 1.0){
	   __Game::deltaTime--;
	   __Game::ticks++;
	   __Game::step();
	   glutPostRedisplay(); // indirectly call the draw() function
    }
    if(__Game::deltaTime > 2){
	   __Game::deltaTime = 2; // make sure frames don't accumulate if the game runs too slow
    }
    if(__Game::totalTimeMillis >= 1000){
	   __Game::totalTimeMillis -= 1000;
	   __Game::currentFPS =  __Game::ticks;
	   //cout << "FPS: " << __Game::ticks << endl;
	   __Game::ticks = 0;
	   
    }
}


// step: This function contains the main logic of the game
// it's executed at a fixed FPS rate (which is equal to the FPS static constant of this class)
void __Game::step(){
    Keyboard::step();
    Camera::lookAt(__Game::player->getX()+TILE_WIDTH/2.0f, __Game::player->getY()+TILE_HEIGHT/2.0f, TILE_HEIGHT/2.0f);
    Camera::update();
    if(_Room::currentRoom != nullptr){
	   _Room::currentRoom->step();
    }
}




// draw: This is the DisplayFunc for OpenGL. Everything is drawn inside this function.
void __Game::draw(){
    
    // window background color
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // camera
    Camera::display();

    ///////////// drawing code goes here //////////////
    if(_Room::currentRoom != nullptr){
	   _Room::currentRoom->draw();
    }
    //////////////////////////////////////////////////
    // draw FPS
    char fps_str[5] = "";
    char msg[10] = "FPS: ";
    _itoa_s(__Game::currentFPS, fps_str, 10);
    strcat_s(msg, fps_str);
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    __Game::displayText(10, 10, msg);
    glEnable(GL_LIGHTING);

    ///////////////// Draw game over or game win ///////////////////
    if(__Game::isGameOver || __Game::isWinner){
	   GLuint tex = G::TEX_LOSE;
	   if(__Game::isWinner){
		  tex = G::TEX_WIN;
	   }
	   glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	   gluOrtho2D(0, __Game::windowWidth, 0, __Game::windowHeight);
	   glDisable(GL_LIGHTING);
	   G::beginTexture(tex);
	   glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, 0.0f);
		  glVertex2f(0, 0);
		  glTexCoord2f((float)__Game::windowWidth/400.0f, 0.0f);
		  glVertex2f(__Game::windowWidth, 0);
		  glTexCoord2f((float)__Game::windowWidth/400.0f, (float)__Game::windowHeight/400.0f);
		  glVertex2f(__Game::windowWidth, __Game::windowHeight);
		  glTexCoord2f(0.0f, (float)__Game::windowHeight/400.0f);
		  glVertex2f(0, __Game::windowHeight);
	   glEnd();
	   G::endTexture();
	   glEnable(GL_LIGHTING);
    }

    // draw screen and swap buffers
    glutSwapBuffers();
}

void __Game::gameOver(){
    if(__Game::isGameOver){
	   return;
    }
    __Game::isGameOver = true;
    if(__Game::player != nullptr){
	   _Room::currentRoom->removeEntity(__Game::player);
    }
}

void __Game::gameWin(){
    if(__Game::isWinner){
	   return;
    }
    __Game::isWinner = true;
    if(__Game::player != nullptr){
	   _Room::currentRoom->removeEntity(__Game::player);
    }
}

void __Game::onWidowResize(int windowWidth, int windowHeight){
    glViewport(0, 0, windowWidth, windowHeight);
    __Game::windowWidth = windowWidth;
    __Game::windowHeight = windowHeight;
}

void __Game::displayText(int x, int y, char str[]){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, __Game::windowWidth, 0, __Game::windowHeight);

    glRasterPos2f(x, y);
    int len = (int) strlen(str);
    for (int i = 0; i < len; i++) {
	   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
}
