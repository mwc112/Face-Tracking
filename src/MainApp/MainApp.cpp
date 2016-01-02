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
    Size halfSize = rect.size()/2;
    return Point(rect.tl().x + halfSize.width, rect.tl().y + halfSize.height);
}opencv

void drawFaceOnFrame(Mat frame, Face face) {
    auto radius = 5;
    try { circle(frame, centerOfRect(face.nose), radius, NOSE_COLOR, -1); } catch (...){}
    try { circle(frame, centerOfRect(face.rightEye), radius, RIGHT_EYE_COLOR, -1); } catch (...){}
    try { circle(frame, centerOfRect(face.leftEye), radius, LEFT_EYE_COLOR, -1); } catch (...){}
    rectangle(frame, face.face, FACE_COLOR);
}

void drawFaceOnFrameRects(Mat frame, Face face) {
    rectangle(frame, face.nose, NOSE_COLOR);
    rectangle(frame, face.rightEye, RIGHT_EYE_COLOR);
    rectangle(frame, face.leftEye, LEFT_EYE_COLOR);
    rectangle(frame, face.face, FACE_COLOR);
}


string faceDescription(Face face) {
    
}

>>>>>>> 93f641425b71d95eba51af07c3a993949810c853
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
            face.drawOnFrame(frame);
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

