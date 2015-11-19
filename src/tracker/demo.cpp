#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"


using namespace std;
using namespace cv;

void faceChanged(Face face);

int main(int argc, char* argv[])
{
    FeatureTracker featureTracker("face_test2.mov");
    featureTracker.faceChanged = &faceChanged;
    featureTracker.start();
    while(1){};
    return 0;
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

enum Direction {
    Left,
    Middle,
    Right,
    Unknown
};
void directionChanged(Direction dir);
Direction previousDirection = Unknown;
void faceChanged(Face face) {
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
    if (dir != previousDirection) {
        directionChanged(dir);
        previousDirection = dir;
    }
}

void directionChanged(Direction dir) {
    switch (dir) {
        case Left:
            cout << "Left" << endl;
            break;
        case Right:
            cout << "Right" << endl;
            break;
        case Middle:
            cout << "Middle" << endl;
            break;
        case Unknown:
            cout << "Unknown" << endl;
            break;
    }
}