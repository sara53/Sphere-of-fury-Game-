#pragma once
#include "Enemy.h"

class EnemyAll : public Enemy{

public:
    EnemyAll(float x, float y);
    void start();
    void step();
    void draw();
};

