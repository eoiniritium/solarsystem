#include <iostream>
#include "object.hpp"
#include "raylib.h"

int main()
{

    obj sun;
    sun.point.x = 250;
    sun.point.y = 250;
    sun.mass = 1000; //1,000,000

    loc location;
    location.x = 400;
    location.y = 100;

    loc velocity;
    velocity.x = 0.000003;
    velocity.y = 0.000003;

    double mass = 10;

    Object x(mass, location, velocity, 5, WHITE);
    Object y(sun.mass, sun.point, (loc){0, 0}, 5, YELLOW);




    // GRAPHICS
    const int sw = 1280;
    const int sh = 720;    
    int fps;


    printf("Target FPS: ");
    std::cin >> fps;

    InitWindow(sw, sh, "Gravity");
    SetTargetFPS(fps);

    while(!WindowShouldClose())
    {
        {
            x.updateVelocity(sun);
            x.updatePosition(100000);
        }
        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(10, 10);
            {
                x.draw();
                DrawCircle(sun.point.x, sun.point.y, 1, YELLOW);
            }
        EndDrawing();
    }


    return 0;
}