#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <string>
#include <functional>
#include <stdio.h>
#include "Face.h"

enum Direction {
	Left, Middle, Right, Unknown
};

class HeadTracker {
public:
	Direction getDirection(Face face);
private:
	Direction currentDirection;
};
#endif
