#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"
#include "HeadTracker.h"
#include "CameraInput.h"



using namespace std;
using namespace cv;

const Scalar NOSE_COLOR = Scalar(255, 225, 255);
const Scalar LEFT_EYE_COLOR = Scalar(255, 225, 0);
const Scalar RIGHT_EYE_COLOR = Scalar(0, 225, 255);
const Scalar FACE_COLOR = Scalar(0,0,255);
const Scalar EYE_REGION_COLOR = Scalar(255,0,0);
const Scalar NOSE_REGION_COLOR = Scalar(155,0,0);


string directionName(Direction dir);


void drawFaceOnFrame(Mat frame, Face face) {
    rectangle(frame, face.nose, NOSE_COLOR);
    rectangle(frame, face.rightEye, RIGHT_EYE_COLOR);
    rectangle(frame, face.leftEye, LEFT_EYE_COLOR);
    rectangle(frame, face.face, FACE_COLOR);
}


int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker((Features) (Eyes | Nose));
    HeadTracker headTracker;

    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    
    while(1){
        try {
            
            Mat frame = ci.getFrame();
            Face face = featureTracker.getFeatures(frame);
            drawFaceOnFrame(frame, face);
            imshow("Demo", frame); //show the frame
            waitKey(20);
            Direction dir = headTracker.getDirection(face);
            cout << directionName(dir) << endl;
        } catch (const char * e) {
//            cout << e << endl;
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
/*
 lO is leftOverlap
 rO is rightOverlap
 
 +-----------+     +-----------+
 |           |     |           |
 |  leftEye  |     |  rightEye |
 +-----------+     +-----------+
        <-lO->     <-rO->
        +---------------+
        |     nose      |
        +---------------+
 */

