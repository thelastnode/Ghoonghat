#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "point.hpp"
#include "gesturerecognizer.hpp"

namespace VisionControl
{
    class Light
    {
    public:
        Light(int x0, int y0);

        void clearGesture();

        enum Handedness { Unknown, Left, Right };
        Handedness handedness;

    private:
        Point current;
        Point change;
        GestureRecognizer gestureRecognizer;
        int distance;
        int hp;
    };

}

#endif // LIGHT_HPP
