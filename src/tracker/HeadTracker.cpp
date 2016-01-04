#include "HeadTracker.h"

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>
#include <dlib/dlib/geometry/vector.h>
#include <dlib/dlib/geometry/point_transforms.h>

using namespace cv;
using namespace std;
using dlib::point;

point convert(Point p) {
    return dlib::point(p.x, p.y);
}
Point convert(point p) {
    return Point(p.x(), p.y());
}

Direction HeadTracker::getDirection(Face face) {
    Direction newDirection;
    


    point noseBottom = convert(face.landmarks[30]);
    point noseTop = convert(face.landmarks[27]); 
    
    auto rightEye = face.landmarks[39], leftEye = face.landmarks[42];
    auto eyeAngle = atan2(rightEye.x - leftEye.x, rightEye.y - leftEye.y);
    
    //rotate the nose ridge to account for head roll
    //add 90 degrees (M_PI_2) because interocular axis is perpendicular to nose ridge
    noseBottom = rotate_point(noseTop, noseBottom, eyeAngle + M_PI_2);

    auto m = (float)(noseBottom.x() - noseTop.x())/(float)(noseBottom.y() - noseTop.y());
    
    if (m <= 1 && m >= -1) {
        newDirection = Middle;
    } else if (m < -1) {
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
