#pragma once
class Keyboard
{
private:
    
public:
  
    static bool  keyArray [128];
    static bool  specialArray [128];

    static void step();
    static bool up,down,left,right,space;
    static void KeyPress(unsigned char key, int x, int y);
    static void keyRelease(unsigned char key, int x, int y);
    static void specialPress(int key, int x, int y);
    static void specialRelease(int key, int x, int y);


};

