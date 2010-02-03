#ifndef POINT_HPP
#define POINT_HPP

namespace VisionControl
{
    class Point
    {
    public:
        int x;
        int y;

        Point(const int a, const int b) : x(a), y(b) {}

        Point operator-(const Point& p) const;
    };
}

#endif // POINT_HPP
