// TODO Delete:
#include <cstdio>

#include <cstdlib>
#include <sstream>

#include "executor.hpp"

using namespace std;
using namespace VisionControl;

Executor::Executor() : currentState(Dead), left(0), right(0)
{
}

void Executor::process(list<Light> &lights)
{
    // TODO Delete me
    // printf("%d\n", currentState);
    switch (currentState) {
        case Dead:
            if (lights.size() > 0) {
                currentState = Activation;
                energy = 0;
            }
            break;
        case Activation:
            if (lights.size() == 0) {
                if (left && left->distanceTraveled() == 0) {
                    mouseClick();
                }
                currentState = Dead;
                break;
            }
            if (energy < ACTIVATION_ENERGY) {
                energy++;
            } else {
                if (lights.size() == 1) {
                    currentState = MouseMove;
                } else if (lights.size() == 2) {
                    currentState = Charging;
                    charge = 0;
                }
            }
            break;
        case MouseMove:
            // only one light, arbitrarily assign to left
            if (lights.size() == 0) {
                if (left && left->distanceTraveled() == 0) {
                    mouseClick();
                }
                currentState = Dead;
                break;
            }
            left = &lights.front();
            if (left->changeInDistance() > 0) {
                mouseMove(-left->changeInPosition().x, left->changeInPosition().y);
            }
            break;
        case Charging:
            // IMMA CHARGIN MAH LAZHARZ!
            break;
        case Discharging:
            break;
        case Zoom:
            break;
        case Scroll:
            break;
        case Volume:
            break;
        case FFRW:
            break;
        case Gesture:
            break;
    }
}

void Executor::mouseMove(int dx, int dy)
{
    stringstream ss;
    ss << "xdotool mousemove_relative " << dx*MOUSE_ACCEL << " " << dy*MOUSE_ACCEL;
    const char* cmd = ss.str().c_str();
    system(cmd);
}

void Executor::mouseClick()
{
    system("xdotool mousedown 1; xdotool mouseup 1");
}
