#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"
#include "HeadTracker.h"
#include "CameraInput.h"
#include "wm.h"


using namespace std;
using namespace cv;

string directionName(Direction dir);

int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker((Features) (Eyes | Nose));
    HeadTracker headTracker;
    wm *w_manager = new wm();
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    
    Mat frame;
    while (true) {
        try {
            frame = ci.getFrame();
            Face face = featureTracker.getFeatures(frame);
            face.drawOnFrame(frame);
            Direction dir = headTracker.getDirection(face);
            w_manager->set_focus_screen((wm::Direction)dir);
            cout << directionName(dir) << endl;
            imshow("Demo", frame);
            waitKey(20);
        } catch (const char * e) {
            imshow("Demo", frame);
            waitKey(20);
        }
    };
    return 0;
}




string directionName(Direction dir) {
    switch (dir) {
        case Left: return "left";
        case Right: return "right";
        case Middle: return "middle";
        case Unknown: return "unknown";
    }
}

