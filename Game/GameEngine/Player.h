#pragma once
#include "_Entity.h"


class Player : public _Entity{
private:
    float direction;
    float speed;
    float rotation;
    float color[3];
    int horMovementDelay;
    float speedScale;
    float vspeedBase;
public:
    static const int HOR_MOVEMENT_DELAY_MAX = 15;

    Player(float x, float y);
    void start();
    void step();
    void draw();
    void setHorMovementDelay(int horMovementDelay){
	   this->horMovementDelay = horMovementDelay;
    }
};

