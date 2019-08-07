#include <Windows.h>
#include<gl\glut.h>
#include "Keyboard.h"
#include <iostream>
#include "declarations.h"
#include "_Room.h"
#include "RmLevel1.h"
#include "RmLevel2.h"
#include "RmLevel3.h"
#include "RmLevel4.h"
#include "RmLevel5.h"
#include "RmLevel6.h"
#include "RmLevel7.h"
#include "Camera.h"
#include "__Game.h"
using namespace std;


// static variables declaration
bool Keyboard::up, Keyboard::down, Keyboard::left, Keyboard::right, Keyboard::space;
bool Keyboard::keyArray [128];
bool Keyboard::specialArray [128];


// step: executed 60 times per second
void Keyboard::step(){

    Keyboard::up = Keyboard::specialArray[GLUT_KEY_UP];
    Keyboard::down = Keyboard::specialArray[GLUT_KEY_DOWN];
    Keyboard::left = Keyboard::specialArray[GLUT_KEY_LEFT];
    Keyboard::right = Keyboard::specialArray[GLUT_KEY_RIGHT];
    Keyboard::space = Keyboard::keyArray[' '];

    if(Keyboard::keyArray['Q']){
	   Camera::increaseSLopeAngle(1);
    }
    if(Keyboard::keyArray['A']){
	   Camera::increaseSLopeAngle(-1);
    }
    if(Keyboard::keyArray['W']){
	   Camera::increaseDistance(-1);
    }
    if(Keyboard::keyArray['S']){
	   Camera::increaseDistance(1);
    }
}


// KeyPress: executed when an alphanumeric key is pressed
// this is a registered function for open gl
void Keyboard::KeyPress(unsigned char key, int x, int y){

    if (key < 0 || key >127 ){
	   return;
    }
    
    if(Keyboard::keyArray[key]==false){
	   Keyboard::keyArray[toupper(key)]=true;
	   Keyboard::keyArray[tolower(key)]=true;
    }

    // Press R to restart room
    if(key == 'r' || key == 'R'){
	   _Room::currentRoom->restart();
    }

    // press 1-7 to go to level, 8 to win (for developers only)
    if(DEVELOPER_MODE){
	   if(key == '1'){
		  _Room::gotoRoom(new RmLevel1());
	   } else if(key == '2'){
		  _Room::gotoRoom(new RmLevel2());
	   } else if(key == '3'){
		  _Room::gotoRoom(new RmLevel3());
	   } else if(key == '4'){
		  _Room::gotoRoom(new RmLevel4());
	   } else if(key == '5'){
		  _Room::gotoRoom(new RmLevel5());
	   } else if(key == '6'){
		  _Room::gotoRoom(new RmLevel6());
	   } else if(key == '7'){
		  _Room::gotoRoom(new RmLevel7());
	   } else if(key == '8'){
		  __Game::gameWin();
	   }
    }

    // Press Enter to restart when game is over or game win
    if((int)key == 13){
	   if(__Game::isGameOver){
		  _Room::currentRoom->restart();
	   } else if(__Game::isWinner){
		  exit(0);
	   }
    }

    // press ESC to exit
    if((int)key == 27){
	   exit(0);
    }
}


// keyRelease: executed when an alphanumeric key is released
// this is a registered function for open gl
void Keyboard::keyRelease(unsigned char key, int x, int y){
    if (key < 0 || key >127 ){
	   return;
    }
    Keyboard::keyArray[toupper(key)]=false;
    Keyboard::keyArray[tolower(key)]=false;
}


// KeyPress: executed when a special key is pressed
// this is a registered function for open gl
void Keyboard::specialPress(int key, int x, int y){
    if (key < 0 || key >127 ){
	   return;
    }
    
    if(Keyboard::specialArray[key]==false){
	   Keyboard::specialArray[key]=true;
    }

}


// KeyPress: executed when a special key is released
// this is a registered function for open gl
void Keyboard::specialRelease(int key, int x, int y){
    if (key < 0 || key >127 ){
        return;
    }
    Keyboard::specialArray[key]=false;
}