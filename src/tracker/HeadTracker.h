#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <string>
#include <functional>
#include <stdio.h>
#include "Face.h"
#include <string.h>

enum Direction {
    Top_Left,
    Top_Middle,
    Top_Right,
    Bottom_Left,
    Bottom_Middle,
    Bottom_Right,
    Unknown
};

class HeadTracker {
public:
    Direction getDirection(Face face);
    std::string directionName(Direction dir);
private:
    Direction currentDirection;
};
#endif
