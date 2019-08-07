#pragma once
#include "Player.h"

//class Player;

class __Game{
public:
    // static constants
    static const int FPS = 60;

    // static variables
    static int currentFPS;
    static long double oldTime; 
    static long double currentTime; 
    static long double deltaTime; 
    static long double ticks;
    static long double totalTimeMillis;
    static long double millisPerFrame;
    static int windowWidth;
    static int windowHeight;
    static Player* player;
    static bool isGameOver;
    static bool isWinner;

    // static functions
    static void start();
    static void idle();
    static void step();
    static void draw();
    static void gameOver();
    static void gameWin();
    static void onWidowResize(int windowWidth, int windowHeight);
    static void displayText(int x, int y, char str[]);
};

