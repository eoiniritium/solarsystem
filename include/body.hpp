#pragma once

#include "raylib.h"
#include <vector>
#include <cmath>
#include "logger.hpp"

const double gravConstant = 6.7408e-11;

struct bodyStruct
{
    double mass;
    int x;
    int y;
};

class Body
{
    public:
    Body(double mass, double radius, double velocity, double heading, int id, int x, int y, Color color)
    {
        this->mass = mass;
        this->radius = radius;
        this->velocity = velocity;
        this->heading = heading;
        this->id = id;

        this->x = x;
        this->y = y;

        this->color = color;

    }
    
    bodyStruct outputInfo()
    {
        bodyStruct res;
        res.mass = mass;
        res.x = x;
        res.y = y;
        return res;
    }

    void draw()
    {
        DrawCircle(x, y, radius, color);
    }
    private:
    double calculateDistance(bodyStruct s)
    {
        double a = pow((x - s.x), 2) + pow((y-s.y), 2);
        return sqrt(a);
    }

    double calculateGravityStrength(double distance, bodyStruct s)
    {
        // g = GM/d^2
        double gm = s.mass * gravConstant;
        double d2 = distance * distance;
        return gm/d2;
    }

    double getAngle(bodyStruct s)
    {
        // atan2(y, x) for some reason they are backwards. Dont question it
        // y = yb - ya
        // x = xb - xa
        // s = b

        double y1 = s.y - y; // avoid name clashing
        double x1 = s.y - x; // avoid name clashing

        return atan2(y1, x1); // Angle to point in space
    }

    double getDeltaX(double force, double theta)
    {
        return cos(theta) * force;
    }

    double getDeltaY(double force, double theta)
    {
        return sin(theta) * force;
    }

    public:
    void step(std::vector<bodyStruct> objects)
    {
        double tx, ty;
        tx = ty = 0; // set them all to 0

        for(int i = 0; i < objects.size(); ++i)
        {
            double angle;
            double f;
            bodyStruct obj;

            obj = objects[i];
            f = calculateGravityStrength(calculateDistance(obj), obj);
            angle = getAngle(obj);

            //printf("Force %lf Angle %lf\n", f, angle);

            tx += getDeltaX(f, angle);
            ty += getDeltaY(f, angle);
        }

        x += tx * GetFrameTime();
        y += ty * GetFrameTime();
    }

    public:
    double mass;
    double radius;
    double velocity;
    double heading;
    int id;

    int x, y;

    Color color;

};

void printBodies(bodyStruct x)
{
    printf("Mass: %lf  Position: (%d, %d)\n", x.mass, x.x, x.y);
}