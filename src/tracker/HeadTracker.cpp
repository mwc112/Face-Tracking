#include "HeadTracker.h"

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Direction HeadTracker::getDirection(Face face) {
    //    if (face.nose == Rect()) {
    //        return;
    //    }
    bool hasRightEye = face.rightEye.area() != 0;
    bool hasLeftEye = face.leftEye.area() != 0;
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
        //TODO throw something better
        throw "head";
    }
    if (dir != currentDirection) {
        currentDirection = dir;
        return dir;
    } else {
        //TODO throw something better
        throw "head";
    }
}

