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
    try { circle(frame, centerOfRect(face.nose), radius, WHITE_COLOR, -1); } catch (...){}
    try { circle(frame, centerOfRect(face.rightEye), radius, CYAN_COLOR, -1); } catch (...){}
    try { circle(frame, centerOfRect(face.leftEye), radius, YELLOW_COLOR, -1); } catch (...){}
    rectangle(frame, face.face, RED_COLOR);
}

void drawFaceOnFrameRects(Mat frame, Face face) {
    rectangle(frame, face.nose, WHITE_COLOR);
    rectangle(frame, face.rightEye, CYAN_COLOR);
    rectangle(frame, face.leftEye, YELLOW_COLOR);
    rectangle(frame, face.face, RED_COLOR);
}


string faceDescription(Face face) {
    
}

int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker((Features) (Eyes | Nose));
    FeatureAverager featureAverager;
    HeadTracker headTracker;
    wm *w_manager = new wm();
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    
    Mat frame;
    while (true) {
        try {
            frame = ci.getFrame();
            Face face = featureTracker.getFeatures(frame);
            drawFaceOnFrame(frame, face);
            Direction dir = headTracker.getDirection(face);
            w_manager->set_focus_screen((wm::Direction)dir);
            cout << directionName(dir) << endl;
            imshow("Demo", frame);
            waitKey(20);
        } catch (const char * e) {
            //cout << e << endl;
            imshow("Demo", frame); //show the frame
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

