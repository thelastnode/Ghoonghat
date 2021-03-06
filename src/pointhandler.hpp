#ifndef POINTHANDLER_HPP
#define POINTHANDLER_HPP

#include <list>

#include "light.hpp"
#include "point.hpp"

#include "deprecated.hpp"

namespace VisionControl
{
    class PointHandler
    {
    public:
        PointHandler() {}

        PointHandler& operator<<(const Point p);
        DEPRECATED(void process());

    protected:
        std::list<Point> pointsToProcess;
        std::list<Light> lights;

        // For determining distance
        bool tooClose(Point p1, Point p2, int threshold);

       // For removing Lights
       static bool noHealth(const Light& l);
    };
}

#endif // POINTHANDLER_HPP
