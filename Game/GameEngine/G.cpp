#include "G.h"
#include <Windows.h>
#include <GL\glut.h>
#include "imageloader.h"
#include "declarations.h"
#include <iostream>
using namespace std;


//----------------------------------- Loading Textures ---------------------------------


// Textures declaration
GLuint G::TEX_T1;
GLuint G::TEX_T2;
GLuint G::TEX_GRASS;
GLuint G::TEX_GRASS2;
GLuint G::TEX_WALL;
GLuint G::TEX_WALL2;
GLuint G::TEX_WALL3;
GLuint G::TEX_RED;
GLuint G::TEX_GREEN;
GLuint G::TEX_BLUE;
GLuint G::TEX_YELLOW;
GLuint G::TEX_CHANGER_RED;
GLuint G::TEX_CHANGER_GREEN;
GLuint G::TEX_CHANGER_BLUE;
GLuint G::TEX_CHANGER_YELLOW;
GLuint G::TEX_SKULL_RED;
GLuint G::TEX_SKULL_GREEN;
GLuint G::TEX_SKULL_BLUE;
GLuint G::TEX_SKULL_YELLOW;
GLuint G::TEX_ENEMY;
GLuint G::TEX_ENEMY_BLADE;
GLuint G::TEX_LOSE;
GLuint G::TEX_WIN;


// Load all textures
void G::loadTextures(){
    G::TEX_T1 = G::loadTexture("img.bmp");
    G::TEX_T2 = G::loadTexture("img2.bmp");
    G::TEX_GRASS = G::loadTexture("tex_grass.bmp");
    G::TEX_GRASS2 = G::loadTexture("tex_grass2.bmp");
    G::TEX_WALL = G::loadTexture("tex_wall.bmp");
    G::TEX_WALL2 = G::loadTexture("tex_wall2.bmp");
    G::TEX_WALL3 = G::loadTexture("tex_wall3.bmp");
    G::TEX_RED = G::loadTexture("tex_red.bmp");
    G::TEX_GREEN = G::loadTexture("tex_green.bmp");
    G::TEX_BLUE = G::loadTexture("tex_blue.bmp");
    G::TEX_YELLOW = G::loadTexture("tex_yellow.bmp");
    G::TEX_CHANGER_RED = G::loadTexture("tex_color_changer_red.bmp");
    G::TEX_CHANGER_GREEN = G::loadTexture("tex_color_changer_green.bmp");
    G::TEX_CHANGER_BLUE = G::loadTexture("tex_color_changer_blue.bmp");
    G::TEX_CHANGER_YELLOW = G::loadTexture("tex_color_changer_yellow.bmp");
    G::TEX_SKULL_RED = G::loadTexture("tex_skull_red.bmp");
    G::TEX_SKULL_GREEN = G::loadTexture("tex_skull_green.bmp");
    G::TEX_SKULL_BLUE = G::loadTexture("tex_skull_blue.bmp");
    G::TEX_SKULL_YELLOW = G::loadTexture("tex_skull_yellow.bmp");
    G::TEX_ENEMY = G::loadTexture("tex_enemy.bmp");
    G::TEX_ENEMY_BLADE = G::loadTexture("tex_enemy_blade.bmp");
    G::TEX_LOSE = G::loadTexture("tex_lose.bmp");
    G::TEX_WIN = G::loadTexture("tex_win.bmp");
}


//---------------------------------------------------------------------------------------

// Load a specific texture from a filename and return the texture id
// This function is called inside loadTextures()
GLuint G::loadTexture(char imageFilename[]) {
    char path[100] = "images/";
    strcat(path, imageFilename);
    Image* image = loadBMP(path);
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				0,                            //0 for now
				GL_RGB,                       //Format OpenGL uses for image
				image->width, image->height,  //Width and height
				0,                            //The border of the image
				GL_RGB, //GL_RGB, because pixels are stored in RGB format
				GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
							 //as unsigned numbers
				image->pixels);               //The actual pixel data
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete image;
    return textureId; //Returns the id of the texture
}

// Start using a texture for the shape you draw
void G::beginTexture(GLuint textureId){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glColor3f(1, 1, 1);
}

// End using texture so that the next shapes you draw are not affected by the texture
void G::endTexture(){
    glDisable(GL_TEXTURE_2D);
}


// getCubeTextureFromColor: takes a vector of RGB color and returns the corresponding texture id of cube
GLuint G::getCubeTextureFromColor(float color[]){
    // red
    if(color[0] == 1 && color[1] == 0 && color[2] == 0){
	   return G::TEX_RED;
    }
    // green
    if(color[0] == 0 && color[1] == 1 && color[2] == 0){
	   return G::TEX_GREEN;
    }
    // blue
    if(color[0] == 0 && color[1] == 0 && color[2] == 1){
	   return G::TEX_BLUE;
    }
    // yellow
    if(color[0] == 1 && color[1] == 1 && color[2] == 0){
	   return G::TEX_YELLOW;
    }
}


// getChangerTextureFromColor: takes a vector of RGB color and returns the corresponding texture id of the color changer
GLuint G::getChangerTextureFromColor(float color[]){
    // red
    if(color[0] == 1 && color[1] == 0 && color[2] == 0){
	   return G::TEX_CHANGER_RED;
    }
    // green
    if(color[0] == 0 && color[1] == 1 && color[2] == 0){
	   return G::TEX_CHANGER_GREEN;
    }
    // blue
    if(color[0] == 0 && color[1] == 0 && color[2] == 1){
	   return G::TEX_CHANGER_BLUE;
    }
    // yellow
    if(color[0] == 1 && color[1] == 1 && color[2] == 0){
	   return G::TEX_CHANGER_YELLOW;
    }
}


// getSkullTextureFromColor: takes a vector of RGB color and returns the corresponding texture id of the skull
GLuint G::getSkullTextureFromColor(float color[]){
    // red
    if(color[0] == 1 && color[1] == 0 && color[2] == 0){
	   return G::TEX_SKULL_RED;
    }
    // green
    if(color[0] == 0 && color[1] == 1 && color[2] == 0){
	   return G::TEX_SKULL_GREEN;
    }
    // blue
    if(color[0] == 0 && color[1] == 0 && color[2] == 1){
	   return G::TEX_SKULL_BLUE;
    }
    // yellow
    if(color[0] == 1 && color[1] == 1 && color[2] == 0){
	   return G::TEX_SKULL_YELLOW;
    }
}


//--------------------------- Helper drawing functions ------------------------------------

// cube with texture
void G::drawCube(GLfloat halfSide, GLuint textureId){
    G::beginTexture(textureId);
    int aroundX = 0;
    for(int i = 0; i < 6; i++){
	   if(i >= 4){
		  aroundX = 1;
	   }
	   glPushMatrix();
	   glRotatef(90*(i%4) + 90*aroundX*(1+i%4) , aroundX, 1-aroundX, 0);
	   glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, 0.0f);
		  glVertex3f(-halfSide, -halfSide, -halfSide);
		  glTexCoord2f(1.0f, 0.0f);
		  glVertex3f(+halfSide, -halfSide, -halfSide);
		  glTexCoord2f(1.0f, 1.0f);
		  glVertex3f(+halfSide, +halfSide, -halfSide);
		  glTexCoord2f(0.0f, 1.0f);
		  glVertex3f(-halfSide, +halfSide, -halfSide);
	   glEnd();
	   glPopMatrix();
    }
    G::endTexture();
}

