#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "point.hpp"
#include "cvpointhandler.hpp"

#include "constants.hpp"

using namespace std;
using namespace VisionControl;

//TODO: use COLOR_THRESHOLD
int THRESHOLD = 160;

CvPointHandler ph;

void handleFrame(IplImage* frame) {
    for (int y = 0; y < frame->height; y++) {
        uchar* ptr = (uchar*) (frame->imageData + y * frame->widthStep);
        for (int x = 0; x < frame->width; x++) {
            int r = ptr[3*x+0];
            int g = ptr[3*x+1];
            int b = ptr[3*x+2];
            if (r > THRESHOLD && g > THRESHOLD && b > THRESHOLD) {
                ph << Point(x, y);
            }
        }
    }
    ph.process(frame);
}

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 2) {
        cerr << "Usage: " << argv[0] << " [config file]\n";
        return 1;
    }
    CvCapture *cap = cvCaptureFromCAM(0);
    if (cap == 0) {
        cerr << "Error opening camera!\n";
        return 2;
    }
    cvNamedWindow("Cam", CV_WINDOW_AUTOSIZE);

    for (;;) {
        IplImage *frame = cvQueryFrame(cap);
        IplImage *out = cvCreateImage(cvGetSize(frame), frame->depth,
                frame->nChannels);
        cvCvtColor(frame, out, CV_RGB2BGR);
        handleFrame(out);
        cvShowImage("Cam", out);
        cvReleaseImage(&out);
        char key = cvWaitKey(2);
        if (key == 27) break;
        if (key == 'w') { THRESHOLD++; printf("THRESHOLD: %d\n", THRESHOLD); }
        if (key == 's') { THRESHOLD--; printf("THRESHOLD: %d\n", THRESHOLD); }
    }
    cvReleaseCapture(&cap);
    cvDestroyWindow("Cam");
    return 0;
}
