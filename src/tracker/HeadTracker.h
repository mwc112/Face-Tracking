#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <string>
#include <functional>
#include <stdio.h>
#include "Face.h"
#include <dlib/svm.h>

enum Direction {
    Left,
    Middle,
    Right,
    Unknown
};
typedef dlib::matrix<double,6,1> sample_type;
typedef dlib::radial_basis_kernel<sample_type> kernel_type;

class HeadTracker {
public:
    HeadTracker();
    Direction getDirection(Face face);
private:
    Direction currentDirection;
    dlib::krls<kernel_type> test;
    int trains = 0;
};
#endif