#ifndef FACE_H
#define FACE_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

const cv::Scalar WHITE_COLOR(255, 225, 255);
const cv::Scalar CYAN_COLOR(255, 225, 0);
const cv::Scalar YELLOW_COLOR(0, 225, 255);
const cv::Scalar RED_COLOR(0,0,255);

struct Face {
    cv::Rect face,
        leftEye,
        rightEye,
        nose;
    void drawOnFrame(cv::Mat frame) {
        rectangle(frame, this->nose, WHITE_COLOR);
        rectangle(frame, this->rightEye, CYAN_COLOR);
        rectangle(frame, this->leftEye, YELLOW_COLOR);
        rectangle(frame, this->face, RED_COLOR);
    };
};
#endif
