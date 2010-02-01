#include "light.hpp"

using namespace VisionControl;

Light::Light(int x0, int y0) : handedness(Unknown), current(x0, y0), change(0, 0), gestureRecognizer(current)
{
}
