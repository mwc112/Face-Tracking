#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include <dlib/dlib/image_processing/frontal_face_detector.h>
#include <dlib/dlib/image_processing.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "Face.h"

class FeatureTracker {
public:
	FeatureTracker();
	Face getFeatures(cv::Mat frame);
private:
	Face findFeaturesInFace(cv::Mat head, dlib::rectangle face);
	cv::Rect prevhead;
	dlib::frontal_face_detector detector;
	dlib::shape_predictor sp;
};
#endif
