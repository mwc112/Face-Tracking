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

string directionName(Direction dir){
    switch (dir) {
        case Top_Left: return "top left";
        case Top_Right: return "top right";
        case Top_Middle: return "top middle";
        case Bottom_Left: return "bottom left";
        case Bottom_Right: return "bottom right";
        case Bottom_Middle: return "bottom middle";
        case Unknown: return "unknown";
    }
    return "unknown";
}

enum LR{
  Left,
  Middle,
  Right
};
enum TB{
  Top,
  Mid,
  Bottom
};

LR directionFromEyesToEdge(Face face) {
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

LR directionFromNoseRidge(Face face) {
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
}

TB directionFromEyeBrow(Face face){
    //TODO make relative
    auto upperRightEye = convert(face.landmarks[19]); 
    auto rightEyebrow = convert(face.landmarks[37]);
    auto distance = dlib::length(upperRightEye - rightEyebrow);
  
    if (distance > 41) {
        return Top;
        std::cout << "t" << distance << std::endl;
    } else if (distance < 39) {
        return Bottom;
        std::cout << "b" << distance << std::endl;
    }
    return Mid;

}


Direction votesToDirection(std::vector<LR> LRVotes, std::vector<TB> TBVotes, Direction currentDirection){
  bool sameLR = true;
  bool sameTB = true;
  for (int i = 0; i < LRVotes.size(); i++){
      sameLR &= (LRVotes[i] == LRVotes[0]);
  }
  for (int i = 0; i < TBVotes.size(); i++){
      sameTB &= (TBVotes[i] == TBVotes[0]);
  }
  if  (sameLR && sameTB){
    switch(TBVotes[0]){
      case (Top) : {
        switch(LRVotes[0]){
          case (Left) : {
            return Top_Left;        
          }
          case (Middle) : {
            return Top_Middle;        
          }
          case (Right) : {
            return Top_Right;        
          }
        }
      }
      case (Bottom) : {
        switch(LRVotes[0]){
          case (Left) : {
            return Bottom_Left;        
          }
          case (Middle) : {
            return Bottom_Middle;        
          }
          case (Right) : {
            return Bottom_Right;        
          }
        }
      }
    }
  }
  return currentDirection;
}

Direction HeadTracker::getDirection(Face face) {
    std::vector<LR> LRVotes;
    std::vector<TB> TBVotes;    
    Direction newDirection = currentDirection;
    LRVotes.push_back(directionFromEyesToEdge(face));
    LRVotes.push_back(directionFromNoseRidge(face));
    TBVotes.push_back(directionFromEyeBrow(face)); 
   
    newDirection = votesToDirection(LRVotes, TBVotes, currentDirection);

    if (newDirection != currentDirection) {
        currentDirection = newDirection;
        return newDirection;
    } else {
        throw "No new direction";
    }
}


