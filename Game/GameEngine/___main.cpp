#include <Windows.h>
#include <GL\glut.h>
#include "__Game.h"
#include "Keyboard.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "declarations.h"
using namespace std;


void main(int argc, char** argv){
    // initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create Game Window
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(__Game::windowWidth, __Game::windowHeight);
    glutCreateWindow("");

    // call backs
    glutDisplayFunc(__Game::draw);
    glutIdleFunc(__Game::idle);
    glutKeyboardFunc(Keyboard::KeyPress);
    glutKeyboardUpFunc(Keyboard::keyRelease);
    glutSpecialFunc(Keyboard::specialPress);
    glutSpecialUpFunc(Keyboard::specialRelease);
    glutReshapeFunc(__Game::onWidowResize);

    // start game and enter main loop
    __Game::start();
    glutMainLoop();
}