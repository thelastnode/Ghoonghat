#ifndef CVPOINTHANDLER_HPP
#define CVPOINTHANDLER_HPP

#include <opencv/cv.h>

#include "pointhandler.hpp"

namespace VisionControl
{
    class CvPointHandler : public PointHandler
    {
    public:
        CvPointHandler();

        void process(IplImage* frame);

        //TODO: remove debug
        int debugfilename;

    protected:
        Point calcMidpoint(Point a, Point b);
    };
}

#endif // CVPOINTHANDLER_HPP
