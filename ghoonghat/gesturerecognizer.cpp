#include <cstdlib>

#include "gesturerecognizer.hpp"
#include "constants.hpp"

using namespace VisionControl;

GestureRecognizer& GestureRecognizer::operator<<(const Point p) {
    int dx = p.x - lastPoint.x;
    int dy = p.y - lastPoint.y;

    if (abs(dx) < GEST_DIST_THRESHOLD && abs(dy) < GEST_DIST_THRESHOLD) {
        return (*this);
    }


    Gesture::Direction dir = changeToDir(dx, dy);

    lastPoint = p;
    if (dir != gesture.last()) {
        gesture << dir;
    }
    return (*this);
}

Gesture::Direction GestureRecognizer::changeToDir(const int dx, const int dy) {

    if (abs(dy) > abs(dx)) {
        // Up or Down
        if (dy > 0) {
            return Gesture::Down;
        } else {
            return Gesture::Up;
        }
    } else {
        // Left or right
        if (dx > 0) {
            return Gesture::Left;
        } else {
            return Gesture::Right;
        }
    }
}
