#include "Camera.h"
#include <Windows.h>
#include <gl\glut.h>
#include "declarations.h"
#include <iostream>
#include "__Game.h"
using namespace std;

double Camera::xfrom , Camera::yfrom , Camera::zfrom;
double Camera::xto , Camera::yto , Camera::zto;
double Camera::slopeAngle , Camera::distance;


void Camera::init(double angle, double distance, double xto, double yto, double zto){
    Camera::xto = xto;
    Camera::yto = yto;
    Camera::zto = zto;
    Camera::distance = distance;
    Camera::slopeAngle = angle;
}
void Camera::lookAt(float xto, float yto, float zto){
    Camera::xto = xto;
    Camera::yto = yto;
    Camera::zto = zto;
}
void Camera::update(){
    Camera::xfrom = Camera::xto;
    Camera::yfrom = Camera::yto - cos(Camera::slopeAngle*PI/180.0)*Camera::distance;
    Camera::zfrom = Camera::zto + sin(Camera::slopeAngle*PI/180.0)*Camera::distance;
}
void Camera::increaseSLopeAngle(double inc){
    Camera::slopeAngle += inc;
    if(Camera::slopeAngle > MAX_ANGLE){
	   Camera::slopeAngle = MAX_ANGLE;
    }
    if(Camera::slopeAngle < MIN_ANGLE){
	   Camera::slopeAngle = MIN_ANGLE;
    }
}
void Camera::increaseDistance(double inc){
    Camera::distance += inc;
    if(Camera::distance > MAX_DISTANCE){
	   Camera::distance = MAX_DISTANCE;
    }
    if(Camera::distance < MIN_DISTANCE){
	   Camera::distance = MIN_DISTANCE;
    }
}

void Camera::display(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)__Game::windowWidth / (float)__Game::windowHeight, 0.1, 1000);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(Camera::xfrom, Camera::yfrom, Camera::zfrom,
	   Camera::xto, Camera::yto, Camera::zto,
	   0, 1, 0);
}