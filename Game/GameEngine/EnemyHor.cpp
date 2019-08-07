#include "EnemyHor.h"
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

EnemyHor::EnemyHor(float x, float y) : Enemy(x, y) {
    this->hspeed = 1;
}


void EnemyHor::start(){
    Enemy::start();

}


void EnemyHor::step(){
    Enemy::step();
    
}

void EnemyHor::draw(){
    Enemy::draw();
    
   
}