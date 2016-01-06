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
#if CV_MAJOR_VERSION == 3
    operator cv::_InputOutputArray () const {
        return mat;
    }
#endif
    operator dlib::cv_image<dlib::bgr_pixel> () const {
        return dlib::cv_image<dlib::bgr_pixel>(mat);
    }
    dlib::cv_image<dlib::bgr_pixel> dlibImage() {
        return dlib::cv_image<dlib::bgr_pixel>(mat);
    } 
    void flip(){
      cv::flip(mat,mat, 1);
    } 
    void equaliseFrame() {
      //this should help in high contrast settings (eg if a window is behind you)
      //equalize the Value channel
      cv::Mat channels[3];
      //convert to HSV from RGB
      cv::cvtColor(mat, mat, CV_RGB2HSV);
      //split into H, S and V channels
      cv::split(mat, channels);
      //equalize only the V channel.
      cv::equalizeHist(channels[2], channels[2]);
      //remerge
      cv::merge(channels, 3, mat);
      //convert back to RGB
      cv::cvtColor(mat, mat, CV_HSV2RGB);
    }
};
#endif
