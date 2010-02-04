#include <cstdio>
#include <cstdlib>
#include <list>
#include <set>

#include "cvpointhandler.hpp"

//TODO remove debug imports
#include <opencv/highgui.h>
#include <sstream>

using namespace std;
using namespace VisionControl;

CvPointHandler::CvPointHandler() : PointHandler(), debugfilename(0)
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
            for (int y = midpoint.y-4; y < midpoint.y+4; y+=2) {
                uchar* ptr = (uchar*) (frame->imageData + y * frame->widthStep);
                for (int x = midpoint.x-4; x < midpoint.x+4; x+=2) {
                    r += ptr[3*x+0];
                    g += ptr[3*x+1];
                    b += ptr[3*x+2];
                }
            }

            printf("midpoint rgb:(%d, %d, %d)\n", r/25, g/25, b/25);

            // "too close" to be considered a unique point... yea, that's a bit of stretch on the function name...
            //if (tooClose(*unglobbedIterator, (*lightIterator).position(), LIGHT_DIST_THRESHOLD)) {
            if (r > MIDPOINT_COLOR_THRESHOLD*25 || g > MIDPOINT_COLOR_THRESHOLD*25 || b > MIDPOINT_COLOR_THRESHOLD*25) {
                (*lightIterator) << (*unglobbedIterator);
                decrement.erase(&*lightIterator);
                break;
            }
        }
        if (lightIterator == lights.end()) {
             // Didn't get assigned to a light
             Point p = *unglobbedIterator;
             lights.push_back(Light(p.x, p.y));
        }
    }
    for (set<Light*>::iterator it = decrement.begin(); it != decrement.end(); it++) {
        (**it)--;
    }
    lights.remove_if(noHealth);
    // TODO handle lights
    int i = 0;
    for (list<Light>::iterator it = lights.begin(); it != lights.end(); it++) {
        Light l = *it;
        printf("Light %d - Position: (%d, %d), dPosition: (%d, %d), Distance: %d\n", i,
            l.position().x, l.position().y,
            l.changeInPosition().x, l.changeInPosition().y, l.distanceTraveled());
        i++;
    }
    stringstream ss;
    //debug print frame if crap happens
    if (i>1){
        ss<<"output"<<debugfilename<<".jpg";
        debugfilename++;
        cvSaveImage(ss.str().c_str(),frame);
    }
}
