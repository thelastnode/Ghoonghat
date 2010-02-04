#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <list>
#include <map>
#include <string>

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

        std::map<std::string, std::string> commandMap;

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

        // For gestures
        std::string gestureString;
        void loadCommandMap(const char* filename);
    };
}

#endif // EXECUTOR_HPP
