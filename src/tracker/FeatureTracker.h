#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include <dlib/dlib/image_processing/frontal_face_detector.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include "Face.h"


enum Features {
    Eyes,
    Nose
};

class FeatureTracker {
public:
    FeatureTracker(Features features);
    Face getFeatures(cv::Mat frame);
private:
    Face findFeaturesInFace(cv::Mat head, cv::Rect face);
    cv::CascadeClassifier faceCascade, lefteyeCascade, righteyeCascade, noseCascade, earCascade;
    dlib::frontal_face_detector detector;
    Features requiredFeatures;
    cv::Rect prevhead;
};
#endif
