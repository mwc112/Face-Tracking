#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"
#include "HeadTracker.h"
#include "CameraInput.h"


using namespace std;
using namespace cv;
using namespace std::placeholders;

void faceChanged(Face face);
string directionName(Direction dir);

int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker(ci);
    HeadTracker headTracker(featureTracker);

    while(1){
        try {
            cout << directionName(headTracker.getDirection()) << endl;
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

