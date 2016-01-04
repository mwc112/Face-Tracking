#include <iostream>
#include <stdio.h>
#include <time.h>

#include<dlib/dlib/opencv.h>

#include "Win.h"
#include "Settings.h"
#include "VideoManager.h"

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
    Settings* settings = Settings::getInstance();

    VideoManager vm;
    settings->addVideoObserver(&vm);
   
    FeatureTracker featureTracker;

    HeadTracker headTracker;
    //wm w_manager;
    
    Win win;   
    
    Mat frame;

    while (!win.is_closed()) {
        try {
            frame = vm.getFrame();
            Face face = featureTracker.getFeatures(frame);
            drawFaceOnFrame(frame, face);
            Direction dir = headTracker.getDirection(face);
            dlib::cv_image<dlib::bgr_pixel> dlib_frame(frame);
            win.image.set_image(dlib_frame);
            if (settings->getTrackingState()){
              //w_manager.set_focus_screen((wm::Direction)dir);
              cout << directionName(dir) << endl;
            }
        } catch (const char * e) {
            dlib::cv_image<dlib::bgr_pixel> dlib_frame(frame);
            win.image.set_image(dlib_frame);
            //cout << e << endl;
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
    return "unknown";
}

