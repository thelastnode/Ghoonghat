#include "point.hpp"

using namespace VisionControl;

Point Point::operator-(const Point& p) const
{
    return Point(this->x - p.x, this->y - p.y);
}
