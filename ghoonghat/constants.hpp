#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace VisionControl
{
    // Distance until gesture activates
    const int GEST_DIST_THRESHOLD = 50;

    // Distance until a point is considered distinct from another
    const int POINT_DIST_THRESHOLD = 20;

    // Distance until a light is considered a different light
    const int LIGHT_DIST_THRESHOLD = 50;

    // Minimum R, G and B values to consider for a point
    const int COLOR_THRESHOLD = 160;

    // Starting HP (health points) of a Light
    const int MAX_HP = 5;
}

#endif // CONSTANTS_HPP
