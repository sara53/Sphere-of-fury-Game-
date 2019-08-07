#pragma once
#include "Enemy.h"

class EnemyVer : public Enemy{

public:
    EnemyVer(float x, float y);
    void start();
    void step();
    void draw();
};

