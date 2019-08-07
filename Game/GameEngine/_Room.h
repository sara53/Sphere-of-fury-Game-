#pragma once
#include <vector>
#include "_Entity.h"
#include <string>
#include <Windows.h>
#include <GL\glut.h>

class _Entity;

class _Room{
private:

    // private variables
    _Entity*** staticCollisionMap;
    std::vector<_Entity*> staticEntityList;
    std::vector<_Entity*> dynamicEntityList;
    unsigned int currentStaticEntityIndex;
    unsigned int currentDynamicEntityIndex;
    char filename[50];

    // private functions
    void drawBorderWalls();

protected:

    int roomWidth;
    int roomHeight;
    int roomNumber;
    GLuint borderWallTexture;
    bool hasFloor;
    GLuint floorTexture;

public:

    // static variables
    static _Room* currentRoom;
    static bool entityRemovedItself;

    // constructor
    _Room(int roomNumber, char filename[]);
    ~_Room();

    // instance functions
    void initDimensionsAndCollisionSections(int w, int h);
    void prepare();
    virtual void start();
    virtual void step();
    virtual void draw();
    virtual void win();
    void restart();
    void addEntity(_Entity* newEntity);
    void removeEntity(_Entity* e);
    virtual void createEntityFromChar(char cha, float x, float y);

    // static functions
    static void gotoRoom(_Room* newRoom);

    // getters
    inline _Entity*** getStaticCollisionMap(){return this->staticCollisionMap;}
    inline std::vector<_Entity*> getDynamicEntityList(){return this->dynamicEntityList;}
    inline int getRoomWidth(){return this->roomWidth;}
    inline int getRoomHeight(){return this->roomHeight;}
    
   
};
