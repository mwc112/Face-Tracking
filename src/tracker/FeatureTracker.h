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

enum Features {
    Eyes,
    Nose
};

class FeatureTracker {
public:
    FeatureTracker(Input &input);
    Face getFeatures(Features features);
private:
    Face findFeaturesInFace(cv::Mat head, cv::Rect face);
    cv::CascadeClassifier faceCascade, lefteyeCascade, righteyeCascade, noseCascade, earCascade;
    Input &input;
    cv::Mat head;
    cv::Mat frame;
    
};
#endif
