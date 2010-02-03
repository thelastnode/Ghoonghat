#include <cstdio>
#include <cstdlib>
#include <list>
#include <set>

#include "constants.hpp"
#include "pointhandler.hpp"

using namespace std;
using namespace VisionControl;

PointHandler& PointHandler::operator<<(const Point p)
{
    pointsToProcess.push_back(p);
    return (*this);
}

inline bool PointHandler::tooClose(const Point p1, const Point p2, const int threshold)
{
    return ((abs(p2.x - p1.x) + abs(p2.y - p1.y)) < threshold);
}

bool PointHandler::noHealth(const Light& l) 
{
	return (l.health() == 0);
}

void PointHandler::process()
{
    if (pointsToProcess.size() == 0) {
        return;
    }

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

    for (list<Point>::const_iterator it = unglobbed.begin(); it != unglobbed.end(); it++) {
        list<Light>::iterator it2;
        for (it2 = lights.begin(); it2 != lights.end(); it2++) {
            // "too close" to be considered a unique point... yea, that's a bit of stretch on the function name...
            if (tooClose(*it, (*it2).position(), LIGHT_DIST_THRESHOLD)) {
                (*it2) << (*it);
                decrement.erase(&*it2);
                break;
            }
        }
        if (it2 == lights.end()) {
             // Didn't get assigned to a light
             Point p = *it;
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
        /*
        printf("Light %d - Position: (%d, %d), dPosition: (%d, %d)\n", i,
            l.position().x, l.position().y,
        l.changeInPosition().x, l.changeInPosition.y);
        */
        printf("Light %d - Position: (%d, %d)\n", i,
            l.position().x, l.position().y);
        i++;
    }
}
