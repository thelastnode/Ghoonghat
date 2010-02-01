#ifndef _GESTURERECOGNIZER_HPP_
#define _GESTURERECOGNIZER_HPP_

#include "gesture.hpp"
#include "point.hpp"

class GestureRecognizer
{
    public:
        Gesture getGesture() { return gesture; }

        GestureRecognizer& operator<<(const Point p);

        GestureRecognizer(const Point p) : lastPoint(p) {}

    private:
        Gesture gesture;
        Point lastPoint;

        static Gesture::Direction changeToDir(const int dx, const int dy);

        static const int DIST_THRESHOLD = 50;
};

#endif
