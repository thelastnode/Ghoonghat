// TODO Better Error Handling
#include <iostream>


#include <cstdlib>
#include <fstream>
#include <sstream>

#include "executor.hpp"

using namespace std;
using namespace VisionControl;

Executor::Executor() : currentState(Dead), left(0), right(0), hasMoved(false), hasMouseMoved(false)
{
    loadCommandMap(GESTURE_CONFIG_FILE);
}

void Executor::process(list<Light> &lights)
{
    switch (currentState) {
        case Dead:
            hasMoved = false;
            hasMouseMoved = false;
            if (lights.size() == 1) {
                currentState = MouseMove;
            } else if (lights.size() == 2) {
                currentState = Charging;
                charge = 0;
            }
            break;
        case MouseMove:
            // only one light, arbitrarily assign to left
            if (lights.size() == 0) {
                if (!hasMouseMoved && !hasMoved) {
                    mouseClick(Left);
                }
                currentState = Dead;
            }
            if (lights.size() == 2) {
                currentState = Charging;
                charge = 0;
            }
            if (lights.size() == 1) {
                left = &lights.front();
                if (left->changeInDistance() > 0) {
                    mouseMove(-left->changeInPosition().x, left->changeInPosition().y);
                    hasMouseMoved = true;
                }
            }
            break;
        case Charging:
            // IMMA CHARGIN MAH LAZHARZ!
            if (lights.size() == 0) {
                currentState = Dead;
            }
            if (lights.size() == 1) {
                currentState = Discharging;
                charge = REQUIRED_DISCHARGE;
            }
            if (lights.size() == 2) {
                if (charge >= REQUIRED_CHARGE) {
                    // Determine handedness before doing anything
                    if (lights.front().handedness == Light::Unknown || lights.back().handedness == Light::Unknown) {
                        determineHandedness(lights);
                    }

                    // YOU ARE HERE.
                    if (left->gesture().last() == right->gesture().last()) {
                        // Volume and Media Control
                        if (left->gesture().last() == Gesture::Up) {
                            volume(Louder);
                        } else if (left->gesture().last() == Gesture::Down) {
                            volume(Softer);
                        } else {
                            if (left->gesture().last() == Gesture::Left) {
                                mediaControl(RW);
                            } else if (left->gesture().last() == Gesture::Right) {
                                mediaControl(FF);
                            }
                            currentState = FFRW;
                        }
                    }

                    // Zooming
                    if (left->gesture().last() == Gesture::Left && right->gesture().last() == Gesture::Right) {
                        zoom(In);
                    } else if (left->gesture().last() == Gesture::Right && right->gesture().last() == Gesture::Left) {
                        zoom(Out);
                    }

                    // Scrolling
                    if (left->gesture().last() == Gesture::Up && right->gesture().last() == Gesture::Neutral) {
                        scroll(Up);
                    } else if (left->gesture().last() == Gesture::Down && right->gesture().last() == Gesture::Neutral) {
                        scroll(Down);
                    }

                    // Gestures
                    if (left->gesture().last() == Gesture::Neutral && right->gesture().last() != Gesture::Neutral) {
                        currentState = Gesture;
                    }

                    charge = 0;
                    hasMoved = true;
                } else {
                    charge += lights.front().changeInDistance();
                    charge += lights.back().changeInDistance();
                }
            }
            break;
        case Discharging:
            if (lights.size() == 0) {
                if (!hasMoved && !hasMouseMoved) {
                    mediaControl(PlayPause);
                }
                currentState = Dead;
            }
            if (lights.size() == 1) {
                if (charge > 0) {
                    charge--;
                } else {
                    if (!hasMoved) {
                        mouseClick(Right);
                    }
                    currentState = Dead;
                }
            }
            if (lights.size() == 2) {
                currentState = Charging;
                charge = 0;
            }
            break;
        case FFRW:
            if (lights.size() == 0) {
                currentState = Dead;
            }
            if (lights.size() == 1) {
                currentState = MouseMove;
            }
            break;
        case Gesture:
            hasMoved = true;
            if (lights.size() == 2) {
                gestureString = right->gesture().str();
            }
            if (lights.size() < 2) {
                printf("BEFORE\n");
                const char * const cmd = commandMap[gestureString].c_str();
                printf("NOT BEFORE\n");
                printf("GEST: %s, EXECUTING: %s\n", gestureString.c_str(),cmd);
                system(cmd);
                currentState = Dead;
            }
            break;
    }
}

void Executor::determineHandedness(list<Light> &light)
{
    Light *first = &light.front();
    Light *second = &light.back();
    if (first->position().x > second->position().x) {
        first->handedness = Light::Left;
        left = first;
        second->handedness = Light::Right;
        right = second;
    } else {
        first->handedness = Light::Right;
        right = first;
        second->handedness = Light::Left;
        left = second;
    }
}

void Executor::mouseMove(int dx, int dy)
{
    stringstream ss;
    ss << "xdotool mousemove_relative " << dx*MOUSE_ACCEL << " " << dy*MOUSE_ACCEL;
    const char* cmd = ss.str().c_str();
    system(cmd);
}

void Executor::mouseClick(MouseButton button)
{
    if (button == Left) {
        system("xdotool mousedown 1; xdotool mouseup 1");
    } else if (button == Right) {
        system("xdotool mousedown 3; xdotool mouseup 3");
    }
}

void Executor::volume(VolumeChange change) {
    if (change == Louder) {
        system("xdotool keydown XF86AudioRaiseVolume; xdotool keyup XF86AudioRaiseVolume");
    } else  if (change == Softer) {
        system("xdotool keydown XF86AudioLowerVolume; xdotool keyup XF86AudioLowerVolume");
    }
}

void Executor::mediaControl(MediaFunction func)
{
    switch (func) {
        case FF:
            system("xdotool keydown XF86AudioNext; xdotool keyup XF86AudioNext");
            break;
        case RW:
            system("xdotool keydown XF86AudioPrev; xdotool keyup XF86AudioPrev");
            break;
        case PlayPause:
            system("xdotool keydown XF86AudioPlay; xdotool keyup XF86AudioPlay");
            break;
    }
}

void Executor::zoom(ZoomControl dir)
{
    switch (dir) {
        case In:
            system("xdotool keydown Super; xdotool mousedown 4; xdotool mouseup 4; xdotool keyup Super");
            break;
        case Out:
            system("xdotool keydown Super; xdotool mousedown 5; xdotool mouseup 5; xdotool keyup Super");
            break;
    }
}

void Executor::scroll(ScrollControl dir)
{
    switch (dir) {
        case Up:
            system("xdotool mousedown 4; xdotool mouseup 4");
            break;
        case Down:
            system("xdotool mousedown 5; xdotool mouseup 5");
            break;
    }
}

void Executor::loadCommandMap(const char* filename) {
     string line;
     ifstream file(filename);

     if (file.is_open()) {
          while (!file.eof()) {
               getline(file, line);
               string gest  = line.substr(0, line.find(":"));
               string cmd = line.substr(line.find(":") + 1);
               commandMap[gest] = cmd;
          }
          file.close();
     } else {
          cerr << "Unable to open config!\n";
     }
}

