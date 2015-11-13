#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

enum Direction {
    Left,
    Middle,
    Right,
    Unknown
};
class FeatureTracker {
public:
    FeatureTracker(int inputDevice);
    FeatureTracker(std::string inputFile);
    void (*headDirectionChanged)(Direction headDirection);
    void start();
private:
    cv::VideoCapture cap;
};
#endif