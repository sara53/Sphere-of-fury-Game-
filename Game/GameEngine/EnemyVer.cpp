#include "EnemyVer.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Keyboard.h"
#include "CollisionBox.h"
#include "G.h"
#include "declarations.h"
#include "Camera.h"
#include "__Game.h"
#include <cmath>
#include "Wall.h"
#include "ColoredCube.h"
#include "ColorChanger.h"
#include "_Room.h"
using namespace std;

EnemyVer::EnemyVer(float x, float y) : Enemy(x, y) {
    this->vspeed = 1;
}


void EnemyVer::start(){
    Enemy::start();

}


void EnemyVer::step(){
    Enemy::step();
    
}

void EnemyVer::draw(){
    Enemy::draw();
    
   
}