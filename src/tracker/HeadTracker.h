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
    HeadTracker(FeatureTracker ft);
    Direction getDirection();
private:
    Direction currentDirection;
    FeatureTracker featureTracker;
};
#endif