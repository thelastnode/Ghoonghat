#include <cstdlib>

#include "constants.hpp"
#include "light.hpp"

using namespace VisionControl;

Light::Light(int x0, int y0) : handedness(Unknown), currentPosition(x0, y0), dPosition(0, 0), gestureRecognizer(currentPosition), distance(0), hp(MAX_HP)
{
}

Light::Light(Point p) : handedness(Unknown), currentPosition(p.x, p.y), dPosition(0, 0), gestureRecognizer(currentPosition), distance(0), hp(MAX_HP)
{
}

Light& Light::operator<<(const Point p)
{
    dPosition = p - currentPosition;
    gestureRecognizer << p;
    currentPosition = p;
    int d = abs(dPosition.x) + abs(dPosition.y);
    if (d > JITTER_THRESHOLD) {
        distance += d;
    }
    return (*this);
}

int Light::changeInDistance() const
{
    int d = abs(dPosition.x) + abs(dPosition.y);
    if (d > JITTER_THRESHOLD) {
        return d;
    }
    return 0;
}
