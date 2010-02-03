#ifndef _GESTURE_HPP_
#define _GESTURE_HPP_

#include <list>
#include <string>

namespace VisionControl
{
    class Gesture
    {
        public:
            enum Direction { Neutral, Up, Down, Left, Right };

            std::string str();

            Gesture& operator<<(const Direction);
            Direction operator[](const int index);

            Direction last() {
                if (dirs.size() == 0) return Neutral;
                else return dirs.back();
            }

        private:
            std::list<Direction> dirs;
    };

    inline Gesture& Gesture::operator<<(const Direction d)
    {
        dirs.push_back(d);
        return *this;
    }
}

#endif
