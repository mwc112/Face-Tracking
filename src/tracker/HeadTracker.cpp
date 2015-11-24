#include "HeadTracker.h"

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void HeadTracker::inputFace(Face face) {
    //    if (face.nose == Rect()) {
    //        return;
    //    }
    bool hasRightEye = face.rightEye != Rect();
    bool hasLeftEye = face.leftEye != Rect();
    Direction dir;
    if (hasLeftEye && hasRightEye) {
        float leftOverlap = (face.rightEye & face.nose).width;
        float rightOverlap = (face.nose & face.leftEye).width;
        
        if (leftOverlap > rightOverlap) {
            dir = Right;
        } else {
            dir = Left;
        }
    } else if (hasLeftEye && !hasRightEye) {
        dir = Right;
    } else if (!hasLeftEye && hasRightEye) {
        dir = Left;
    } else {
        return;
    }
    if (dir != currentDirection) {
        directionChanged(dir);
        currentDirection = dir;
    }
}

std::string HeadTracker::directionString(Direction dir) {
    switch (dir) {
        case Left:
            return "Left";
        case Right:
            return "Right";
        case Middle:
            return "Middle";
        case Unknown:
            return "Unknown";
    }
}
