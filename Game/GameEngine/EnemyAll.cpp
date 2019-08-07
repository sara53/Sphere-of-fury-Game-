#include "EnemyAll.h"
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

EnemyAll::EnemyAll(float x, float y) : Enemy(x, y) {
    this->hspeed = 1;
    this->vspeed = 1;
}


void EnemyAll::start(){
    Enemy::start();

}


void EnemyAll::step(){
    Enemy::step();
    
}

void EnemyAll::draw(){
    Enemy::draw();
    
   
}