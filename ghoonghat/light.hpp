#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "constants.hpp"
#include "point.hpp"
#include "gesturerecognizer.hpp"

namespace VisionControl
{
    class Light
    {
    public:
        Light(int x0, int y0);
        Light(Point p);

        void clearGesture();

        enum Handedness { Unknown, Left, Right };
        Handedness handedness;

        Light& operator<<(const Point p);
        void operator--(int /* post */) { hp--; }
        void operator++(int /* post */) { hp = MAX_HP; }

        Point position() const { return currentPosition; }
        Point changeInPosition() const { return dPosition; }
        int health() const { return hp; }
        int distanceTraveled() const { return distance; }


    private:
        Point currentPosition;
        Point dPosition;
        GestureRecognizer gestureRecognizer;
        int distance;
        int hp;
    };

}

#endif // LIGHT_HPP
