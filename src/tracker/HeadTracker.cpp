#include "HeadTracker.h"

#include "opencv2/highgui/highgui.hpp"
#include <iostream>


using namespace cv;
using namespace std;


Direction HeadTracker::getDirection(Face face) {
    Direction newDirection;
    if (face.landmarks[30].x > face.landmarks[27].x) {
        newDirection = Left;
    } else {
        newDirection = Right;
    }
    if (newDirection != currentDirection) {
        currentDirection = newDirection;
        return newDirection;
    } else {
        throw "No new direction";
    }
}


