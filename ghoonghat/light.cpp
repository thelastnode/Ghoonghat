#include "constants.hpp"
#include "light.hpp"

using namespace VisionControl;

Light::Light(int x0, int y0) : handedness(Unknown), currentPosition(x0, y0), dPosition(0, 0), gestureRecognizer(currentPosition), distance(0), hp(MAX_HP)
{
}

Light::Light(Point p) : handedness(Unknown), currentPosition(p.x, p.y), dPosition(0, 0), gestureRecognizer(currentPosition), distance(0), hp(MAX_HP)
{
}

void Light::operator<<(const Point p)
{
    /*
    dPosition = currentPosition - p;
    gestureRecognizer << p;
    currentPosition = p;
    distance += dPosition.x + dPosition.y;
    */
    // return (*this);
}
