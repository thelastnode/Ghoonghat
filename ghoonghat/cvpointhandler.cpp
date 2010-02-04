#include <cstdlib>
#include <list>
#include <set>

#include "cvpointhandler.hpp"

using namespace std;
using namespace VisionControl;

CvPointHandler::CvPointHandler() : PointHandler()
{
}

Point CvPointHandler::calcMidpoint(Point a, Point b)
{
    return Point((a.x + b.x)/2, (a.y + b.y)/2);
}

void CvPointHandler::process(IplImage *frame)
{
    list<Point> unglobbed;

    for (list<Point>::const_iterator it = pointsToProcess.begin(); it != pointsToProcess.end(); it++)
    {
        Point current = *it;
        bool isTooClose = false;
        for (list<Point>::const_iterator it2 = unglobbed.begin(); it2 != unglobbed.end(); it2++) {
            if (tooClose(current, *it2, POINT_DIST_THRESHOLD)) {
                isTooClose = true;
                break;
            }
        }
        if (!isTooClose) {
            unglobbed.push_back(current);
        }
    }
    pointsToProcess.clear();

    set<Light*> decrement;

    // Add all lights to the set to decrement initially , then remove from set
    for (list<Light>::iterator it = lights.begin(); it != lights.end(); it++) {
        decrement.insert(&*it);
    }

    for (list<Point>::const_iterator unglobbedIterator = unglobbed.begin(); unglobbedIterator != unglobbed.end(); unglobbedIterator++) {
        list<Light>::iterator lightIterator;
        for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
            Point midpoint = calcMidpoint(*unglobbedIterator, (*lightIterator).position());
            int r = 0, g = 0, b = 0;
            for (int y = midpoint.y-MIDPOINT_CHECK_RADIUS; y <= midpoint.y+MIDPOINT_CHECK_RADIUS; y+=MIDPOINT_CHECK_STEP) {
                uchar* ptr = (uchar*) (frame->imageData + y * frame->widthStep);
                for (int x = midpoint.x-MIDPOINT_CHECK_RADIUS; x <= midpoint.x+MIDPOINT_CHECK_RADIUS; x+=MIDPOINT_CHECK_STEP) {
                    if (x < 0 || y < 0 || x >= CAM_WIDTH || y >= CAM_HEIGHT) {
                        continue;
                    }
                    r += ptr[3*x+0];
                    g += ptr[3*x+1];
                    b += ptr[3*x+2];
                }
            }

            // "too close" to be considered a unique point... yea, that's a bit of stretch on the function name...
            //if (tooClose(*unglobbedIterator, (*lightIterator).position(), LIGHT_DIST_THRESHOLD)) {
            if (r > MIDPOINT_COLOR_THRESHOLD*MIDPOINT_NUM_POINT_CHECK
                || g > MIDPOINT_COLOR_THRESHOLD*MIDPOINT_NUM_POINT_CHECK
                || b > MIDPOINT_COLOR_THRESHOLD*MIDPOINT_NUM_POINT_CHECK) {
                    if (decrement.find(&*lightIterator) != decrement.end()) {
                        (*lightIterator) << (*unglobbedIterator);
                        decrement.erase(&*lightIterator);
                    }
                break;
            }
        }
        if (lightIterator == lights.end() && lights.size() < 2) {
             // Didn't get assigned to a light AND < 2 lights in existence
             Point p = *unglobbedIterator;
             lights.push_back(Light(p.x, p.y));
        }
    }
    for (set<Light*>::iterator it = decrement.begin(); it != decrement.end(); it++) {
        (**it)--;
    }
    lights.remove_if(noHealth);

    executor.process(lights);
}
