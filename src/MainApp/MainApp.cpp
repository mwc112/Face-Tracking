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

class FeatureAverager {
public:
    Face getFeatures(Face newestFace);
private:
    Face previousFace;
};


Face FeatureAverager::getFeatures(Face newestFace) {
    return newestFace;
}



Point centerOfRect(Rect rect) {
    if (rect.area() == 0) {
        throw "no rect";
    }
    Size halfSize = Size(rect.size().width/2, rect.size().height/2);
    return Point(rect.tl().x + halfSize.width, rect.tl().y + halfSize.height);
}

void drawFaceOnFrame(Mat frame, Face face) {
    auto radius = 5;
//    try { circle(frame, centerOfRect(face.nose), radius, WHITE_COLOR, -1); } catch (...){}
//    try { circle(frame, centerOfRect(face.rightEye), radius, CYAN_COLOR, -1); } catch (...){}
//    try { circle(frame, centerOfRect(face.leftEye), radius, YELLOW_COLOR, -1); } catch (...){}
    for (int i = 0; i < face.landmarks.size(); i++){
        try { circle(frame, face.landmarks[i], radius, YELLOW_COLOR, -1); } catch (...){}
        try { putText(frame, to_string(i), face.landmarks[i], FONT_HERSHEY_SIMPLEX, 1, CYAN_COLOR); } catch (...){}
    }
    rectangle(frame, face.face, RED_COLOR);
}



int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker((Features) (Eyes | Nose));
    FeatureAverager featureAverager;
    HeadTracker headTracker;
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    //wm w_manager;
    
    Mat frame;
    frame = ci.getFrame();
    imshow("Demo", frame);
    waitKey(20);
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

