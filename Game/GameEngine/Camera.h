#include<cmath>
#pragma once

class Camera
{
private:
    static double xfrom , yfrom , zfrom;
    static double xto , yto , zto;
    static double slopeAngle , distance;

public:

    static void init(double angle, double distance, double xto, double yto, double zto);
    ///////////////////////////////////////////////////////////////////////

    static void lookAt(float xto, float yto, float zto);
    ///////////////////////////////////////////////////////////////////////

    static void update();
    ///////////////////////////////////////////////////////////////////////

    static void increaseSLopeAngle(double inc);
    ///////////////////////////////////////////////////////////////////////

    static void increaseDistance(double inc);
    ///////////////////////////////////////////////////////////////////////

	static void display();

};