#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace VisionControl
{
    // Distance until gesture activates
    const int GEST_DIST_THRESHOLD = 50;

    // Distance until a point is considered distinct from another
    const int POINT_DIST_THRESHOLD = 20;

    // Distance until a light is considered a different light
    const int LIGHT_DIST_THRESHOLD = 100;

    // Minimum movement required to add to distance
    const int JITTER_THRESHOLD = 10;

    // Minimum R, G and B values to consider for a point
    const int COLOR_THRESHOLD = 130;

    // Minimum R, G and B values to consider in a midpoint for a continous glob
    const int MIDPOINT_COLOR_THRESHOLD = 20;

    // Starting HP (health points) of a Light
    const int MAX_HP = 5;
}

#endif // CONSTANTS_HPP
