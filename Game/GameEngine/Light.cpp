#include "Light.h"
#include <Windows.h>
#include <GL\glut.h>


void Light::init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat directedLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat directedLightPos[] = {-1, -1, 1, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);


    GLfloat directedLight2[] = {1.0f, 1.0f, 1.0f, 0.5f};
    GLfloat directedLightPos2[] = {1, 1, -1, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, directedLight2);
    glLightfv(GL_LIGHT1, GL_POSITION, directedLightPos2);
}