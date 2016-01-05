#ifndef FRAME_H
#define FRAME_H
#include "opencv2/imgproc/imgproc.hpp"

#include<dlib/dlib/opencv.h>

struct Frame {
    cv::Mat mat;
    Frame() {}
    Frame(cv::Mat mat) : mat(mat) {}
    Frame& operator =(const Frame& a) {
        mat = a.mat;
        return *this;
    }
    operator cv::Mat () const {
        return mat;
    }
    operator cv::Mat& () {
        return mat;
    }
    operator cv::_InputOutputArray () const {
        return mat;
    }
    operator dlib::cv_image<dlib::bgr_pixel> () const {
        return dlib::cv_image<dlib::bgr_pixel>(mat);
    }
    dlib::cv_image<dlib::bgr_pixel> dlibImage() {
        return dlib::cv_image<dlib::bgr_pixel>(mat);
    }
};
#endif
