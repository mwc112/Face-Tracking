#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"
#include "HeadTracker.h"
#include "CameraInput.h"
#include "wm.h"
#include <csignal>

using namespace std;
using namespace cv;

string directionName(Direction dir);

void drawFaceOnFrame(Mat frame, Face face) {
    auto radius = 5;
    for (int i = 0; i < face.landmarks.size(); i++){
        try { circle(frame, face.landmarks[i], radius, YELLOW_COLOR, -1); } catch (...){}
        try { putText(frame, to_string(i), face.landmarks[i], FONT_HERSHEY_SIMPLEX, 0.5, CYAN_COLOR); } catch (...){}
    }
    rectangle(frame, face.face, RED_COLOR);
}



void signalHandler(int signum) {
    exit(signum);
}



int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);  
    CameraInput ci;
    FeatureTracker featureTracker;
    HeadTracker headTracker;
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    //wm w_manager;
    
    Mat frame;
    while (true) {
        try {
            frame = ci.getFrame();
            Face face = featureTracker.getFeatures(frame);
            drawFaceOnFrame(frame, face);
            Direction dir = headTracker.getDirection(face);
            //w_manager.set_focus_screen((wm::Direction)dir);
            cout << directionName(dir) << endl;
            imshow("Demo", frame);
            waitKey(1);
        } catch (const char * e) {
            //cout << e << endl;
            imshow("Demo", frame); //show the frame
            waitKey(1);
        } catch (NoInput e) {
            cout << "No Camera detected, exiting.." << endl;
            exit(0);
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
    throw "lol";
}

