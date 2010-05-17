# Ghoonghat

## Introduction
Ghoonghat is a gesture-based computer control system using computer vision. Ghoonghat was designed to be used with a webcam with an infrared-only filter (I use the inside of a floppy disk for this) and two infrared light sources (I use bright red LEDs which overflow into the infrared spectrum for this). In theory, this could probably also work in a very dark room with a pair of flashlights, the input essentially has to be light points on a black background (though some noise is acceptable). The application expects between zero to two points on the screen at any time, and ignores any additional points.

Currently, the execution of commands is handled through the `Executor` class. At the moment, it's fairly hacked together (system calls galore!), but it works.

The code is modular, so the components can be used for different applications without much change.

## Installation

After installing the OpenCV development libraries, simply run `make` in this directory. For the current `Executor` class, system calls to `xdotool` and `xsendkeycode` are made, so those two tools will be necessary as well if you do not modify the `Executor`.

On Ubuntu, these packages are:
* libcv-dev
* libcvaux-dev
* libhighgui-dev
* xdotool
* lineakd

They can be installed conveniently through the command:
`sudo apt-get install libcv-dev libcvaux-dev libhighgui-dev xdotool lineakd`


## Usage

The current set of commands can be seen in the Executor class.

Since I use LEDs mounted on gloves, I will use "hands" to describe lights. In summary:

* Single hand moves the mouse, single hand on then off clicks the mouse (similar to a touchpad)
* Turning the second hand on then off while using the mouse control right clicks
* Pinching in and out runs Super + MouseWheel in or out (zoom in compiz)
* Both hands up or down runs volume up or down (through X volume up/down)
* Both hands left or right skips backwards or forwards (media controls through X)
* Holding the right hand still and moving the left hand up or down scrolls the mouse wheel
* Holding the left hand still while moving the right hand engages gesture mode, which runs the gestures in the `gestures.cfg` file. The format is `chain of movements:command to run`. Valid movements are `U`[p] `D`[own] `L`[eft] `R`[ight]; see the provided gestures.cfg file for examples.

The entire execution framework can be seen and modified in the `Executor` class.

## Author

Ghoonghat was written by Ankit Shankar (ankitshankar+gh@gmail.com) with the help of Aaron Fan (aaron.y.fan+gh@gmail.com).

## License

See LICENSE.
