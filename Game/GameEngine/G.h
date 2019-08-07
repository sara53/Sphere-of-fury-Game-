#pragma once
#include <Windows.h>
#include <GL\glut.h>
#include "imageloader.h"

class G {
public:
    // textures
    static GLuint TEX_T1;
    static GLuint TEX_T2;
    static GLuint TEX_GRASS;
    static GLuint TEX_GRASS2;
    static GLuint TEX_WALL;
    static GLuint TEX_WALL2;
    static GLuint TEX_WALL3;
    static GLuint TEX_RED;
    static GLuint TEX_GREEN;
    static GLuint TEX_BLUE;
    static GLuint TEX_YELLOW;
    static GLuint TEX_CHANGER_RED;
    static GLuint TEX_CHANGER_GREEN;
    static GLuint TEX_CHANGER_BLUE;
    static GLuint TEX_CHANGER_YELLOW;
    static GLuint TEX_SKULL_RED;
    static GLuint TEX_SKULL_GREEN;
    static GLuint TEX_SKULL_BLUE;
    static GLuint TEX_SKULL_YELLOW;
    static GLuint TEX_ENEMY;
    static GLuint TEX_ENEMY_BLADE;
    static GLuint TEX_LOSE;
    static GLuint TEX_WIN;

    // static functions
    static void loadTextures();
    static GLuint loadTexture(char imageFilename[]);
    static void beginTexture(GLuint textureId);
    static void endTexture();
    static void drawCube(GLfloat halfSide, GLuint textureId);
    static GLuint getCubeTextureFromColor(float color[]);
    static GLuint getChangerTextureFromColor(float color[]);
    static GLuint getSkullTextureFromColor(float color[]);
    
    
};

