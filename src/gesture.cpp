#include "gesture.hpp"

using namespace VisionControl;

std::string Gesture::str()
{
    std::string s;
    for (std::list<Direction>::const_iterator it = dirs.begin(); it != dirs.end(); it++) {
        char c;
        switch(*it) {
            case Up:
                c = 'U';
                break;
            case Down:
                c = 'D';
                break;
            case Left:
                c = 'L';
                break;
            case Right:
                c = 'R';
                break;
                        case Neutral:
                                // Stop compiler warnings
                                break;
        }
        s.push_back(c);
    }
    if (s.size() == 0) {
        s.push_back('N');
    }
    return s;
}

Gesture::Direction Gesture::operator[](const int index)
{
    if (dirs.size() == 0 && index == 0) {
        return Neutral;
    }
    int i = 0;
    for (std::list<Direction>::const_iterator it = dirs.begin(); it != dirs.end(); it++) {
        if (i == index) {
            return *it;
        }
        i++;
    }
    return Neutral;
}

