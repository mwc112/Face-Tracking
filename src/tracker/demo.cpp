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

int main(int argc, char* argv[])
{
    
    CameraInput ci;
    FeatureTracker featureTracker(ci);
    HeadTracker headTracker;
    
    headTracker.directionChanged = [&](Direction dir) {
        cout << headTracker.directionString(dir) << endl;
    };
    
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

