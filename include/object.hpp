#pragma once
#include <iostream>
#include <math.h>
#include "logger.hpp"

typedef struct
{
    double x;
    double y;
} loc;

typedef struct
{
    loc point;
    double mass;
} obj;

class Object
{   private:
    double mass;
    loc location;
    loc velocity;
    
    
    public:
    Object(double mass, loc location, loc initialVelocity)
    {
        this->mass = mass;
        this->location = location;
        this->velocity = initialVelocity;
    }

    void updateVelocity(obj other)
    {
        double DTOO = distanceToObject(this->location, other.point);
        double force = forceGravity(this->mass, other.mass, DTOO);
        double accel = acceleration(force, this->mass);
        double angle = angleToObject(this->location, other.point);
        double thta = theta(angle);
        loc delta = xySpeed(accel, thta);
        delta = sign(delta, angle);

        // Delta is change in velocity needed
        velocity.x += delta.x;
        velocity.y += delta.y;
    }

    void updatePosition()
    {
        location.x += velocity.x;
        location.y += velocity.y;
    }

    void draw()
    {
        printf("X: %f Y: %f\n", location.x, location.y);
    }

    private:
    double distanceToObject(loc a, loc b) // PASS
    {
        double res;
        double dx = fabs(a.x - b.x); // Fabs is float abs
        double dy = fabs(a.y - b.y);

        res = sqrt(dx * dx + dy * dy);

        return res;
    }

    double forceGravity(double m1, double m2, double distance) // PASS
    {

        const double G = 6.67408e-11;
        double force;

        force = m1 * m2;
        force = force / (distance * distance);

        force = force * G;

        return force;
    }

    double acceleration(double force, double mass) // PASS
    {
        double res = force / mass;
        return res;
    }

    double radToDegrees(double radians) // PASS
    {
        double res = radians * (180 / 3.14);
        return res;
    }

    double angleToObject(loc a, loc b) // PASS
    {
        double k1, k2, k3;

        k1 = a.y - b.y;
        k2 = a.x - b.x;

        k3 = radToDegrees(atan2(k1, k2)) + 180;
        k3 = std::fmod(k3, 360);

        return k3;
    }

    double theta(double angle) // PASS
    {
        double res = std::fmod(angle, 90);
        return res;
    }

    loc xySpeed(double acceleration, double theta) // PASS
    {
        loc res;

        res.x = sin(theta) * acceleration;
        res.y = cos(theta) * acceleration;

        return res;
    }

    loc sign(loc dxy, double angle) // PASS I THINK
    {
        loc res;
        if(angle > 0 && angle < 90) 
        {
            return dxy;
        }
        else if(angle > 90 && angle < 180)
        {
            res.x = -dxy.x;
            res.y = dxy.y;
        }
        else if(angle > 180 && angle < 270)
        {
            res.x = -dxy.x;
            res.y = -dxy.y;
        }
        else if(angle > 180 && angle < 360)
        {
            res.x = +dxy.x;
            res.y = -dxy.y;
        }

        if(angle == 90 || angle == 270)
        {
            res.x = 0;
        }
        else if(angle == 0 || angle == 180)
        {
            res.y = 0;
        }

        return res;
    }
};