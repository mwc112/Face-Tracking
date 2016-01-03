#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include <dlib/dlib/image_processing/frontal_face_detector.h>
#include <dlib/dlib/image_processing.h>
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
    Face findFeaturesInFace(cv::Mat head, dlib::rectangle face);
    cv::CascadeClassifier faceCascade, lefteyeCascade, righteyeCascade, noseCascade, earCascade;
    cv::Rect prevhead;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor sp;
    Features requiredFeatures;
};
#endif
