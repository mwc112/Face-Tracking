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

Direction directionFromEyesToEdge(Face face) {
    auto outerRightEye = convert(face.landmarks[36]), outerLeftEye = convert(face.landmarks[45]);
    auto rightFaceSide = convert(face.landmarks[0]), leftFaceSide = convert(face.landmarks[16]);
    auto rightDistance = dlib::length(outerRightEye - rightFaceSide);
    auto leftDistance = dlib::length(outerLeftEye - leftFaceSide);
    if (leftDistance > rightDistance * 2) {
        return Left;
    } else if (rightDistance > leftDistance * 2) {
        return Right;
    }
    return Middle;
}

Direction directionFromNoseRidge(Face face) {
    point noseBottom = convert(face.landmarks[30]);
    point noseTop = convert(face.landmarks[27]);
    
    auto rightEye = face.landmarks[39], leftEye = face.landmarks[42];
    auto eyeAngle = atan2(rightEye.x - leftEye.x, rightEye.y - leftEye.y);
    
    //rotate the nose ridge to account for head roll
    //add 90 degrees (M_PI_2) because interocular axis is perpendicular to nose ridge
    noseBottom = rotate_point(noseTop, noseBottom, eyeAngle + M_PI_2);
    
    auto m = (float)(noseBottom.x() - noseTop.x())/(float)(noseBottom.y() - noseTop.y());
    
    auto threshold = 0.2;
    if (m <= threshold && m >= -threshold) {
        return Middle;
    } else if (m < -threshold) {
        return Left;
    } else if (m > threshold){
        return Right;
    }
    return Unknown;
}
string directionName(Direction dir);

Direction HeadTracker::getDirection(Face face) {
    Direction newDirection = currentDirection;
    Direction eyesDir = directionFromEyesToEdge(face);
    Direction noseDir = directionFromNoseRidge(face);
    
    if (noseDir == eyesDir) {
        newDirection = noseDir;
    }

    if (newDirection != currentDirection) {
        currentDirection = newDirection;
        return newDirection;
    } else {
        throw "No new direction";
    }
}
