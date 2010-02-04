#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace VisionControl
{
    const int CAM_WIDTH  = 640;
    const int CAM_HEIGHT = 480;

    // Distance until gesture activates
    const int GEST_DIST_THRESHOLD = 50;

    // Distance until a point is considered distinct from another
    const int POINT_DIST_THRESHOLD = 20;

    // Distance until a light is considered a different light
    const int LIGHT_DIST_THRESHOLD = 50; // 100;

    // Minimum movement required to add to distance
    const int JITTER_THRESHOLD = 10;

    // Minimum R, G and B values to consider for a point
    const int COLOR_THRESHOLD = 130;

    // Minimum R, G and B values to consider in a midpoint for a continous glob
    const int MIDPOINT_COLOR_THRESHOLD = 130;

    // Number of points to the left and right of the midpoint to check
    const int MIDPOINT_CHECK_RADIUS = 4;

    const int MIDPOINT_CHECK_STEP = 2;

    // Number of points checked around the midpoint
    const int MIDPOINT_NUM_POINT_CHECK = ((2*MIDPOINT_CHECK_RADIUS)/MIDPOINT_CHECK_STEP+1)<<2;

    // Starting HP (health points) of a Light
    const int MAX_HP = 5;

    // Multiplier for mouse acceleration
    const int MOUSE_ACCEL = 3;

    // State machine constants:

    // Required activation energy
    const int ACTIVATION_ENERGY = 3;
}

#endif // CONSTANTS_HPP
