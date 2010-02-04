#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <list>

#include "light.hpp"

namespace VisionControl
{
    class Executor
    {
    public:
        Executor();

        void process(std::list<Light> &lights);

    private:
        enum State { Dead, Activation, MouseMove, Charging, Discharging, Zoom, Scroll, Volume, FFRW, Gesture };

        State currentState;
        int energy;
        int charge;

        Light *left;
        Light *right;

        // Methods abusing xdotool
        void mouseMove(int dx, int dy);
        void mouseClick();
    };
}

#endif // EXECUTOR_HPP
