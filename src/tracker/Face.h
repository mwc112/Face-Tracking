#ifndef FACE_H
#define FACE_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

struct Face {
    cv::Rect face,
        leftEye,
        rightEye,
        nose;
};
#endif