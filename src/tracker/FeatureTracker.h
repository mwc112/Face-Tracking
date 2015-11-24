#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Input.h"
#include <stdio.h>

struct Face {
    cv::Rect leftEye,
             rightEye,
             nose;
};


class FeatureTracker {
public:
    FeatureTracker(Input &input);
    std::function<void(Face)> faceChanged;
    void start();
private:
    Input &input;
};
#endif