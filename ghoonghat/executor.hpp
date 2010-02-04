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
        enum State { Dead, MouseMove, Charging, Discharging, FFRW, Gesture };

        State currentState;
        int charge;

        Light *left;
        Light *right;

        bool hasMoved;
        bool hasMouseMoved;

        void determineHandedness(std::list<Light> &lights);

        // Methods abusing xdotool
        void mouseMove(int dx, int dy);

        enum MouseButton { Left, Right };
        void mouseClick(MouseButton button);

        enum VolumeChange { Louder, Softer };
        void volume(VolumeChange change);

        enum MediaFunction { FF, RW, PlayPause };
        void mediaControl(MediaFunction func);

        enum ZoomControl { In, Out };
        void zoom(ZoomControl dir);

        enum ScrollControl { Up, Down };
        void scroll(ScrollControl dir);
    };
}

#endif // EXECUTOR_HPP
