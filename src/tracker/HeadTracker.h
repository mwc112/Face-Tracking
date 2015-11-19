#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <string>
#include <functional>
#include <stdio.h>
#include "FeatureTracker.h"

enum Direction {
    Left,
    Middle,
    Right,
    Unknown
};

class HeadTracker {
public:
    std::function<void(Direction)> directionChanged;
    void inputFace(Face);
    std::string directionString(Direction);
    Direction currentDirection;
};
#endif