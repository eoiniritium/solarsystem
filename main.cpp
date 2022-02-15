#include<iostream>
#include "object.hpp"

int main()
{
    int iters = 100;

    obj sun;
    sun.point.x = 6;
    sun.point.y = 7;
    sun.mass = 1000000; //1,000,000

    loc location;
    location.x = 9;
    location.y = 3;

    loc velocity;
    velocity.x = 0;
    velocity.y = 0;

    double mass = 100;

    Object x(mass, location, velocity);

    for(int i = 0; i < iters; ++i)
    {
        x.updateVelocity(sun);
        x.updatePosition();
        x.draw();
    }
    
    return 0;
}