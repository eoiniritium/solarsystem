#include "raylib.h"
#include <iostream>
#include <vector>

#include "body.hpp"
#include "logger.hpp"

const int sw = 1280;
const int sh = 720;

int main()
{
    int numBodies, fps;
    std::vector<Body> objs;
    std::vector<bodyStruct> locations; // List of all bodies location and mass for gravity calculations

    // LOGGING
    Logger log("log.txt");
    log.clearFile();
    log.writeToFile("This is the logger");

    // Settings io
    {
        std::cout << "Number of bodies in simulation: ";
        std::cin >> numBodies;
        std::cout << std::endl << "Target framerate: ";
        std::cin >> fps;
        std::cout << std::endl;
    }

    // Allocate objects
    for(int i = 0; i < numBodies; ++i)
    {
        Body n(1.0, 2.0, 60.0, 10.0, i, i * 10, i * 10, WHITE);
        objs.push_back(n);
        locations.push_back(n.outputInfo());
    }
    
    
    InitWindow(sw, sh, "Space gravity simulation");
    SetTargetFPS(fps);

    SetExitKey(KEY_ESCAPE);
    while(!WindowShouldClose())
    {
        // Variable update
        {
            for(int i = 0; i < numBodies; ++i)
            {
                objs[i].step(locations);
            }
            locations.clear(); // Empty array
            for(int i = 0; i < numBodies; ++i)
            {
                locations.push_back(objs[i].outputInfo());
            }
        }

        // Draw
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(10, 10);
            {
                for(int i = 0; i < numBodies; ++i)
                {
                    objs[i].draw();
                }
            }
            EndDrawing();
        }
    }
}